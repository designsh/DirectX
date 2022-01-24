#include "PreCompile.h"
#include "GameEngineDirectXDevice.h"
#include "GameEngineWindow.h"

// 포인터형 싱글톤
GameEngineDirectXDevice* GameEngineDirectXDevice::Inst = new GameEngineDirectXDevice();

GameEngineDirectXDevice::GameEngineDirectXDevice() :
	Device_(nullptr),
	Context_(nullptr),
	SwapChain_(nullptr)
{
}

GameEngineDirectXDevice::~GameEngineDirectXDevice()
{
	if (nullptr != Device_)
	{
		Device_->Release();
		Device_ = nullptr;
	}

	if (nullptr != Context_)
	{
		Context_->Release();
		Context_ = nullptr;
	}
}

void GameEngineDirectXDevice::Initialize()
{
	if (nullptr == GameEngineWindow::GetInst().GetWindowHWND())
	{
		GameEngineDebug::MsgBoxError("Window Hwnd ERROR");
		return;
	}

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Direct 11 Version 사용
	D3D_FEATURE_LEVEL eLV = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	// Device 생성
	if (S_OK != D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, iFlag, nullptr, 0, D3D11_SDK_VERSION, &Device_, &eLV, &Context_))
	{
		GameEngineDebug::MsgBoxError("D3D11 Create Device ERROR");
	}

	// DirectX 11Version 사용이 불가능하다면 에러
	if (eLV != D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0)
	{
		GameEngineDebug::MsgBoxError("D3D11 Not FEATURE LEVEL 11 ERROR");
	}

	// 스왑체인 생성
	CreateSwapChain();
}

void GameEngineDirectXDevice::CreateSwapChain()
{
	if (0 >= GameEngineWindow::GetInst().GetSize().x && 0 >= GameEngineWindow::GetInst().GetSize().y)
	{
		GameEngineDebug::MsgBoxError("Screen Size Zero");
	}

	float4 ScreenSize = GameEngineWindow::GetInst().GetSize();

	DXGI_SWAP_CHAIN_DESC ScInfo = { 0, };

	ScInfo.BufferDesc.Width = ScreenSize.uix();
	ScInfo.BufferDesc.Height = ScreenSize.uiy();

	// 모니터에 간섭해서 1초에 60프레임 백버퍼를 스왑해라.
	ScInfo.BufferDesc.RefreshRate.Numerator = 60.0f;

	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;


}
