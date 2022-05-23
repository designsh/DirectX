#include "PreCompile.h"
#include "SpikeFiend.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "CatacombsMap.h"
#include "MainPlayer.h"
#include "MouseObject.h"

SpikeFiend::SpikeFiend() :
	SpikeFiend_(nullptr),
	BodyCollider_(nullptr),
	SpawnRoomNo_(-1),
	SpawnTile_(),
	MonsterInfo_(),
	CurHP_(0),
	MapHP_(0),
	DropGold_(0),
	State_(),
	PrevState_(SpikeFiend_FSMState::SF_ROOMDETECT),
	CurState_(SpikeFiend_FSMState::SF_ROOMDETECT),
	PrevDir_(SpikeFiend_TargetDir::SF_B),
	CurDir_(SpikeFiend_TargetDir::SF_B)
{
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
	State_.Update();
	// �浹üũ


	
	// �浹ü ��ġ ����



	// Z Order ����



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

	return false;
}

// �̵����� ���� üũ����Ʈ




// ���ݹ��� ���� üũ����Ʈ




#pragma endregion

#pragma region AnimationEnd Callback Function
void SpikeFiend::AttackEnd()
{
	// ������ �������� ������


	// ������ ��ȯ
	State_.ChangeState("Idle");
}

void SpikeFiend::GetHitEnd()
{
	// �ƴ϶�� ������ ��ȯ
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
