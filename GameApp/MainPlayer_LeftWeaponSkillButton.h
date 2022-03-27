#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_LeftWeaponSkillButton : public GameEngineActor
{
private:	// member Var
	bool IsActive_;											// ���ʹ��� ��ų��� Ȱ��/��Ȱ��ȭ

private:
	Button_State ButtonState_;								// ��ư ����

private:
	GameEngineUIRenderer* CurSkillButton_;					// ���� ���õ� ���� ��ų ��ư
	GameEngineCollision* CurSkillButtonCollision_;			// ���� ���õ� ���� ��ų ��ư �浹ü

private:
	std::vector<WeaponSkillBtn_List> LWeaponSkillList_;		// ���� ���ʹ��� Ȱ��ȭ ��ų���
	int SkillListPushCount_[4];								// ���� ���ʹ��� Ȱ��ȭ ��ų��� ��������(0:�⺻��ų)

	//struct WeaponSkillBtn_List
	//{
	//	int								SkillPage;					// �ش� ��ų ������ No
	//	int								SkillID;					// �ش� ��ų ID
	//	int								PushNo;						// �ش� ��ų ��Ͽ� �߰��� ����
	//	std::string						ButtonName;					// ��ų��ư �ؽ����̸�(�⺻,Ŭ��,����(��Ȱ��))
	//	GameEngineUIRenderer*			SkillButton;				// ��ų��ư ������
	//};

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

public:
	void UpdateWeaponSkillList(int _SkillID);
	void InitLWeaponSkillList();

public:
	void CurLWeaponSkillBtnCol(GameEngineCollision* _Other);
	void LWeaponActiveSkillListView(bool _Flag);
};

