#include "PreCompile.h"
#include "EditorRandomMap.h"

#include <GameEngine/GameEngineTileMapRenderer.h>

// Catacombs / ChaosSanctuary
LevelType EditorRandomMap::CurLevelType = LevelType::None;

bool EditorRandomMap::FirstRandomLoad_ = false;
std::vector<int> EditorRandomMap::IgnoreRange;
std::vector<std::vector<float4>> EditorRandomMap::RandomRange;
std::vector<std::vector<int>> EditorRandomMap::RandomReversRange;
std::vector<std::vector<int>> EditorRandomMap::RandomNextRange;

EditorRandomMap::EditorRandomMap() :
	SelectFloorTileIndex_(0),
	SelectWallTileIndex_(0),
	MapInfo_(),
	MapMinIndexX_(),
	MapMinIndexY_(),
	MapMaxIndexX_(),
	MapMaxIndexY_(),
	RoomCnt_(0),
	minIndexX_(0),
	minIndexY_(0),
	maxIndexX_(0),
	maxIndexY_(0)
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

void EditorRandomMap::RandomRoad(int _Count, bool _Multidirectional)
{
	if (false == _Multidirectional) // �ѹ��� ���� �ε�(��) ����
	{
		for (int i = 0; i < 4; i++)
		{
			if (i == IgnoreRange[0])
			{
				continue;
			}

			RandomNextRange[0].push_back(i);
		}

		int DirIndex = RandomNextRange[0][RoadRandom_.RandomInt(0, static_cast<int>(RandomNextRange[0].size()) - 1)];

		float4 Dir = RandomRange[0][DirIndex];

		for (size_t i = 0; i < _Count; i++)
		{
			SetFloorTile(TileIndex{ RandomStartPos_[0].ix(), RandomStartPos_[0].iy() }, 0);
			RandomStartPos_[0] += Dir;
		}

		IgnoreRange[0] = RandomReversRange[0][DirIndex];
		RandomNextRange[0].clear();
	}
	else // �ٹ��� ���� �ε�(��) ����
	{
		if (false == FirstRandomLoad_)
		{
			// ���� ���� Flag On
			FirstRandomLoad_ = true;

			// ���� �����Ǿ����Ƿ� �ִ� 4���� ���� �ε� ����
			for (int i = 0; i < 4; ++i)
			{
				RandomNextRange[i].push_back(i);
			}

			std::vector<int> DirIndex = { {-1}, {-1}, {-1}, {-1}, };
			std::vector<float4> Dir = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < _Count; ++j)
				{
					DirIndex[i] = RandomNextRange[i][RoadRandom_.RandomInt(0, static_cast<int>(RandomNextRange[i].size()) - 1)];
					Dir[i] = RandomRange[i][DirIndex[i]];
					SetFloorTile(TileIndex{ RandomStartPos_[i].ix(), RandomStartPos_[i].iy() }, SelectFloorTileIndex_);
					RandomStartPos_[i] += Dir[i];
				}
			}

			for (int i = 0; i < 4; ++i)
			{
				IgnoreRange[i] = RandomReversRange[i][DirIndex[i]];
				RandomNextRange[i].clear();
			}

			DirIndex.clear();
			Dir.clear();
		}
		else
		{
			// �ִ� 3���� ���� �ε� ����
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 3; j++)
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

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < _Count; ++j)
				{
					DirIndex[i] = RandomNextRange[i][RoadRandom_.RandomInt(0, static_cast<int>(RandomNextRange[i].size()) - 1)];
					Dir[i] = RandomRange[i][DirIndex[i]];
					SetFloorTile(TileIndex{ RandomStartPos_[i].ix(), RandomStartPos_[i].iy() }, SelectFloorTileIndex_);
					RandomStartPos_[i] += Dir[i];
				}
			}

			for (int i = 0; i < 4; ++i)
			{
				IgnoreRange[i] = RandomReversRange[i][DirIndex[i]];
				RandomNextRange[i].clear();
			}

			DirIndex.clear();
			Dir.clear();
		}
	}
}

void EditorRandomMap::TotalMapScale(int _MaxIndexX, int _MaxIndexY)
{
	// �ε����� �̿��Ͽ� ���� ���� ������ ���
	
	// ���� �ʹ��� �׸��� Clear
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsStartIter = MapMaxScale_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsEndIter = MapMaxScale_.end();
	for (; GridsStartIter != GridsEndIter; ++GridsStartIter)
	{
		// ������ ����ó��
		(*GridsStartIter).second->Death();
	}
	MapMaxScale_.clear();

	// �� ���� ����
	if (_MaxIndexX % 2 == 0)
	{
		MapInfo_.minIndexY_ = -(_MaxIndexX / 2);
		MapInfo_.maxIndexY_ = _MaxIndexX / 2;
	}
	else
	{
		MapInfo_.minIndexY_ = -(_MaxIndexX / 2);
		MapInfo_.maxIndexY_ = (_MaxIndexX / 2) + 1;
	}

	if (_MaxIndexY % 2 == 0)
	{
		MapInfo_.minIndexX_ = -(_MaxIndexY / 2);
		MapInfo_.maxIndexX_ = _MaxIndexY / 2;
	}
	else
	{
		MapInfo_.minIndexX_ = -(_MaxIndexY / 2);
		MapInfo_.maxIndexX_ = (_MaxIndexY / 2) + 1;
	}

	// ���� �� ������ �׸���� ������
	for (int y = MapInfo_.minIndexY_; y < MapInfo_.maxIndexY_; ++y)
	{
		for (int x = MapInfo_.minIndexX_; x < MapInfo_.maxIndexX_; ++x)
		{
			float4 Pos = float4::ZERO;
			Pos.x = (x - y) * TileSizeHalf_.x;
			Pos.y = (x + y) * -TileSizeHalf_.y;

			GameEngineTileMapRenderer* MapMaxRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
			MapMaxRenderer->SetImage("RandomMapGrid.png");
			MapMaxRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
			MapMaxRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
			MapMaxScale_.insert(std::make_pair(TileIndex(x, y).Index_, MapMaxRenderer));
		}
	}
}

void EditorRandomMap::RandomRoom(int _RoomCnt, int _WidthIndex, int _HeightIndex)
{
	// �����Ϸ��� �� ������ ���� ó��
	if (0 >= _RoomCnt)
	{
		// ����ڰ� ���ϴ� ������ �����
		CreateRoomManual(_WidthIndex, _HeightIndex);
	}
	else
	{
		// ������� �ѹ��� �������� ��� ���� ���� �� ��ġ
		RoomCnt_ = _RoomCnt;
		CreateRoomAuto(_WidthIndex, _HeightIndex);
	}
}

bool EditorRandomMap::RoomArrangeCheck(int _WidthIndex, int _HeightIndex)
{
	// �ʺ�/���� ���� ����(�ּ� ��ũ�� 2x2)
	int RandomWidth = RoomRandom_.RandomInt(2, _WidthIndex);
	int RandomHeight = RoomRandom_.RandomInt(2, _HeightIndex);

	// ���� �� ���� ������ ������ ��ġ�� ���� ���� ����
	int CenterIndexX = RoomRandom_.RandomInt(MapInfo_.minIndexX_, MapInfo_.maxIndexX_);
	int CenterIndexY = RoomRandom_.RandomInt(MapInfo_.minIndexY_, MapInfo_.maxIndexY_);

	// ���� ������ ���� �ε����� �������� �ʺ�/������ ���� ũ�Ⱑ ��ġ�������� �Ǵ�
	int RoomStartX = 0;
	int RoomEndX = 0;
	int RoomStartY = 0;
	int RoomEndY = 0;
	if (RandomWidth % 2 == 0)
	{
		RoomStartY = -(RandomWidth / 2);
		RoomEndY = RandomWidth / 2;
	}
	else
	{
		RoomStartY = -(RandomWidth / 2);
		RoomEndY = (RandomWidth / 2) + 1;
	}

	if (RandomHeight % 2 == 0)
	{
		RoomStartX = -(RandomHeight / 2);
		RoomEndX = RandomHeight / 2;
	}
	else
	{
		RoomStartX = -(RandomHeight / 2);
		RoomEndX = (RandomHeight / 2) + 1;
	}

	// ���� ������ ���Ǽ��� �����ε����� ��ȯ
	RoomStartX += CenterIndexX;
	RoomEndX += CenterIndexX;
	RoomStartY += CenterIndexY;
	RoomEndY += CenterIndexY;

	// ���� ������ ���ѵ� �������� �����ϴ� ���϶��� ����
	if (MapInfo_.minIndexX_ <= RoomStartX && MapInfo_.maxIndexX_ > RoomEndX &&
		MapInfo_.minIndexY_ <= RoomStartY && MapInfo_.maxIndexY_ > RoomEndY)
	{
		// ��ġ���ʰ� �����ϵ��� ���� ����
		int CurRoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
		for (int i = 0; i < CurRoomCnt; ++i)
		{
			// ���� ������ �������� �̿��Ͽ� �� �Ѱ��� ��ģ�ٸ� ����???
			//if (MapInfo_.RoomInfo_[i].minIndexX_ == RoomStartX && )
			//{
			//	return;
			//}
		}

		// �뿡 ���� ����
		RandomRoomInfo NewRoom = {};
		NewRoom.TileType_ = RandomMapTileType::ROOM;
		NewRoom.RoomNo_ = RoomCnt_ + 1;

		// ���� ������ ���� ����
		NewRoom.minIndexX_ = RoomStartX;
		NewRoom.maxIndexX_ = RoomEndX;
		NewRoom.minIndexY_ = RoomStartY;
		NewRoom.maxIndexY_ = RoomEndY;

		// ���� ������ ���� ����
		NewRoom.RoomCenterIndex_ = TileIndex(CenterIndexX, CenterIndexY);

		// ���� ������ ���� ũ��
		NewRoom.WidthIndex_ = RandomWidth;
		NewRoom.HeightIndex_ = RandomHeight;

		MapInfo_.RoomInfo_.push_back(NewRoom);

		return true;
	}

	return false;
}

void EditorRandomMap::CreateRoomAuto(int _WidthIndex, int _HeightIndex)
{
	int RoomCnt = RoomCnt_;
	while (0 < RoomCnt)
	{
		// �ڵ����� �� ������ŭ ����
		if(false == RoomArrangeCheck(_WidthIndex, _HeightIndex))
		{
			// �� ���� ���з� ����
			continue;
		}

		--RoomCnt;
	}

	// �ڵ����� ������ ���� ȭ�鿡 ������
	RenderingAutoRoom();
}

void EditorRandomMap::RenderingAutoRoom()
{
	// ���� �ѹ��� ������
	for (int i = 0; i < RoomCnt_; ++i)
	{
		RoomRender NewRoomRenderer = {};

		RandomRoomInfo CurRoomInfo = MapInfo_.RoomInfo_[i];
		for (int y = CurRoomInfo.minIndexY_; y < CurRoomInfo.maxIndexY_; ++y)
		{
			for (int x = CurRoomInfo.minIndexX_; x < CurRoomInfo.maxIndexX_; ++x)
			{
				float4 Pos = float4::ZERO;
				Pos.x = (x - y) * TileSizeHalf_.x;
				Pos.y = (x + y) * -TileSizeHalf_.y;

				GameEngineTileMapRenderer* NewRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
				NewRenderer->SetImage(FloorTileTextureName_);
				NewRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
				NewRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
				NewRenderer->GetTransform()->SetLocalZOrder(-10.f);
				NewRenderer->SetIndex(SelectFloorTileIndex_);
				NewRoomRenderer.TileRenderer_.insert(std::make_pair(TileIndex(x, y).Index_, NewRenderer));
			}
		}

		RoomRenderer_.push_back(NewRoomRenderer);
	}
}

void EditorRandomMap::CreateRoomManual(int _WidthIndex, int _HeightIndex)
{
	// ���۸��� �� ����

	// ���� �����Ǵ� ���� ���� ���� ���ѹ����� �����ϴ��� üũ
	if(false == RoomArrangeCheck(_WidthIndex, _HeightIndex))
	{
		// �� ���� ���з� ����
		return;
	}

	// ������ ���� ������ �̿��Ͽ� ȭ�鿡 ������
	RenderingManualRoom();

	// ������ �밹�� ����
	++RoomCnt_;
}

void EditorRandomMap::RenderingManualRoom()
{
	// �������� �̿��Ͽ� ȭ�鿡 ������
	RoomRender NewRoomRenderer = {};

	RandomRoomInfo CurRoomInfo = MapInfo_.RoomInfo_[RoomCnt_];
	for (int y = CurRoomInfo.minIndexY_; y < CurRoomInfo.maxIndexY_; ++y)
	{
		for (int x = CurRoomInfo.minIndexX_; x < CurRoomInfo.maxIndexX_; ++x)
		{
			float4 Pos = float4::ZERO;
			Pos.x = (x - y) * TileSizeHalf_.x;
			Pos.y = (x + y) * -TileSizeHalf_.y;

			GameEngineTileMapRenderer* NewRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
			NewRenderer->SetImage(FloorTileTextureName_);
			NewRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
			NewRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
			NewRenderer->GetTransform()->SetLocalZOrder(-10.f);
			NewRenderer->SetIndex(SelectFloorTileIndex_);
			NewRoomRenderer.TileRenderer_.insert(std::make_pair(TileIndex(x, y).Index_, NewRenderer));
		}
	}

	RoomRenderer_.push_back(NewRoomRenderer);
}

void EditorRandomMap::AllRoomClear()
{
	// ������ ����
	std::vector<RandomRoomInfo>::iterator StartIter = MapInfo_.RoomInfo_.begin();
	std::vector<RandomRoomInfo>::iterator EndIter = MapInfo_.RoomInfo_.end();
	for (; StartIter != EndIter;)
	{
		MapInfo_.RoomInfo_.erase(StartIter);
		StartIter = MapInfo_.RoomInfo_.begin();
		EndIter = MapInfo_.RoomInfo_.end();
	}
	MapInfo_.RoomInfo_.clear();

	// �� ������ ����
	for (int i = 0; i < static_cast<int>(RoomRenderer_.size()); ++i)
	{
		// ������ ����
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = RoomRenderer_[i].TileRenderer_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = RoomRenderer_[i].TileRenderer_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			// ������ ����ó��
			(*StartIter).second->Death();
		}
		RoomRenderer_[i].TileRenderer_.clear();
	}

	std::vector<RoomRender>::iterator RendererStartIter = RoomRenderer_.begin();
	std::vector<RoomRender>::iterator RendererEndIter = RoomRenderer_.end();
	for (; RendererStartIter != RendererEndIter;)
	{
		RoomRenderer_.erase(RendererStartIter);
		RendererStartIter = RoomRenderer_.begin();
		RendererEndIter = RoomRenderer_.end();
	}
	RoomRenderer_.clear();

	// �� ���� �ʱ�ȭ
	RoomCnt_ = 0;
}

void EditorRandomMap::RoomConnection()
{
	// ���� ����



}
