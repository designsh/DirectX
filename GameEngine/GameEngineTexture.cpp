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
	for (int y = 0; y < _y; y++)
	{
		float4 CurStart;

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

