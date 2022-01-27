#pragma once
#include <GameEngine/GameEngineDirectXDevice.h>

// ���� : 
class GameEngineIndexBuffer;
class GameEngineIndexBufferManager
{
private:
	static GameEngineIndexBufferManager* Inst;

public:
	static GameEngineIndexBufferManager& GetInst()
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
	std::map<std::string, GameEngineIndexBuffer*> ResourcesMap;

private:
	GameEngineIndexBufferManager(); // default constructer ����Ʈ ������
	~GameEngineIndexBufferManager(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineIndexBufferManager(const GameEngineIndexBufferManager& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineIndexBufferManager(GameEngineIndexBufferManager&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineIndexBufferManager& operator=(const GameEngineIndexBufferManager& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineIndexBufferManager& operator=(const GameEngineIndexBufferManager&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	GameEngineIndexBuffer* Create(const std::string& _Name, const std::vector<UINT>& _Index, D3D11_USAGE _Usage);
	GameEngineIndexBuffer* Load(const std::string& _Path);
	GameEngineIndexBuffer* Load(const std::string& _Name, const std::string& _Path);
	GameEngineIndexBuffer* Find(const std::string& _Name);
};




