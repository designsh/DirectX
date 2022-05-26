#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// �з� : ����
// �뵵 : ĳ���ͻ������� ��ư
// ���� : ���� ������ �÷��̾�� ���ӽ���
class GameEngineUIRenderer;
class GameEngineCollision;
class GameEngineSoundPlayer;
class TitleLevelMoveBtn : public GameEngineActor
{
private:	// member Var
	Button_State ButtonState_;

private:
	GameEngineUIRenderer* PrevMenuBtn_;
	GameEngineCollision* MainCollider_;

private:
	GameEngineSoundPlayer* ButtonClickSound_;

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
	void ChangeStartReset();

public:
	void PrevButtonClick(GameEngineCollision* _OtherCollision);

public:
	void DebugRender();
};

