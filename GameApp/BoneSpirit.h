#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "FixedTileMap_Common.h"
#include "MainPlayerInfomation.h"

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
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class BoneSpirit : public GameEngineActor
{
private:
	static int ProjetileCount;

private:	// member Var
	GameEngineImageRenderer* Renderer_;
	GameEngineCollision* Collider_;

private:
	GameEngineFSM State_;
	SkillList BonsSpiritInfo_;

private:
	BoneSpirit_Dir CurDir_;
	float4 StartPos_;
	float4 MouseClickPos_;

private:
	TileIndex MoveTargetTile_;
	std::list<PathIndex> MovePath_;
	float4 MoveTargetDir_;
	float MoveSpeed_;

private:
	int NavigationIndex_;
	bool FireStart_;
	bool Targeting_;
	int Damage_;

private:
	GameEngineActor* TargetMonster_;

private:
	GameEngineSoundPlayer* StateSound_;

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
	void TargetCollision(GameEngineCollision* _Other);

private:
	void TargetDirCheckAndAnimationSetting(const float4& _TargetPos, const std::string& _StateName);
	void AnimationChangeCheck(const std::string& _StateName);

private:
	void CreateCollision();
	void CreateAnimation();
	void CreateFSMState();
	void ExplodeAnimationEnd();

private:
	bool MonsterDetect();

private:
	// Ŭ���������� �̵�����
	void StartMoveState();
	void UpdateMoveState();
	void EndMoveState();

	// Ÿ��Ž�� ����
	void StartSearchState();
	void UpdateSearchState();
	void EndSearchState();

	// �߻� ����
	void StartFireState();
	void UpdateFireState();
	void EndFireState();

	// ���߻���
	void StartExplodeState();
	void UpdateExplodeState();
	void EndExplodeState();

public:
	void BoneSpiritFire(const float4& _StartPos, const float4& _MouseClickPos, GameEngineActor* _TargetingMonster = nullptr);
};

