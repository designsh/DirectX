#pragma once
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"


// �з� : 
// �뵵 : 
// ���� : 
class GameEngineSampler : public GameEngineObjectNameBase
{
	friend class GameEngineSamplerManager;

private:	// member Var
	ID3D11SamplerState* State_;
	D3D11_SAMPLER_DESC Info_;

public:
	GameEngineSampler(); // default constructer ����Ʈ ������
	~GameEngineSampler(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineSampler(const GameEngineSampler& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineSampler(GameEngineSampler&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineSampler& operator=(const GameEngineSampler& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineSampler& operator=(const GameEngineSampler&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private: // GameEngineSamplerManager������ ȣ���ϵ��� ����
	void Create(const D3D11_SAMPLER_DESC& _Info);

public:
	inline ID3D11SamplerState** GetSamplerState()
	{
		return &State_;
	}

public:
	void ReSetting(const D3D11_SAMPLER_DESC& _Info);
};

