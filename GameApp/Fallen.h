#pragma once
#include <GameEngineBase/GameEnginePathFind.h>

#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFSM.h>

#include "GlobalEnumClass.h"
#include "AllMonsterInfomation.h"

#include "Monster_Common.h"
#include "FixedTileMap_Common.h"
#include "RandomTileMap_Common.h"


// 방향관련
enum class Fallen_TargetDir
{
	FL_LB,
	FL_LT,
	FL_RT,
	FL_RB,
	FL_B,
	FL_L,
	FL_T,
	FL_R
};

// 상태관련
enum class Fallen_FSMState
{
	FL_ROOMDETECT,				// 룸진입 적 체크 상태
	FL_IDLE,					// 대기상태
	FL_WALK,					// 타겟까지 이동상태
	FL_ATTACK,					// 공격범위내 적 진입
	FL_GETHIT,					// 피격 상태(적이 공격하여 전환)
	FL_DEATH,					// 사망 상태(몬스터 체력 0)
	FL_DEAD,					// 시체 상태(마우스와 충돌중이며, 플레이가 소환스킬시전 체크)
};

// 분류 : 일반몬스터
// 용도 : 
// 설명 : 대기상태에서 일정범위를 순환이동하다가 플레이어 발견시 플레이어에게로 이동하며,
//           플레이어에게 공격을 가한다.
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class Fallen : public GameEngineActor
{
public: // 생성갯수 = 네비게이션 인덱스
	static int FallenCnt;

private:
	GameEngineImageRenderer* Fallen_;
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
	Fallen_FSMState PrevState_;
	Fallen_FSMState CurState_;

private: // 이동관련
	std::list<PathIndex> MovePath_;
	TileIndex MoveTargetTile_;
	float4 MoveTargetDir_;
	float MoveSpeed_;
	Fallen_TargetDir PrevDir_;
	Fallen_TargetDir CurDir_;

private: // 공격관련
	bool Attack_;

private: // 사운드관련
	GameEngineSoundPlayer* StateSound_;

private: // 피격관련
	bool SpecialGetHit_;
	float SpecialGetHitTime_;
	MonsterDamageType CurDamageType_;

public:
	Fallen();
	~Fallen();

protected:		// delete constructer
	Fallen(const Fallen& _other) = delete;
	Fallen(Fallen&& _other) noexcept = delete;

private:		//delete operator
	Fallen& operator=(const Fallen& _other) = delete;
	Fallen& operator=(const Fallen&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline Fallen_FSMState GetCurState() const
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
	void InitFallen();
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

