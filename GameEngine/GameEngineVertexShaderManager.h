#pragma once

// 설명 : 
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
	GameEngineVertexShaderManager(); // default constructer 디폴트 생성자
	~GameEngineVertexShaderManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineVertexShaderManager(const GameEngineVertexShaderManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineVertexShaderManager(GameEngineVertexShaderManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineVertexShaderManager& operator=(const GameEngineVertexShaderManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineVertexShaderManager& operator=(const GameEngineVertexShaderManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public: // Create Vertex Shader(문자열로 셰이더 코드를 수신하여 셰이더 생성)
	// Vertex Shader를 생성하나, EntryPoint(진입함수명)을 수신하지않은 상태로 Vertex Shader 생성
	// EntryPoint(진입함수명)을 수신받지않으므로 Vertex Shader의 이름과 EntryPoint(진입함수명)이 동일하다.
	GameEngineVertexShader* Create(const std::string& _Name, const std::string& _ShaderCode, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		return Create(_Name, _ShaderCode, _Name, _VersionHigh, _VersionLow);
	}

	// Vertex Shader를 생성하는 인자를 모두 수신하여 이에 해당하는 Vertex Shader 생성
	GameEngineVertexShader* Create(const std::string& _Name, const std::string& _ShaderCode, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public: // Create Vertex Shader(파일명과 경로를 이용하여 셰이더 생성)
	GameEngineVertexShader* Load(const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

	// 파일명과 EntryPoint가 달라도 셰이더를 생성할 수 있도록 EntryPoint이름을 수신한다.
	GameEngineVertexShader* Load(const std::string& _FileName, const std::string& _Path, const std::string& _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

public:
	GameEngineVertexShader* Find(const std::string& _Name);
};




