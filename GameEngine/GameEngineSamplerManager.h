#pragma once
#include "GameEngineDevice.h"

class GameEngineSampler;
class GameEngineSamplerManager
{
private:
	static GameEngineSamplerManager* Inst;

public:
	static GameEngineSamplerManager& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:	// member Var
	std::map<std::string, GameEngineSampler*> ResourcesMap;

public:
	GameEngineSampler* Create(const std::string& _Name, const D3D11_SAMPLER_DESC& _Info);
	GameEngineSampler* Find(const std::string& _Name);

private:
	GameEngineSamplerManager(); // default constructer 디폴트 생성자
	~GameEngineSamplerManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineSamplerManager(const GameEngineSamplerManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineSamplerManager(GameEngineSamplerManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineSamplerManager& operator=(const GameEngineSamplerManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineSamplerManager& operator=(const GameEngineSamplerManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:

};




