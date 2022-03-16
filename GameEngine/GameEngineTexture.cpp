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

GameEngineTexture::~GameEngineTexture() // default destructer ����Ʈ �Ҹ���
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

float4 GameEngineTexture::GetTextureSize() const
{
	unsigned int ImageWidth = TextureDesc_.Width;
	unsigned int ImageHeight = TextureDesc_.Height;

	float4 ReturnValue = float4::ZERO;
	ReturnValue.x = static_cast<float>(ImageWidth);
	ReturnValue.y = static_cast<float>(ImageHeight);

	return ReturnValue;
}

int GameEngineTexture::GetCutCount() const
{
	return static_cast<int>(CutList_.size());
}

void GameEngineTexture::Create(ID3D11Texture2D* _Texture2D)
{
	if (nullptr == _Texture2D)
	{
		GameEngineDebug::MsgBoxError("Texture Is null GameEngine Texture Create Error");
	}

	Texture2D_ = _Texture2D;
}

void GameEngineTexture::Create(float4 _TextureSize, DXGI_FORMAT _Format, D3D11_USAGE _Usage, unsigned int _BindFlag)
{
	D3D11_TEXTURE2D_DESC TextureInfo = { 0, };
	TextureInfo.ArraySize = 1;
	TextureInfo.Width = _TextureSize.uix();
	TextureInfo.Height = _TextureSize.uiy();
	TextureInfo.Format = _Format;
	TextureInfo.SampleDesc.Count = 1;
	TextureInfo.SampleDesc.Quality = 0;
	TextureInfo.MipLevels = 1;
	TextureInfo.Usage = _Usage;

	if (_Usage == D3D11_USAGE::D3D11_USAGE_DYNAMIC)
	{
		TextureInfo.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		TextureInfo.CPUAccessFlags = 0;
	}

	TextureInfo.BindFlags = _BindFlag;

	Create(TextureInfo);
}

void GameEngineTexture::Create(D3D11_TEXTURE2D_DESC _Desc)
{
	TextureDesc_ = _Desc;

	GameEngineDevice::GetDevice()->CreateTexture2D(&TextureDesc_, nullptr, &Texture2D_);
	if (nullptr == Texture2D_)
	{
		GameEngineDebug::MsgBoxError("Texture Create Error");
		return;
	}

	if (_Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
	{
		CreateRenderTargetView();
	}
	if (_Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
	{
		CreateShaderResourceView();
	}
}

ID3D11RenderTargetView* GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RenderTargetView_)
	{
		return RenderTargetView_;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D_, nullptr, &RenderTargetView_))
	{
		GameEngineDebug::MsgBoxError("RenderTargetView Create Error");
	}

	return RenderTargetView_;
}

ID3D11ShaderResourceView* GameEngineTexture::CreateShaderResourceView()
{
	if (nullptr != ShaderResourceViewPtr_)
	{
		return ShaderResourceViewPtr_;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateShaderResourceView(Texture2D_, nullptr, &ShaderResourceViewPtr_))
	{
		GameEngineDebug::MsgBoxError("RenderTargetView Create Error");
	}

	return ShaderResourceViewPtr_;
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
		GameEngineDebug::MsgBoxError("�ε��Ҽ� ���� �̹��� �����Դϴ�" + Extension);
	}
	else if (Extension == "DDS")
	{
		GameEngineDebug::MsgBoxError("�ε��Ҽ� ���� �̹��� �����Դϴ�" + Extension);
	}
	else
	{
		// DirectX::WIC_FLAGS_NONE ���� Flag�� �����ϸ� DirectX�� ��ü������ �̹����� �´� �ɼǼ����� �Ѵ�.
		if (S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, Image_))
		{
			GameEngineDebug::MsgBoxError("�ε��Ҽ� ���� �̹��� �����Դϴ�" + _Path);
		}
	}

	if (S_OK != DirectX::CreateShaderResourceView(GameEngineDevice::GetDevice(), Image_.GetImages(), Image_.GetImageCount(), Image_.GetMetadata(), &ShaderResourceViewPtr_))
	{
		GameEngineDebug::MsgBoxError("���̴� ���ҽ� �並 �����ϴµ� �����߽��ϴ�." + _Path);
	}

	TextureDesc_.Width = static_cast<unsigned int>(Image_.GetMetadata().width);
	TextureDesc_.Height = static_cast<unsigned int>(Image_.GetMetadata().height);
}

bool GameEngineTexture::IsCut()
{
	return CutList_.size() != 0;
}

void GameEngineTexture::Cut(int _x, int _y)
{
	// Sprites Image Cutting

	// ������ ���� : ������ ���� x, y
	// UV�� �������� �̹����� ����
	// x,y = ��ġ, z,w = ũ��
	float4 CurStart = float4::ZERO;

	for (int y = 0; y < _y; y++)
	{
		CurStart.z = 1.0f / _x;
		CurStart.w = 1.0f / _y;

		CurStart.y = CurStart.w * y;

		for (int x = 0; x < _x; x++)
		{
			CurStart.x = CurStart.z * x;
			CutList_.push_back(CurStart);
		}
	}
}

void GameEngineTexture::PushCutIndex(const float4& _Size, const float4& _Pos)
{
	// Atlases Image Cutting

	float4 CutUv = float4::ZERO;

	// ��ġ
	CutUv.x = _Pos.x;
	CutUv.y = _Pos.y;

	// ũ��
	CutUv.z = _Size.x;
	CutUv.w = _Size.y;

	CutList_.push_back(CutUv);
}

float4 GameEngineTexture::GetCutData(int _Index)
{
	if (0 == CutList_.size())
	{
		GameEngineDebug::MsgBoxError("�ڸ��� ���� �ؽ�ó���� �ε����� �������� �߽��ϴ�.");
	}

	if (_Index > CutList_.size())
	{
		GameEngineDebug::MsgBoxError("�ڸ� ������ ���ؼ� �ε����� �ʹ� Ů�ϴ�.");
	}

	return CutList_[_Index];
}

