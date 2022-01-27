#include "PreCompile.h"
#include "GameEngineRenderingPipeLineManager.h"
#include "GameEngineRenderingPipeLine.h"

GameEngineRenderingPipeLineManager* GameEngineRenderingPipeLineManager::Inst = new GameEngineRenderingPipeLineManager();

GameEngineRenderingPipeLineManager::GameEngineRenderingPipeLineManager()
{

}

GameEngineRenderingPipeLineManager::~GameEngineRenderingPipeLineManager()
{
	for (const std::pair<std::string, GameEngineRenderingPipeLine*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineRenderingPipeLineManager::GameEngineRenderingPipeLineManager(GameEngineRenderingPipeLineManager&& _other) noexcept
{

}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLineManager::Create(const std::string& _Name)
{
	GameEngineRenderingPipeLine* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}

	GameEngineRenderingPipeLine* NewRes = new GameEngineRenderingPipeLine();
	NewRes->SetName(_Name);

	ResourcesMap.insert(std::map<std::string, GameEngineRenderingPipeLine*>::value_type(_Name, NewRes));

	return NewRes;
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLineManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLineManager::Load(const std::string& _Name, const std::string& _Path)
{
	GameEngineRenderingPipeLine* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineRenderingPipeLine* NewRes = new GameEngineRenderingPipeLine();
	NewRes->SetName(_Name);

	ResourcesMap.insert(std::map<std::string, GameEngineRenderingPipeLine*>::value_type(_Name, NewRes));

	return NewRes;
}

GameEngineRenderingPipeLine* GameEngineRenderingPipeLineManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineRenderingPipeLine*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}