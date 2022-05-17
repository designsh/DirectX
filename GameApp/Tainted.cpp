#include "PreCompile.h"
#include "Tainted.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer.h"

#include "CatacombsMap.h"

int Tainted::TantedCnt = 0;

Tainted::Tainted() :
	MonsterInfo_{},
	SpawnTile_(),
	SpawnRoomNo_(-1),
	NavigationIndex_(-1),
	Tainted_(nullptr),
	BodyCollider_(nullptr),
	AttackCollider_(nullptr),
	State_(),
	TargetPos_(float4::ZERO),
	CurPos_(float4::ZERO),
	MoveSpeed_(200.f),
	PrevDir_(Tainted_Dir::TT_B),
	CurDir_(Tainted_Dir::TT_B),
	RoomDetect_(false),
	PrevState_(Tainted_FSMState::ST_IDLE),
	CurState_(Tainted_FSMState::ST_IDLE),
	SkillDelayTime_(20.f)
{
	NavigationIndex_ = TantedCnt;
	++TantedCnt;
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
	State_.Update();

	// Z Order ����
	TileIndex CurTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(float4(GetTransform()->GetWorldPosition().x, GetTransform()->GetWorldPosition().y - 55.f));
	GetTransform()->SetLocalZOrder(-static_cast<float>(CurTileIndex.X_ + CurTileIndex.Y_));
}

void Tainted::SetEnemyDetectionList(int _SpawnRoomNo)
{
	// ���� �⺻���� ����
	RoomDetectList_.clear();
	SpawnTile_ = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());
	SpawnRoomNo_ = _SpawnRoomNo;

	// ������ ���� ��� ��Ÿ�� ������ ����������� �ۼ�
	int RoomTileListCnt = static_cast<int>(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_.size());
	for (int i = 0; i < RoomTileListCnt; ++i)
	{
		// ���� �ٴ�Ÿ���� Get
		float4 FloorCenterPos = GlobalValue::CatacombsMap->GetFloorTileIndexToPos(GlobalValue::CatacombsMap->GetRandomMapInfo().RoomInfo_[SpawnRoomNo_ - 1].AllIndexLists_[i]);

		// �ٴ�Ÿ�� 1������ ��Ÿ���� 3x3�� ����
		TileIndex WallTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(FloorCenterPos);

		// �� ��� �ٴ�Ÿ�ϱ����� ��Ÿ�ϸ���� ����
		// => ��� ��Ÿ�ϸ���� ������������ �ȴ�.
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
