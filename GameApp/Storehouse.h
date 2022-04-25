#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : â�������Ʈ
// �뵵 : â��â ����
// ���� : ���콺�� �浹�Ͽ���, �÷��̾ �����Ÿ� ���Խ� â��â ����
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

