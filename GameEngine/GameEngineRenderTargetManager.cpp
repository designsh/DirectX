#include "PreCompile.h"
#include "GameEngineRenderTargetManager.h"
#include "GameEngineRenderTarget.h"

GameEngineRenderTargetManager* GameEngineRenderTargetManager::Inst = new GameEngineRenderTargetManager();

GameEngineRenderTargetManager::GameEngineRenderTargetManager() // default constructer 디폴트 생성자
{

}

GameEngineRenderTargetManager::~GameEngineRenderTargetManager() // default destructer 디폴트 소멸자
{
	for (const std::pair<std::string, GameEngineRenderTarget*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineRenderTargetManager::GameEngineRenderTargetManager(GameEngineRenderTargetManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

GameEngineRenderTarget* GameEngineRenderTargetManager::Create(const std::string& _Name, const std::string& _TextureName, float4 _Color)
{
	GameEngineRenderTarget* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}


	GameEngineRenderTarget* NewRes = new GameEngineRenderTarget();
	NewRes->SetName(_Name);
	NewRes->Create(_TextureName, _Color);

	ResourcesMap.insert(std::map<std::string, GameEngineRenderTarget*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineRenderTarget* GameEngineRenderTargetManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineRenderTarget* GameEngineRenderTargetManager::Load(const std::string& _Name, const std::string& _Path)
{
	GameEngineRenderTarget* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineRenderTarget* NewRes = new GameEngineRenderTarget();
	NewRes->SetName(_Name);


	ResourcesMap.insert(std::map<std::string, GameEngineRenderTarget*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineRenderTarget* GameEngineRenderTargetManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineRenderTarget*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}