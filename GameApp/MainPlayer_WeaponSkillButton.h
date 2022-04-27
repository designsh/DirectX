#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// ��ų ���� Ÿ��
enum class DirectType
{
	None = -1,
	Left,
	Right
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_WeaponSkillButton : public GameEngineActor
{
private:	// member Var
	DirectType						DirectType_;				// �ش� ��ų�� �ش��ϴ� Ÿ��(Left, Right)

private:
	int								SkillPage_;					// �ش� ��ų ������ No
	int								SkillID_;					// �ش� ��ų ID
	int								PushNo_;					// �ش� ��ų ��Ͽ� �߰��� ����
	std::string						ButtonName_;				// ��ų��ư �ؽ����̸�(�⺻,Ŭ��,����(��Ȱ��))
	float4							SkillBtnPos_;				// ��ų��ư ��ġ

private:
	Button_State					ButtonState_;				// ��ư ����

private:
	GameEngineUIRenderer*			SkillButtonRenderer_;		// ��ų��ư ������
	GameEngineCollision*			SkillButtonCollision_;		// ��ų��ư �浹ü

private:
	GameEngineCollision*			MoveableChkCol_;			// �÷��̾� �̵��Ǵ� üũ�� �浹ü

public:
	MainPlayer_WeaponSkillButton();
	~MainPlayer_WeaponSkillButton();

protected:		// delete constructer
	MainPlayer_WeaponSkillButton(const MainPlayer_WeaponSkillButton& _other) = delete;
	MainPlayer_WeaponSkillButton(MainPlayer_WeaponSkillButton&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_WeaponSkillButton& operator=(const MainPlayer_WeaponSkillButton& _other) = delete;
	MainPlayer_WeaponSkillButton& operator=(const MainPlayer_WeaponSkillButton&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SelectCurrentSkill(GameEngineCollision* _Other);

public:
	void CreateSkillButton(int _PushNo, const float4& _Pos, int _SkillID);
	void SetWeaponDirType(DirectType _DirType);
	void SelectCurWeapon(DirectType _DirType, int _SkillID, const std::string& _TextureName);
};

