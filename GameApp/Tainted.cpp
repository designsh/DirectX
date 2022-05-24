#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

int Tainted::TaintedCnt = 0;

Tainted::Tainted() :
	MonsterInfo_{},
	SpawnTile_(),
	SpawnRoomNo_(-1),
	NavigationIndex_(-1),
	Tainted_(nullptr),
	BodyCollider_(nullptr),
	State_(),
	PrevDir_(Tainted_Dir::TT_B),
	CurDir_(Tainted_Dir::TT_B),
	PrevState_(Tainted_FSMState::TT_IDLE),
	CurState_(Tainted_FSMState::TT_IDLE),
	IdleDelayTime_(1.5f),
	MoveTargetTile_(),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(200.f),
	CurHP_(0),
	MapHP_(0),
	DropGold_(0),
	Attack_(false)
{
	NavigationIndex_ = TaintedCnt;
	++TaintedCnt;
}

Tainted::~Tainted()
{
}

void Tainted::Start()
{
	// Tainted 초기화
	InitTainted();
}

void Tainted::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(BodyCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// 상태 갱신
	State_.Update();

	// 충돌체 위치 갱신
	float4 MyPos = float4(GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y, 0.f);
	float4 CamPos = float4(GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().x, GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().y, 0.f);
	BodyCollider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	// 충돌처리(마우스와 충돌처리)
	BodyCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&Tainted::MouseCollision, this, std::placeholders::_1));

	// 공격상태일때 타겟과 충돌중이라면 타겟에게 피해를 입힘
	if (Tainted_FSMState::TT_ATTACK == CurState_)
	{
		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Player), std::bind(&Tainted::EnemyCollision, this, std::placeholders::_1));
	}
}

#pragma region EnemyCheck List Function
// 룸 진입 체크 리스트
void Tainted::SetEnterTheRoomDetectList(int _SpawnRoomNo)
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

bool Tainted::EnterTheRoomDetectCheck()
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
void Tainted::AttackEnd()
{
	// 대기상태 전환
	State_.ChangeState("Idle");
}

void Tainted::GetHitEnd()
{
	// 대기상태 전환
	State_.ChangeState("Idle");
}

void Tainted::DeathEnd()
{
	// 시체상태 전환
	State_.ChangeState("Dead");
}

#pragma endregion

#pragma region 외부접근 강제상태전환
void Tainted::SpawnToDeath()
{
	// 스킬시전용으로 사용하려는 시체로 생성
	// => 스폰과 동시에 사망처리
	CurHP_ = 0;
	State_.ChangeState("Death");
}

void Tainted::GetHitDamage(int _Damage)
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
