#pragma once

// ���� : 
class GameEngineVertexShader;
class GameEngineVertexShaderManager
{
private:
	static GameEngineVertexShaderManager* Inst;

public:
	static GameEngineVertexShaderManager& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private:	// member Var
	std::map<std::string, GameEngineVertexShader*> ResourcesMap;

private:
	GameEngineVertexShaderManager(); // default constructer ����Ʈ ������
	~GameEngineVertexShaderManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineVertexShaderManager(const GameEngineVertexShaderManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineVertexShaderManager(GameEngineVertexShaderManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineVertexShaderManager& operator=(const GameEngineVertexShaderManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineVertexShaderManager& operator=(const GameEngineVertexShaderManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	GameEngineVertexShader* Create(const std::string& _Name, std::function<float4(const float4)> _Function);
	GameEngineVertexShader* Load(const std::string& _Path);
	GameEngineVertexShader* Load(const std::string& _Name, const std::string& _Path);
	GameEngineVertexShader* Find(const std::string& _Name);
};




