#pragma once
#include <GameEngine/GameEngineActor.h>

#include "SketelonWizard.h"

enum class WizardProjectile_Dir
{
	PJ_LB,
	PJ_LT,
	PJ_RT,
	PJ_RB,
	PJ_B,
	PJ_L,
	PJ_T,
	PJ_R,
};

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

private:
	SkeletonWizardType ProjectileType_;
	float4 StartPos_;
	float4 TargetPos_;

private:
	WizardProjectile_Dir CurDir_;
	float4 MoveTargetDir_;
	float MoveSpeed_;

private:
	int Damage_;

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

private:
	void InitWizardProjectile();
	void TextureCutting();

private:
	void CreateAnimation();
	void CreateColdTypeAnimation();
	void CreateFireTypeAnimation();
	void CreateLightingTypeAnimation();
	void CreatePoisonTypeAnimation();
	void CreateCollision();

private:
	void TargetDirCheckAndAnimationSetting();
	void ChangeAnimationCheck();

private:
	void TargetCollision(GameEngineCollision* _Other);

public:
	void SkeletonWizardFire(SkeletonWizardType _ProjectileType, const float4& _FireStartPos, const float4& _TargetPos, int _Damage);
};

