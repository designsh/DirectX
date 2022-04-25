#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 창고오브젝트
// 용도 : 창고창 오픈
// 설명 : 마우스와 충돌하였고, 플레이어가 일정거리 진입시 창고창 오픈
class GameEngineImageRenderer;
class GameEngineCollision;
class Storehouse : public GameEngineActor
{
private:	// member Var
	bool DistanceCheck_;

private:
	GameEngineImageRenderer* StorehouseRenderer_;
	GameEngineCollision* StorehouseCollision_;

public:
	Storehouse();
	~Storehouse();

protected:		// delete constructer
	Storehouse(const Storehouse& _other) = delete;
	Storehouse(Storehouse&& _other) noexcept = delete;

private:		//delete operator
	Storehouse& operator=(const Storehouse& _other) = delete;
	Storehouse& operator=(const Storehouse&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void MouseLButtonClick(GameEngineCollision* _Other);

private:
	void DistanceCheck();

public:
};

