#include "PreCompile.h"
#include "Zombie.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

int Zombie::ZombieCnt = 0;

Zombie::Zombie() : 
	Zombie_(nullptr),
	BodyCollider_(nullptr),
	SpawnRoomNo_(-1),
	SpawnTile_(),
	IdleDelayTime_(1.f),
	NavigationIndex_(-1),
	MonsterInfo_(),
	CurHP_(0),
	MapHP_(0),
	DropGold_(0),
	State_(),
	PrevState_(Zombie_FSMState::ZB_ROOMDETECT),
	CurState_(Zombie_FSMState::ZB_ROOMDETECT),
	MoveTargetTile_(),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(50.f),
	PrevDir_(Zombie_TargetDir::ZB_B),
	CurDir_(Zombie_TargetDir::ZB_B),
	Attack_(false),
	StateSound_(nullptr),
	SpecialGetHit_(false),
	SpecialGetHitTime_(0.2f),
	CurDamageType_(MonsterDamageType::NONE)
{
	NavigationIndex_ = ZombieCnt;
	++ZombieCnt;
}

Zombie::~Zombie()
{
}

void Zombie::Start()
{
	// �ش� ���Ͱ��� �ʱ�ȭ
	InitZombie();
}

void Zombie::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(BodyCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// ���� ����
	State_.Update();

	if (true == SpecialGetHit_)
	{
		SpecialGetHitTime_ -= _DeltaTime;
		if (0.f >= SpecialGetHitTime_)
		{
			CurDamageType_ = MonsterDamageType::NONE;
			SpecialGetHit_ = false;
			Zombie_->SetResultColor(float4::ONE);
		}
	}

	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 38.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));

	// �浹ü ��ġ ����
	float4 MyPos = float4(GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y, 0.f);
	float4 CamPos = float4(GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().x, GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().y, 0.f);
	BodyCollider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	// �浹ó��(���콺�� �浹ó��)
	BodyCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&Zombie::MouseCollision, this, std::placeholders::_1));

	// ���ݻ����϶� Ÿ�ٰ� �浹���̶�� Ÿ�ٿ��� ���ظ� ����
	if (Zombie_FSMState::ZB_ATTACK == CurState_)
	{
		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Player), std::bind(&Zombie::EnemyCollision, this, std::placeholders::_1));
	}
}

#pragma region EnemyCheck List Function
// �� ���� üũ ����Ʈ
void Zombie::SetEnterTheRoomDetectList(int _SpawnRoomNo)
{
	// �������� �⺻���� ����
	SpawnRoomNo_ = _SpawnRoomNo;
	if (-1 != SpawnRoomNo_)
	{
		SpawnTile_ = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());

		// ���� ���� ������ ���� �ٴ�Ÿ�� ���� ��Ÿ���� ��� ���� ������� �ۼ�
		int RoomTileListCnt = static_cast<int>(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_.size());
		RoomTileList_.clear();
		for (int i = 0; i < RoomTileListCnt; ++i)
		{
			// �ٴ�Ÿ���� ��ġ Get
			float4 FloorCenterPos = GlobalValue::CatacombsMap->GetFloorTileIndexToPos(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_[i]);

			// �ٴ�Ÿ�� 1�� ���� 3x3�� ��Ÿ���� ������.
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

bool Zombie::EnterTheRoomDetectCheck()
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
void Zombie::AttackEnd()
{
	// ������ ��ȯ
	State_.ChangeState("Idle");
}

void Zombie::GetHitEnd()
{
	// �ƴ϶�� ������ ��ȯ
	State_.ChangeState("Idle");
}

void Zombie::DeathEnd()
{
	// ��ü���� ��ȯ
	State_.ChangeState("Dead");
}

#pragma endregion

#pragma region �ܺ����� ����������ȯ
void Zombie::SpawnToDeath()
{
	// ��ų���������� ����Ϸ��� ��ü�� ����
	// => ������ ���ÿ� ���ó��
	CurHP_ = 0;
	State_.ChangeState("Death");
}

void Zombie::HitDamage(int _Damage)
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

void Zombie::SpecialHitDamage(int _Damage, MonsterDamageType _DamageType)
{
	// �÷��̾� ��ȯ��(���̷���(������))�� �߻�ü�� ���� �ǰݽ� ȣ��
	CurDamageType_ = _DamageType;
	CurHP_ -= _Damage;
	if (0 >= CurHP_)
	{
		CurHP_ = 0;
		State_.ChangeState("Death");
	}
	else
	{
		if (false == SpecialGetHit_)
		{
			SpecialGetHit_ = true;
		}

		State_.ChangeState("GetHit");
	}
}

#pragma endregion
