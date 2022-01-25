#pragma once

// ���� : 
class GameEngineRenderTarget;
class GameEngineRenderTargetManager
{
private:
	static GameEngineRenderTargetManager* Inst;

public:
	static GameEngineRenderTargetManager& GetInst()
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
	std::map<std::string, GameEngineRenderTarget*> ResourcesMap;

public:
	GameEngineRenderTarget* Create(const std::string& _Name, const std::string& _TextureName, float4 _Color);
	GameEngineRenderTarget* Load(const std::string& _Path);
	GameEngineRenderTarget* Load(const std::string& _Name, const std::string& _Path);
	GameEngineRenderTarget* Find(const std::string& _Name);

private:
	GameEngineRenderTargetManager(); // default constructer ����Ʈ ������
	~GameEngineRenderTargetManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRenderTargetManager(const GameEngineRenderTargetManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRenderTargetManager(GameEngineRenderTargetManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRenderTargetManager& operator=(const GameEngineRenderTargetManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRenderTargetManager& operator=(const GameEngineRenderTargetManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����
};




