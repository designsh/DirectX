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
	// 뷰포트의 치수를 정의 한다.
	ViewPort_.Height = _Height;					// 세로길이
	ViewPort_.Width = _Width;						// 가로길이
	ViewPort_.TopLeftX = _TopLeftX;			// LeftTop X값(가로시작위치)
	ViewPort_.TopLeftY = _TopLeftY;			// LeftTop Y값(세로시작위치)
	ViewPort_.MinDepth = _MinDepth;		// Min Z(최소깊이)
	ViewPort_.MaxDepth = _MaxDepth;		// Max Z(최대깊이)
}

void GameEngineRasterizer::SetScissor(LONG _Left, LONG _Top, LONG _Right, LONG _Bottom)
{
	// 가위-사각형 치수를 정의한다.
	Scissor_.left = _Left;
	Scissor_.top = _Top;
	Scissor_.right = _Right;
	Scissor_.bottom = _Bottom;

	// 가위-사각형 셋팅을 위해 Flag On
	SicssorFlag_ = true;
}

void GameEngineRasterizer::Create(const D3D11_RASTERIZER_DESC& _Value)
{
	// D3D11_RASTERIZER_DESC : Rasterizer의 상태를 정의하는 구조체
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&_Value, &State_))
	{
		GameEngineDebug::MsgBoxError("Create Rasterizer Error.");
		return;
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
	if (true == SicssorFlag_)
	{
		GameEngineDevice::GetContext()->RSSetScissorRects(1, &Scissor_);
	}
}

void GameEngineRasterizer::Setting()
{
	GameEngineDevice::GetContext()->RSSetState(State_);
}
