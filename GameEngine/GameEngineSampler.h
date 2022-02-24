#pragma once
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"


// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineSampler : public GameEngineObjectNameBase
{
	friend class GameEngineSamplerManager;

private:	// member Var
	ID3D11SamplerState* State_;
	D3D11_SAMPLER_DESC Info_;

public:
	GameEngineSampler(); // default constructer 디폴트 생성자
	~GameEngineSampler(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineSampler(const GameEngineSampler& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineSampler(GameEngineSampler&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineSampler& operator=(const GameEngineSampler& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineSampler& operator=(const GameEngineSampler&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private: // GameEngineSamplerManager에서만 호출하도록 제한
	void Create(const D3D11_SAMPLER_DESC& _Info);

public:
	inline ID3D11SamplerState** GetSamplerState()
	{
		return &State_;
	}

public:
	void ReSetting(const D3D11_SAMPLER_DESC& _Info);
};

