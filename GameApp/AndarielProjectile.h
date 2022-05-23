#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>

enum class AndarielProjectile_Dir
{
	PJ_B,
	PJ_LB,
	PJ_L,
	PJ_LT,
	PJ_T,
	PJ_RT,
	PJ_R,
	PJ_RB,
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineImageRenderer;
class GameEngineCollision;
class AndarielProjectile : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Renderer_;
	GameEngineCollision* Collider_;

private:
	bool FireStart_;
	AndarielProjectile_Dir TargetDir_;
	float4 MoveDir_;
	float MoveSpeed_;

private:
	int Damage_;

public:
	AndarielProjectile();
	~AndarielProjectile();

protected:		// delete constructer
	AndarielProjectile(const AndarielProjectile& _other) = delete;
	AndarielProjectile(AndarielProjectile&& _other) noexcept = delete;

private:		//delete operator
	AndarielProjectile& operator=(const AndarielProjectile& _other) = delete;
	AndarielProjectile& operator=(const AndarielProjectile&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void TargetCollision(GameEngineCollision* _Other);

private:
	void InitProjectile();
	void TextureCutting();
	void CreateAnimation();
	void CreateCollision();

public: // ������ ���ÿ� �ش� �������� �߻�
	void SkillAttackProjectile(AndarielProjectile_Dir _AnimationDir, float4 _MoveDir, int _Damage);
};

