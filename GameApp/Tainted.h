#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "GlobalEnumClass.h"
#include "AllMonsterInfomation.h"

#include "Monster_Common.h"
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
	TT_ROOMDETECT,				// 룸진입 적 체크 상태
	TT_IDLE,					// 대기상태
	TT_WALK,					// 타겟까지 이동상태
	TT_ATTACK,					// 공격범위내 적 진입
	TT_GETHIT,					// 피격 상태(적이 공격하여 전환)
	TT_DEATH,					// 사망 상태(몬스터 체력 0)
	TT_DEAD,					// 시체 상태(마우스와 충돌중이며, 플레이가 소환스킬시전 체크)
};

// 분류 : 일반몬스터
// 용도 : 
// 설명 : 
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class Tainted : public GameEngineActor
{
public: // 생성갯수 = 네비게이션 인덱스
	static int TaintedCnt;

private:
	GameEngineImageRenderer* Tainted_;
	GameEngineCollision* BodyCollider_;

private: // 생성관련
	int SpawnRoomNo_;
	TileIndex SpawnTile_;
	float IdleDelayTime_;
	int NavigationIndex_;

private: // 체크리스트관련
	std::vector<TileIndex> RoomTileList_;

private: // 몬스터 정보
	AllMonsterInfo MonsterInfo_;
	int CurHP_;
	int MapHP_;
	int DropGold_;

private: // 상태관련
	GameEngineFSM State_;
	Tainted_FSMState PrevState_;
	Tainted_FSMState CurState_;

private: // 이동관련
	std::list<PathIndex> MovePath_;
	TileIndex MoveTargetTile_;
	float4 MoveTargetDir_;
	float MoveSpeed_;
	Tainted_Dir PrevDir_;
	Tainted_Dir CurDir_;

private: // 공격관련
	bool Attack_;

private: // 사운드관련
	GameEngineSoundPlayer* StateSound_;

private: // 피격관련
	bool SpecialGetHit_;
	float SpecialGetHitTime_;
	MonsterDamageType CurDamageType_;

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

public:
	inline Tainted_FSMState GetCurState() const
	{
		return CurState_;
	}

private: // Collision Callback Function
	void MouseCollision(GameEngineCollision* _Ohter);
	void EnemyCollision(GameEngineCollision* _Other);

private:
	void TargetDirCheck(const float4& _TargetPos, const std::string& _StateName);
	void ChangeAnimationCheck(const std::string& _StateName);

private: // 해당 몬스터 초기화 및 생성
	void InitTainted();
	void TextureCutting();
	void CreateAnimation();
	void CreateAnimationEndFunction();
	void CreateFSMState();
	void CreateCollision();
	void CreateInfomation();

private: // FSM State
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

private: // 특정 애니메이션 종료시 호출되는 함수
	void AttackEnd();
	void GetHitEnd();
	void DeathEnd();

public: // 외부접근 강제 상태전환
	void SpawnToDeath();
	void HitDamage(int _Damage);
	void SpecialHitDamage(int _Damage, MonsterDamageType _DamageType);

public: // 적 체크 리스트관련
	void SetEnterTheRoomDetectList(int _SpawnRoomNo);
	bool EnterTheRoomDetectCheck();
};

