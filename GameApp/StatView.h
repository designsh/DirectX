#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

enum class StatPointType
{
	NONE = -1,
	STR,
	DEX,
	VIT,
	ENR,
	MAX
};

// 분류 : 상태창
// 용도 : 플레이어 정보 표시
// 설명 : 
class GameEngineUIRenderer;
class GameEngineCollision;
class GameEngineLevel;
class StatView : public GameEngineActor
{
private:
	static int StatPoint;

private:	// member Var
	GameEngineUIRenderer* PanelRenderer_;						// 상태창(판넬)
	GameEngineUIRenderer* IDRenderer_;							// 상태창 ID
	GameEngineUIRenderer* JobClassRenderer_;					// 상태창 직업명
	GameEngineUIRenderer* CurLevelRenderer_;					// 상태창 현재 레벨
	GameEngineUIRenderer* CurExpRenderer_;						// 상태창 경험치
	GameEngineUIRenderer* StrengthRenderer_;					// 상태창 힘
	GameEngineUIRenderer* DexterityRenderer_;					// 상태창 민첩
	GameEngineUIRenderer* VitalityRenderer_;					// 상태창 생명력
	GameEngineUIRenderer* EnergyRenderer_;						// 상태창 에너지
	GameEngineUIRenderer* DamageRenderer_;						// 상태창 공격데미지(최소) -  상태창 공격데미지(최대)
	GameEngineUIRenderer* AttackRatingRenderer_;				// 상태창 공격등급
	GameEngineUIRenderer* DefenseRenderer_;						// 상태창 방어
	GameEngineUIRenderer* StaminaRenderer_;						// 상태창 스태미나
	GameEngineUIRenderer* LifeRenderer_;						// 상태창 라이프
	GameEngineUIRenderer* ManaRenderer_;						// 상태창 마나
	GameEngineUIRenderer* FireResistanceRenderer_;				// 상태창 파이어 저항력
	GameEngineUIRenderer* ColdResistanceRenderer_;				// 상태창 콜드 저항력
	GameEngineUIRenderer* LightningResistanceRenderer_;			// 상태창 라이트닝 저항력
	GameEngineUIRenderer* PoisonResistanceRenderer_;			// 상태창 포이즌 저항력

private:
	GameEngineUIRenderer* CloseButton_;							// 상태창 종료버튼
	GameEngineCollision* MainCollider_;							// 상태창 종료버튼 충돌체

private:
	std::string IDString_;										// 상태창 ID
	std::string JobClassString_;								// 상태창 직업명
	std::string CurLevelString_;								// 상태창 현재 레벨
	std::string CurExpString_;									// 상태창 경험치
	std::string StrengthString_;								// 상태창 힘
	std::string DexterityString_;								// 상태창 민첩
	std::string VitalityString_;								// 상태창 생명력
	std::string EnergyString_;									// 상태창 에너지
	std::string MinDamageString_;								// 상태창 공격데미지(최소)
	std::string MaxDamageString_;								// 상태창 공격데미지(최대)
	std::string AttackRatingString_;							// 상태창 공격등급
	std::string DefenseString_;									// 상태창 방어
	std::string StaminaString_;									// 상태창 스태미나
	std::string LifeString_;									// 상태창 라이프
	std::string ManaString_;									// 상태창 마나
	std::string FireResistanceString_;							// 상태창 파이어 저항력
	std::string ColdResistanceString_;							// 상태창 콜드 저항력
	std::string LightningResistanceString_;						// 상태창 라이트닝 저항력
	std::string PoisonResistanceString_;						// 상태창 포이즌 저항력

private:
	Button_State ButtonState_;

private: // 플레이어 레벨업시 활성화되어 스탯을 증가시키는 버튼
	GameEngineUIRenderer* STRPointUpButton_;					// 힘 증가버튼 렌더러
	GameEngineCollision* STRPointUpButtonCollider_;				// 힘 증가버튼 충돌체
	GameEngineUIRenderer* DEXPointUpButton_;					// 민첩 증가버튼 렌더러
	GameEngineCollision* DEXPointUpButtonCollider_;				// 민첩 증가버튼 충돌체
	GameEngineUIRenderer* VITPointUpButton_;					// 생명력 증가버튼 렌더러
	GameEngineCollision* VITPointUpButtonCollider_;				// 생명력 증가버튼 충돌체
	GameEngineUIRenderer* ENRPointUpButton_;					// 에너지 증가버튼 렌더러
	GameEngineCollision* ENRPointUpButtonCollider_;				// 에너지 증가버튼 충돌체

	Button_State STRButtonState_;								// 힘 증가버튼 상태
	Button_State DEXButtonState_;								// 민첩 증가버튼 상태
	Button_State VITButtonState_;								// 생명력 증가버튼 상태
	Button_State ENRButtonState_;								// 에너지 증가버튼 상태

public:
	StatView();
	~StatView();

protected:		// delete constructer
	StatView(const StatView& _other) = delete;
	StatView(StatView&& _other) noexcept = delete;

private:		//delete operator
	StatView& operator=(const StatView& _other) = delete;
	StatView& operator=(const StatView&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

public:
	void InitStatView();

public:
	void CloseButtonClick(GameEngineCollision* _Other);
	void STRButtonClick(GameEngineCollision* _Other);
	void DEXButtonClick(GameEngineCollision* _Other);
	void VITButtonClick(GameEngineCollision* _Other);
	void ENRButtonClick(GameEngineCollision* _Other);

public:
	void StatPointUP(StatPointType _Type);

public:
	void CurEXPUpdate(float _EXP);

public: // 레벨업으로인한 스탯포인트 부여
	void LevelUpStatPointGrant();
};

