#pragma once
#include <GameEngineBase/GameEngineObjectBase.h>

// 분류 : 게임 코어
// 용도 : 
// 설명 : 게임 구동에 필요한 기본구조를 제공하며, 해당 클래스를 상속받는 객체가 반드시 초기화/리소스로드/게임루프/릴리즈기능을
//           구현하도록 제공
class GameEngineCore : public GameEngineObjectBase
{
private:	// member Var

public:
	template<typename UserGameType>
	static void Start()
	{
		UserGameType NewUserGame;

		NewUserGame.Initialize();
		NewUserGame.ResourcesLoad();

		// Game Loop
		while (NewUserGame.IsOn())
		{
			NewUserGame.GameLoop();
		}

		NewUserGame.Release();
	}

protected:
	GameEngineCore(); // default constructer 디폴트 생성자
	~GameEngineCore(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineCore(const GameEngineCore& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineCore(GameEngineCore&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineCore& operator=(const GameEngineCore& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineCore& operator=(const GameEngineCore&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void EngineDestory();

protected:
	virtual void Initialize() = 0;
	virtual void ResourcesLoad() = 0;
	virtual void GameLoop() = 0;
	virtual void Release() = 0;
};

