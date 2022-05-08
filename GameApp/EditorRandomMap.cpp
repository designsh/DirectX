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

bool EditorRandomMap::Compare(std::pair<int, float>& _First, std::pair<int, float>& _Second)
{
	return _First.second < _Second.second;
}

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

void EditorRandomMap::AllClear()
{
	// �����
	AllRoomClear();

	// ��������
	AllCorridorClear();

	// 

}

void EditorRandomMap::AllRoomClear()
{
	// ������ ����
	AllRoomInfomationClear();

	// �� ������ ����
	AllRoomRendererClear();

	// �� ���� �ʱ�ȭ
	RoomCnt_ = 0;
}

void EditorRandomMap::AllRoomInfomationClear()
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

	// �� ���� �ʱ�ȭ
	RoomCnt_ = 0;
}

void EditorRandomMap::AllRoomRendererClear()
{
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
}

void EditorRandomMap::RoomRenderClear(int _Index)
{
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = RoomRenderer_[_Index].TileRenderer_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = RoomRenderer_[_Index].TileRenderer_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// ������ ����ó��
		(*StartIter).second->Death();
	}
	RoomRenderer_[_Index].TileRenderer_.clear();

	std::vector<RoomRender>::iterator RendererStartIter = RoomRenderer_.begin() + _Index;
	RoomRenderer_.erase(RendererStartIter);
}

void EditorRandomMap::AllCorridorClear()
{
	// �������� ����
	AllCorridorInfomationClear();

	// ���� ������ ����
	AllCorridorRendererClear();
}

void EditorRandomMap::AllCorridorInfomationClear()
{
	// �������� ����
	std::vector<RandomCorridorInfo>::iterator StartIter = MapInfo_.CorridorInfo_.begin();
	std::vector<RandomCorridorInfo>::iterator EndIter = MapInfo_.CorridorInfo_.end();
	for (; StartIter != EndIter;)
	{
		MapInfo_.CorridorInfo_.erase(StartIter);
		StartIter = MapInfo_.CorridorInfo_.begin();
		EndIter = MapInfo_.CorridorInfo_.end();
	}
	MapInfo_.CorridorInfo_.clear();
}

void EditorRandomMap::AllCorridorRendererClear()
{
	// ���� ������ ����
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = CorridorRenderer_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = CorridorRenderer_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// ������ ����ó��
		(*StartIter).second->Death();
	}
	CorridorRenderer_.clear();
}

void EditorRandomMap::TotalMapRendererClear()
{
	// �ӽ��ּ�
	//std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsStartIter = MapMaxScale_.begin();
	//std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsEndIter = MapMaxScale_.end();
	//for (; GridsStartIter != GridsEndIter; ++GridsStartIter)
	//{
	//	// ������ ����ó��
	//	(*GridsStartIter).second->Death();
	//}
	//MapMaxScale_.clear();
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

bool EditorRandomMap::RoomArrangeCheck(int _WidthIndex, int _HeightIndex, int _RoomCnt)
{
	// �ʺ�/���� ���� ����(�ּ� ��ũ�� 3x3)
	int RandomWidth = RoomRandom_.RandomInt(6, _WidthIndex);
	int RandomHeight = RoomRandom_.RandomInt(6, _HeightIndex);

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
		// �뿡 ���� ����
		RandomRoomInfo NewRoom = {};
		NewRoom.TileType_ = RandomMapTileType::ROOM;
		NewRoom.RoomNo_ = _RoomCnt + 1;

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

		// ���� ������ ���� ��� Ÿ���ε��� ����
		for (int y = NewRoom.minIndexY_; y < NewRoom.maxIndexY_; ++y)
		{
			for (int x = NewRoom.minIndexX_; x < NewRoom.maxIndexX_; ++x)
			{
				TileIndex CurTile = TileIndex(x, y);
				NewRoom.AllIndexLists_.push_back(CurTile);
			}
		}

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
		if(false == RoomArrangeCheck(_WidthIndex, _HeightIndex, RoomCnt_ - RoomCnt))
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
	for (int i = 0; i < static_cast<int>(MapInfo_.RoomInfo_.size()); ++i)
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

				if (TileIndex(x, y) == CurRoomInfo.RoomCenterIndex_)
				{
					NewRenderer->SetImage("FloorGrid_Center.png");
					NewRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
					NewRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
					NewRenderer->GetTransform()->SetLocalZOrder(-10.f);
					NewRenderer->SetIndex(0);
				}
				else
				{
					NewRenderer->SetImage(FloorTileTextureName_);
					NewRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
					NewRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
					NewRenderer->GetTransform()->SetLocalZOrder(-10.f);
					NewRenderer->SetIndex(SelectFloorTileIndex_);
				}
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
	if(false == RoomArrangeCheck(_WidthIndex, _HeightIndex, RoomCnt_))
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

void EditorRandomMap::RoomPushOut()
{
	// ���� �� ������ ��� ����
	AllRoomRendererClear();

	// ���� ������ ���������� �˻��Ͽ� ���� ���� ��ġ�� ���� ���� �о�� ó��
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		// �� �Ѱ� ����
		RandomRoomInfo CurRoomInfo = MapInfo_.RoomInfo_[i];

		// �� �̵����� ����
#pragma region �̵��������
		float4 TileMoveDir = float4::ZERO;
		GameEngineRandom RandomDir;
		int Dir = RandomDir.RandomInt(0, 7);
		switch (Dir)
		{
			case 0: // TOP
			{
				TileMoveDir = float4(-1, -1);
				break;
			}
			case 1: // RIGHT TOP
			{
				TileMoveDir = float4(0, -1);
				break;
			}
			case 2: // RIGHT
			{
				TileMoveDir = float4(1, -1);
				break;
			}
			case 3: // RIGHT BOTTOM
			{
				TileMoveDir = float4(1, 0);
				break;
			}
			case 4: // BOTTOM
			{
				TileMoveDir = float4(1, 1);
				break;
			}
			case 5: // LEFT BOTTOM
			{
				TileMoveDir = float4(0, 1);
				break;
			}
			case 6: // LEFT
			{
				TileMoveDir = float4(-1, 1);
				break;
			}
			case 7: // LEFT TOP
			{
				TileMoveDir = float4(-1, 0);
				break;
			}
		}

		TileMoveDir *= 4.f;
#pragma endregion

		// ��� ���� �˻��Ͽ� ���������ʴ°����� �̵�
		if (true == RoomIntersectsMoveCheck(i, TileMoveDir))
		{
		}
	}

	// ���ġ ������ ��� �Ϸ�� ��ü�� ���� ������ ����
	TotalMapRendererClear();

	// ���� �˻簡 ����� ��� �� ������
	RenderingAutoRoom();
}

bool EditorRandomMap::RoomIntersectsMoveCheck(int _CurIndex, float4 _Dir)
{
	bool MoveChkFlag = false;
	int StandardRoomTileListsCnt = static_cast<int>(MapInfo_.RoomInfo_[_CurIndex].AllIndexLists_.size());
	while (true)
	{
		// ������ ������ ��� ��� ���������� üũ
		// �Ѱ��� ���̶� �������ٸ� ����Ͽ� �̵�
		int AllRoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
		for (int k = 0; k < AllRoomCnt; ++k)
		{
			MoveChkFlag = false;

			// ���� �� ����
			if (MapInfo_.RoomInfo_[_CurIndex].RoomNo_ == MapInfo_.RoomInfo_[k].RoomNo_)
			{
				continue;
			}

			// ���η��� �ƴѵ��� ���� �����ִٸ� �̵�
			int CompareRoomTileListsCnt = static_cast<int>(MapInfo_.RoomInfo_[k].AllIndexLists_.size());
			for (int i = 0; i < StandardRoomTileListsCnt; ++i)
			{
				for (int j = 0; j < CompareRoomTileListsCnt; ++j)
				{
					// ���� ���� �̵����⿡ ���� 
					if (MapInfo_.RoomInfo_[_CurIndex].AllIndexLists_[i].X_ == MapInfo_.RoomInfo_[k].AllIndexLists_[j].X_ + _Dir.ix() &&
						MapInfo_.RoomInfo_[_CurIndex].AllIndexLists_[i].Y_ == MapInfo_.RoomInfo_[k].AllIndexLists_[j].Y_ + _Dir.iy())
					{
						MoveChkFlag = true;

						// Ÿ���� 2ĭ�� �̵�
						MapInfo_.RoomInfo_[_CurIndex].minIndexX_ += _Dir.ix();
						MapInfo_.RoomInfo_[_CurIndex].maxIndexX_ += _Dir.ix();
						MapInfo_.RoomInfo_[_CurIndex].minIndexY_ += _Dir.iy();
						MapInfo_.RoomInfo_[_CurIndex].maxIndexY_ += _Dir.iy();

						// ���� ���� ������ġ �缳��
						MapInfo_.RoomInfo_[_CurIndex].RoomCenterIndex_ = MapInfo_.RoomInfo_[_CurIndex].RoomCenterIndex_ + TileIndex(_Dir.ix(), _Dir.iy());

						// ���� Ÿ���� �ε��� ���� ����
						MapInfo_.RoomInfo_[_CurIndex].AllIndexLists_.clear();
						for (int y = MapInfo_.RoomInfo_[_CurIndex].minIndexY_; y < MapInfo_.RoomInfo_[_CurIndex].maxIndexY_; ++y)
						{
							for (int x = MapInfo_.RoomInfo_[_CurIndex].minIndexX_; x < MapInfo_.RoomInfo_[_CurIndex].maxIndexX_; ++x)
							{
								MapInfo_.RoomInfo_[_CurIndex].AllIndexLists_.push_back(TileIndex(x, y));
							}
						}
					}
				}
			}

			if (true == MoveChkFlag)
			{
				break;
			}
		}

		if (false == MoveChkFlag)
		{
			return true;
		}
	}

	return false;
}

void EditorRandomMap::RoomDistanceMeasurement()
{
	// �� �뿡���� �ٸ� ����� �Ÿ� ����� ����
	int RoomCount = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCount; ++i)
	{
		// ���� ������ ��� ���� �ָ��ִ� ���� No�� ����
		SearchRoomDistance(i);
	}

	// ��� ���� �Ÿ������ �̿��Ͽ� ������� ������� ���� �ָ��������ִ� ���� ã�Ƴ��� ����
	for (int i = 0; i < RoomCount; ++i)
	{
		// ���� üũ�ϴ� �� Get
		RandomRoomInfo CurCheckRoom = MapInfo_.RoomInfo_[i];

		// ���ᰡ���� ��� ���� Ž�� �� ������, ����ָ� �ִ� �� ����


		






		// 220509 SJH �ӽÿ�
		// ���ĵǾ����Ƿ� ������ 0��°�� ���� ������ ��
		MapInfo_.RoomInfo_[i].AdjacentRoomNo_ = CurCheckRoom.AllRoomDistList_[0].first;

		// ��������°�� ���� �ָ��ִ� ��
		int VectorSize = static_cast<int>(CurCheckRoom.AllRoomDistList_.size());
		if (0 != VectorSize)
		{
			MapInfo_.RoomInfo_[i].NotadjacentRoomNo_ = CurCheckRoom.AllRoomDistList_[VectorSize - 1].first;
		}



		int a = 0;
	}
}

void EditorRandomMap::SearchRoomDistance(int _CheckIndex)
{
	std::map<int, float> RoomDistanceMap;
	float4 CurRoomPos = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[_CheckIndex].RoomCenterIndex_);
	int RoomCount = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCount; ++i)
	{
		// ���� �� ����
		if (MapInfo_.RoomInfo_[_CheckIndex].RoomNo_ == MapInfo_.RoomInfo_[i].RoomNo_)
		{
			continue;
		}

		// ��� ����� �Ÿ� ����(�� ���� �����ε��� ����)
		float4 CheckRoomPos = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[i].RoomCenterIndex_);

		// ���� �ε����� ��ġ�� ���� �Ÿ�üũ�ϴ� �ε����� �Ÿ��� ���
		// => �� ���ͻ����� �Ÿ����� �� ��Ͽ� ����
		float Length = float4::Distance(CurRoomPos, CheckRoomPos);
		RoomDistanceMap.insert(std::make_pair(MapInfo_.RoomInfo_[i].RoomNo_, Length));
	}

	// ���ȣ�� ������ �ۼ��� ����� �Ÿ��� �̿��Ͽ� ������
	std::vector<std::pair<int, float>> ReSortVector(RoomDistanceMap.begin(), RoomDistanceMap.end());
	std::sort(ReSortVector.begin(), ReSortVector.end(), EditorRandomMap::Compare);

	// ���� üũ�ϴ� ��� ������ ��� ����� �Ÿ��� �����Ͽ� ��� ����
	MapInfo_.RoomInfo_[_CheckIndex].AllRoomDistList_ = ReSortVector;
}

void EditorRandomMap::RoomConnection()
{
	// �뼾��-�뼾�� ���� ����
	// ���� �����ε��������� �̿��Ͽ� ������� ���͸� �����ϴ� ���� ����
	int RoomCount = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCount; ++i)
	{
		// �� ����
		RandomRoomInfo CurRoomInfo = MapInfo_.RoomInfo_[i];

		// ��(��)�� ���� ������ ���� �˰��ֱ� ������ ���� ������ ��� ������ �ϰ�,
		// ����� ���� ��ȣ�� ���(ConnectionRoomList_)�� �����Ѵ�.
		if (0 < CurRoomInfo.AdjacentRoomNo_)
		{
			RoomConnectionStart(CurRoomInfo.RoomNo_ - 1, CurRoomInfo.AdjacentRoomNo_ - 1);
		}
	}

	// ���� ������ ��� ���� ������
	AllCorridorRendering();
}

void EditorRandomMap::RoomConnectionStart(int _CurIndex, int _ConnectionIndex)
{
	// ���� �����Ϸ��� ��� �̹� ����Ǿ��ִ��� üũ
	int ConnectionRoomCnt = static_cast<int>(MapInfo_.RoomInfo_[_ConnectionIndex].ConnectionRoomList_.size());
	for (int i = 0; i < ConnectionRoomCnt; ++i)
	{
		// �̹� ����Ǿ��ִٸ� ����
		if (MapInfo_.RoomInfo_[_ConnectionIndex].ConnectionRoomList_[i] == MapInfo_.RoomInfo_[_CurIndex].RoomNo_)
		{
			return;
		}
	}

	// �����Ϸ��� ���� ��ġ������ ���� �뿡�� ������ ���� ������ ����
	ConnectRoomDir(_CurIndex, _ConnectionIndex);

	// ���� ���� ���� �Ϸ�Ǿ����Ƿ� ����뿡�� �����Ϸ��� ���� ���ͱ��� �������
	SetCorridorTile(_CurIndex, _ConnectionIndex);
}

void EditorRandomMap::ConnectRoomDir(int _CurIndex, int _ConnectionIndex)
{
	float4 CurRoomCenter = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[_CurIndex].RoomCenterIndex_);
	float4 ConnectionRoomCenter = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_);
	float4 Dir = (ConnectionRoomCenter - CurRoomCenter).NormalizeReturn3D();

	// 1. �»��
	if (Dir.x < 0.f && Dir.y >= 0.f)
	{
		MapInfo_.RoomInfo_[_CurIndex].CenterType_ = RoomCenterDirType::DIRTC_T;
	}
	// 2. ����
	else if (Dir.x >= 0.f && Dir.y >= 0.f)
	{
		MapInfo_.RoomInfo_[_CurIndex].CenterType_ = RoomCenterDirType::DIRTC_R;
	}
	// 3. ���ϴ�
	else if (Dir.x >= 0.f && Dir.y < 0.f)
	{
		MapInfo_.RoomInfo_[_CurIndex].CenterType_ = RoomCenterDirType::DIRTC_B;
	}
	// 4. ���ϴ�
	else if (Dir.x < 0.f && Dir.y < 0.f)
	{
		MapInfo_.RoomInfo_[_CurIndex].CenterType_ = RoomCenterDirType::DIRTC_L;
	}
}

void EditorRandomMap::SetCorridorTile(int _CurIndex, int _ConnectionIndex)
{
	RandomCorridorInfo NewCorridorInfo = {};

	NewCorridorInfo.CorridorType_ = RandomMapTileType::CORRIDOR;
	RoomCenterDirType CenterType = MapInfo_.RoomInfo_[_CurIndex].CenterType_;

	TileIndex CorridorTileIndex = MapInfo_.RoomInfo_[_CurIndex].RoomCenterIndex_;
	switch (CenterType)
	{
		case RoomCenterDirType::DIRTC_T:
		{
			while (true)
			{
				// 1. x�ε��� ����(��ǥŸ�� �ε�������), y�ε��� ������� ���� �ε����� ����
				if (CorridorTileIndex.X_ != MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.X_)
				{
					CorridorTileIndex.X_ -= 1;

					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. ��� �Ϸ�Ǿ��ٸ� ����� ������ 2�ٷ� �����


						// 4. �Ϸ�� ���� ���� ��� ����
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// Ÿ�� ���� ����
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
				// 2. ��ǥŸ�� ��ġ���� x�ε����� ��� �����Ͽ��ٸ� y�ε����� ��ǥ �ε������� �̵�
				else
				{
					// ��ǥŸ���ε������� �����ϴµ� �����ؾ��ϴ��� �����ؾ��ϴ��� �Ǵ�
					if (CorridorTileIndex.Y_ < MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.Y_)
					{
						// y �ε��� ����
						CorridorTileIndex.Y_ += 1;
					}
					else
					{
						// y�ε��� ����
						CorridorTileIndex.Y_ -= 1;
					}

					// ���� ������ ����Ÿ���� �ε����� ��ǥŸ���ε����� �����ϸ� �ݺ��� �ߴ�
					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. ��� �Ϸ�Ǿ��ٸ� ����� ������ 2�ٷ� �����


						// 4. �Ϸ�� ���� ���� ��� ����
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// Ÿ�� ���� ����
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
			}
			break;
		}
		case RoomCenterDirType::DIRTC_B:
		{
			while (true)
			{
				// 1. x�ε��� ����(��ǥŸ�� �ε�������), y�ε��� ������� ���� �ε����� ����
				if (CorridorTileIndex.X_ != MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.X_)
				{
					CorridorTileIndex.X_ += 1;

					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. ��� �Ϸ�Ǿ��ٸ� ����� ������ 2�ٷ� �����


						// 4. �Ϸ�� ���� ���� ��� ����
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// Ÿ�� ���� ����
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
				// 2. ��ǥŸ�� ��ġ���� x�ε����� ��� �����Ͽ��ٸ� y�ε����� ��ǥ �ε������� �̵�
				else
				{
					// ��ǥŸ���ε������� �����ϴµ� �����ؾ��ϴ��� �����ؾ��ϴ��� �Ǵ�
					if (CorridorTileIndex.Y_ < MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.Y_)
					{
						// y �ε��� ����
						CorridorTileIndex.Y_ += 1;
					}
					else
					{
						// y�ε��� ����
						CorridorTileIndex.Y_ -= 1;
					}

					// ���� ������ ����Ÿ���� �ε����� ��ǥŸ���ε����� �����ϸ� �ݺ��� �ߴ�
					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. ��� �Ϸ�Ǿ��ٸ� ����� ������ 2�ٷ� �����


						// 4. �Ϸ�� ���� ���� ��� ����
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// Ÿ�� ���� ����
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
			}
			break;
		}
		case RoomCenterDirType::DIRTC_L:
		{
			while (true)
			{
				// 1. y�ε��� ����(��ǥŸ�� �ε�������), x�ε��� ������� ���� �ε����� ����
				if (CorridorTileIndex.Y_ != MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.Y_)
				{
					CorridorTileIndex.Y_ += 1;

					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. ��� �Ϸ�Ǿ��ٸ� ����� ������ 2�ٷ� �����


						// 4. �Ϸ�� ���� ���� ��� ����
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// Ÿ�� ���� ����
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
				// 2. ��ǥŸ�� ��ġ���� y�ε����� ��� �����Ͽ��ٸ� x�ε����� ��ǥ �ε������� �̵�
				else
				{
					// ��ǥŸ���ε������� �����ϴµ� �����ؾ��ϴ��� �����ؾ��ϴ��� �Ǵ�
					if (CorridorTileIndex.X_ < MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.X_)
					{
						// y �ε��� ����
						CorridorTileIndex.X_ += 1;
					}
					else
					{
						// y�ε��� ����
						CorridorTileIndex.X_ -= 1;
					}

					// ���� ������ ����Ÿ���� �ε����� ��ǥŸ���ε����� �����ϸ� �ݺ��� �ߴ�
					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. ��� �Ϸ�Ǿ��ٸ� ����� ������ 2�ٷ� �����


						// 4. �Ϸ�� ���� ���� ��� ����
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// Ÿ�� ���� ����
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
			}
			break;
		}
		case RoomCenterDirType::DIRTC_R:
		{
			while (true)
			{
				// 1. y�ε��� ����(��ǥŸ�� �ε�������), x�ε��� ������� ���� �ε����� ����
				if (CorridorTileIndex.Y_ != MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.Y_)
				{
					CorridorTileIndex.Y_ -= 1;

					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. ��� �Ϸ�Ǿ��ٸ� ����� ������ 2�ٷ� �����


						// 4. �Ϸ�� ���� ���� ��� ����
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// Ÿ�� ���� ����
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
				// 2. ��ǥŸ�� ��ġ���� y�ε����� ��� �����Ͽ��ٸ� x�ε����� ��ǥ �ε������� �̵�
				else
				{
					// ��ǥŸ���ε������� �����ϴµ� �����ؾ��ϴ��� �����ؾ��ϴ��� �Ǵ�
					if (CorridorTileIndex.X_ < MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.X_)
					{
						// y �ε��� ����
						CorridorTileIndex.X_ += 1;
					}
					else
					{
						// y�ε��� ����
						CorridorTileIndex.X_ -= 1;
					}

					// ���� ������ ����Ÿ���� �ε����� ��ǥŸ���ε����� �����ϸ� �ݺ��� �ߴ�
					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. ��� �Ϸ�Ǿ��ٸ� ����� ������ 2�ٷ� �����


						// 4. �Ϸ�� ���� ���� ��� ����
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// Ÿ�� ���� ����
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
			}
			break;
		}
	}

	// ���� �Ϸ�Ǿ��ٸ� ����� ���� ��ȣ�� ���(ConnectionRoomList_)�� ����
	MapInfo_.RoomInfo_[_CurIndex].ConnectionRoomList_.push_back(MapInfo_.RoomInfo_[_ConnectionIndex].RoomNo_);
}

void EditorRandomMap::CorridorRendering(int _Index)
{
	// ���� ������
	int TileIndexCnt = static_cast<int>(MapInfo_.CorridorInfo_[_Index].AllIndexLists_.size());
	for (int i = 0; i < TileIndexCnt; ++i)
	{
		TileIndex Index = MapInfo_.CorridorInfo_[_Index].AllIndexLists_[i];

		// ��ġ�� Ÿ���ε����� �����ϸ� ������ ����
		if (CorridorRenderer_.end() != CorridorRenderer_.find(Index.Index_))
		{
			continue;
		}

		float4 Pos = float4::ZERO;
		Pos.x = (Index.X_ - Index.Y_) * TileSizeHalf_.x;
		Pos.y = (Index.X_ + Index.Y_) * -TileSizeHalf_.y;

		GameEngineTileMapRenderer* NewRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
		NewRenderer->SetImage(FloorTileTextureName_);
		NewRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
		NewRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
		NewRenderer->GetTransform()->SetLocalZOrder(-13.f);
		NewRenderer->SetIndex(3);
		CorridorRenderer_.insert(std::make_pair(Index.Index_, NewRenderer));
	}
}

void EditorRandomMap::AllCorridorRendering()
{
	int CorridorCnt = static_cast<int>(MapInfo_.CorridorInfo_.size());
	for (int i = 0; i < CorridorCnt; ++i)
	{
		int TileIndexCnt = static_cast<int>(MapInfo_.CorridorInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < TileIndexCnt; ++j)
		{
			TileIndex Index = MapInfo_.CorridorInfo_[i].AllIndexLists_[j];

			// ��ġ�� Ÿ���ε����� �����ϸ� ������ ����
			if (CorridorRenderer_.end() != CorridorRenderer_.find(Index.Index_))
			{
				continue;
			}

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * TileSizeHalf_.x;
			Pos.y = (Index.X_ + Index.Y_) * -TileSizeHalf_.y;

			GameEngineTileMapRenderer* NewRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
			NewRenderer->SetImage(FloorTileTextureName_);
			NewRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
			NewRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
			NewRenderer->GetTransform()->SetLocalZOrder(-13.f);
			NewRenderer->SetIndex(3);
			CorridorRenderer_.insert(std::make_pair(Index.Index_, NewRenderer));
		}
	}
}

void EditorRandomMap::CreateWall()
{
	// ��/���� ������ ����


}

void EditorRandomMap::CreateDoor()
{
	// ��-����-�� �������� ������ ����


}
