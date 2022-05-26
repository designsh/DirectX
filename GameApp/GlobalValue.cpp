#include "PreCompile.h"
#include "GlobalValue.h"

// ���� ����
GameEngineSoundPlayer* GlobalValue::BackGroundSound = nullptr;

// ���� UI����
MonsterTopHPBar* GlobalValue::TopHPBar = nullptr;
SummonsEmblem* GlobalValue::Emblem = nullptr;

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
CatacombsMap* GlobalValue::CatacombsMap = nullptr;

// ������Ʈ����
// ����(������ ����ɶ����� ����ȴ�.)
Portal* GlobalValue::Portal = nullptr;

// ������(�ش� �ʿ��� �����ϴ� ������Ʈ)
Storehouse* GlobalValue::Storehouse = nullptr;

// īŸ�޸�(�ش� �ʿ��� �����ϴ� ������Ʈ)


// ���Ͱ���

// ����
Andariel* GlobalValue::Andariel = nullptr;
