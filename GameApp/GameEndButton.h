#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : Ÿ��Ʋ���� ���������ư
// ���� : ������ ����
class GameEndButton : public GameEngineActor
{
private:	// member Var

public:
	GameEndButton();
	~GameEndButton();

protected:		// delete constructer
	GameEndButton(const GameEndButton& _other) = delete;
	GameEndButton(GameEndButton&& _other) noexcept = delete;

private:		//delete operator
	GameEndButton& operator=(const GameEndButton& _other) = delete;
	GameEndButton& operator=(const GameEndButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

