#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Monster : public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

