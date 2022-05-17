#pragma once
#include <GameEngine/GameEngineActor.h>

#include "FixedTileMap_Common.h"
#include "MainPlayerInfomation.h"

// 골렘 타겟방향
enum class GolemTargetDir
{
	GL_LB,
	GL_LT,
	GL_RT,
	GL_RB,
	GL_B,
	GL_L,
	GL_T,
	GL_R,
};

// 소환된 골렘 타입
enum class GolemType
{
	NONE = -1,
	CLAY,
	BLOOD,
	IRON,
	FIRE,
};

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineImageRenderer;
class GameEngineCollision;
class SummonsGolem : public GameEngineActor
{
private:
	GameEngineImageRenderer* GolemRenderer_;
	GameEngineCollision* BodyCollider_;

private:
	SkillList GolemInfo_;

private:
	GolemType GolemType_;
	float4 SpawnPos_;

private:
	std::vector<TileIndex> MoveRange_;				// 플레이어기준 이동가능범위(타일목록)
	GolemTargetDir PrevDir_;						// 이전 방향
	GolemTargetDir CurDir_;							// 현재 방향

public:
	SummonsGolem();
	~SummonsGolem();

protected:		// delete constructer
	SummonsGolem(const SummonsGolem& _other) = delete;
	SummonsGolem(SummonsGolem&& _other) noexcept = delete;

private:		//delete operator
	SummonsGolem& operator=(const SummonsGolem& _other) = delete;
	SummonsGolem& operator=(const SummonsGolem&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void InitGolem();
	void TextureCutting();
	void CreateFSMState();
	void CreateCollision();

public:
	void SpawnGolem(GolemType _GolemType, const float4& _SpawnPos);
	void CreateGolemInfo();
	void CreateAnimation();
	void CreateAnimationEndFunction();

public:
	void CurGolemDeath();
};

