#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer.h"

#include "CatacombsMap.h"
#include "MonsterTopHPBar.h"

int Tainted::TaintedCnt = 0;

Tainted::Tainted() :
	EnemyCol_(false),
	MonsterInfo_{},
	SpawnTile_(),
	SpawnRoomNo_(-1),
	NavigationIndex_(-1),
	Tainted_(nullptr),
	BodyCollider_(nullptr),
	State_(),
	TargetPos_(float4::ZERO),
	CurPos_(float4::ZERO),
	MoveSpeed_(200.f),
	PrevDir_(Tainted_Dir::TT_B),
	CurDir_(Tainted_Dir::TT_B),
	RoomDetect_(false),
	PrevState_(Tainted_FSMState::ST_IDLE),
	CurState_(Tainted_FSMState::ST_IDLE),
	SkillDelayTime_(20.f),
	CurHP_(0),
	MapHP_(0),
	DropGold_(0)
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

	// Z Order 갱신
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 55.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 15.f);

	// 충돌체 위치 갱신
	float4 MyPos = GetTransform()->GetLocalPosition();
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	BodyCollider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	// 충돌처리
	BodyCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&Tainted::MouseCollision, this, std::placeholders::_1), std::bind(&Tainted::MouseCollisionEnd, this, std::placeholders::_1));

	if (CurState_ != Tainted_FSMState::ST_DEAD && CurState_ != Tainted_FSMState::ST_DEATH)
	{
		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Player), std::bind(&Tainted::EnemyCollision, this, std::placeholders::_1), std::bind(&Tainted::EnemyCollisionEnd, this, std::placeholders::_1));
	}
}

void Tainted::SetEnemyDetectionList(int _SpawnRoomNo)
{
	// 생성 기본정보 저장
	RoomDetectList_.clear();
	SpawnTile_ = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());
	SpawnRoomNo_ = _SpawnRoomNo;

	// 생성된 룸의 모든 벽타일 정보를 감지목록으로 작성
	int RoomTileListCnt = static_cast<int>(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_.size());
	for (int i = 0; i < RoomTileListCnt; ++i)
	{
		// 현재 바닥타일을 Get
		float4 FloorCenterPos = GlobalValue::CatacombsMap->GetFloorTileIndexToPos(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_[i]);

		// 바닥타일 1개기준 벽타일은 3x3개 생성
		TileIndex WallTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(FloorCenterPos);

		// 룸 모든 바닥타일기준의 벽타일목록을 생성
		// => 모든 벽타일목록이 적감지범위가 된다.
		for (int y = 0; y < 3; ++y)
		{
			for (int x = 0; x < 3; ++x)
			{
				RoomDetectList_.push_back(WallTileIndex);
				WallTileIndex.X_ += 1;
			}

			WallTileIndex.X_ = GlobalValue::CatacombsMap->GetWallTileIndex(FloorCenterPos).X_;
			WallTileIndex.Y_ += 1;
		}
	}
}

void Tainted::GetHitDamage(int _Damage)
{
	CurHP_ -= _Damage;
	if (0 >= CurHP_)
	{
		CurHP_ = 0;
		State_.ChangeState("Tainted_DEATH");
	}
	else
	{
		State_.ChangeState("Tainted_GETHIT");
	}
}

void Tainted::SpawnToDeath()
{
	// 스킬시전용으로 사용하려는 시체로 생성
	// => 스폰과 동시에 사망처리
	CurHP_ = 0;
	State_.ChangeState("Tainted_DEATH");
}
