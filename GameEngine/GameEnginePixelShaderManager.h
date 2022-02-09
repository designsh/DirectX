#pragma once

class GameEnginePixelShader;
class GameEnginePixelShaderManager
{
private:
	static GameEnginePixelShaderManager* Inst;

public:
	static GameEnginePixelShaderManager& GetInst()
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
	std::map<std::string, GameEnginePixelShader*> ResourcesMap;

private:
	GameEnginePixelShaderManager();
	~GameEnginePixelShaderManager();

protected:		// delete constructer
	GameEnginePixelShaderManager(const GameEnginePixelShaderManager& _other) = delete;
	GameEnginePixelShaderManager(GameEnginePixelShaderManager&& _other) noexcept;

private:		//delete operator
	GameEnginePixelShaderManager& operator=(const GameEnginePixelShaderManager& _other) = delete;
	GameEnginePixelShaderManager& operator=(const GameEnginePixelShaderManager&& _other) = delete;

public: // Create Pixel Shader(���ڿ��� ���̴� �ڵ带 �����Ͽ� ���̴� ����)
	// Pixel Shader�� �����ϳ�, EntryPoint(�����Լ���)�� ������������ ���·� Pixel Shader ����
	// EntryPoint(�����Լ���)�� ���Ź��������Ƿ� Pixel Shader�� �̸��� EntryPoint(�����Լ���)�� �����ϴ�.
	GameEnginePixelShader* Create(const std::string& _Name, const std::string& _ShaderCode, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		return Create(_Name, _ShaderCode, _Name, _VersionHigh, _VersionLow);
	}

	// Pixel Shader�� �����ϴ� ���ڸ� ��� �����Ͽ� �̿� �ش��ϴ� Pixel Shader ����
	GameEnginePixelShader* Create(const std::string& _Name, const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Create Vertex Shader(���ϸ�� ��θ� �̿��Ͽ� ���̴� ����)
	GameEnginePixelShader* Load(const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);
	
	// ���ϸ�� EntryPoint�� �޶� ���̴��� ������ �� �ֵ��� EntryPoint�̸��� �����Ѵ�.
	GameEnginePixelShader* Load(const std::string& _FileName, const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public:
	GameEnginePixelShader* Find(const std::string& _Name);
};




