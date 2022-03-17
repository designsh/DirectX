#pragma once
#include "GameEngineDevice.h"

class GameEngineDepthBuffer;
class GameEngineDepthBufferManager
{
private:
	static GameEngineDepthBufferManager* Inst;

public:
	static GameEngineDepthBufferManager& GetInst()
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
	std::map<std::string, GameEngineDepthBuffer*> ResourcesMap;

public:
	GameEngineDepthBuffer* Create(const std::string& _Name, float4 _Size);
	GameEngineDepthBuffer* Load(const std::string& _Path);
	GameEngineDepthBuffer* Load(const std::string& _Name, const std::string& _Path);
	GameEngineDepthBuffer* Find(const std::string& _Name);

private:
	GameEngineDepthBufferManager();
	~GameEngineDepthBufferManager();

protected:		// delete constructer
	GameEngineDepthBufferManager(const GameEngineDepthBufferManager& _other) = delete;
	GameEngineDepthBufferManager(GameEngineDepthBufferManager&& _other) noexcept;

private:		//delete operator
	GameEngineDepthBufferManager& operator=(const GameEngineDepthBufferManager& _other) = delete;
	GameEngineDepthBufferManager& operator=(const GameEngineDepthBufferManager&& _other) = delete;

public:

};
