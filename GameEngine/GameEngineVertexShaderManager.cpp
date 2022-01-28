#include "PreCompile.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShaderManager* GameEngineVertexShaderManager::Inst = new GameEngineVertexShaderManager();

GameEngineVertexShaderManager::GameEngineVertexShaderManager() // default constructer ����Ʈ ������
{

}

GameEngineVertexShaderManager::~GameEngineVertexShaderManager() // default destructer ����Ʈ �Ҹ���
{
	for (const std::pair<std::string, GameEngineVertexShader*>& Res : ResourcesMap)
	{
		if (nullptr != Res.second)
		{
			delete Res.second;
		}
	}

	ResourcesMap.clear();
}

GameEngineVertexShaderManager::GameEngineVertexShaderManager(GameEngineVertexShaderManager&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

GameEngineVertexShader* GameEngineVertexShaderManager::Create(const std::string& _Name, const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	GameEngineVertexShader* FindRes = Find(_Name);
	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
	}

	GameEngineVertexShader* NewRes = new GameEngineVertexShader();
	NewRes->SetName(_Name);

	// Vertex Shader ���� �����ÿ��� ������Ͽ� �߰�����
	if (false == NewRes->Create(_ShaderCode, _EntryPoint, _VersionHigh, _VersionLow))
	{
		delete NewRes;
		return nullptr;
	}

	ResourcesMap.insert(std::map<std::string, GameEngineVertexShader*>::value_type(_Name, NewRes));

	return NewRes;
}

GameEngineVertexShader* GameEngineVertexShaderManager::Load(const std::string& _Path)
{
	return Load(GameEnginePath::GetFileName(_Path), _Path);
}

GameEngineVertexShader* GameEngineVertexShaderManager::Load(const std::string& _Name, const std::string& _Path)
{
	GameEngineVertexShader* FindRes = Find(_Name);

	if (nullptr != FindRes)
	{
		GameEngineDebug::MsgBoxError(_Name + " Is Overlap Load");
	}

	GameEngineVertexShader* NewRes = new GameEngineVertexShader();
	NewRes->SetName(_Name);


	ResourcesMap.insert(std::map<std::string, GameEngineVertexShader*>::value_type(_Name, NewRes));
	return NewRes;
}

GameEngineVertexShader* GameEngineVertexShaderManager::Find(const std::string& _Name)
{
	std::map<std::string, GameEngineVertexShader*>::iterator FindIter = ResourcesMap.find(_Name);

	if (FindIter != ResourcesMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}