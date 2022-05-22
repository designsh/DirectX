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
	// Tainted �ʱ�ȭ
	InitTainted();
}

void Tainted::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(BodyCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// ���� ����
	State_.Update();

	// Z Order ����
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_) + 15.f);

	// �浹ü ��ġ ����
	float4 MyPos = GetTransform()->GetLocalPosition();
	float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
	BodyCollider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	// �浹ó��(���콺�� �浹ó��)
	BodyCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&Tainted::MouseCollision, this, std::placeholders::_1));

	// ������� or ��ü���°� �ƴҶ��� �浹üũ
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
	// ��ų���������� ����Ϸ��� ��ü�� ����
	// => ������ ���ÿ� ���ó��
	CurHP_ = 0;
	State_.ChangeState("Tainted_DEATH");
}
