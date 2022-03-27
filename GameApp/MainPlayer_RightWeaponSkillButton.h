#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_RightWeaponSkillButton : public GameEngineActor
{
private:	// member Var
	bool IsActive_;											// ���ʹ��� ��ų��� Ȱ��/��Ȱ��ȭ

private:
	Button_State ButtonState_;								// ��ư ����

private:
	GameEngineUIRenderer* CurSkillButton_;					// ���� ���õ� ���� ��ų ��ư
	GameEngineCollision* CurSkillButtonCollision_;			// ���� ���õ� ���� ��ų ��ư �浹ü

private:
	std::vector<WeaponSkillBtn_List> RWeaponSkillList_;		// ���� �����ʹ��� Ȱ��ȭ ��ų���
	int SkillListPushCount_[4];								// ���� �����ʹ��� Ȱ��ȭ ��ų��� ��������(0:�⺻��ų)

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

