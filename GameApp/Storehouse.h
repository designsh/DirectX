#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : â��������Ʈ
// �뵵 : â��â ����
// ���� : ���콺�� �浹�Ͽ���, �÷��̾ �����Ÿ� ���Խ� â��â ����
class GameEngineImageRenderer;
class Storehouse : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Storehouse_;

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

public:
};
