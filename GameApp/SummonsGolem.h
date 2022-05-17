#pragma once
#include <GameEngine/GameEngineActor.h>

#include "FixedTileMap_Common.h"
#include "MainPlayerInfomation.h"

// �� Ÿ�ٹ���
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

// ��ȯ�� �� Ÿ��
enum class GolemType
{
	NONE = -1,
	CLAY,
	BLOOD,
	IRON,
	FIRE,
};

// �з� : 
// �뵵 : 
// ���� : 
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
	std::vector<TileIndex> MoveRange_;				// �÷��̾���� �̵����ɹ���(Ÿ�ϸ��)
	GolemTargetDir PrevDir_;						// ���� ����
	GolemTargetDir CurDir_;							// ���� ����

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

