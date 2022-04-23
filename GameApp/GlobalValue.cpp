#include "PreCompile.h"
#include "GlobalValue.h"

// ���� ������ ������ �����÷��̾�
MainPlayer* GlobalValue::CurPlayer = nullptr;

// ���� ������ �÷��̾��� �̸�(ID)
// ĳ���ͻ����������� ĳ���͸� ����� �⺻������ �����Ͽ� ���Ϸ� ����(ID.txt)
// �ε��������� ������ ĳ���� ������ �ε��Ͽ� �÷��̾� ��������
// �÷��̷������� ��������� ���� ���ŵ� �÷��̾� ������ �̿��Ͽ� �������� ������
std::string GlobalValue::CurPlayerID = "";

// ���� ������ ������ ���� ���콺������Ʈ
MouseObject* GlobalValue::CurMouse = nullptr;

// ���� ������ ������ �÷��̾��� ���ʽ�ų/�����ʽ�ų
MainPlayer_LeftWeaponSkillButton* GlobalValue::CurLeftSkill = nullptr;
MainPlayer_RightWeaponSkillButton* GlobalValue::CurRightSkill = nullptr;

// ���� ������ ������ NPC
WeaponNPC* GlobalValue::WeaponNPC = nullptr;
ChandleryNPC* GlobalValue::ChandleryNPC = nullptr;

// �ʰ���
TownMap* GlobalValue::TownMap = nullptr;
