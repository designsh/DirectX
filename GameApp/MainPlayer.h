#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 플레이어
// 용도 : 
// 설명 : 직업에 따라 정보가 달라진다.
class CommonInfomation;
class GameEngineImageRenderer;
class MainPlayer : public GameEngineActor
{
private:	// member Var
	CommonInfomation* PlayerInfomation_;

private:
	GameEngineImageRenderer* PlayerImageRenderer;

public:
	MainPlayer();
	~MainPlayer();

protected:		// delete constructer
	MainPlayer(const MainPlayer& _other) = delete;
	MainPlayer(MainPlayer&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer& operator=(const MainPlayer& _other) = delete;
	MainPlayer& operator=(const MainPlayer&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

