#include "PreCompile.h"
#include "GameEngineTexture.h"

GameEngineTexture::GameEngineTexture() : 
	Texture2D_(nullptr),
	RenderTargetView_(nullptr),
	TextureDesc_{},
	ShaderResourceViewPtr_(nullptr),
	Image_{}
{
}

GameEngineTexture::~GameEngineTexture() // default destructer 디폴트 소멸자
{
	if (nullptr != ShaderResourceViewPtr_)
	{
		ShaderResourceViewPtr_->Release();
		ShaderResourceViewPtr_ = nullptr;
	}

	if (nullptr != RenderTargetView_)
	{
		RenderTargetView_->Release();
		RenderTargetView_ = nullptr;
	}

	if (nullptr != Texture2D_)
	{
		Texture2D_->Release();
		Texture2D_ = nullptr;
	}
}

float4 GameEngineTexture::GetImageSize() const
{
	unsigned int ImageWidth = TextureDesc_.Width;
	unsigned int ImageHeight = TextureDesc_.Height;

	float4 ReturnValue = float4::ZERO;
	ReturnValue.x = static_cast<float>(ImageWidth);
	ReturnValue.y = static_cast<float>(ImageHeight);

	return ReturnValue;
}

ID3D11RenderTargetView* GameEngineTexture::GetRenderTargetView()
{
	return RenderTargetView_;
}

ID3D11ShaderResourceView** GameEngineTexture::GetShaderResourcesView()
{
	return &ShaderResourceViewPtr_;
}

void GameEngineTexture::Create(ID3D11Texture2D* _Texture2D)
{
	if (nullptr == _Texture2D)
	{
		GameEngineDebug::MsgBoxError("Texture Is null GameEngine Texture Create Error");
	}

	Texture2D_ = _Texture2D;
}

ID3D11RenderTargetView* GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RenderTargetView_)
	{
		GameEngineDebug::MsgBoxError("RenderTargetView OverLap Create Error");
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D_, nullptr, &RenderTargetView_))
	{
		GameEngineDebug::MsgBoxError("RenderTargetView Create Error");
	}

	return RenderTargetView_;
}

void GameEngineTexture::Load(const std::string& _Path)
{
	std::wstring wPath = L"";
	GameEngineString::StringToWString(_Path, wPath);

	GameEngineFile NewFile = GameEngineFile(_Path);

	std::string Extension = NewFile.GetExtension();
	GameEngineString::toupper(Extension);

	if (Extension == "TGA")
	{
		GameEngineDebug::MsgBoxError("로드할수 없는 이미지 포맷입니다" + Extension);
	}
	else if (Extension == "DDS")
	{
		GameEngineDebug::MsgBoxError("로드할수 없는 이미지 포맷입니다" + Extension);
	}
	else
	{
		// DirectX::WIC_FLAGS_NONE 으로 Flag를 설정하면 DirectX가 자체적으로 이미지에 맞는 옵션설정을 한다.
		if (S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, Image_))
		{
			GameEngineDebug::MsgBoxError("로드할수 없는 이미지 포맷입니다" + _Path);
		}
	}

	if (S_OK != DirectX::CreateShaderResourceView(GameEngineDevice::GetDevice(), Image_.GetImages(), Image_.GetImageCount(), Image_.GetMetadata(), &ShaderResourceViewPtr_))
	{
		GameEngineDebug::MsgBoxError("쉐이더 리소스 뷰를 생성하는데 실패했습니다." + _Path);
	}

	TextureDesc_.Width = static_cast<unsigned int>(Image_.GetMetadata().width);
	TextureDesc_.Height = static_cast<unsigned int>(Image_.GetMetadata().height);
}

