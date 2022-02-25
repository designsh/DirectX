#pragma once
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineBlend : public GameEngineObjectNameBase
{
	friend class GameEngineBlendManager;

private:	// member Var
	ID3D11BlendState* State_;
	D3D11_BLEND_DESC Info_;
	float4 Factor_;
	unsigned int Mask_;

public:
	GameEngineBlend(); // default constructer 디폴트 생성자
	~GameEngineBlend(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineBlend(const GameEngineBlend& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineBlend(GameEngineBlend&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineBlend& operator=(const GameEngineBlend& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineBlend& operator=(const GameEngineBlend&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Create(const D3D11_BLEND_DESC& _Info, float4 _Factor, unsigned int _Mask);

public:
	inline ID3D11BlendState** GetSamplerState()
	{
		return &State_;
	}

public:
	void ReCreate(const D3D11_BLEND_DESC& _Info, float4 _Factor, unsigned int _Mask);

public:
	void Setting();
};

