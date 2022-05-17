#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "GlobalEnumClass.h"
#include "AllMonsterInfomation.h"

#include "FixedTileMap_Common.h"
#include "RandomTileMap_Common.h"

// 이동방향
enum class Tainted_Dir
{
	TT_LB,
	TT_LT,
	TT_RT,
	TT_RB,
	TT_B,
	TT_L,
	TT_T,
	TT_R
};

// 상태관련
enum class Tainted_FSMState
{
	ST_ROOMDETECT,				// 룸진입 적 체크 상태
	ST_IDLE,					// 대기상태
	ST_WALK,					// 타겟까지 이동상태
	ST_NORMALATTACK,			// 일반공격범위내 적 진입
	ST_GETHIT,					// 피격 상태(적이 공격하여 전환)
	ST_DEATH,					// 사망 상태(몬스터 체력 0)
	ST_DEAD,					// 시체 상태(마우스와 충돌중이며, 플레이가 소환스킬시전 체크)
};

// 상태전환 타일목록 타입
enum class Tainted_TileCheckType
{
	MOVE,
	ATTACK,
};

// 분류 : 일반몬스터
// 용도 : 
// 설명 : 
class GameEngineImageRenderer;
class GameEngineCollision;
class Tainted : public GameEngineActor
{
public: // 생성갯수 = 네비게이션 인덱스
	static int TaintedCnt;

private:
	bool MouseColStart_;

private:
	AllMonsterInfo MonsterInfo_;
	int CurHP_;
	int MapHP_;
	int DropGold_;

private: // 생성관련
	TileIndex SpawnTile_;
	int SpawnRoomNo_;
	int NavigationIndex_;

private:
	GameEngineImageRenderer* Tainted_;
	GameEngineCollision* BodyCollider_;

private:
	GameEngineFSM State_;

private: // 이동관련
	float4 TargetPos_;
	float4 CurPos_;
	float MoveSpeed_;
	std::list<PathIndex> MovePath_;
	float4 MoveTargetDir_;
	TileIndex MoveTargetIndex_;

private: // 방향관련
	Tainted_Dir PrevDir_;
	Tainted_Dir CurDir_;

private: // 적감지관련
	bool RoomDetect_;
	std::vector<TileIndex> RoomDetectList_;						// 최초 적의 룸진입체크 타일목록
	std::map<__int64, Tainted_TileCheckType> CheckTileList_;	// 이동, 일반공격, 스킬공격 전환 체크타일목록

private: // 상태관련
	Tainted_FSMState PrevState_;
	Tainted_FSMState CurState_;

private: // 공격관련
	std::vector<TileIndex> AttackList_;	// 공격가능 범위
	std::vector<TileIndex> SkillList_;	// 스킬공격 가능범위
	float SkillDelayTime_;				// 스킬공격 쿨타임

public:
	Tainted();
	~Tainted();

protected:		// delete constructer
	Tainted(const Tainted& _other) = delete;
	Tainted(Tainted&& _other) noexcept = delete;

private:		//delete operator
	Tainted& operator=(const Tainted& _other) = delete;
	Tainted& operator=(const Tainted&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private: // 마우스와 충돌
	void MouseCollision(GameEngineCollision* _Other);
	void MouseCollisionEnd(GameEngineCollision* _Other);

private: // 해당 몬스터 초기화 및 생성
	void InitTainted();
	void TextureCutting();
	void CreateAnimation();
	void CreateAnimationEndFunction();
	void CreateFSMState();
	void CreateCollision();
	void CreateInfomation();

private: // 방향체크
	void TargetDirCheck(const float4& _TargetPos, const std::string& _StateName);
	void ChangeAnimationCheck(const std::string& _StateName);

private: // 체크타일목록 생성 및 체크후 상태전환
	void SetCheckTileList(TileIndex _CurTileIndex);
	void CheckChangeState(TileIndex _PlayerTileIndex);

private: // 애니메이션 종료시점 호출함수
	void NormalAttackEnd();
	void GetHitEnd();
	void DeathEnd();

public: // 룸진입 체크타일목록 작성
	void SetEnemyDetectionList(int _SpawnRoomNo);

private:
	// 최초 적탐지 상태
	void StartRoomDetect();
	void UpdateRoomDetect();
	void EndRoomDetect();

	// 대기상태
	void StartIdle();
	void UpdateIdle();
	void EndIdle();

	// 이동상태(적감지상태)
	void StartMove();
	void UpdateMove();
	void EndMove();

	// 기본공격상태
	void StartNormalAttack();
	void UpdateNormalAttack();
	void EndNormalAttack();

	// 피격상태
	void StartGetHit();
	void UpdateGetHit();
	void EndGetHit();

	// 사망상태
	void StartDeath();
	void UpdateDeath();
	void EndDeath();

	// 시체상태
	void StartDead();
	void UpdateDead();
	void EndDead();

public:
	void GetHitDamage(int _Damage);
	void SpawnToDeath();
};

