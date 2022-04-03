#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 이미지
// 용도 : 하단상태바
// 설명 : 플레이어의 하단상태바관리
class GameEngineUIRenderer;
class MainPlayer_CurrentHP;
class MainPlayer_CurrentMP;
class MainPlayer_LeftWeaponSkillButton;
class MainPlayer_RightWeaponSkillButton;
class MainPlayer_Stamina;
class MainPlayer_MiniMenu;
class MainPlayer_LevelUpActiveButton;
class MainPlayer_CurExpProgressBar;
class BottomStateBar : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* Panel_;

private: // HP/MP
	MainPlayer_CurrentHP* HP_;
	MainPlayer_CurrentMP* MP_;

private: // 활성화스킬버튼(좌/우)
	MainPlayer_LeftWeaponSkillButton* LWeaponSkill_;
	MainPlayer_RightWeaponSkillButton* RWeaponSkill_;

private: // 스태미나
	MainPlayer_Stamina* Stamina_;

private: // 미니메뉴
	MainPlayer_MiniMenu* MiniMenu_;

private: // 레벨업시 활성화되는 버튼
	MainPlayer_LevelUpActiveButton* AddStatPointButton_;
	MainPlayer_LevelUpActiveButton* AddSkillPointButton_;

private: // 현재 경험치
	MainPlayer_CurExpProgressBar* CurExpProgressBar_;

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

	inline MainPlayer_LevelUpActiveButton* GetStatPointControl()
	{
		return AddStatPointButton_;
	}

	inline MainPlayer_LevelUpActiveButton* GetSkillPointControl()
	{
		return AddSkillPointButton_;
	}
	
	inline MainPlayer_CurExpProgressBar* GetEXPProgressBarControl()
	{
		return CurExpProgressBar_;
	}

public:
	void InitBottomStateBar();			// 총괄 초기화
	void InitCurrentHP();				// 현재 HP
	void InitCurrentMP();				// 현재 MP
	void InitCurrentStamina();			// 현재 스테미나
	void InitLeftSkillBtn();			// 현재 활성화 왼쪽 스킬버튼(목록생성)
	void InitRightSkillBtn();			// 현재 활성화 오른쪽 스킬버튼(목록생성)
	void InitLiquidMedicine();			// 현재 물약장착 상태
	void InitEXP();						// 현재 경험치
	
public:
	void ConsumptionHP(float _Damage);	// 현재 HP 감소
	void ConsumptionMP(float _MP);		// 현재 MP 감소
};

