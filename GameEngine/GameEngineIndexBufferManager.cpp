#include "PreCompile.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineIndexBufferManager.h"

GameEngineIndexBufferManager* GameEngineIndexBufferManager::Inst = new GameEngineIndexBufferManager();

GameEngineIndexBufferManager::GameEngineIndexBufferManager() // default constructer 디폴트 생성자
{

}

GameEngineIndexBufferManager::~GameEngineIndexBufferManager() // default destructer 디폴트 소멸자
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

GameEngineIndexBufferManager::GameEngineIndexBufferManager(GameEngineIndexBufferManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

GameEngineIndexBuffer* GameEngineIndexBufferManager::Create(const std::string& _Name, const std::vector<UINT>& _Index, D3D11_USAGE _Usage)
{
	GameEngineIndexBuffer* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}

	GameEngineIndexBuffer* NewRes = new GameEngineIndexBuffer();
	NewRes->SetName(_Name);
	NewRes->Create(_Index, _Usage);

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