#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineProgressBarRenderer;
class MainPlayer_CurrentHP : public GameEngineActor
{
private:	// member Var
	GameEngineProgressBarRenderer* HPRenderer_;

private:
	float test = 1.0f;

public:
	MainPlayer_CurrentHP();
	~MainPlayer_CurrentHP();

protected:		// delete constructer
	MainPlayer_CurrentHP(const MainPlayer_CurrentHP& _other) = delete;
	MainPlayer_CurrentHP(MainPlayer_CurrentHP&& _other) noexcept = delete;

private:		//delete operator
	MainPlayer_CurrentHP& operator=(const MainPlayer_CurrentHP& _other) = delete;
	MainPlayer_CurrentHP& operator=(const MainPlayer_CurrentHP&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void AllHPRecovery();					// ���� ü�� ��� ȸ��
	void HPRecovery(float _Damage);			// ���� ü�� ȸ��
	void HPConsumption(float _Damage);		// ���� ü�� �Ҹ�

};

