#pragma once

class GameEngineRenderingPipeLine;
class GameEngineRenderingPipeLineManager
{
private:
	static GameEngineRenderingPipeLineManager* Inst;

public:
	static GameEngineRenderingPipeLineManager& GetInst()
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
	std::map<std::string, GameEngineRenderingPipeLine*> ResourcesMap;

public:
	GameEngineRenderingPipeLine* Create(const std::string& _Name);
	GameEngineRenderingPipeLine* Load(const std::string& _Path);
	GameEngineRenderingPipeLine* Load(const std::string& _Name, const std::string& _Path);
	GameEngineRenderingPipeLine* Find(const std::string& _Name);

private:
	GameEngineRenderingPipeLineManager(); // default constructer 디폴트 생성자
	~GameEngineRenderingPipeLineManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRenderingPipeLineManager(const GameEngineRenderingPipeLineManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRenderingPipeLineManager(GameEngineRenderingPipeLineManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRenderingPipeLineManager& operator=(const GameEngineRenderingPipeLineManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRenderingPipeLineManager& operator=(const GameEngineRenderingPipeLineManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:

};




