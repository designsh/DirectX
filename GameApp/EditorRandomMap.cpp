#include "PreCompile.h"
#include "EditorRandomMap.h"

#include <GameEngine/GameEngineTileMapRenderer.h>

// Catacombs / ChaosSanctuary
LevelType EditorRandomMap::CurLevelType = LevelType::None;

std::vector<int> EditorRandomMap::IgnoreRange;
std::vector<std::vector<float4>> EditorRandomMap::RandomRange;
std::vector<std::vector<int>> EditorRandomMap::RandomReversRange;
std::vector<std::vector<int>> EditorRandomMap::RandomNextRange;

EditorRandomMap::EditorRandomMap() :
	SelectFloorTileIndex_(0),
	SelectWallTileIndex_(0),
	MapInfo_()
{
}

EditorRandomMap::~EditorRandomMap()
{
}

void EditorRandomMap::Start()
{
	// Ÿ��
	TileSize_ = float4(160.f, 80.f);
	TileSizeHalf_ = TileSize_.halffloat4();
	TileSizeHHalf_ = TileSizeHalf_.halffloat4();

	// �ٴ�Ÿ��
	FloorTileImageSize_ = { 160.0f, 80.f };
	FloorTileImageSizeHalf_ = FloorTileImageSize_.halffloat4();
	FloorTileIndexPivotPos_ = { 0.0f, -TileSizeHalf_.y };

	RandomStartPos_.clear();
	RandomStartPos_ = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };

	IgnoreRange.resize(4);
	RandomNextRange.resize(4);
	RandomRange = { {float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN},
					{float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN},
					{float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN},
					{float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN}, };
	RandomReversRange = { {1, 0, 3, 2},
						  {1, 0, 3, 2},
						  {1, 0, 3, 2},
						  {1, 0, 3, 2}, };
}

void EditorRandomMap::CatacombsTextrueSetting()
{
	// īŸ�� �ؽ��ķ� ����
	FloorTileTextureName_ = "Catacombs_Floor.png";
	WallTileTextureName_ = "Catacombs_Wall.png";

	// ��Ÿ��
	WallTileImageSize_ = { 160.0f, 320.f };
	WallTileImageSizeHalf_ = WallTileImageSize_.halffloat4();
	WallTileIndexPivotPos_ = { 0.0f, TileSize_.y };

	// ���� ���õ� ���� Ÿ�� ����
	CurLevelType = LevelType::Catacombs;
}

void EditorRandomMap::ChaosSanctuaryTextrueSetting()
{
	// ī���� ���� �ؽ��ķ� ����
	FloorTileTextureName_ = "ChaosSanctuary_Floor.png";
	WallTileTextureName_ = "ChaosSanctuary_Wall.png";

	// ��Ÿ��
	WallTileImageSize_ = { 160.0f, 480.f };
	WallTileImageSizeHalf_ = WallTileImageSize_.halffloat4();
	WallTileIndexPivotPos_ = { 0.0f, TileSize_.y };

	// ���� ���õ� ���� Ÿ�� ����
	CurLevelType = LevelType::ChaosSanctuary;
}

TileIndex EditorRandomMap::GetFloorTileIndex(float4 _Pos)
{
	TileIndex Index = {};

	float RatioX = ((_Pos.x / TileSizeHalf_.x) - (_Pos.y / TileSizeHalf_.y)) / 2.0f;
	float RatioY = ((_Pos.y / TileSizeHalf_.y) + (_Pos.x / TileSizeHalf_.x)) / -2.0f;

	if (0 > RatioX)
	{
		RatioX += -1.f;
	}

	if (0 > RatioY)
	{
		RatioY += -1.f;
	}

	Index.X_ = static_cast<int>(RatioX);
	Index.Y_ = static_cast<int>(RatioY);

	return Index;
}

void EditorRandomMap::SetFloorTile(float4 _Pos, int CurTileIndex_)
{
	SetFloorTile(GetFloorTileIndex(_Pos), CurTileIndex_);
}

void EditorRandomMap::SetFloorTile(TileIndex _Index, int CurTileIndex_)
{
	if (FloorTiles_.end() != FloorTiles_.find(_Index.Index_))
	{
		FloorTiles_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);
		return;
	}

	float4 Pos = float4::ZERO;
	Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHalf_.x;
	Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHalf_.y;

	GameEngineTileMapRenderer* FloorTileRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
	FloorTileRenderer->SetImage(FloorTileTextureName_);
	FloorTileRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
	FloorTileRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
	FloorTileRenderer->SetIndex(CurTileIndex_);
	FloorTiles_.insert(std::make_pair(_Index.Index_, FloorTileRenderer));
}

void EditorRandomMap::SetWallTile(float4 _Pos, int CurTileIndex_)
{
	SetWallTile(GetWallTileIndex(_Pos), CurTileIndex_);
}

void EditorRandomMap::SetWallTile(TileIndex _Index, int CurTileIndex_)
{
	if (WallTiles_.end() != WallTiles_.find(_Index.Index_))
	{
		WallTiles_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);
		return;
	}

	float4 Pos = float4::ZERO;
	Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
	Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

	GameEngineTileMapRenderer* NewRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
	NewRenderer->SetImage(WallTileTextureName_);
	NewRenderer->GetTransform()->SetLocalScaling(WallTileImageSize_);
	NewRenderer->GetTransform()->SetLocalPosition(WallTileIndexPivotPos_ + Pos);
	NewRenderer->GetTransform()->SetLocalZOrder(-2.f);
	NewRenderer->SetIndex(CurTileIndex_);
	WallTiles_.insert(std::make_pair(_Index.Index_, NewRenderer));
}

TileIndex EditorRandomMap::GetWallTileIndex(float4 _Pos)
{
	TileIndex Index = {};

	float RatioX = ((_Pos.x / TileSizeHHalf_.x) - (_Pos.y / TileSizeHHalf_.y)) / 2.0f;
	float RatioY = ((_Pos.y / TileSizeHHalf_.y) + (_Pos.x / TileSizeHHalf_.x)) / -2.0f;

	if (0 > RatioX)
	{
		RatioX += -0.5f;
	}
	else
	{
		RatioX += 0.5f;
	}

	if (0 > RatioY)
	{
		RatioY += -0.5f;
	}
	else
	{
		RatioY += 0.5f;
	}

	Index.X_ = static_cast<int>(RatioX);
	Index.Y_ = static_cast<int>(RatioY);

	return Index;
}

float4 EditorRandomMap::GetFloorTileIndexToPos(TileIndex _TileIndex)
{
	float4 TilePos = float4::ZERO;
	TilePos.x = (_TileIndex.X_ - _TileIndex.Y_) * TileSize_.x;
	TilePos.y = (_TileIndex.X_ + _TileIndex.Y_) * -TileSize_.y;

	return TilePos;
}

float4 EditorRandomMap::GetWallTileIndexToPos(TileIndex _TileIndex)
{
	float4 TilePos = float4::ZERO;
	TilePos.x = (_TileIndex.X_ - _TileIndex.Y_) * TileSize_.halffloat4().halffloat4().x;
	TilePos.y = (_TileIndex.X_ + _TileIndex.Y_) * -TileSize_.halffloat4().halffloat4().y;

	return TilePos;
}

#pragma region ������� ������ ���� �Լ�

// 0. ���� Ŭ�������
void EditorRandomMap::AllClear()
{
	// ���� ���� �� ������ ����
	AllCorridorClear();

	// �� ���� �� ������ ����
	AllRoomClear();

	// ��/�� ���� �� ������ ����
	AllWallClear();
}

void EditorRandomMap::AllCorridorClear()
{
	// ������ �ٴ�Ÿ��

	// ���� ������ ����
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		TileIndex CurTile = MapInfo_.CorridorInfo_.AllIndexLists_[i];

		// �ش� Ÿ�� ����
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator DelTile = FloorTiles_.find(CurTile.Index_);
		if(FloorTiles_.end() != DelTile)
		{
			// ������ ���̰�
			(*DelTile).second->Death();

			// ��Ͽ��� ����
			FloorTiles_.erase(DelTile);
		}
	}

	// ���� ���� ����
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		MapInfo_.CorridorInfo_.AllIndexLists_.clear();
	}
	MapInfo_.CorridorInfo_ = {};

	// ������ġ �ʱ�ȭ
	RandomStartPos_ = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };
}

void EditorRandomMap::AllRoomClear()
{
	// ���� �ٴ�Ÿ��

	// �� ������ ����
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			TileIndex CurTile = MapInfo_.RoomInfo_[i].AllIndexLists_[j];

			// �ش� Ÿ�� ����
			std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator DelTile = FloorTiles_.find(CurTile.Index_);
			if (FloorTiles_.end() != DelTile)
			{
				// ������ ���̰�
				(*DelTile).second->Death();

				// ��Ͽ��� ����
				FloorTiles_.erase(DelTile);
			}
		}
	}

	// ������ ����
	MapInfo_.RoomInfo_.clear();
}

void EditorRandomMap::AllWallClear()
{
	// ��/���� ��Ÿ��

}

// 1. ���� ���� ����
void EditorRandomMap::CreateRandomCorridor(int _Create, int _Thickness, int _LenTileCount, int _DirCnt)
{
	// ���� ���� ����
	CreateRandomCorridorInfo(_Create, _Thickness, _LenTileCount, _DirCnt);

	// ���� ������ �̿��Ͽ� ȭ�鿡 ������
	CorridorRendering();
}

void EditorRandomMap::CreateRandomCorridorInfo(int _Create, int _Thickness, int _LenTileCount, int _DirCnt)
{
	// Ÿ��Ÿ�� ����(����)
	MapInfo_.CorridorInfo_.CorridorType_ = RandomMapTileType::CORRIDOR;

	// ���� ���� ����
	for (int k = 0; k < _Create; ++k) // �����ݺ�
	{
		for (int i = 0; i < _DirCnt; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (j == IgnoreRange[i])
				{
					continue;
				}

				RandomNextRange[i].push_back(j);
			}
		}

		std::vector<int> DirIndex = { {-1}, {-1}, {-1}, {-1}, };
		std::vector<float4> Dir = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };

		for (int i = 0; i < _DirCnt; i++)
		{
			DirIndex[i] = RandomNextRange[i][RoadRandom_.RandomInt(0, static_cast<int>(RandomNextRange[i].size()) - 1)];
			Dir[i] = RandomRange[i][DirIndex[i]];

			for (int j = 0; j < _LenTileCount; ++j)
			{
				for (int m = 0; m < _Thickness; ++m)
				{
					// ����1 : �̹� �����ϴ� Ÿ���� �߰������ʴ´�.
					if (Dir[i] == float4::UP || Dir[i] == float4::DOWN)
					{
						if (false == CorridorOverlapCheck(TileIndex{ RandomStartPos_[i].ix() + m, RandomStartPos_[i].iy() }))
						{
							MapInfo_.CorridorInfo_.AllIndexLists_.push_back(TileIndex{ RandomStartPos_[i].ix() + m, RandomStartPos_[i].iy() });
						}
					}
					else
					{
						if (false == CorridorOverlapCheck(TileIndex{ RandomStartPos_[i].ix(), RandomStartPos_[i].iy() + m }))
						{
							MapInfo_.CorridorInfo_.AllIndexLists_.push_back(TileIndex{ RandomStartPos_[i].ix(), RandomStartPos_[i].iy() + m });
						}
					}
				}

				RandomStartPos_[i] += Dir[i];
			}

		}

		for (int i = 0; i < _DirCnt; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				IgnoreRange[i] = RandomReversRange[i][DirIndex[j]];
				break;
			}

			RandomNextRange[i].clear();
		}

		DirIndex.clear();
		Dir.clear();
	}
}

bool EditorRandomMap::CorridorOverlapCheck(TileIndex _TileIndex)
{
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		if (MapInfo_.CorridorInfo_.AllIndexLists_[i] == _TileIndex)
		{
			return true;
		}
	}

	return false;
}

void EditorRandomMap::CorridorRendering()
{
	// ���� ������ �̿��Ͽ� ������
	// ��, ������ Ÿ���ε����� �����Ѵٸ� �ٽ� ������ ����
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		SetFloorTile(MapInfo_.CorridorInfo_.AllIndexLists_[i], SelectFloorTileIndex_);
	}
}

// 2. ������ �������� ������ ����
void EditorRandomMap::CreateRoomArrange(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex)
{
	// �� ��ġ ���� ����
	CreateRoomArrangeInfo(_RoomCount, _MaxWidthIndex, _MaxHeightIndex);

	// �� ��ġ������ �̿��Ͽ� ȭ�鿡 ������
	RoomRendering();
}

void EditorRandomMap::CreateRoomArrangeInfo(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex)
{
	// ���� ������ �̿��Ͽ� ���ġ
	GameEngineRandom RoomRandom;

	// 0. ��ġ�Ϸ��� �밹����ŭ �ݺ�
	int RoomCnt = 0;
	for (;;)
	{
		if (_RoomCount < RoomCnt)
		{
			break;
		}

		// 0. ����Ÿ�������� �̿��Ͽ� ���� �߽�Ÿ���� ����
		int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());

		// ����1: ���� �����ε����� ��ġ�� ��˻�
		TileIndex CenterTile = MapInfo_.CorridorInfo_.AllIndexLists_[RoomRandom.RandomInt(0, CorridorTileCnt) - 1];
		if (true == RoomOverlapCheck(CenterTile))
		{
			continue;
		}

		// 2. ���� �⺻���� ����
		RandomRoomInfo NewRoom = {};

		NewRoom.TileType_ = RandomMapTileType::ROOM;
		NewRoom.RoomNo_ = RoomCnt + 1;

		// 3. ���� ũ��� �������� ��������(�ּ� 3x3�� ��ũ�⸦ ������.
		int RandomWidthIndex = RoomRandom.RandomInt(3, _MaxWidthIndex);
		int RandomHeightIndex = RoomRandom.RandomInt(3, _MaxHeightIndex);
		NewRoom.WidthIndex_ = RandomWidthIndex;
		NewRoom.HeightIndex_ = RandomHeightIndex;

		// 4. ���� �߽� ����
		NewRoom.RoomCenterIndex_ = CenterTile;

		// 5. ���� �߽��� �������� ���� X,Y �ּ�/�ִ��ε����� ��� �� ����
		int RoomStartX = 0;
		int RoomEndX = 0;
		int RoomStartY = 0;
		int RoomEndY = 0;
		if (NewRoom.WidthIndex_ % 2 == 0)
		{
			RoomStartY = -(NewRoom.WidthIndex_ / 2);
			RoomEndY = NewRoom.WidthIndex_ / 2;
		}
		else
		{
			RoomStartY = -(NewRoom.WidthIndex_ / 2);
			RoomEndY = (NewRoom.WidthIndex_ / 2) + 1;
		}

		if (NewRoom.HeightIndex_ % 2 == 0)
		{
			RoomStartX = -(NewRoom.HeightIndex_ / 2);
			RoomEndX = NewRoom.HeightIndex_ / 2;
		}
		else
		{
			RoomStartX = -(NewRoom.HeightIndex_ / 2);
			RoomEndX = (NewRoom.HeightIndex_ / 2) + 1;
		}

		// 6. ���� ������ ���Ǽ��� �����ε����� ��ȯ
		RoomStartX += NewRoom.RoomCenterIndex_.X_;
		RoomEndX += NewRoom.RoomCenterIndex_.X_;
		RoomStartY += NewRoom.RoomCenterIndex_.Y_;
		RoomEndY += NewRoom.RoomCenterIndex_.Y_;

		NewRoom.minIndexX_ = RoomStartX;
		NewRoom.maxIndexX_ = RoomEndX;
		NewRoom.minIndexY_ = RoomStartY;
		NewRoom.maxIndexY_ = RoomEndY;

		// 7. ���� �����ϴ� ��� Ÿ���ε����� ����
		for (int y = NewRoom.minIndexY_; y < NewRoom.maxIndexY_; ++y)
		{
			for (int x = NewRoom.minIndexX_; x < NewRoom.maxIndexX_; ++x)
			{
				NewRoom.AllIndexLists_.push_back(TileIndex(x, y));
			}
		}

		MapInfo_.RoomInfo_.push_back(NewRoom);

		// 8. CurRoom Cnt ����
		++RoomCnt;
	}
}

bool EditorRandomMap::RoomOverlapCheck(TileIndex _CenterTile)
{
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		if (MapInfo_.RoomInfo_[i].RoomCenterIndex_ == _CenterTile)
		{
			return true;
		}
	}

	return false;
}

void EditorRandomMap::RoomRendering()
{
	// ������ �������� �̿��Ͽ� ȭ�鿡 ������
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			SetFloorTile(MapInfo_.RoomInfo_[i].AllIndexLists_[j], 13);
		}
	}
}

// 3. ����/�� ������ �̿��Ͽ� ��/�� ���� ����
void EditorRandomMap::CreateWall()
{
	// ��/�� ���� ����
	CreateWallInfo();

	// ��/�� ������ �̿��Ͽ� ȭ�鿡 ������
	WallRendering();
}

void EditorRandomMap::CreateWallInfo()
{
	// 1. ���� ���� ������ ����
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			TileIndex CurTileIndex = MapInfo_.RoomInfo_[i].AllIndexLists_[j];

			// �ٴ�Ÿ�� 1������ ��Ÿ���� 3x3�� ����
			


			RandomWallInfo NewWall = {};

			// ����1: �̹� �����ϴ� Ÿ���ε����� ��Ͽ� �߰������ʴ´�.
			if (true == WallOverlapCheck(CurTileIndex))
			{
				continue;
			}

			MapInfo_.WallInfo_.push_back(NewWall);
		}
	}
	
	// 2. ������ ������ ����
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		TileIndex CurTileIndex;

		
		RandomWallInfo NewWall = {};

		// ����1: �̹� �����ϴ� Ÿ���ε����� ��Ͽ� �߰������ʴ´�.
		if (true == WallOverlapCheck(CurTileIndex))
		{
			continue;
		}

		MapInfo_.WallInfo_.push_back(NewWall);
	}

	// 3. ���ǿ� ���� ���� �⺻Ÿ�԰� ��Ÿ���� �����Ѵ�.

}

bool EditorRandomMap::WallOverlapCheck(TileIndex _WallTileIndex)
{
	int WallCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallCnt; ++i)
	{
		if (MapInfo_.WallInfo_[i].WallTileIndex_ == _WallTileIndex)
		{
			return true;
		}
	}

	return false;
}

void EditorRandomMap::WallRendering()
{
	int WallCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallCnt; ++i)
	{
		SetWallTile(MapInfo_.WallInfo_[i].WallTileIndex_, SelectWallTileIndex_);
	}
}
#pragma endregion
