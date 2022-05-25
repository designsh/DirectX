#include "PreCompile.h"
#include "Andariel.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineCore.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"
#include "MainPlayer.h"
#include "CatacombsMap.h"

#include "Portal.h"

#include "AndarielProjectile.h"
#include "AndarielDeathEffect.h"

int Andariel::AndarielCnt = 0;

Andariel::Andariel() :
	Andariel_(nullptr),
	AndarielEffect_(nullptr),
	BodyCollider_(nullptr),
	SpawnRoomNo_(-1),
	SpawnTile_(),
	IdleDelayTime_(1.f),
	NavigationIndex_(-1),
	SkillDelayTime_(15.f),
	SkillAttack_(false),
	ProjectileCnt_(0),
	ProjectileStartDir_(float4::ZERO),
	Attack_(false),
	MonsterInfo_(),
	CurHP_(0),
	MapHP_(0),
	DropGold_(0),
	State_(),
	PrevState_(Andariel_FSMState::AD_ROOMDETECT),
	CurState_(Andariel_FSMState::AD_ROOMDETECT),
	MoveTargetTile_(),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(150.f),
	PrevDir_(Andariel_TargetDir::AD_B),
	CurDir_(Andariel_TargetDir::AD_B)
{
	NavigationIndex_ = AndarielCnt;
	++AndarielCnt;
}

Andariel::~Andariel()
{
}

void Andariel::Start()
{
	// 해당 몬스터관련 초기화
	InitAndariel();
}

void Andariel::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(BodyCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// 상태 갱신
	State_.Update();

	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));

	// 스킬쿨타임 소모
	// 단, 시체상태이거나 사망상태이면 쿨타임 소모없음
	if (Andariel_FSMState::AD_DEATH != CurState_ && 
		Andariel_FSMState::AD_DEAD != CurState_ &&
		Andariel_FSMState::AD_ROOMDETECT != CurState_)
	{
		if (false == SkillAttack_)
		{
			SkillDelayTime_ -= _DeltaTime;
			if (0.f >= SkillDelayTime_)
			{
				SkillAttack_ = true;
				SkillDelayTime_ = 15.f;
			}
		}
	}

	// 충돌체 위치 갱신
	float4 MyPos = float4(GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y, 0.f);
	float4 CamPos = float4(GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().x, GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().y, 0.f);
	BodyCollider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	// 충돌처리(마우스와 충돌처리)
	BodyCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&Andariel::MouseCollision, this, std::placeholders::_1));

	// 공격상태일때 타겟과 최초충돌이라면 타겟에게 피해를 입힘
	if (Andariel_FSMState::AD_ATTACK == CurState_)
	{
		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Player), std::bind(&Andariel::EnemyCollision, this, std::placeholders::_1));
	}
}

#pragma region EnemyCheck List Function
// 룸 진입 체크 리스트
void Andariel::SetEnterTheRoomDetectList(int _SpawnRoomNo)
{
	// 생성관련 기본정보 저장
	SpawnRoomNo_ = _SpawnRoomNo;
	if (-1 != SpawnRoomNo_)
	{
		SpawnTile_ = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());

		// 현재 내가 생성된 룸의 바닥타일 기준 벽타일을 모두 감지 목록으로 작성
		int RoomTileListCnt = static_cast<int>(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_.size());
		RoomTileList_.clear();
		for (int i = 0; i < RoomTileListCnt; ++i)
		{
			// 바닥타일의 위치 Get
			float4 FloorCenterPos = GlobalValue::CatacombsMap->GetFloorTileIndexToPos(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_[i]);

			// 바닥타일 1개 기준 3x3의 벽타일을 가진다.
			TileIndex WallTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(FloorCenterPos);
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					RoomTileList_.push_back(WallTileIndex);
					WallTileIndex.X_ += 1;
				}

				WallTileIndex.X_ = GlobalValue::CatacombsMap->GetWallTileIndex(FloorCenterPos).X_;
				WallTileIndex.Y_ += 1;
			}
		}
	}
}

bool Andariel::EnterTheRoomDetectCheck()
{
	TileIndex PlayerTile = GlobalValue::CatacombsMap->GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());
	for (auto& CheckTile : RoomTileList_)
	{
		if (CheckTile == PlayerTile)
		{
			return true;
		}
	}

	return false;
}

#pragma endregion

#pragma region AnimationEnd Callback Function
void Andariel::AttackEnd()
{
	// 대기상태 전환
	State_.ChangeState("Idle");
}

void Andariel::SkillAttackEnd()
{
	// 대기상태 전환
	State_.ChangeState("Idle");
}

void Andariel::DeathEnd()
{
	// 시체상태 전환
	State_.ChangeState("Dead");
}

#pragma endregion

#pragma region AnimationFrame Callback Function
void Andariel::ProjectileFire()
{
	if (10 <= ProjectileCnt_)
	{
		return;
	}

	float4 MoveDir = float4::ZERO;

	// 최초 시작방향결정
	if (0 == ProjectileCnt_)
	{
		// 플레이어를 바라보는 방향벡터를 -45도 회전시킨 방향벡터를 초기값으로 설정
		float4 Direct = (GlobalValue::CurPlayer->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition()).NormalizeReturn3D();
		Direct.RotateZDegree(-45.f);
		ProjectileStartDir_ = Direct;
		MoveDir = ProjectileStartDir_;
	}
	// 이동방향 결정
	else
	{
		// 시작방향벡터를 9도씩회전시켜서 발사체의 이동방향벡터를 계산한다.
		// 시장방향벡터 ~ 90도회전 이동방향벡터를 가진다.
		ProjectileStartDir_.RotateZDegree(9.f);
		MoveDir = ProjectileStartDir_;
	}

	// 발사체 생성(소멸시간 결정 - 5초)
	AndarielProjectile* NewProjectile = GetLevel()->CreateActor<AndarielProjectile>();
	NewProjectile->GetTransform()->SetWorldPosition(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y));
	NewProjectile->SkillAttackProjectile(static_cast<int>(CurDir_), MoveDir, MonsterInfo_.Damage);
	NewProjectile->Release(5.f);

	// 발사체 생성카운트 증가(총 10개 생성)
	++ProjectileCnt_;
}

void Andariel::DeathEffectStart()
{
	// 각 방향별 사망모션 3프레임에 호출되며 사망 이펙트를 생성
	// => 생성시 본체 불꽃, 이동불꽃, 카메라쉐이킹효과
	// => 본체불꽃 애니메이션종료시 이펙트 사망, 카메라쉐이킹중단, 보스 사망, 보스자리에 포탈생성(엔딩레벨이동용)
	AndarielDeathEffect* DeathEffect = GetLevel()->CreateActor<AndarielDeathEffect>();
	DeathEffect->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	DeathEffect->GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));
	DeathEffect->CreateDeathFire();
}

#pragma endregion

#pragma region 외부접근 강제상태전환
void Andariel::SpawnToDeath()
{
	// 스킬시전용으로 사용하려는 시체로 생성
	// => 스폰과 동시에 사망처리
	CurHP_ = 0;
	State_.ChangeState("Death");
}

void Andariel::GetHitDamage(int _Damage)
{
	CurHP_ -= _Damage;
	if (0 >= CurHP_)
	{
		CurHP_ = 0;
		State_.ChangeState("Death");
	}
	else
	{
		State_.ChangeState("GetHit");
	}
}

#pragma endregion

#pragma region 완전한 사망
void Andariel::PortalSpawnAfterDeath()
{
	// 내가 죽은자리에 포탈생성 후
	GameEngineLevel* NextLevel = GameEngineCore::LevelFind("EndingLevel");
	Portal* EndingPortal = GetLevel()->CreateActor<Portal>(static_cast<int>(UpdateOrder::OBJECT));
	EndingPortal->GetTransform()->SetWorldPosition(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y, 0.f));
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	EndingPortal->GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));
	EndingPortal->CreateLevelChangePortal(PortalType::TOWN, NextLevel);
	GlobalValue::Portal = EndingPortal;

	// 나는 죽는다.
	Death();

	// 전역 초기화
	GlobalValue::Andariel = nullptr;
}

#pragma endregion
