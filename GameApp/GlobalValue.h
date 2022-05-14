#pragma once

// �з� : �۷ι� 
// �뵵 : �������
// ���� : �����÷��̾�� ���� ���� �������� ����ؾ��ϴ� ������ ���� ��ü�� �ش� Ŭ�������� ����
//            (����!!!) �ش� ���� �����Ҷ� �����ؾ��Ѵ�.
class MainPlayer;
class MouseObject;
class MainPlayer_LeftWeaponSkillButton;
class MainPlayer_RightWeaponSkillButton;
class WeaponNPC;
class ChandleryNPC;
class TownMap;
class Portal;
class Storehouse;
class CatacombsMap;
class GlobalValue
{
public: // �÷��̾� ����
	static MainPlayer* CurPlayer;
	static std::string CurPlayerID;

public: // ���콺����
	static MouseObject* CurMouse;

public: // ��ų��ư����(��ų��ϻ����� ������)
	static MainPlayer_LeftWeaponSkillButton* CurLeftSkill;
	static MainPlayer_RightWeaponSkillButton* CurRightSkill;

public: // NPC ����
	static WeaponNPC* WeaponNPC;
	static ChandleryNPC* ChandleryNPC;

public: // �ʰ���
	static TownMap* TownMap;
	static CatacombsMap* CatacombsMap;

public: // ������Ʈ����
	// ����
	static Portal* Portal;

	// ������
	static Storehouse* Storehouse;

	// īŸ�޸�
	

	// ī����������
};

