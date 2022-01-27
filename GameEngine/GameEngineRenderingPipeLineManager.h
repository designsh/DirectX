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
	GameEngineRenderingPipeLineManager(); // default constructer ����Ʈ ������
	~GameEngineRenderingPipeLineManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRenderingPipeLineManager(const GameEngineRenderingPipeLineManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRenderingPipeLineManager(GameEngineRenderingPipeLineManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRenderingPipeLineManager& operator=(const GameEngineRenderingPipeLineManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRenderingPipeLineManager& operator=(const GameEngineRenderingPipeLineManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:

};




