#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : Ÿ��Ʋ���� ��ư
// ���� : ĳ���ͻ��������� �̵�
class GameStartButton : public GameEngineActor
{
private:	// member Var

public:
	GameStartButton();
	~GameStartButton();

protected:		// delete constructer
	GameStartButton(const GameStartButton& _other) = delete;
	GameStartButton(GameStartButton&& _other) noexcept = delete;

private:		//delete operator
	GameStartButton& operator=(const GameStartButton& _other) = delete;
	GameStartButton& operator=(const GameStartButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};
