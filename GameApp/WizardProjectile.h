#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineImageRenderer;
class GameEngineCollision;
class WizardProjectile : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Renderer_;
	GameEngineCollision* Collider_;

public:
	WizardProjectile();
	~WizardProjectile();

protected:		// delete constructer
	WizardProjectile(const WizardProjectile& _other) = delete;
	WizardProjectile(WizardProjectile&& _other) noexcept = delete;

private:		//delete operator
	WizardProjectile& operator=(const WizardProjectile& _other) = delete;
	WizardProjectile& operator=(const WizardProjectile&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;

private:
	void TargetCollision(GameEngineCollision* _Other);

public:
	void SkeletonWizardFire();
};

