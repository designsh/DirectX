#pragma once
#include <GameEngine/GameEngineActor.h>

#include "MainPlayerInfomation.h"

// �ִϸ��̼� ����
enum class PoisonNova_AniDir
{
	PN_T,
	PN_RT,
	PN_R,
	PN_RB,
	PN_B,
	PN_LB,
	PN_L,
	PN_LT,
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineImageRenderer;
class GameEngineCollision;
class PoisonNova : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Renderer_;
	GameEngineCollision* Collider_;

private:
	SkillList PoisonNovaInfo_;

private:
	PoisonNova_AniDir AnimationCurDir_;
	bool FireStart_;
	float4 MoveDir_;
	float MoveSpeed_;

public:
	PoisonNova();
	~PoisonNova();

protected:		// delete constructer
	PoisonNova(const PoisonNova& _other) = delete;
	PoisonNova(PoisonNova&& _other) noexcept = delete;

private:		//delete operator
	PoisonNova& operator=(const PoisonNova& _other) = delete;
	PoisonNova& operator=(const PoisonNova&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline int GetDamage() const
	{
		return PoisonNovaInfo_.SkillDamage;
	}

private: // Ÿ���浹ó��
	void TargetCollision(GameEngineCollision* _Other);

private: // ���� �浹ó��
	void WallCollisionCheck();

public: // �߻�ü �߻��غ� ó��
	void CreateAnimation();
	void CreateCollision();
	void PoisonNoveFire(int _DirType, float4 _MoveDir);
};

