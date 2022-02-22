#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineImageRenderer;
class Player : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* PlayerImageRenderer;

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

