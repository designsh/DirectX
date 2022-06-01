#pragma once
#include <GameEngine/GameEngineActor.h>

#include "MainPlayerInfomation.h"

// 애니메이션 방향
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

// 분류 : 
// 용도 : 
// 설명 : 
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

private: // 타겟충돌처리
	void TargetCollision(GameEngineCollision* _Other);

private: // 벽과 충돌처리
	void WallCollisionCheck();

private: // 애니메이션종료시 호출
	void ProjectileAnimationEnd();
	void ExplodeAnimationEnd();

public: // 발사체 발사준비 처리
	void CreateAnimation();
	void CreateCollision();
	void TeethFire(int _DirType, float4 _MoveDir);
};

