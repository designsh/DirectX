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

public:
	GameEngineVertexShader* Create(const std::string& _Name, std::function<float4(const float4)> _Function);
	GameEngineVertexShader* Load(const std::string& _Path);
	GameEngineVertexShader* Load(const std::string& _Name, const std::string& _Path);
	GameEngineVertexShader* Find(const std::string& _Name);
};




