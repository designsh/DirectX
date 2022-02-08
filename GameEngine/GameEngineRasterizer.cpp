#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() :
	State_(nullptr),
	OldState_(nullptr),
	Desc_{},
	WireDesc_{},
	ViewPort_{},
	ChangeScissorIndex_(0)
{
}

GameEngineRasterizer::~GameEngineRasterizer()
{
	Clear();
}

void GameEngineRasterizer::SwitchState()
{
	// SOLID <-> WIREFRAME ��ü ���
	ID3D11RasterizerState* State = State_;
	State_ = OldState_;
	OldState_ = State;
}

void GameEngineRasterizer::SetViewPort(float _Width, float _Height, float _TopLeftX, float _TopLeftY, float _MinDepth, float _MaxDepth)
{
	// ����Ʈ�� ġ���� ���� �Ѵ�.
	ViewPort_.Height = _Height;					// ���α���
	ViewPort_.Width = _Width;						// ���α���
	ViewPort_.TopLeftX = _TopLeftX;			// LeftTop X��(���ν�����ġ)
	ViewPort_.TopLeftY = _TopLeftY;			// LeftTop Y��(���ν�����ġ)
	ViewPort_.MinDepth = _MinDepth;		// Min Z(�ּұ���)
	ViewPort_.MaxDepth = _MaxDepth;		// Max Z(�ִ����)
}

void GameEngineRasterizer::PushScissorRect(D3D11_RECT _Rect)
{
	// ����-�簢�� ġ�����Ǹ�Ͽ� �߰�
	ScissorRects_.push_back(_Rect);

	// ����-�簢�� ��� Flag ����
	Desc_.ScissorEnable = true;

	// ������ ���ŵǾ����Ƿ� Rasterizer State�� �����
	Clear();
	Create(Desc_);
}

void GameEngineRasterizer::ChangeScissorRect(int _Index)
{
	ChangeScissorIndex_ = _Index;
}

void GameEngineRasterizer::Create(const D3D11_RASTERIZER_DESC& _Value)
{
	// Rasterizer State ����
	Desc_ = _Value;

	// ����-�簢���� ����� ġ�����Ǹ���� ���������ʴٸ�
	// ����-�簢�� ��뿩�� Flag ����
	if (0 == ScissorRects_.size())
	{
		Desc_.ScissorEnable = false;
	}

	// WireFrame Raterizer State ���������� Description ����
	WireDesc_ = Desc_;
	WireDesc_.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;

	// D3D11_RASTERIZER_DESC : Rasterizer�� ���¸� �����ϴ� ����ü
	// D3D11_FILL_SOLID �� Rasterizer State
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&Desc_, &State_))
	{
		GameEngineDebug::MsgBoxError("Create Solid Rasterizer Error.");
		return;
	}

	// D3D11_FILL_WIREFRAME �� Rasterizer State
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&WireDesc_, &OldState_))
	{
		GameEngineDebug::MsgBoxError("Create WireFrame Rasterizer Error.");
		return;
	}

}

void GameEngineRasterizer::Clear()
{
	// Rasterizer Old State Release
	if (nullptr != OldState_)
	{
		OldState_->Release();
		OldState_ = nullptr;
	}

	// Rasterizer Current State Release
	if (nullptr != State_)
	{
		State_->Release();
		State_ = nullptr;
	}
}

void GameEngineRasterizer::SettingViewPort()
{
	// ���������������ο� ����Ʈ�� ����ִ´�.
	// ù��° ���� : ���ε��� ����Ʈ�� ��
	// �ι�° ���� : ��ġ�� ���ε��� D3D11_VIEWPORT ������ �迭
	GameEngineDevice::GetContext()->RSSetViewports(1, &ViewPort_);
}

void GameEngineRasterizer::SettingScissor()
{	
	// ����-�簢�� ����(D3D11_RASTERIZER_DESC�� ScissorEnable = TRUE�� �ش� ���� �ʿ�
	if (true == static_cast<bool>(Desc_.ScissorEnable))
	{
		// ù��° ���� : ����-�簢������ ����
		// �ι�° ���� : �簢���� ����ü ���� ����� ������
		// ��, Scissor Rectangle�� �ϳ��� Render Target�� �������� ����-�簢���� �����Ҽ� ����.
		// ���� ����-�簢���� ����� ���ÿ� �������� Render Target�� �������ϴ� ��� ����� ����Ѵ�.
		// Ex) UI�� ���ؼ� ������ �ִ� ȭ�� Ư���κ��� �����Ҷ� �ش� �κ��� �ȼ�ó���� �� �ʿ�����Ƿ� 
		//        Scissor-Rectangle �� ����Ѵ�.
		GameEngineDevice::GetContext()->RSSetScissorRects(1, &ScissorRects_[ChangeScissorIndex_]);
	}
}

void GameEngineRasterizer::Setting()
{
	GameEngineDevice::GetContext()->RSSetState(State_);
}
