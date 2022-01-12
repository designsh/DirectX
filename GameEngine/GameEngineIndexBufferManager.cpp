#include "PreCompile.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineIndexBuffer.h"

GameEngineIndexBufferManager* GameEngineIndexBufferManager::Inst = new GameEngineIndexBufferManager();

GameEngineIndexBufferManager::GameEngineIndexBufferManager() // default constructer ����Ʈ ������
{

}

GameEngineIndexBufferManager::~GameEngineIndexBufferManager() // default destructer ����Ʈ �Ҹ���
{
	for (const std::pair<std::string, GameEngineIndexBuffer*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineIndexBufferManager::GameEngineIndexBufferManager(GameEngineIndexBufferManager&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

GameEngineIndexBuffer* GameEngineIndexBufferManager::Create(const std::string& _Name, const std::vector<int>& _Index)
{
	GameEngineIndexBuffer* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineIndexBuffer* NewRes = new GameEngineIndexBuffer();
	NewRes->SetName(_Name);
	NewRes->Indexs_ = _Index;

	ResourcesMap.insert(std::map<std::string, GameEngineIndexBuffer*>::value_type(_Name, NewRes));

	return NewRes;
}

GameEngineIndexBuffer* GameEngineIndexBufferManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineIndexBuffer* GameEngineIndexBufferManager::Load(const std::string& _Name, const std::string& _Path)
{
	GameEngineIndexBuffer* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineIndexBuffer* NewRes = new GameEngineIndexBuffer();
	NewRes->SetName(_Name);

	ResourcesMap.insert(std::map<std::string, GameEngineIndexBuffer*>::value_type(_Name, NewRes));

	return NewRes;
}

GameEngineIndexBuffer* GameEngineIndexBufferManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineIndexBuffer*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}