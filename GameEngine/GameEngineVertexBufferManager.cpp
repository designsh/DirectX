#include "PreCompile.h"
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBufferManager* GameEngineVertexBufferManager::Inst = new GameEngineVertexBufferManager();

GameEngineVertexBufferManager::GameEngineVertexBufferManager()
{

}

GameEngineVertexBufferManager::~GameEngineVertexBufferManager()
{
	// Ranged Base Iterator 사용
	// 범위기반반복자 : 기본적인 for문과 달리 시작점과 끝점을 알려주지 않더라도, 해당 데이터의 반복자를 순회하는 기능
	// -. 원형 : for (데이터타입 반복자를받아올변수 : 데이터 리스트)
	for (const std::pair<std::string, GameEngineVertexBuffer*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}
	ResourcesMap.clear();
}

GameEngineVertexBufferManager::GameEngineVertexBufferManager(GameEngineVertexBufferManager&& _other) noexcept
{

}

GameEngineVertexBuffer* GameEngineVertexBufferManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineVertexBuffer* GameEngineVertexBufferManager::Load(const std::string& _Name, const std::string& _Path)
{
	// 동일한 이름의 정점버퍼 생성 불가
	GameEngineVertexBuffer* FindRes = Find(_Name);
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + "Is Overlap Load");
	}

	// 신규 Vertex Buffer 생성
	GameEngineVertexBuffer* NewRes = new GameEngineVertexBuffer();
	NewRes->SetName(_Name);

	// 관리목록에 추가
	ResourcesMap.insert(std::map<std::string, GameEngineVertexBuffer*>::value_type(_Name, NewRes));

	// 신규 생성된 정점버퍼 반환
	return NewRes;
}

GameEngineVertexBuffer* GameEngineVertexBufferManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineVertexBuffer*>::iterator FindIter = ResourcesMap.find(_Name);
	if(FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}

