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
	MonsterInfo_{},
	SpawnTile_(),
	SpawnRoomNo_(-1),
	NavigationIndex_(-1),
	Tainted_(nullptr),
	BodyCollider_(nullptr),
	State_(),
	PrevDir_(Tainted_Dir::TT_B),
	CurDir_(Tainted_Dir::TT_B),
	PrevState_(Tainted_FSMState::ST_IDLE),
	CurState_(Tainted_FSMState::ST_IDLE),
	IdleDelayTime_(1.5f),
	MoveTargetTile_(),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(200.f),
	TargetActor_(nullptr),
	TargetType_(),
	TargetCol_(false),
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
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 15.f);

	// 충돌체 위치 갱신
	float4 MyPos = GetTransform()->GetLocalPosition();
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	BodyCollider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	// 충돌처리(마우스와 충돌처리)
	BodyCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&Tainted::MouseCollision, this, std::placeholders::_1));

	// 사망상태 or 시체상태가 아닐때만 충돌체크
	if (CurState_ != Tainted_FSMState::ST_DEAD && CurState_ != Tainted_FSMState::ST_DEATH)
	{
		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Player), std::bind(&Tainted::EnemyCollision, this, std::placeholders::_1), std::bind(&Tainted::EnemyCollisionEnd, this, std::placeholders::_1));
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
