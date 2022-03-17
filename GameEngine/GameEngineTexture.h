#pragma once
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTexture : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11Texture2D* Texture2D_;
	ID3D11RenderTargetView* RenderTargetView_;
	ID3D11ShaderResourceView* ShaderResourceView_;
	ID3D11DepthStencilView* DepthStencilView_;

private:
	D3D11_TEXTURE2D_DESC TextureDesc_;
	DirectX::ScratchImage Image_;

	// ============================= Image Cutting ============================= //
private:
	std::vector<float4> CutList_;   // �̹��� UV���������� �߶󳻾� �����ϴ� ���(�ִϸ��̼ǿ�)

public:
	GameEngineTexture(); // default constructer ����Ʈ ������
	~GameEngineTexture(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineTexture(const GameEngineTexture& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineTexture(GameEngineTexture&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineTexture& operator=(const GameEngineTexture& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineTexture& operator=(const GameEngineTexture&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	float4 GetTextureSize() const;
	int GetCutCount() const;

public:
	inline ID3D11RenderTargetView* GetRenderTargetView()
	{
		return RenderTargetView_;
	}

	inline ID3D11ShaderResourceView** GetShaderResourcesView()
	{
		return &ShaderResourceView_;
	}

	inline ID3D11DepthStencilView* GetDepthStencilView()
	{
		return DepthStencilView_;
	}

public:
	void Create(ID3D11Texture2D* _Texture2D);
	void Create(float4 _TextureSize, DXGI_FORMAT _Format, D3D11_USAGE _Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT, unsigned int _BindFlag = D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE);
	void Create(D3D11_TEXTURE2D_DESC _Desc);

public:
	ID3D11RenderTargetView* CreateRenderTargetView();
	ID3D11ShaderResourceView* CreateShaderResourceView();
	ID3D11DepthStencilView* CreateDepthStencilView();

public:
	void Load(const std::string& _Path);

	// ============================= Image Cutting ============================= //
public:
	bool IsCut();
	void Cut(int _x, int _y);
	void PushCutIndex(const float4& _Size, const float4& _Pos);
	float4 GetCutData(int _Index);
	float4 GetPixel(int _x, int _y);
};

