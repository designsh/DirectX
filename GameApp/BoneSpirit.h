#pragma once
#include <GameEngine/GameEngineActor.h>

// �̵����
enum class BoneSpirit_Dir
{
	BS_LB,
	BS_LT,
	BS_RT,
	BS_RB,
	BS_B,
	BS_L,
	BS_T,
	BS_R,
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineImageRenderer;
class GameEngineCollision;
class BoneSpirit : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Renderer_;
	GameEngineCollision* Collider_;

private:
	BoneSpirit_Dir CurDir_;
	float4 StartPos_;
	float4 TargetPos_;


public:
	BoneSpirit();
	~BoneSpirit();

protected:		// delete constructer
	BoneSpirit(const BoneSpirit& _other) = delete;
	BoneSpirit(BoneSpirit&& _other) noexcept = delete;

private:		//delete operator
	BoneSpirit& operator=(const BoneSpirit& _other) = delete;
	BoneSpirit& operator=(const BoneSpirit&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitWizardProjectile();
	void TextureCutting();

private:
	void CreateCollision();
	void CreateAnimation();

public:
};

