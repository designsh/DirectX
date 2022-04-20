#pragma once
#include "GameEngineObjectNameBase.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineThread : public GameEngineObjectNameBase
{
private:
	static void GameServerThreadFunction(GameEngineThread* _Thread, std::string _Name);

private:	// member Var
	std::thread Thread_;
	std::function<void(GameEngineThread*)> ThreadFunction_;

public:
	GameEngineThread();
	~GameEngineThread();

protected:		// delete constructer
	GameEngineThread(const GameEngineThread& _other) = delete;
	GameEngineThread(GameEngineThread&& _other) noexcept = delete;

private:		//delete operator
	GameEngineThread& operator=(const GameEngineThread& _other) = delete;
	GameEngineThread& operator=(const GameEngineThread&& _other) = delete;

public:
	void Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _Function);
	void Join();
};

