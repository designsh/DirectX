#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() :
	State_(nullptr),
	ViewPort_{},
	Scissor_{},
	SicssorFlag_(false)
{
}

GameEngineRasterizer::~GameEngineRasterizer()
{
	// ViewPort State Release
	if (nullptr != State_)
	{
		State_->Release();
		State_ = nullptr;
	}
}

GameEngineRasterizer::GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept :
	State_(_other.State_),
	ViewPort_(_other.ViewPort_),
	Scissor_(_other.Scissor_),
	SicssorFlag_(_other.SicssorFlag_)
{
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

void GameEngineRasterizer::SetScissor(LONG _Left, LONG _Top, LONG _Right, LONG _Bottom)
{
	// ����-�簢�� ġ���� �����Ѵ�.
	Scissor_.left = _Left;
	Scissor_.top = _Top;
	Scissor_.right = _Right;
	Scissor_.bottom = _Bottom;

	// ����-�簢�� ������ ���� Flag On
	SicssorFlag_ = true;
}

void GameEngineRasterizer::Create(const D3D11_RASTERIZER_DESC& _Value)
{
	// D3D11_RASTERIZER_DESC : Rasterizer�� ���¸� �����ϴ� ����ü
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&_Value, &State_))
	{
		GameEngineDebug::MsgBoxError("Create Rasterizer Error.");
		return;
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
	if (true == SicssorFlag_)
	{
		GameEngineDevice::GetContext()->RSSetScissorRects(1, &Scissor_);
	}
}

void GameEngineRasterizer::Setting()
{
	GameEngineDevice::GetContext()->RSSetState(State_);
}
