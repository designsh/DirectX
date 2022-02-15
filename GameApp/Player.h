#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class Player : public GameEngineActor
{
private:	// member Var

public:
	Player();
	~Player();

protected:		// delete constructer
	Player(const Player& _other) = delete;
	Player(Player&& _other) noexcept = delete;

private:		//delete operator
	Player& operator=(const Player& _other) = delete;
	Player& operator=(const Player&& _other) = delete;

public:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
};

