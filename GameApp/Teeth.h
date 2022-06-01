#pragma once
#include <GameEngine/GameEngineActor.h>

#include "MainPlayerInfomation.h"

// �ִϸ��̼� ����
enum class Teeth_AniDir
{
	TT_LB,
	TT_LT,
	TT_RT,
	TT_RB,
	TT_B,
	TT_L,
	TT_T,
	TT_R,
};

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class Teeth : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Renderer_;
	GameEngineCollision* Collider_;

private:
	SkillList TeethInfo_;

private:
	Teeth_AniDir AnimationCurDir_;
	bool FireStart_;
	float4 MoveDir_;
	float MoveSpeed_;

private:
	GameEngineSoundPlayer* StateSound_;

public:
	Teeth();
	~Teeth();

protected:		// delete constructer
	Teeth(const Teeth& _other) = delete;
	Teeth(Teeth&& _other) noexcept = delete;

private:		//delete operator
	Teeth& operator=(const Teeth& _other) = delete;
	Teeth& operator=(const Teeth&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline int GetDamage() const
	{
		return TeethInfo_.SkillDamage;
	}

private: // Ÿ���浹ó��
	void TargetCollision(GameEngineCollision* _Other);

private: // ���� �浹ó��
	void WallCollisionCheck();

private: // �ִϸ��̼������ ȣ��
	void ProjectileAnimationEnd();
	void ExplodeAnimationEnd();

public: // �߻�ü �߻��غ� ó��
	void CreateAnimation();
	void CreateCollision();
	void TeethFire(int _DirType, float4 _MoveDir);
};

