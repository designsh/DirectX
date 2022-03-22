#include "PreCompile.h"
#include "GameEngineFontManager.h"
#include "GameEngineFont.h"

GameEngineFontManager* GameEngineFontManager::Inst = new GameEngineFontManager();

GameEngineFontManager::GameEngineFontManager()
{
}

GameEngineFontManager::~GameEngineFontManager()
{
	for (const std::pair<std::string, GameEngineFont*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineFontManager::GameEngineFontManager(GameEngineFontManager&& _other) noexcept
{
}

GameEngineFont* GameEngineFontManager::Load(const std::string& _Path)
{
	GameEngineFont* FindRes = Find(_Path);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Path + " Is Overlap Load");
	}

	GameEngineFont* NewRes = new GameEngineFont();
	NewRes->SetName(_Path);
	NewRes->Load(_Path);

	ResourcesMap.insert(std::map<std::string, GameEngineFont*>::value_type(_Path, NewRes));

	return NewRes;
}

GameEngineFont* GameEngineFontManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineFont*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}