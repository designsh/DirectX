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

public: // Create Vertex Shader(���ڿ��� ���̴� �ڵ带 �����Ͽ� ���̴� ����)
	// Vertex Shader�� �����ϳ�, EntryPoint(�����Լ���)�� ������������ ���·� Vertex Shader ����
	// EntryPoint(�����Լ���)�� ���Ź��������Ƿ� Vertex Shader�� �̸��� EntryPoint(�����Լ���)�� �����ϴ�.
	GameEngineVertexShader* Create(const std::string& _Name, const std::string& _ShaderCode, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		return Create(_Name, _ShaderCode, _Name, _VersionHigh, _VersionLow);
	}

	// Vertex Shader�� �����ϴ� ���ڸ� ��� �����Ͽ� �̿� �ش��ϴ� Vertex Shader ����
	GameEngineVertexShader* Create(const std::string& _Name, const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Create Vertex Shader(���ϸ�� ��θ� �̿��Ͽ� ���̴� ����)
	GameEngineVertexShader* Load(const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

	// ���ϸ�� EntryPoint�� �޶� ���̴��� ������ �� �ֵ��� EntryPoint�̸��� �����Ѵ�.
	GameEngineVertexShader* Load(const std::string& _FileName, const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public:
	GameEngineVertexShader* Find(const std::string& _Name);
};




