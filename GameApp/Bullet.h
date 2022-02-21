#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Bullet : public GameEngineActor
{
public:
	// constrcuter destructer
	Bullet();
	~Bullet();

	// delete Function
	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _DeltaTime) override;
};

