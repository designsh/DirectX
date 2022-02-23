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
	GameEngineSamplerManager(); // default constructer ����Ʈ ������
	~GameEngineSamplerManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineSamplerManager(const GameEngineSamplerManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineSamplerManager(GameEngineSamplerManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineSamplerManager& operator=(const GameEngineSamplerManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineSamplerManager& operator=(const GameEngineSamplerManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:

};




