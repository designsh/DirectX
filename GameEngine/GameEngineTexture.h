#pragma once
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTexture : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11Texture2D* Texture2D_;
	ID3D11RenderTargetView* RenderTargetView_;

private:
	D3D11_TEXTURE2D_DESC TextureDesc_;
	ID3D11ShaderResourceView* ShaderResourceViewPtr_;
	DirectX::ScratchImage Image_;

public:
	GameEngineTexture(); // default constructer 디폴트 생성자
	~GameEngineTexture(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineTexture(const GameEngineTexture& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineTexture(GameEngineTexture&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineTexture& operator=(const GameEngineTexture& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineTexture& operator=(const GameEngineTexture&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	float4 GetImageSize() const;

public:
	ID3D11RenderTargetView* GetRenderTargetView();
	ID3D11ShaderResourceView** GetShaderResourcesView();

public:
	void Create(ID3D11Texture2D* _Texture2D);
	ID3D11RenderTargetView* CreateRenderTargetView();

public:
	void Load(const std::string& _Path);
};

