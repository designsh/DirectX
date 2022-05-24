#include "PreCompile.h"
#include "Fallen.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

int Fallen::FallenCnt = 0;

Fallen::Fallen() :
	Fallen_(nullptr),
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
	PrevState_(Fallen_FSMState::FL_ROOMDETECT),
	CurState_(Fallen_FSMState::FL_ROOMDETECT),
	MoveTargetTile_(),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(150.f),
	PrevDir_(Fallen_TargetDir::FL_B),
	CurDir_(Fallen_TargetDir::FL_B),
	Attack_(false)
{
	NavigationIndex_ = FallenCnt;
	++FallenCnt;
}

Fallen::~Fallen()
{
}

void Fallen::Start()
{
	// �ش� ���Ͱ��� �ʱ�ȭ
	InitFallen();
}

void Fallen::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(BodyCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// ���� ����
	State_.Update();

	// �浹ü ��ġ ����
	float4 MyPos = float4(GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y, 0.f);
	float4 CamPos = float4(GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().x, GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().y, 0.f);
	BodyCollider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	// �浹ó��(���콺�� �浹ó��)
	BodyCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&Fallen::MouseCollision, this, std::placeholders::_1));

	// ���ݻ����϶� Ÿ�ٰ� �浹���̶�� Ÿ�ٿ��� ���ظ� ����
	if (Fallen_FSMState::FL_ATTACK == CurState_)
	{
		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Player), std::bind(&Fallen::EnemyCollision, this, std::placeholders::_1));
	}
}

#pragma region EnemyCheck List Function
// �� ���� üũ ����Ʈ
void Fallen::SetEnterTheRoomDetectList(int _SpawnRoomNo)
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

bool Fallen::EnterTheRoomDetectCheck()
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
void Fallen::AttackEnd()
{
	// ������ ��ȯ
	State_.ChangeState("Idle");
}

void Fallen::GetHitEnd()
{
	// �ƴ϶�� ������ ��ȯ
	State_.ChangeState("Idle");
}

void Fallen::DeathEnd()
{
	// ��ü���� ��ȯ
	State_.ChangeState("Dead");
}

#pragma endregion

#pragma region �ܺ����� ����������ȯ
void Fallen::SpawnToDeath()
{
	// ��ų���������� ����Ϸ��� ��ü�� ����
	// => ������ ���ÿ� ���ó��
	CurHP_ = 0;
	State_.ChangeState("Death");
}

void Fallen::GetHitDamage(int _Damage)
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
