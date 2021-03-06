#pragma once
#include "GameEngineVertexBuffer.h"

// 분류 : 정점버퍼 관리자
// 용도 : 
// 설명 : 정점버퍼 목록을 관리
class GameEngineVertexBuffer;
class GameEngineVertexBufferManager
{
private:
	static GameEngineVertexBufferManager* Inst;

public:
	static GameEngineVertexBufferManager& GetInst()
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
	std::map<std::string, GameEngineVertexBuffer*> ResourcesMap;

private:
	GameEngineVertexBufferManager(); // default constructer 디폴트 생성자
	~GameEngineVertexBufferManager(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineVertexBufferManager(const GameEngineVertexBufferManager& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineVertexBufferManager(GameEngineVertexBufferManager&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineVertexBufferManager& operator=(const GameEngineVertexBufferManager& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineVertexBufferManager& operator=(const GameEngineVertexBufferManager&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	GameEngineVertexBuffer* Load(const std::string& _Path);
	GameEngineVertexBuffer* Load(const std::string& _Name, const std::string& _Path);
	GameEngineVertexBuffer* Find(const std::string& _Name);

public:
	template<typename VertexType>
	GameEngineVertexBuffer* Create(const std::string& _Name, const std::vector<VertexType>& _Vertex, D3D11_USAGE _Usage)
	{
		GameEngineVertexBuffer* FindRes = Find(_Name);

		if (nullptr != FindRes)
		{
			GameEngineDebug::MsgBoxError(_Name + " Is Overlap Create");
		}


		GameEngineVertexBuffer* NewRes = new GameEngineVertexBuffer();
		NewRes->SetName(_Name);
		NewRes->Create<VertexType>(_Vertex, _Usage);

		ResourcesMap.insert(std::map<std::string, GameEngineVertexBuffer*>::value_type(_Name, NewRes));

		return NewRes;
	}
};

