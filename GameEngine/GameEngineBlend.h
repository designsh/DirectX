#pragma once
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineBlend : public GameEngineObjectNameBase
{
	friend class GameEngineBlendManager;

private:	// member Var
	ID3D11BlendState* State_;
	D3D11_BLEND_DESC Info_;
	float4 Factor_;
	unsigned int Mask_;

public:
	GameEngineBlend(); // default constructer ����Ʈ ������
	~GameEngineBlend(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineBlend(const GameEngineBlend& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineBlend(GameEngineBlend&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineBlend& operator=(const GameEngineBlend& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineBlend& operator=(const GameEngineBlend&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

