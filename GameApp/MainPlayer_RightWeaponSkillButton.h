#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_RightWeaponSkillButton : public GameEngineActor
{
private:	// member Var
	bool IsActive_;											// 왼쪽무기 스킬목록 활성/비활성화

private:
	Button_State ButtonState_;								// 버튼 상태

private:
	GameEngineUIRenderer* CurSkillButton_;					// 현재 선택된 왼쪽 스킬 버튼
	GameEngineCollision* CurSkillButtonCollision_;			// 현재 선택된 왼쪽 스킬 버튼 충돌체

private:
	std::vector<WeaponSkillBtn_List> RWeaponSkillList_;		// 현재 오른쪽무기 활성화 스킬목록
	int SkillListPushCount_[4];								// 현재 오른쪽무기 활성화 스킬목록 관리갯수(0:기본스킬)

public:
	MainPlayer_RightWeaponSkillButton();
	~MainPlayer_RightWeaponSkillButton();

protected:		// delete constructer
	MainPlayer_RightWeaponSkillButton(const MainPlayer_RightWeaponSkillButton& _other) = delete;
	MainPlayer_RightWeaponSkillButton(MainPlayer_RightWeaponSkillButton&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_RightWeaponSkillButton& operator=(const MainPlayer_RightWeaponSkillButton& _other) = delete;
	MainPlayer_RightWeaponSkillButton& operator=(const MainPlayer_RightWeaponSkillButton&& _other) = delete;

private:
	void PlayerIsTownCheck();

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void UpdateWeaponSkillList(int _SkillID);
	void InitRWeaponSkillList();

public:
	void CurRWeaponSkillBtnCol(GameEngineCollision* _Other);
	void RWeaponActiveSkillListView(bool _Flag);
};

