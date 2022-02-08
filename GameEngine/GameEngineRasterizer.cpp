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
	// SOLID <-> WIREFRAME 교체 기능
	ID3D11RasterizerState* State = State_;
	State_ = OldState_;
	OldState_ = State;
}

void GameEngineRasterizer::SetViewPort(float _Width, float _Height, float _TopLeftX, float _TopLeftY, float _MinDepth, float _MaxDepth)
{
	// 뷰포트의 치수를 정의 한다.
	ViewPort_.Height = _Height;					// 세로길이
	ViewPort_.Width = _Width;						// 가로길이
	ViewPort_.TopLeftX = _TopLeftX;			// LeftTop X값(가로시작위치)
	ViewPort_.TopLeftY = _TopLeftY;			// LeftTop Y값(세로시작위치)
	ViewPort_.MinDepth = _MinDepth;		// Min Z(최소깊이)
	ViewPort_.MaxDepth = _MaxDepth;		// Max Z(최대깊이)
}

void GameEngineRasterizer::PushScissorRect(D3D11_RECT _Rect)
{
	// 가위-사각형 치수정의목록에 추가
	ScissorRects_.push_back(_Rect);

	// 가위-사각형 사용 Flag 셋팅
	Desc_.ScissorEnable = true;

	// 정보가 갱신되었으므로 Rasterizer State를 재생성
	Clear();
	Create(Desc_);
}

void GameEngineRasterizer::ChangeScissorRect(int _Index)
{
	ChangeScissorIndex_ = _Index;
}

void GameEngineRasterizer::Create(const D3D11_RASTERIZER_DESC& _Value)
{
	// Rasterizer State 편집
	Desc_ = _Value;

	// 가위-사각형을 사용할 치수정의목록이 존재하지않다면
	// 가위-사각형 사용여부 Flag 해제
	if (0 == ScissorRects_.size())
	{
		Desc_.ScissorEnable = false;
	}

	// WireFrame Raterizer State 생성을위한 Description 정의
	WireDesc_ = Desc_;
	WireDesc_.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;

	// D3D11_RASTERIZER_DESC : Rasterizer의 상태를 정의하는 구조체
	// D3D11_FILL_SOLID 용 Rasterizer State
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&Desc_, &State_))
	{
		GameEngineDebug::MsgBoxError("Create Solid Rasterizer Error.");
		return;
	}

	// D3D11_FILL_WIREFRAME 용 Rasterizer State
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
	// 랜더링파이프라인에 뷰포트를 집어넣는다.
	// 첫번째 인자 : 바인딩할 뷰포트의 수
	// 두번째 인자 : 장치에 바인딩할 D3D11_VIEWPORT 구조의 배열
	GameEngineDevice::GetContext()->RSSetViewports(1, &ViewPort_);
}

void GameEngineRasterizer::SettingScissor()
{	
	// 가위-사각형 셋팅(D3D11_RASTERIZER_DESC의 ScissorEnable = TRUE시 해당 셋팅 필요
	if (true == static_cast<bool>(Desc_.ScissorEnable))
	{
		// 첫번째 인자 : 가위-사각형들의 개수
		// 두번째 인자 : 사각형의 구조체 정의 목록의 포인터
		// 단, Scissor Rectangle은 하나의 Render Target에 여러개의 가위-사각형을 지정할수 없다.
		// 다중 가위-사각형은 장면을 동시에 여러개의 Render Target에 렌더링하는 고급 기법에 사용한다.
		// Ex) UI에 의해서 가려져 있는 화면 특정부분이 존재할때 해당 부분을 픽셀처리를 할 필요없으므로 
		//        Scissor-Rectangle 을 사용한다.
		GameEngineDevice::GetContext()->RSSetScissorRects(1, &ScissorRects_[ChangeScissorIndex_]);
	}
}

void GameEngineRasterizer::Setting()
{
	GameEngineDevice::GetContext()->RSSetState(State_);
}
