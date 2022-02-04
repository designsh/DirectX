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
	// ����Ʈ�� ġ���� ���� �Ѵ�.
	ViewPort.Height = _Height;					// ���α���
	ViewPort.Width = _Width;						// ���α���
	ViewPort.TopLeftX = _TopLeftX;			// LeftTop X��(���ν�����ġ)
	ViewPort.TopLeftY = _TopLeftY;			// LeftTop Y��(���ν�����ġ)
	ViewPort.MinDepth = _MinDepth;		// Min Z(�ּұ���)
	ViewPort.MaxDepth = _MaxDepth;		// Max Z(�ִ����)
}

void GameEngineRasterizer::Create(const D3D11_RASTERIZER_DESC& _Value)
{
	// D3D11_RASTERIZER_DESC : Rasterizer�� ���¸� �����ϴ� ����ü
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&_Value, &State))
	{
		GameEngineDebug::MsgBoxError("Create Rasterizer Error.");
		return;
	}
}

void GameEngineRasterizer::SettingViewPort()
{
	// ���������������ο� ����Ʈ�� ����ִ´�.
	GameEngineDevice::GetContext()->RSSetViewports(0, &ViewPort);
}

void GameEngineRasterizer::Setting()
{




}
