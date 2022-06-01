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
enum class Andariel_TargetDir
{
	AD_B,
	AD_LB,
	AD_L,
	AD_LT,
	AD_T,
	AD_RT,
	AD_R,
	AD_RB
};

// 상태관련
enum class Andariel_FSMState
{
	AD_ROOMDETECT,				// 
	AD_IDLE,					// 
	AD_WALK,					// 
	AD_ATTACK,					// 
	AD_SKILLATTACK,				// 
	AD_GETHIT,					// 
	AD_DEATH,					// 
	AD_DEAD,					// 
};

// 분류 : 보스몬스터
// 용도 : 카타콤레벨의 최종보스
// 설명 : 필드(전체맵)에서 플레이어가 최초 스폰한 방의 위치와 가장 먼 위치에 존재하는 방에 스폰하며,
//            일반공격(근접공격)과 스킬공격(원거리) 패턴을 가진다.
//            단 1마리만 필드에 스폰하며, 사망시 사망 이펙트(카메라 쉐이킹, 불꽃오브젝트 소환 등)을 실행하며,
//            사망이펙트 종료시 Boss Portal(Auto)를 스폰하여 플레이어가 다음 레벨로 진입할 수 있게 제공한다.
//            사망이펙트와 동시에 대량의 아이템 or 골드를 드랍한다.
class GameEngineSoundPlayer;
class GameEngineImageRenderer;
class GameEngineCollision;
class Andariel : public GameEngineActor
{
public: // 생성갯수 = 네비게이션 인덱스
	static int AndarielCnt;

private:	// member Var
	GameEngineImageRenderer* Andariel_;
	GameEngineImageRenderer* AndarielEffect_;
	GameEngineCollision* BodyCollider_;

private: // 생성관련
	int SpawnRoomNo_;
	TileIndex SpawnTile_;
	float IdleDelayTime_;
	int NavigationIndex_;

private: // 스킬공격관련
	float SkillDelayTime_;
	bool SkillAttack_;
	int ProjectileCnt_;
	float4 ProjectileStartDir_;

private: // 일반공격관련
	bool Attack_;

private: // 체크리스트관련
	std::vector<TileIndex> RoomTileList_;

private: // 몬스터 정보
	AllMonsterInfo MonsterInfo_;
	int CurHP_;
	int MapHP_;
	int DropGold_;

private: // 상태관련
	GameEngineFSM State_;
	Andariel_FSMState PrevState_;
	Andariel_FSMState CurState_;

private: // 이동관련
	std::list<PathIndex> MovePath_;
	TileIndex MoveTargetTile_;
	float4 MoveTargetDir_;
	float MoveSpeed_;
	Andariel_TargetDir PrevDir_;
	Andariel_TargetDir CurDir_;

private: // 효과음 관려
	GameEngineSoundPlayer* StateSound_;

private: // 피격관련
	bool SpecialGetHit_;
	float SpecialGetHitTime_;
	MonsterDamageType CurDamageType_;

public:
	Andariel();
	~Andariel();

protected:		// delete constructer
	Andariel(const Andariel& _other) = delete;
	Andariel(Andariel&& _other) noexcept = delete;

private:		//delete operator
	Andariel& operator=(const Andariel& _other) = delete;
	Andariel& operator=(const Andariel&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	inline Andariel_FSMState GetCurState() const
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
	void InitAndariel();
	void TextureCutting();
	void CreateAnimation();
	void CreateAnimationEndFunction();
	void CreateSpecificFrameFunction();
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

	// 스킬공격상태
	void StartSkillAttack();
	void UpdateSkillAttack();
	void EndSkillAttack();

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
	void SkillAttackEnd();
	void DeathEnd();

private: // 특정 애니메이션 특정 프레임에 호출되는 함수
	void ProjectileFire();
	void DeathEffectStart();

public: // 외부접근 강제 상태전환
	void SpawnToDeath();
	void HitDamage(int _Damage);
	void SpecialHitDamage(int _Damage, MonsterDamageType _DamageType);

public: // 적 체크 리스트관련
	void SetEnterTheRoomDetectList(int _SpawnRoomNo);
	bool EnterTheRoomDetectCheck();

public: // 완전한 사망처리 후 포탈생성
	void PortalSpawnAfterDeath();
};

