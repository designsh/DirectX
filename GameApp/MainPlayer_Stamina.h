#pragma once
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineProgressBarRenderer;
class GameEngineUIRenderer;
class GameEngineCollision;
class MainPlayer_Stamina : public GameEngineActor
{
private:	// member Var
	GameEngineProgressBarRenderer* StaminaProgressBarRenderer_;

private:
	GameEngineUIRenderer* StaminaButton_;
	GameEngineCollision* StaminaButtonCollision_;

private:
	bool RunActive_;
	Button_State ButtonState_;

private:
	bool Stamina30Percent_;
	float MaxStamina_;
	float CurStamina_;
	float StaminaDrain_;

public:
	MainPlayer_Stamina();
	~MainPlayer_Stamina();

protected:		// delete constructer
	MainPlayer_Stamina(const MainPlayer_Stamina& _other) = delete;
	MainPlayer_Stamina(MainPlayer_Stamina&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_Stamina& operator=(const MainPlayer_Stamina& _other) = delete;
	MainPlayer_Stamina& operator=(const MainPlayer_Stamina&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void InitStaminaDrain();

public:
	void CalculationStaminaConsumption(float _DeltaTime);

private: // ���ο��� ���¹̳� Ȱ��/��Ȱ�� ��ȯ
	void StaminaEnableOrDisabled();
	void StaminaActiveButtonClick(GameEngineCollision* _Other);

public: // �ܺο��� ���¹̳� Ȱ��/��Ȱ�� ��ȯ
	void SetStaminaActive(bool _Flag);
};

