#include "PreCompile.h"
#include "GameEngineTextureManager.h"
#include "GameEngineTexture.h"

GameEngineTextureManager* GameEngineTextureManager::Inst = new GameEngineTextureManager();

GameEngineTextureManager::GameEngineTextureManager() // default constructer 디폴트 생성자
{

}

GameEngineTextureManager::~GameEngineTextureManager() // default destructer 디폴트 소멸자
{
	for (const std::pair<std::string, GameEngineTexture*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineTextureManager::GameEngineTextureManager(GameEngineTextureManager&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

GameEngineTexture* GameEngineTextureManager::Create(const std::string& _Name)
{
	GameEngineTexture* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineTexture* NewRes = new GameEngineTexture();
	NewRes->SetName(_Name);

	ResourcesMap.insert(std::map<std::string, GameEngineTexture*>::value_type(_Name, NewRes));

	return NewRes;
}

GameEngineTexture* GameEngineTextureManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineTexture* GameEngineTextureManager::Load(const std::string& _Name, const std::string& _Path)
{
	GameEngineTexture* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineTexture* NewRes = new GameEngineTexture();
	NewRes->SetName(_Name);

	ResourcesMap.insert(std::map<std::string, GameEngineTexture*>::value_type(_Name, NewRes));

	return NewRes;
}

GameEngineTexture* GameEngineTextureManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineTexture*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}