#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_WeaponSkillButton;
class MainPlayer_LeftWeaponSkillButton : public GameEngineActor
{
private:	// member Var
	bool IsActive_;														// 왼쪽무기 스킬목록 활성/비활성화

private:
	Button_State ButtonState_;											// 버튼 상태

private:
	GameEngineUIRenderer* CurSkillButton_;								// 현재 선택된 왼쪽 스킬 버튼
	GameEngineCollision* CurSkillButtonCollision_;						// 현재 선택된 왼쪽 스킬 버튼 충돌체
	int CurSkillCode_;													// 현재 선택된 왼쪽 스킬 코드

private:
	std::vector<MainPlayer_WeaponSkillButton*> LWeaponSkillList_;		// 현재 왼쪽무기 활성화 스킬목록
	int SkillListPushCount_[4];											// 현재 왼쪽무기 활성화 스킬목록 관리갯수(0:기본스킬)

public:
	MainPlayer_LeftWeaponSkillButton();
	~MainPlayer_LeftWeaponSkillButton();

protected:		// delete constructer
	MainPlayer_LeftWeaponSkillButton(const MainPlayer_LeftWeaponSkillButton& _other) = delete;
	MainPlayer_LeftWeaponSkillButton(MainPlayer_LeftWeaponSkillButton&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_LeftWeaponSkillButton& operator=(const MainPlayer_LeftWeaponSkillButton& _other) = delete;
	MainPlayer_LeftWeaponSkillButton& operator=(const MainPlayer_LeftWeaponSkillButton&& _other) = delete;

private:
	void PlayerIsTownCheck();

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

public:
	void UpdateWeaponSkillList(int _SkillID);
	void InitLWeaponSkillList();

public:
	void CurLWeaponSkillBtnCol(GameEngineCollision* _Other);
	void LWeaponActiveSkillListView(bool _Flag);

public:
	void CurSkillChange(int _SkillID, const std::string& _TextureName);
};

