#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : �̹���
// �뵵 : �ϴܻ��¹�
// ���� : �÷��̾��� �ϴܻ��¹ٰ���
class GameEngineUIRenderer;
class MainPlayer_CurrentHP;
class MainPlayer_CurrentMP;
class MainPlayer_LeftWeaponSkillButton;
class MainPlayer_RightWeaponSkillButton;
class MainPlayer_Stamina;
class MainPlayer_MiniMenu;
class MainPlayer_ActiveButton;
class BottomStateBar : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* Panel_;

private:
	MainPlayer_CurrentHP* HP_;
	MainPlayer_CurrentMP* MP_;

private:
	MainPlayer_LeftWeaponSkillButton* LWeaponSkill_;
	MainPlayer_RightWeaponSkillButton* RWeaponSkill_;

private:
	MainPlayer_Stamina* Stamina_;

private:
	MainPlayer_MiniMenu* MiniMenu_;

private: // �������� Ȱ��ȭ�Ǵ� ��ư
	MainPlayer_LevelUpActiveButton* AddStatPointButton_;
	MainPlayer_LevelUpActiveButton* AddSkillPointButton_;

public:
	BottomStateBar();
	~BottomStateBar();

protected:		// delete constructer
	BottomStateBar(const BottomStateBar& _other) = delete;
	BottomStateBar(BottomStateBar&& _other) noexcept = delete;

private:		//delete operator
	BottomStateBar& operator=(const BottomStateBar& _other) = delete;
	BottomStateBar& operator=(const BottomStateBar&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline MainPlayer_CurrentHP* GetHPControl()
	{
		return HP_;
	}

	inline MainPlayer_CurrentMP* GetMPControl()
	{
		return MP_;
	}

	inline MainPlayer_LeftWeaponSkillButton* GetLeftWeaponSkillControl()
	{
		return LWeaponSkill_;
	}

	inline MainPlayer_RightWeaponSkillButton* GetRightWeaponSkillControl()
	{
		return RWeaponSkill_;
	}

	inline MainPlayer_Stamina* GetStaminaControl()
	{
		return Stamina_;
	}

	inline MainPlayer_MiniMenu* GetMiniMenuControl()
	{
		return MiniMenu_;
	}

public:
	void InitBottomStateBar();			// �Ѱ� �ʱ�ȭ
	void InitCurrentHP();				// ���� HP
	void InitCurrentMP();				// ���� MP
	void InitCurrentStamina();			// ���� ���׹̳�
	void InitLeftSkillBtn();			// ���� Ȱ��ȭ ���� ��ų��ư(��ϻ���)
	void InitRightSkillBtn();			// ���� Ȱ��ȭ ������ ��ų��ư(��ϻ���)
	void InitLiquidMedicine();			// ���� �������� ����
	void InitEXP();						// ���� ����ġ
	
public:
	void ConsumptionHP(float _Damage);	// ���� HP ����
	void ConsumptionMP(float _MP);		// ���� MP ����
};

