#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 분류 : 위젯
// 용도 : 캐릭터생성레벨 버튼
// 설명 : 현재 생성한 플레이어로 게임시작하며, 초기 화면에 렌더링하지않다가 사용자가 직업을 선택하면 렌더링
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

