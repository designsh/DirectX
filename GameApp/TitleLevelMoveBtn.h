#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ����
// �뵵 : ĳ���ͻ������� ��ư
// ���� : ���� ������ �÷��̾�� ���ӽ���
class GameEngineUIRenderer;
class TitleLevelMoveBtn : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* PrevMenuBtn_;

public:
	TitleLevelMoveBtn();
	~TitleLevelMoveBtn();

protected:		// delete constructer
	TitleLevelMoveBtn(const TitleLevelMoveBtn& _other) = delete;
	TitleLevelMoveBtn(TitleLevelMoveBtn&& _other) noexcept = delete;

private:		//delete operator
	TitleLevelMoveBtn& operator=(const TitleLevelMoveBtn& _other) = delete;
	TitleLevelMoveBtn& operator=(const TitleLevelMoveBtn&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

