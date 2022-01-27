#include "PreCompile.h"
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBufferManager* GameEngineVertexBufferManager::Inst = new GameEngineVertexBufferManager();

GameEngineVertexBufferManager::GameEngineVertexBufferManager()
{

}

GameEngineVertexBufferManager::~GameEngineVertexBufferManager()
{
	// Ranged Base Iterator ���
	// ������ݹݺ��� : �⺻���� for���� �޸� �������� ������ �˷����� �ʴ���, �ش� �������� �ݺ��ڸ� ��ȸ�ϴ� ���
	// -. ���� : for (������Ÿ�� �ݺ��ڸ��޾ƿú��� : ������ ����Ʈ)
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
	// ������ �̸��� �������� ���� �Ұ�
	GameEngineVertexBuffer* FindRes = Find(_Name);
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + "Is Overlap Load");
	}

	// �ű� Vertex Buffer ����
	GameEngineVertexBuffer* NewRes = new GameEngineVertexBuffer();
	NewRes->SetName(_Name);

	// ������Ͽ� �߰�
	ResourcesMap.insert(std::map<std::string, GameEngineVertexBuffer*>::value_type(_Name, NewRes));

	// �ű� ������ �������� ��ȯ
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

