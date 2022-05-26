#include "PreCompile.h"
#include "SpikeFiend.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

int SpikeFiend::SpikeFiendCnt = 0;

SpikeFiend::SpikeFiend() :
	SpikeFiend_(nullptr),
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
	PrevState_(SpikeFiend_FSMState::SF_ROOMDETECT),
	CurState_(SpikeFiend_FSMState::SF_ROOMDETECT),
	MoveTargetTile_(),
	MoveTargetDir_(float4::ZERO),
	MoveSpeed_(150.f),
	PrevDir_(SpikeFiend_TargetDir::SF_B),
	CurDir_(SpikeFiend_TargetDir::SF_B),
	Attack_(false),
	StateSound_(nullptr)
{
	NavigationIndex_ = SpikeFiendCnt;
	++SpikeFiendCnt;
}

SpikeFiend::~SpikeFiend()
{
}

void SpikeFiend::Start()
{
	// �ش� ���Ͱ��� �ʱ�ȭ
	InitSpikeFiend();
}

void SpikeFiend::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(BodyCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// ���� ����
	State_.Update();

	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 53.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));

	// �浹ü ��ġ ����
	float4 MyPos = float4(GetTransform()->GetLocalPosition().x, GetTransform()->GetLocalPosition().y, 0.f);
	float4 CamPos = float4(GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().x, GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition().y, 0.f);
	BodyCollider_->GetTransform()->SetWorldPosition(MyPos - CamPos);

	// �浹ó��(���콺�� �浹ó��)
	BodyCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SpikeFiend::MouseCollision, this, std::placeholders::_1));

	// ���ݻ����϶� Ÿ�ٰ� �浹���̶�� Ÿ�ٿ��� ���ظ� ����
	if (SpikeFiend_FSMState::SF_ATTACK == CurState_)
	{
		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Player), std::bind(&SpikeFiend::EnemyCollision, this, std::placeholders::_1));
	}
}

#pragma region EnemyCheck List Function
// �� ���� üũ ����Ʈ
void SpikeFiend::SetEnterTheRoomDetectList(int _SpawnRoomNo)
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

bool SpikeFiend::EnterTheRoomDetectCheck()
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
void SpikeFiend::AttackEnd()
{
	// ������ ��ȯ
	State_.ChangeState("Idle");
}

void SpikeFiend::GetHitEnd()
{
	// ������ ��ȯ
	State_.ChangeState("Idle");
}

void SpikeFiend::DeathEnd()
{
	// ��ü���� ��ȯ
	State_.ChangeState("Dead");
}

#pragma endregion

#pragma region �ܺ����� ����������ȯ
void SpikeFiend::SpawnToDeath()
{
	// ��ų���������� ����Ϸ��� ��ü�� ����
	// => ������ ���ÿ� ���ó��
	CurHP_ = 0;
	State_.ChangeState("Death");
}

void SpikeFiend::GetHitDamage(int _Damage)
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
