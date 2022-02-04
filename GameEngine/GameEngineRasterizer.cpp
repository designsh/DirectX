#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer() :
	State(nullptr),
	ViewPort{}
{
}

GameEngineRasterizer::~GameEngineRasterizer()
{
	// ViewPort State Release
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}
}

GameEngineRasterizer::GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept :
	State(_other.State),
	ViewPort(_other.ViewPort)
{
}

void GameEngineRasterizer::SetViewPort(float _Width, float _Height, float _TopLeftX, float _TopLeftY, float _MinDepth, float _MaxDepth)
{
	// 뷰포트의 치수를 정의 한다.
	ViewPort.Height = _Height;					// 세로길이
	ViewPort.Width = _Width;						// 가로길이
	ViewPort.TopLeftX = _TopLeftX;			// LeftTop X값(가로시작위치)
	ViewPort.TopLeftY = _TopLeftY;			// LeftTop Y값(세로시작위치)
	ViewPort.MinDepth = _MinDepth;		// Min Z(최소깊이)
	ViewPort.MaxDepth = _MaxDepth;		// Max Z(최대깊이)
}

void GameEngineRasterizer::Create(const D3D11_RASTERIZER_DESC& _Value)
{
	// D3D11_RASTERIZER_DESC : Rasterizer의 상태를 정의하는 구조체
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&_Value, &State))
	{
		GameEngineDebug::MsgBoxError("Create Rasterizer Error.");
		return;
	}
}

void GameEngineRasterizer::SettingViewPort()
{
	// 랜더링파이프라인에 뷰포트를 집어넣는다.
	GameEngineDevice::GetContext()->RSSetViewports(0, &ViewPort);
}

void GameEngineRasterizer::Setting()
{




}
