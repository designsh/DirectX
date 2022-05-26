#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// �з� : ����
// �뵵 : ĳ���ͻ������� ��ư
// ���� : ���� ������ �÷��̾�� ���ӽ����ϸ�, �ʱ� ȭ�鿡 �����������ʴٰ� ����ڰ� ������ �����ϸ� ������
class GameEngineUIRenderer;
class GameEngineCollision;
class GameEngineSoundPlayer;
class CurPlayerGameStartButton : public GameEngineActor
{
private:
	static bool ClassSelect_;

public:
	static void UserClassSelect();
	static void UserClassDeselect();

private:	// member Var
	Button_State ButtonState_;

private:
	GameEngineUIRenderer* CurPlayerGameStartBtn_;
	GameEngineCollision* MainCollider_;

private:
	bool RenderFlag_;

private:
	GameEngineSoundPlayer* ButtonClickSound_;

public:
	CurPlayerGameStartButton();
	~CurPlayerGameStartButton();

protected:		// delete constructer
	CurPlayerGameStartButton(const CurPlayerGameStartButton& _other) = delete;
	CurPlayerGameStartButton(CurPlayerGameStartButton&& _other) noexcept = delete;

private:		//delete operator
	CurPlayerGameStartButton& operator=(const CurPlayerGameStartButton& _other) = delete;
	CurPlayerGameStartButton& operator=(const CurPlayerGameStartButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void ChangeStartReset();

public:
	void DebugRender();

public:
	void OKButtonClick(GameEngineCollision* _OtherCollision);

public:
	void GameStartConditionCheck();
	void CheckSameID();
	bool DefaultPathFileNameCheck(const std::string& _PlayerID);
	void CreateCurPlayer(const std::string& _PlayerID);
};

