#pragma once
#include "GameEngineDevice.h"

class GameEngineFolderTexture;
class GameEngineFolderTextureManager
{
private:
	static GameEngineFolderTextureManager* Inst;

public:
	static GameEngineFolderTextureManager& GetInst()
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
	std::map<std::string, GameEngineFolderTexture*> ResourcesMap;

public:
	GameEngineFolderTexture* Load(const std::string& _Path);
	GameEngineFolderTexture* Load(const std::string& _Name, const std::string& _Path);
	GameEngineFolderTexture* Find(const std::string& _Name);

private:
	GameEngineFolderTextureManager();
	~GameEngineFolderTextureManager();

protected:		// delete constructer
	GameEngineFolderTextureManager(const GameEngineFolderTextureManager& _other) = delete;
	GameEngineFolderTextureManager(GameEngineFolderTextureManager&& _other) noexcept;

private:		//delete operator
	GameEngineFolderTextureManager& operator=(const GameEngineFolderTextureManager& _other) = delete;
	GameEngineFolderTextureManager& operator=(const GameEngineFolderTextureManager&& _other) = delete;

public:

};




