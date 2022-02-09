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

public: // Create Pixel Shader(문자열로 셰이더 코드를 수신하여 셰이더 생성)
	// Pixel Shader를 생성하나, EntryPoint(진입함수명)을 수신하지않은 상태로 Pixel Shader 생성
	// EntryPoint(진입함수명)을 수신받지않으므로 Pixel Shader의 이름과 EntryPoint(진입함수명)이 동일하다.
	GameEnginePixelShader* Create(const std::string& _Name, const std::string& _ShaderCode, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		return Create(_Name, _ShaderCode, _Name, _VersionHigh, _VersionLow);
	}

	// Pixel Shader를 생성하는 인자를 모두 수신하여 이에 해당하는 Pixel Shader 생성
	GameEnginePixelShader* Create(const std::string& _Name, const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Create Vertex Shader(파일명과 경로를 이용하여 셰이더 생성)
	GameEnginePixelShader* Load(const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);
	
	// 파일명과 EntryPoint가 달라도 셰이더를 생성할 수 있도록 EntryPoint이름을 수신한다.
	GameEnginePixelShader* Load(const std::string& _FileName, const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public:
	GameEnginePixelShader* Find(const std::string& _Name);
};




