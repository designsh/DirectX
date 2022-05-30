#pragma once
#include <GameEngine/GameEngineActor.h>

#include "MainPlayerInfomation.h"

// 애니메이션 방향
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

// 분류 : 
// 용도 : 
// 설명 : 
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

private: // 타겟충돌처리
	void TargetCollision(GameEngineCollision* _Other);

private: // 벽과 충돌처리
	void WallCollisionCheck();

public: // 발사체 발사준비 처리
	void CreateAnimation();
	void CreateCollision();
	void PoisonNoveFire(int _DirType, float4 _MoveDir);
};

