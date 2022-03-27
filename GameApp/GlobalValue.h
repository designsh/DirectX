#pragma once

// �з� : �۷ι� 
// �뵵 : �������
// ���� : �����÷��̾�� ���� ���� �������� ����ؾ��ϴ� ������ ���� ��ü�� �ش� Ŭ�������� ����
//            (����!!!) �ش� ���� �����Ҷ� �����ؾ��Ѵ�.
struct WeaponSkillBtn_List
{
	int								SkillPage;					// �ش� ��ų ������ No
	int								SkillRow;					// �ش� ��ų ������ Row
	int								SkillColumn;				// �ش� ��ų ������ Column
	int								SkillID;					// �ش� ��ų ID
	int								PushNo;						// �ش� ��ų ��Ͽ� �߰��� ����
	std::string						ButtonName;					// ��ų��ư �ؽ����̸�(�⺻,Ŭ��,����(��Ȱ��))
	GameEngineUIRenderer*			SkillButton;				// ��ų��ư ������
	float4							SkillBtnPos;				// ��ų��ư ��ġ
};

class GameEngineUIRenderer;
class MainPlayer;
class MouseObject;
class GlobalValue
{
public: // �÷��̾� ����
	static MainPlayer* CurPlayer;
	static std::string CurPlayerID;

public: // ���콺����
	static MouseObject* CurMouse;

public:
};

