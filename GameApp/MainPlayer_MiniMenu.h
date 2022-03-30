#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_MiniMenuButton;
class MainPlayer_MiniMenu : public GameEngineActor
{
private:
	static bool MiniMenuActive_;

public:
	static bool MiniMenuActive();

private:	// member Var
	Button_State ButtonState_;

private:
	GameEngineUIRenderer* MiniMenuActiveButton_;
	GameEngineCollision* MiniMenuActiveButtonCollision_;

private: // 미니메뉴버튼 목록
	GameEngineUIRenderer* MiniMenuListPanel_;
	std::vector<MainPlayer_MiniMenuButton*> MiniMenuList_;

public:
	MainPlayer_MiniMenu();
	~MainPlayer_MiniMenu();

protected:		// delete constructer
	MainPlayer_MiniMenu(const MainPlayer_MiniMenu& _other) = delete;
	MainPlayer_MiniMenu(MainPlayer_MiniMenu&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_MiniMenu& operator=(const MainPlayer_MiniMenu& _other) = delete;
	MainPlayer_MiniMenu& operator=(const MainPlayer_MiniMenu&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void CreateMiniMenuList();

private:
	void MiniMenuEnabledOrDisabled();
	void MiniMenuButtonClick(GameEngineCollision* _Other);

public:
	void AllMoveMiniMenu(const float4& _MovePos);

public: // 외부에서 접근하여 미니메뉴버튼 활성/비활성
	void SetMiniMenuActiveFlag(bool _Flag);
};

