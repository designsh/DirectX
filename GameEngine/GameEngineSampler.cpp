#include "PreCompile.h"
#include "GameEngineSampler.h"

GameEngineSampler::GameEngineSampler() :
	State_(nullptr),
	Info_{}
{
}

GameEngineSampler::~GameEngineSampler()
{
	if (nullptr != State_)
	{
		State_->Release();
		State_ = nullptr;
	}
}

void GameEngineSampler::Create(const D3D11_SAMPLER_DESC& _Info)
{
	ID3D11SamplerState* State = nullptr;
	if (S_OK != GameEngineDevice::GetDevice()->CreateSamplerState(&_Info, &State))
	{
		GameEngineDebug::MsgBox("샘플러 생성에 실패했습니다.");
		return;
	}

	// 샘플러 생성에 성공시 샘플러 정보를 교체하고
	Info_ = _Info;

	// 새로 생성된 샘플러로 교체작업을 한다.
	State_ = State;
}

void GameEngineSampler::ReSetting(const D3D11_SAMPLER_DESC& _Info)
{
	Create(_Info);
}
