#include "PreCompile.h"
#include "GameEngineFolderTextureManager.h"
#include "GameEngineFolderTexture.h"

GameEngineFolderTextureManager* GameEngineFolderTextureManager::Inst = new GameEngineFolderTextureManager();

GameEngineFolderTextureManager::GameEngineFolderTextureManager()
{
}

GameEngineFolderTextureManager::~GameEngineFolderTextureManager()
{
	for (const std::pair<std::string, GameEngineFolderTexture*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineFolderTextureManager::GameEngineFolderTextureManager(GameEngineFolderTextureManager&& _other) noexcept
{
}

GameEngineFolderTexture* GameEngineFolderTextureManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineFolderTexture* GameEngineFolderTextureManager::Load(const std::string& _Name, const std::string& _Path)
{
	GameEngineFolderTexture* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineFolderTexture* NewRes = new GameEngineFolderTexture();
	NewRes->SetName(_Name);
	NewRes->Load(_Path);

	ResourcesMap.insert(std::map<std::string, GameEngineFolderTexture*>::value_type(_Name, NewRes));

	return NewRes;
}

GameEngineFolderTexture* GameEngineFolderTextureManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineFolderTexture*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}