#include "PreCompile.h"
#include "EditorRandomMap.h"

#include <GameEngine/GameEngineTileMapRenderer.h>

// Catacombs / ChaosSanctuary
LevelType EditorRandomMap::CurLevelType = LevelType::None;

std::vector<int> EditorRandomMap::IgnoreRange;
std::vector<std::vector<float4>> EditorRandomMap::RandomRange;
std::vector<std::vector<int>> EditorRandomMap::RandomReversRange;
std::vector<std::vector<int>> EditorRandomMap::RandomNextRange;

bool EditorRandomMap::Compare(std::pair<int, float>& _First, std::pair<int, float>& _Second)
{
	return _First.second < _Second.second;
}

EditorRandomMap::EditorRandomMap() :
	FloorGridesActive_(true),
	WallGridesActive_(true),
	SelectFloorTileIndex_(0),
	SelectWallTile1Index_(0),
	SelectWallTile2Index_(0),
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

	// ��Ÿ��
	WallTileImageSize_ = { 160.0f, 320.f };
	WallTileImageSizeHalf_ = WallTileImageSize_.halffloat4();
	WallTileIndexPivotPos_ = { 0.0f, TileSize_.y };

	// ���� ���� �������� �ʱ�ȭ
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

	// ������ ����
	MapInfo_.FloorTileTextureName_ = FloorTileTextureName_;
	MapInfo_.WallTileTextureName_ = WallTileTextureName_;

	// Ÿ��
	TileSize_ = float4(160.f, 80.f);
	TileSizeHalf_ = TileSize_.halffloat4();
	TileSizeHHalf_ = TileSizeHalf_.halffloat4();

	// �ٴ�Ÿ��
	FloorTileImageSize_ = { 160.0f, 80.f };
	FloorTileImageSizeHalf_ = FloorTileImageSize_.halffloat4();
	FloorTileIndexPivotPos_ = { 0.0f, -TileSizeHalf_.y };

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

	// ������ ����
	MapInfo_.FloorTileTextureName_ = FloorTileTextureName_;
	MapInfo_.WallTileTextureName_ = WallTileTextureName_;

	// Ÿ��
	TileSize_ = float4(160.f, 80.f);
	TileSizeHalf_ = TileSize_.halffloat4();
	TileSizeHHalf_ = TileSizeHalf_.halffloat4();

	// �ٴ�Ÿ��
	FloorTileImageSize_ = { 160.0f, 80.f };
	FloorTileImageSizeHalf_ = FloorTileImageSize_.halffloat4();
	FloorTileIndexPivotPos_ = { 0.0f, -TileSizeHalf_.y };

	// ��Ÿ��
	WallTileImageSize_ = { 160.0f, 320.f };
	WallTileImageSizeHalf_ = WallTileImageSize_.halffloat4();
	WallTileIndexPivotPos_ = { 0.0f, TileSize_.y };

	// ���� ���õ� ���� Ÿ�� ����
	CurLevelType = LevelType::ChaosSanctuary;
}

void EditorRandomMap::SetSelectFloorTileIndex(int _Index)
{
	SelectFloorTileIndex_ = _Index;

	// �������
	MapInfo_.CorridorInfo_.TileImageIndex = SelectFloorTileIndex_;

	// ����
	//int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	//for (int i = 0; i < RoomCnt; ++i)
	//{
	//	MapInfo_.RoomInfo_[i].TileImageIndex = SelectFloorTileIndex_;
	//}
}

void EditorRandomMap::SetSelectWallTile1Index(int _Index)
{
	SelectWallTile1Index_ = _Index;

	// �����
	int WallCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallCnt; ++i)
	{
		MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = _Index;
	}
}

void EditorRandomMap::SetSelectWallTile2Index(int _Index)
{
	SelectWallTile2Index_ = _Index;

	// �����
	int WallCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallCnt; ++i)
	{
		MapInfo_.WallInfo_[i].WallTile2ImageIndex_ = _Index;
	}
}

void EditorRandomMap::FloorGridesSwitching()
{
	if (false == FloorGridesActive_)
	{
		FloorGridesActive_ = true;

		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = FloorGrides_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = FloorGrides_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			(*StartIter).second->On();
		}
	}
	else
	{
		FloorGridesActive_ = false;

		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = FloorGrides_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = FloorGrides_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			(*StartIter).second->Off();
		}
	}
}

void EditorRandomMap::WallGridesSwitching()
{
	if (false == WallGridesActive_)
	{
		WallGridesActive_ = true;

		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = WallGrides_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = WallGrides_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			(*StartIter).second->On();
		}
	}
	else
	{
		WallGridesActive_ = false;

		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = WallGrides_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = WallGrides_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			(*StartIter).second->Off();
		}
	}
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

	float4 FloorPos = FloorTileIndexPivotPos_ + Pos;
	FloorPos.z = 9000000.f;
	FloorTileRenderer->GetTransform()->SetLocalPosition(FloorPos);
	FloorTileRenderer->SetIndex(CurTileIndex_);
	FloorTiles_.insert(std::make_pair(_Index.Index_, FloorTileRenderer));
}

void EditorRandomMap::SetWallTile(float4 _Pos, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex)
{
	SetWallTile(GetWallTileIndex(_Pos), CurTileIndex_, _Type, _Multi2TileIndex);
}

void EditorRandomMap::SetWallTile(TileIndex _Index, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex)
{
	float4 Pos = float4::ZERO;
	Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
	Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

	RandomMapWallRenderer NewWallRenderer = {};

	NewWallRenderer.Tiles1_ = CreateTransformComponent<GameEngineTileMapRenderer>();
	NewWallRenderer.Tiles1_->SetImage(WallTileTextureName_);
	NewWallRenderer.Tiles1_->GetTransform()->SetLocalScaling(WallTileImageSize_);
	NewWallRenderer.Tiles1_->GetTransform()->SetLocalPosition(WallTileIndexPivotPos_ + Pos);

	NewWallRenderer.Tiles2_ = nullptr;

	if (_Type == RandomWallDetailType::WL_BENT_MULTI)
	{
		NewWallRenderer.Tiles1_->SetIndex(CurTileIndex_);

		NewWallRenderer.Tiles2_ = CreateTransformComponent<GameEngineTileMapRenderer>();
		NewWallRenderer.Tiles2_->SetImage(WallTileTextureName_);
		NewWallRenderer.Tiles2_->GetTransform()->SetLocalScaling(WallTileImageSize_);
		NewWallRenderer.Tiles2_->GetTransform()->SetLocalPosition(WallTileIndexPivotPos_ + Pos);
		NewWallRenderer.Tiles2_->GetTransform()->SetLocalZOrder(-static_cast<float>(_Index.X_ + _Index.Y_));
		NewWallRenderer.Tiles2_->SetIndex(_Multi2TileIndex);

		WallTiles_.insert(std::make_pair(_Index.Index_, NewWallRenderer));
	}

	NewWallRenderer.Tiles1_->GetTransform()->SetLocalZOrder(-static_cast<float>(_Index.X_ + _Index.Y_));
	NewWallRenderer.Tiles1_->SetIndex(CurTileIndex_);
	WallTiles_.insert(std::make_pair(_Index.Index_, NewWallRenderer));
}

void EditorRandomMap::SetFloorGrid(float4 _Pos, RandomMapTileType _TileType, bool _CenterFlag)
{
	SetFloorGrid(GetFloorTileIndex(_Pos), _TileType, _CenterFlag);
}

void EditorRandomMap::SetFloorGrid(TileIndex _Index, RandomMapTileType _TileType, bool _CenterFlag)
{
	if (FloorGrides_.end() != FloorGrides_.find(_Index.Index_))
	{
		// �̹� �����ϴ� Ÿ���̶�� Ÿ�Կ� ���� �ؽ��� ����
		
		// 1. ����Ÿ���� Ÿ���� ���
		if (_TileType == RandomMapTileType::CORRIDOR)
		{
			FloorGrides_.find(_Index.Index_)->second->SetImage("FloorGrid_Corridor.png");
		}
		// 2. ��Ÿ���� Ÿ���� ���
		else if (_TileType == RandomMapTileType::ROOM)
		{
			// 1) ��Ÿ���� ����Ÿ���� ���
			if (true == _CenterFlag)
			{
				FloorGrides_.find(_Index.Index_)->second->SetImage("FloorGrid_Center.png");
			}
			// 2) �ƴѰ��
			else
			{
				FloorGrides_.find(_Index.Index_)->second->SetImage("FloorGrid_Normal.png");
			}
		}

		return;
	}

	float4 Pos = float4::ZERO;
	Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHalf_.x;
	Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHalf_.y;

	GameEngineTileMapRenderer* FloorGirdRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();

	// 1. ����Ÿ���� Ÿ���� ���
	if (_TileType == RandomMapTileType::CORRIDOR)
	{
		FloorGirdRenderer->SetImage("FloorGrid_Corridor.png");
	}
	// 2. ��Ÿ���� Ÿ���� ���
	else if (_TileType == RandomMapTileType::ROOM)
	{
		// 1) ��Ÿ���� ����Ÿ���� ���
		if (true == _CenterFlag)
		{
			FloorGirdRenderer->SetImage("FloorGrid_Center.png");
		}
		// 2) �ƴѰ��
		else
		{
			FloorGirdRenderer->SetImage("FloorGrid_Normal.png");
		}
	}
	
	FloorGirdRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
	FloorGirdRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
	FloorGirdRenderer->GetTransform()->SetLocalZOrder(-98.f);
	FloorGirdRenderer->SetIndex(0);
	FloorGrides_.insert(std::make_pair(_Index.Index_, FloorGirdRenderer));
}

void EditorRandomMap::SetWallGrid(float4 _Pos, RandomWallBasicType _BasicType, RandomWallDetailType _DetailType)
{
	SetWallGrid(GetWallTileIndex(_Pos), _BasicType, _DetailType);
}

void EditorRandomMap::SetWallGrid(TileIndex _Index, RandomWallBasicType _BasicType, RandomWallDetailType _DetailType)
{
	if (WallGrides_.end() != WallGrides_.find(_Index.Index_))
	{
		return;
	}

	float4 Pos = float4::ZERO;
	Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
	Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

	GameEngineTileMapRenderer* NewRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();

	// �� Ÿ���� Ÿ�Կ� ���� �ؽ��� ����

	// 1. ���� ���
	if (_BasicType == RandomWallBasicType::WALL)
	{
		// �� ���⺰ �ؽ��� ����

		if (_DetailType == RandomWallDetailType::NORMAL)
		{
			NewRenderer->SetImage("WallGrid_Normal.png");
		}
		else if (_DetailType == RandomWallDetailType::NONE)
		{
			NewRenderer->SetImage("WallGrid_None.png");
		}
		else if (_DetailType == RandomWallDetailType::WL_RT_T)
		{
			NewRenderer->SetImage("WallGrid_RT_T.png");
		}
		else if (_DetailType == RandomWallDetailType::WL_RT_T_RE)
		{
			NewRenderer->SetImage("WallGrid_RT_T_RE.png");
		}
		else if (_DetailType == RandomWallDetailType::WL_RT_T_LE)
		{
			NewRenderer->SetImage("WallGrid_RT_T_LE.png");
		}
		// RT_B
		else if (_DetailType == RandomWallDetailType::WL_RT_B)
		{
			NewRenderer->SetImage("WallGrid_RT_B.png");
		}
		else if (_DetailType == RandomWallDetailType::WL_RT_B_RE)
		{
			NewRenderer->SetImage("WallGrid_RT_B_RE.png");
		}
		else if (_DetailType == RandomWallDetailType::WL_RT_B_LE)
		{
			NewRenderer->SetImage("WallGrid_RT_B_LE.png");
		}
		// RB_L
		else if (_DetailType == RandomWallDetailType::WL_RB_L)
		{
			NewRenderer->SetImage("WallGrid_RB_L.png");
		}
		else if (_DetailType == RandomWallDetailType::WL_RB_L_BE)
		{
			NewRenderer->SetImage("WallGrid_RB_L_BE.png");
		}
		else if (_DetailType == RandomWallDetailType::WL_RB_L_TE)
		{
			NewRenderer->SetImage("WallGrid_RB_L_TE.png");
		}
		// RB_R
		else if (_DetailType == RandomWallDetailType::WL_RB_R)
		{
			NewRenderer->SetImage("WallGrid_RB_R.png");
		}
		else if (_DetailType == RandomWallDetailType::WL_RB_R_BE)
		{
			NewRenderer->SetImage("WallGrid_RB_R_BE.png");
		}
		else if (_DetailType == RandomWallDetailType::WL_RB_R_TE)
		{
			NewRenderer->SetImage("WallGrid_RB_R_TE.png");
		}
		// BENT_SINGLE
		else if (_DetailType == RandomWallDetailType::WL_BENT_SINGLE)
		{
			NewRenderer->SetImage("WallGrid_Bent_Single.png");
		}
		// BENT_MULTI1 or BENT_MULTI2
		else if (_DetailType == RandomWallDetailType::WL_BENT_MULTI)
		{
			NewRenderer->SetImage("WallGrid_Bent_Multi.png");
		}
	}
	// 2. ���� ���
	else if (_BasicType == RandomWallBasicType::DOOR)
	{
		// �� ���⺰ �ؽ��� ����
		
		if (_DetailType == RandomWallDetailType::NORMAL)
		{
			NewRenderer->SetImage("WallGrid_Normal.png");
		}
		// 1) �� ���ͱ��� ��� ���ܹ��� ���� ���� �ؽ���(DR_RT_L)
		else if(_DetailType == RandomWallDetailType::DR_RT_L)
		{
			NewRenderer->SetImage("DoorGrid_RT_L.png");
		}
		// 2) �� ���ͱ��� ��� ���ܹ��� ���� ������ �ؽ���(DR_RT_R)
		else if (_DetailType == RandomWallDetailType::DR_RT_R)
		{
			NewRenderer->SetImage("DoorGrid_RT_R.png");
		}
		// 3) �� ���ͱ��� �´� ���ϴܹ��� ���� ���� �ؽ���(DR_RB_T)
		else if (_DetailType == RandomWallDetailType::DR_RB_T)
		{
			NewRenderer->SetImage("DoorGrid_RB_T.png");
		}
		// 4) �� ���ͱ��� �´� ���ϴܹ��� ���� �Ʒ��� �ؽ���(DR_RB_B)
		else if (_DetailType == RandomWallDetailType::DR_RB_B)
		{
			NewRenderer->SetImage("DoorGrid_RB_B.png");
		}
	}

	NewRenderer->GetTransform()->SetLocalScaling(TileSizeHalf_);
	NewRenderer->GetTransform()->SetLocalPosition(Pos);
	NewRenderer->GetTransform()->SetLocalZOrder(-99.f);
	NewRenderer->SetIndex(0);
	WallGrides_.insert(std::make_pair(_Index.Index_, NewRenderer));
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
	TilePos.x = (_TileIndex.X_ - _TileIndex.Y_) * TileSizeHalf_.x;
	TilePos.y = (_TileIndex.X_ + _TileIndex.Y_) * -TileSizeHalf_.y;

	return TilePos;
}

float4 EditorRandomMap::GetWallTileIndexToPos(TileIndex _TileIndex)
{
	float4 TilePos = float4::ZERO;
	TilePos.x = (_TileIndex.X_ - _TileIndex.Y_) * TileSizeHHalf_.x;
	TilePos.y = (_TileIndex.X_ + _TileIndex.Y_) * -TileSizeHHalf_.y;

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

	// ���� Ÿ�� ������ ����
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

	// ���� �׸��� ������ ����
	int CorridorGridCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorGridCnt; ++i)
	{
		TileIndex CurTile = MapInfo_.CorridorInfo_.AllIndexLists_[i];

		// �ش� Ÿ�� ����
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator DelTile = FloorGrides_.find(CurTile.Index_);
		if (FloorGrides_.end() != DelTile)
		{
			// ������ ���̰�
			(*DelTile).second->Death();

			// ��Ͽ��� ����
			FloorGrides_.erase(DelTile);
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

	// �� Ÿ�� ������ ����
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

	// �� �׸��� ������ ����
	for (int i = 0; i < RoomCnt; ++i)
	{
		int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			TileIndex CurTile = MapInfo_.RoomInfo_[i].AllIndexLists_[j];

			// �ش� Ÿ�� ����
			std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator DelTile = FloorGrides_.find(CurTile.Index_);
			if (FloorGrides_.end() != DelTile)
			{
				// ������ ���̰�
				(*DelTile).second->Death();

				// ��Ͽ��� ����
				FloorGrides_.erase(DelTile);
			}
		}
	}

	// ������ ����
	MapInfo_.RoomInfo_.clear();
}

void EditorRandomMap::AllWallClear()
{
	// ��/���� ��Ÿ�� ������ ����
	std::unordered_map<__int64, RandomMapWallRenderer>::iterator StartIter = WallTiles_.begin();
	std::unordered_map<__int64, RandomMapWallRenderer>::iterator EndIter = WallTiles_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter).second.Tiles1_->Death();

		if (nullptr != (*StartIter).second.Tiles2_)
		{
			(*StartIter).second.Tiles2_->Death();
		}
	}
	WallTiles_.clear();

	// ��/���� ��Ÿ�� �׸��� ������ ����
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridesStartIter = WallGrides_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridesEndIter = WallGrides_.end();
	for (; GridesStartIter != GridesEndIter; ++GridesStartIter)
	{
		(*GridesStartIter).second->Death();
	}
	WallGrides_.clear();

	// ��/�� ���� ����
	MapInfo_.WallInfo_.clear();
}

// 1. ���� ���� ����
void EditorRandomMap::CreateRandomCorridor(int _Create, int _Thickness, int _LenTileCount, int _DirCnt)
{
	// ���� ���� ����
	CreateRandomCorridorInfo(_Create, _Thickness, _LenTileCount, _DirCnt);

	// ���� ������ �̿��Ͽ� ȭ�鿡 ������
	CorridorGridRendering();
}

void EditorRandomMap::CreateRandomCorridorInfo(int _Create, int _Thickness, int _LenTileCount, int _DirCnt)
{
	// Ÿ��Ÿ�� ����(����)
	MapInfo_.CorridorInfo_.CorridorType_ = RandomMapTileType::CORRIDOR;
	MapInfo_.CorridorInfo_.TileImageIndex = SelectFloorTileIndex_;
	
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

bool EditorRandomMap::Corridor8WaySearch(TileIndex _CheckTileIndex)
{
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		if (MapInfo_.CorridorInfo_.AllIndexLists_[i] == _CheckTileIndex)
		{
			return true;
		}
	}

	return false;
}

void EditorRandomMap::CorridorGridRendering()
{
	// ���� ������ �̿��Ͽ� ������
	// ��, ������ Ÿ���ε����� �����Ѵٸ� �ٽ� ������ ����
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		SetFloorGrid(MapInfo_.CorridorInfo_.AllIndexLists_[i], MapInfo_.CorridorInfo_.CorridorType_);
	}
}

// 2. ������ �������� ������ ����
void EditorRandomMap::CreateRoomArrange(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex)
{
	// �� ��ġ ���� ����
	CreateRoomArrangeInfo(_RoomCount, _MaxWidthIndex, _MaxHeightIndex);

	// �� ��ġ������ �̿��Ͽ� ȭ�鿡 ������
	RoomGridRendering();
}

void EditorRandomMap::CreateRoomArrangeInfo(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex)
{
	// ���� ������ �̿��Ͽ� ���ġ
	GameEngineRandom RoomRandom;

	// 0. ��ġ�Ϸ��� �밹����ŭ �ݺ�
	int RoomCnt = 0;
	for (;;)
	{
		if (_RoomCount <= RoomCnt)
		{
			break;
		}

		// 0. ����Ÿ�������� �̿��Ͽ� ���� �߽�Ÿ���� ����
		int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());

		// ����1: ����Ÿ�������� 1���� �����Ҷ�
		int RandomIndex = RoomRandom.RandomInt(0, CorridorTileCnt) - 1;
		if (RandomIndex < 0)
		{
			RandomIndex = 0;
		}

		// ����2: ���� �����ε����� ��ġ�� ��˻�
		TileIndex CenterTile = MapInfo_.CorridorInfo_.AllIndexLists_[RandomIndex];
		if (true == RoomOverlapCheck(CenterTile))
		{
			continue;
		}

		// 2. ���� �⺻���� ����
		RandomRoomInfo NewRoom = {};

		NewRoom.TileType_ = RandomMapTileType::ROOM;
		NewRoom.RoomNo_ = RoomCnt + 1;
		NewRoom.TileImageIndex = 16;

		// 3. ���� ũ��� �������� ��������(�ּ� 5x5�� ��ũ�⸦ ������.
		int RandomWidthIndex = RoomRandom.RandomInt(5, _MaxWidthIndex);
		int RandomHeightIndex = RoomRandom.RandomInt(5, _MaxHeightIndex);
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

		// 7. ��� Ÿ���ε����� ����
		for (int y = NewRoom.minIndexY_; y < NewRoom.maxIndexY_; ++y)
		{
			for (int x = NewRoom.minIndexX_; x < NewRoom.maxIndexX_; ++x)
			{
				TileIndex CurTile = TileIndex(x, y);

				// ����Ÿ���̶�� �̹��� �ε��� ����
				if (CurTile == NewRoom.RoomCenterIndex_)
				{
					NewRoom.TileImageIndex = 1;
				}
				else
				{
					NewRoom.TileImageIndex = 16;
				}

				// ���� Ÿ�ϸ�� �߰�
				NewRoom.AllIndexLists_.push_back(CurTile);

			}
		}

		// 8. ���� ���� �����ϴ� ��� Ÿ���� �ٸ����� ���Ÿ�ϰ� ��ġ���ʴ´ٸ�
		if (false == RoomIntersectsCheck(NewRoom.AllIndexLists_))
		{
			// 9. ����Ÿ�ϸ�Ͽ� ������ Ÿ���� �����Ҷ� ������Ͽ��� �ش� Ÿ������
			for (int y = NewRoom.minIndexY_; y < NewRoom.maxIndexY_; ++y)
			{
				for (int x = NewRoom.minIndexX_; x < NewRoom.maxIndexX_; ++x)
				{
					CorridorOverlapTileIndexCheck(TileIndex(x, y));
				}
			}

			// 10. ������ ���� �Ϸ�
			MapInfo_.RoomInfo_.push_back(NewRoom);
			++RoomCnt;
		}
	}

	// ��� ���� ��ġ�Ϸ��Ͽ����Ƿ� �� �뿡�� ���� �ָ��������ִ� ���� ����
	for (int i = 0; i < RoomCnt; ++i)
	{
		SetTheFarthestRoom(i);
	}
}

void EditorRandomMap::SetTheFarthestRoom(int _CheckRoomIndex)
{
	// �Ÿ����� �� ����
	std::map<int, float> RoomDistanceMap;

	// ���� ���� ���� ��ġ
	float4 CurRoomPos = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[_CheckRoomIndex].RoomCenterIndex_);

	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		// ���� �� ����
		if (MapInfo_.RoomInfo_[_CheckRoomIndex].RoomNo_ == MapInfo_.RoomInfo_[i].RoomNo_)
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

	// �����ĿϷ�Ǿ����Ƿ� ���� ������ �������ε����� ���� �ָ��ִ� ���̴�.
	int SortVectorCnt = static_cast<int>(ReSortVector.size());
	if (0 < SortVectorCnt)
	{
		MapInfo_.RoomInfo_[_CheckRoomIndex].TheFarthestRoomNo_ = ReSortVector[SortVectorCnt - 1].first;
	}
}

bool EditorRandomMap::RoomIntersectsCheck(const std::vector<TileIndex>& _TileList)
{
	for (auto& CheckTile : _TileList)
	{
		int RoomCount = static_cast<int>(MapInfo_.RoomInfo_.size());
		for (int i = 0; i < RoomCount; ++i)
		{
			int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
			for (int j = 0; j < RoomTileCnt; ++j)
			{
				if (MapInfo_.RoomInfo_[i].AllIndexLists_[j] == CheckTile)
				{
					return true;
				}
			}
		}
	}

	return false;
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

void EditorRandomMap::CorridorOverlapTileIndexCheck(TileIndex _TileIndex)
{
	// �� ��ġ�� ���� Ÿ�ϸ�Ͽ� ������ Ÿ���� �����ϸ� ����Ÿ�ϸ�Ͽ��� ����
	int CorridorCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorCnt; ++i)
	{
		if (MapInfo_.CorridorInfo_.AllIndexLists_[i] == _TileIndex)
		{
			std::vector<TileIndex>::iterator FindListIter = MapInfo_.CorridorInfo_.AllIndexLists_.begin() + i;
			MapInfo_.CorridorInfo_.AllIndexLists_.erase(FindListIter);
			break;
		}
	}
}

void EditorRandomMap::RoomGridRendering()
{
	// ������ �������� �̿��Ͽ� ȭ�鿡 ������
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			// ���� ����Ÿ���� ���
			if (MapInfo_.RoomInfo_[i].AllIndexLists_[j] == MapInfo_.RoomInfo_[i].RoomCenterIndex_)
			{
				SetFloorGrid(MapInfo_.RoomInfo_[i].AllIndexLists_[j], MapInfo_.RoomInfo_[i].TileType_, true);
			}
			else
			{
				SetFloorGrid(MapInfo_.RoomInfo_[i].AllIndexLists_[j], MapInfo_.RoomInfo_[i].TileType_);
			}
		}
	}
}

// 3. ����/�� ������ �̿��Ͽ� ��/�� ���� ����
void EditorRandomMap::CreateWall()
{
	// ��/�� ���� ����
	CreateWallInfo();

	// ��/�� ������ �̿��Ͽ� ȭ�鿡 ������
	WallGridRendering();
}

void EditorRandomMap::CreateWallInfo()
{
	// 1. ���� ������ ����
	CreateRoomWallInfo();

	// 2. ������ ������ ����
	CreateOutWallInfo();

	// 3. �ܰ������� ����
	SearchOutWall();

	// 4. �ܰ��� ��� ��ġ
	UpdateOutWallInfo();

	// 5. ���� ���Ӻ����� ��Ÿ������ ����
	UpdateRoomWallInfo();

	// 6. ����������� ���� ã�Ƴ��� ��� ����
	RemainingWallTreatment();

	// 7. ��<->�� ���� or ��<->���� �����ϴ� ���� ����
	//    ���� �����ε����� �������� �� ������ Ž���Ͽ� �� or ������ ������
	//    ������ ���õȴ�.
	//    ��, �׻� ���� ����Ÿ���� �������� 2�� �ٴ�Ÿ���� �̿��Ѵ�.
	//    RIGHT or Left => DOOR_T & DOOR_B
	//    TOP or Bottom => DOOR_L & DOOR_R
	CreateDoorInfo();
}

void EditorRandomMap::CreateOutWallInfo()
{
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		// �ٴ�Ÿ���� Ÿ���� �߽���ǥ�� 0,0
		float4 FloorCenterPos = GetFloorTileIndexToPos(MapInfo_.CorridorInfo_.AllIndexLists_[i]);

		// �ٴ�Ÿ�� 1������ ��Ÿ���� 3x3�� ����
		TileIndex WallTileIndex = GetWallTileIndex(FloorCenterPos);

		// ��Ÿ���� Ÿ���� ������� 0,0
		for (int y = 0; y < 3; ++y)
		{
			for (int x = 0; x < 3; ++x)
			{
				// ����1: �̹� �����ϴ� Ÿ���ε����� ��Ͽ� �߰������ʴ´�.
				if (true == WallOverlapCheck(WallTileIndex))
				{
					WallTileIndex.X_ += 1;
					continue;
				}

				RandomWallInfo NewWall = {};
				NewWall.WallTileIndex_ = WallTileIndex;
				NewWall.SearchTileFlag_.clear();
				NewWall.SearchTileFlag_.resize(9);
				NewWall.WallBasicType_ = RandomWallBasicType::WALL;
				NewWall.WallDetailType_ = RandomWallDetailType::NORMAL; // �ʱ������ NormalŸ������ ����

				NewWall.WallTile1ImageIndex_ = 0;
				NewWall.WallTile2ImageIndex_ = 0;
				NewWall.WallTextureName_ = WallTileTextureName_;
				NewWall.WallTileSize_ = TileSize_;
				NewWall.WallRenderSize_ = WallTileImageSize_;
				NewWall.WallRenderPivotPos_ = WallTileIndexPivotPos_;

				MapInfo_.WallInfo_.push_back(NewWall);

				WallTileIndex.X_ += 1;
			}

			WallTileIndex.X_ = GetWallTileIndex(FloorCenterPos).X_;
			WallTileIndex.Y_ += 1;
		}
	}
}

void EditorRandomMap::CreateRoomWallInfo()
{
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			// �ٴ�Ÿ���� Ÿ���� �߽���ǥ�� 0,0
			float4 FloorCenterPos = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[i].AllIndexLists_[j]);

			// �ٴ�Ÿ�� 1������ ��Ÿ���� 3x3�� ����
			TileIndex WallTileIndex = GetWallTileIndex(FloorCenterPos);

			// ��Ÿ���� Ÿ���� ������� 0,0
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					// ����1: �̹� �����ϴ� Ÿ���ε����� ��Ͽ� �߰������ʴ´�.
					if (true == WallOverlapCheck(WallTileIndex))
					{
						WallTileIndex.X_ += 1;
						continue;
					}

					RandomWallInfo NewWall = {};
					NewWall.WallTileIndex_ = WallTileIndex;
					NewWall.SearchTileFlag_.clear();
					NewWall.SearchTileFlag_.resize(9);
					NewWall.WallBasicType_ = RandomWallBasicType::WALL;
					NewWall.WallDetailType_ = RandomWallDetailType::NORMAL; // �ʱ������ NormalŸ������ ����

					NewWall.WallTile1ImageIndex_ = 0;
					NewWall.WallTile2ImageIndex_ = 0;
					NewWall.WallTextureName_ = WallTileTextureName_;
					NewWall.WallTileSize_ = TileSize_;
					NewWall.WallRenderSize_ = WallTileImageSize_;
					NewWall.WallRenderPivotPos_ = WallTileIndexPivotPos_;

					MapInfo_.WallInfo_.push_back(NewWall);

					WallTileIndex.X_ += 1;
				}

				WallTileIndex.X_ = GetWallTileIndex(FloorCenterPos).X_;
				WallTileIndex.Y_ += 1;
			}
		}
	}
}

void EditorRandomMap::SearchOutWall()
{
	int WallTileCount = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallTileCount; ++i)
	{
		//		TileIndex( 0,  0) => 0
		// T:	TileIndex(-1,  0) => 1
		// RT:	TileIndex(-1, -1) => 2
		// R:	TileIndex( 0, -1) => 3
		// RB:	TileIndex( 1, -1) => 4
		// B:	TileIndex( 1,  0) => 5
		// LB:	TileIndex( 1,  1) => 6
		// L:	TileIndex( 0,  1) => 7
		// LT:	TileIndex(-1,  1) => 8
		TileIndex CurWallTile = MapInfo_.WallInfo_[i].WallTileIndex_;
		TileIndex TopTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(-1, 0);
		TileIndex RightTopTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(-1, -1);
		TileIndex RightTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(0, -1);
		TileIndex RightBottomTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(1, -1);
		TileIndex BottomTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(1, 0);
		TileIndex LeftBottomTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(1, 1);
		TileIndex LeftTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(0, 1);
		TileIndex LeftTopTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(-1, 1);

		// �������� 8���� Ž���Ͽ� Ÿ���� �����ϴ��� �Ǵ�
		MapInfo_.WallInfo_[i].SearchTileFlag_[0] = Wall8WaySearch(CurWallTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[1] = Wall8WaySearch(TopTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[2] = Wall8WaySearch(RightTopTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[3] = Wall8WaySearch(RightTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[4] = Wall8WaySearch(RightBottomTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[5] = Wall8WaySearch(BottomTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[6] = Wall8WaySearch(LeftBottomTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[7] = Wall8WaySearch(LeftTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[8] = Wall8WaySearch(LeftTopTile);

		// 1) ����
		// ����, R, L, LB, B, RB TRUE
		if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// 2) �Ʒ���
		// ����, R, L, LT, T, RT TRUE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// 3) �޺�
		// ����, T, B, RT, R, RB TRUE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// 4) ������
		// ����, T, B, LT, L, LB TRUE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// 5) Ư��
		// (1) ����, T, LT TRUE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// (2) L, LT FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// (2) LT, T FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// (3) RT, T FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// (4) R, RT FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// (5) R, RB FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// (6) B, RB FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// (7) LB, B FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// (8) L, LB FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// RT FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// ����, T, RT, R TRUE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// ����, R, RB, B TRUE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// ����, L, LB, B TRUE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// ����, T, LT, L TRUE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// RB FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// R  FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// LB FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// RT FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// B FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
		// T FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::NONE;
		}
	}
}

void EditorRandomMap::UpdateOutWallInfo()
{
	int WallTileCount = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallTileCount; ++i)
	{
		TileIndex CurWallTile = MapInfo_.WallInfo_[i].WallTileIndex_;
		TileIndex TopTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(-1, 0);
		TileIndex RightTopTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(-1, -1);
		TileIndex RightTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(0, -1);
		TileIndex RightBottomTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(1, -1);
		TileIndex BottomTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(1, 0);
		TileIndex LeftBottomTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(1, 1);
		TileIndex LeftTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(0, 1);
		TileIndex LeftTopTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(-1, 1);

		// �������� 8���� Ž���Ͽ� Ÿ���� �����ϴ��� �Ǵ�
		MapInfo_.WallInfo_[i].SearchTileFlag_[0] = Wall8WaySearch(CurWallTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[1] = Wall8WaySearch(TopTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[2] = Wall8WaySearch(RightTopTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[3] = Wall8WaySearch(RightTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[4] = Wall8WaySearch(RightBottomTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[5] = Wall8WaySearch(BottomTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[6] = Wall8WaySearch(LeftBottomTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[7] = Wall8WaySearch(LeftTile);
		MapInfo_.WallInfo_[i].SearchTileFlag_[8] = Wall8WaySearch(LeftTopTile);

		// 1) ���ӵ� ���� Ž���Ͽ� Ÿ�� ����

		// ���ӵ� ����
		// L, ����, R, LB, B, RB Ÿ���� �����ϰ�, LT, T, RTŸ���� ������
		if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
		{
			if (MapInfo_.WallInfo_[i].WallTileIndex_.Y_ % 2 == 0)
			{
				MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_RT_T;
				MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 26;
			}
		}
		// ���ӵ� �Ʒ���
		// L, ����, R, LT, T, RT Ÿ���� �����ϰ�, LB, B, RBŸ���� ������
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			if (MapInfo_.WallInfo_[i].WallTileIndex_.Y_ % 2 == 0)
			{
				MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_RT_B;
				MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 26;
			}
		}
		// ���ӵ� �޺�
		// ����, T, RT, R, RB, B Ÿ���� �����ϰ� LT, L, LBŸ���� ������
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
		{
			if (MapInfo_.WallInfo_[i].WallTileIndex_.X_ % 2 == 0)
			{
				MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_RB_L;
				MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 25;
			}
		}
		// ���ӵ� ������
		// ����, T, LT, L, LB, B Ÿ���� �����ϰ� RT, R, RBŸ���� ������
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			if (MapInfo_.WallInfo_[i].WallTileIndex_.X_ % 2 == 0)
			{
				MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_RB_R;
				MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 25;
			}
		}
		// RT, T, LT, L, LB : RB_L_TE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_RB_L_TE;
			MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 15;
		}
		// RT, R, RB, B, LB FALSE
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_RT_B_RE;
			MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 16;
		}
		// 
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_RT_T_RE;
			MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 16;
		}
		// 
		else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
			MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
		{
			MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_RB_R_TE;
			MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 15;
		}
		else
		{
			// 2) Ư���� ���� Ž���Ͽ� Ÿ�� ����
			if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[1] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[3] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
			{
				MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_BENT_MULTI;
				MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 28;
				MapInfo_.WallInfo_[i].WallTile2ImageIndex_ = 27;
			}
			else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
			{
				MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_BENT_MULTI;
				MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 28;
				MapInfo_.WallInfo_[i].WallTile2ImageIndex_ = 27;
			}
			else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
			{
				MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_BENT_MULTI;
				MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 28;
				MapInfo_.WallInfo_[i].WallTile2ImageIndex_ = 27;
			}
			else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
			{
				MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_BENT_MULTI;
				MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 28;
				MapInfo_.WallInfo_[i].WallTile2ImageIndex_ = 27;
			}
			else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[2] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[4] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[5] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[6] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[7] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[8] == false)
			{
				MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_BENT_SINGLE;
				MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 1;
			}
			else if (MapInfo_.WallInfo_[i].SearchTileFlag_[0] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[1] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[2] == false &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[3] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[4] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[5] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[6] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[7] == true &&
				MapInfo_.WallInfo_[i].SearchTileFlag_[8] == true)
			{
				MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_BENT_SINGLE;
				MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 1;
			}
		}
	}
}

void EditorRandomMap::UpdateRoomWallInfo()
{
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		// 1) ���� �ܰ� �ٴ� Ÿ���� ��� Ž��
		int RoomTileIndexCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileIndexCnt; ++j)
		{
			TileIndex CurFloorTileIndex = MapInfo_.RoomInfo_[i].AllIndexLists_[j];

			// (0) ���ܲ� ��
			if (CurFloorTileIndex.X_ == MapInfo_.RoomInfo_[i].minIndexX_ &&
				CurFloorTileIndex.Y_ == MapInfo_.RoomInfo_[i].minIndexY_)
			{
				float4 CurFloorTilePos = GetFloorTileIndexToPos(CurFloorTileIndex);
				TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);
				for (auto& WallTile : MapInfo_.WallInfo_)
				{
					if (WallTile.WallTileIndex_ == WallTileIndex)
					{
						WallTile.WallDetailType_ = RandomWallDetailType::WL_BENT_MULTI;
						WallTile.WallTile1ImageIndex_ = 28;
						WallTile.WallTile2ImageIndex_ = 27;
						break;
					}
				}
			}
			// (0) ���ϴܲ� ��
			else if (CurFloorTileIndex.X_ == MapInfo_.RoomInfo_[i].maxIndexX_ - 1 &&
				CurFloorTileIndex.Y_ == MapInfo_.RoomInfo_[i].maxIndexY_ - 1)
			{
				float4 CurFloorTilePos = GetFloorTileIndexToPos(CurFloorTileIndex);
				TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);
				WallTileIndex.X_ += 2;
				WallTileIndex.Y_ += 2;

				for (auto& WallTile : MapInfo_.WallInfo_)
				{
					if (WallTile.WallTileIndex_ == WallTileIndex)
					{
						WallTile.WallDetailType_ = RandomWallDetailType::WL_BENT_SINGLE;
						WallTile.WallTile1ImageIndex_ = 1;
						break;
					}
				}
			}
			// (0) �»�� ����
			else if (CurFloorTileIndex.X_ == MapInfo_.RoomInfo_[i].minIndexX_ &&
				CurFloorTileIndex.Y_ == MapInfo_.RoomInfo_[i].maxIndexY_ - 1)
			{
				float4 CurFloorTilePos = GetFloorTileIndexToPos(CurFloorTileIndex);
				TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);
				WallTileIndex.Y_ += 2;

				for (auto& WallTile : MapInfo_.WallInfo_)
				{
					if (WallTile.WallTileIndex_ == WallTileIndex)
					{
						WallTile.WallDetailType_ = RandomWallDetailType::WL_RB_L_TE;
						WallTile.WallTile1ImageIndex_ = 15;
						break;
					}
				}
			}
			// (0) ���ϴ� ����
			else if (CurFloorTileIndex.X_ == MapInfo_.RoomInfo_[i].maxIndexX_ - 1 &&
				CurFloorTileIndex.Y_ == MapInfo_.RoomInfo_[i].minIndexY_)
			{
				float4 CurFloorTilePos = GetFloorTileIndexToPos(CurFloorTileIndex);
				TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);
				WallTileIndex.X_ += 2;

				for (auto& WallTile : MapInfo_.WallInfo_)
				{
					if (WallTile.WallTileIndex_ == WallTileIndex)
					{
						WallTile.WallDetailType_ = RandomWallDetailType::WL_RT_B_RE;
						WallTile.WallTile1ImageIndex_ = 16;
						break;
					}
				}
			}
			// (1) �׿ܺ�
			else
			{
				// (1) �ּ� X �ε����� ���� => ����
				if (CurFloorTileIndex.X_ == MapInfo_.RoomInfo_[i].minIndexX_)
				{
					// [1] �������� �Ǵ��Ҽ� �ִ� ��� ��Ÿ���� �˾Ƴ���.
					//     ��� �˾Ƴ� ��Ÿ���� �̹� Ÿ���� ������ �������ִٸ� ��������������
					//     NORMALŸ���̶�� �������� Ÿ���� �����Ѵ�.
					float4 CurFloorTilePos = GetFloorTileIndexToPos(CurFloorTileIndex);
					TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);

					for (int y = 0; y < 3; ++y)
					{
						for (auto& WallTile : MapInfo_.WallInfo_)
						{
							if (WallTile.WallTileIndex_ == WallTileIndex)
							{
								if (WallTile.WallTileIndex_.Y_ % 2 == 0)
								{
									WallTile.WallDetailType_ = RandomWallDetailType::WL_RT_T;
									WallTile.WallTile1ImageIndex_ = 26;
								}
								else
								{
									WallTile.WallDetailType_ = RandomWallDetailType::NONE;
								}
								break;
							}
						}

						WallTileIndex = WallTileIndex + TileIndex(0, 1);
					}
				}
				// (2) �ּ� Y �ε����� ���� => ������
				if (CurFloorTileIndex.Y_ == MapInfo_.RoomInfo_[i].minIndexY_)
				{
					float4 CurFloorTilePos = GetFloorTileIndexToPos(CurFloorTileIndex);

					TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);

					for (int x = 0; x < 3; ++x)
					{
						for (auto& WallTile : MapInfo_.WallInfo_)
						{
							if (WallTile.WallTileIndex_ == WallTileIndex)
							{
								if (WallTile.WallTileIndex_.X_ % 2 == 0)
								{
									WallTile.WallDetailType_ = RandomWallDetailType::WL_RB_R;
									WallTile.WallTile1ImageIndex_ = 25;
								}
								else
								{
									WallTile.WallDetailType_ = RandomWallDetailType::NONE;
								}
								break;
							}
						}

						WallTileIndex = WallTileIndex + TileIndex(1, 0);
					}
				}
				// (3) �ִ� X �ε����� ���� => �Ʒ���
				if (CurFloorTileIndex.X_ == MapInfo_.RoomInfo_[i].maxIndexX_ - 1)
				{
					float4 CurFloorTilePos = GetFloorTileIndexToPos(CurFloorTileIndex);

					TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);
					WallTileIndex.X_ += 2;

					for (int y = 0; y < 3; ++y)
					{
						for (auto& WallTile : MapInfo_.WallInfo_)
						{
							if (WallTile.WallTileIndex_ == WallTileIndex)
							{
								if (WallTile.WallTileIndex_.Y_ % 2 == 0)
								{
									WallTile.WallDetailType_ = RandomWallDetailType::WL_RT_B;
									WallTile.WallTile1ImageIndex_ = 26;
								}
								else
								{
									WallTile.WallDetailType_ = RandomWallDetailType::NONE;
								}
								break;
							}
						}

						WallTileIndex = WallTileIndex + TileIndex(0, 1);
					}
				}
				// (4) �ִ� Y �ε����� ���� => �޺�
				if (CurFloorTileIndex.Y_ == MapInfo_.RoomInfo_[i].maxIndexY_ - 1)
				{
					float4 CurFloorTilePos = GetFloorTileIndexToPos(CurFloorTileIndex);

					TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);
					WallTileIndex.Y_ += 2;

					for (int x = 0; x < 3; ++x)
					{
						for (auto& WallTile : MapInfo_.WallInfo_)
						{
							if (WallTile.WallTileIndex_ == WallTileIndex)
							{
								if (WallTile.WallTileIndex_.X_ % 2 == 0)
								{
									WallTile.WallDetailType_ = RandomWallDetailType::WL_RB_L;
									WallTile.WallTile1ImageIndex_ = 25;
								}
								else
								{
									WallTile.WallDetailType_ = RandomWallDetailType::NONE;
								}
								break;
							}
						}

						WallTileIndex = WallTileIndex + TileIndex(1, 0);
					}
				}
			}

		}
	}
}

void EditorRandomMap::RemainingWallTreatment()
{
	int WallTileCount = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallTileCount; ++i)
	{
		// �� ��Ÿ�Ժ� ���� üũ

		// (1) RT_B
		if (MapInfo_.WallInfo_[i].WallDetailType_ == RandomWallDetailType::WL_RT_B)
		{
			// RB_L or RB_R�� ������ ���̶�� BENT_MULTI Ÿ������ ����
			TileIndex BottomCheckTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(2, 0);
			for (auto& WallTile : MapInfo_.WallInfo_)
			{
				if (WallTile.WallTileIndex_ == BottomCheckTile)
				{
					if (WallTile.WallDetailType_ == RandomWallDetailType::WL_RB_L ||
						WallTile.WallDetailType_ == RandomWallDetailType::WL_RB_R ||
						WallTile.WallDetailType_ == RandomWallDetailType::WL_BENT_SINGLE)
					{
						MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_BENT_MULTI;
						MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 28;
						MapInfo_.WallInfo_[i].WallTile2ImageIndex_ = 27;
						break;
					}
				}
			}

			// BENG_SINGLE�� ������ ���̶�� RT_B
			TileIndex RightCheckTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(0, -2);
			for (auto& WallTile : MapInfo_.WallInfo_)
			{
				if (WallTile.WallTileIndex_ == BottomCheckTile)
				{
					if (WallTile.WallDetailType_ == RandomWallDetailType::WL_BENT_SINGLE)
					{
						MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_RT_B_RE;
						MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 26;
						break;
					}
				}
			}
		}
		// (2) RB_L
		if (MapInfo_.WallInfo_[i].WallDetailType_ == RandomWallDetailType::WL_RB_L)
		{
			// RT_B or RT_T�� �����º��̶�� �̸� BENT_MULTI Ÿ������ ����
			TileIndex BottomCheckTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(0, 2);
			for (auto& WallTile : MapInfo_.WallInfo_)
			{
				if (WallTile.WallTileIndex_ == BottomCheckTile)
				{
					if (WallTile.WallDetailType_ == RandomWallDetailType::WL_RT_T ||
						WallTile.WallDetailType_ == RandomWallDetailType::WL_RT_B)
					{
						MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_BENT_MULTI;
						MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 28;
						MapInfo_.WallInfo_[i].WallTile2ImageIndex_ = 27;
						break;
					}
				}
			}
		}
		// (3) RT_T
		if (MapInfo_.WallInfo_[i].WallDetailType_ == RandomWallDetailType::WL_RT_T)
		{
			// BENT_SINGLE�� ������ ������ Ÿ���̸� RT_T_RE or RT_B_RE
			TileIndex RightCheckTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(0, -2);
			for (auto& WallTile : MapInfo_.WallInfo_)
			{
				if (WallTile.WallTileIndex_ == RightCheckTile)
				{
					if (WallTile.WallDetailType_ == RandomWallDetailType::WL_BENT_SINGLE)
					{
						MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_RT_T_RE;
						MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 16;
						break;
					}
				}
			}
		}
		// (4) RB_L_TE
		if (MapInfo_.WallInfo_[i].WallDetailType_ == RandomWallDetailType::WL_RB_L_TE)
		{
			// BENT_SINGLE�� ������ ������ Ÿ���̸� RT_T_RE or RT_B_RE
			TileIndex LeftCheckTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(0, 2);
			for (auto& WallTile : MapInfo_.WallInfo_)
			{
				if (WallTile.WallTileIndex_ == LeftCheckTile)
				{
					if (WallTile.WallDetailType_ == RandomWallDetailType::WL_RT_T ||
						WallTile.WallDetailType_ == RandomWallDetailType::WL_RT_B)
					{
						MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_BENT_MULTI;
						MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 28;
						MapInfo_.WallInfo_[i].WallTile2ImageIndex_ = 27;
						break;
					}
				}
			}
		}
		// (5) RT_B_RE
		if (MapInfo_.WallInfo_[i].WallDetailType_ == RandomWallDetailType::WL_RT_B_RE)
		{
			// RB_R �� ������ ������ Ÿ���̸� BENT_MULTI
			TileIndex BottomCheckTile = MapInfo_.WallInfo_[i].WallTileIndex_ + TileIndex(2, 0);
			for (auto& WallTile : MapInfo_.WallInfo_)
			{
				if (WallTile.WallTileIndex_ == BottomCheckTile)
				{
					if (WallTile.WallDetailType_ == RandomWallDetailType::WL_RB_R ||
						WallTile.WallDetailType_ == RandomWallDetailType::WL_RB_L)
					{
						MapInfo_.WallInfo_[i].WallDetailType_ = RandomWallDetailType::WL_BENT_MULTI;
						MapInfo_.WallInfo_[i].WallTile1ImageIndex_ = 28;
						MapInfo_.WallInfo_[i].WallTile2ImageIndex_ = 27;
						break;
					}
				}
			}
		}
	}
}

void EditorRandomMap::CreateDoorInfo()
{
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		TileIndex RoomCenterTileIndex = MapInfo_.RoomInfo_[i].RoomCenterIndex_;

		// 4���� Ž���Ͽ� ������ ����ǰų�, ���� �ٸ� ��� ����Ǵ� ������ ã�Ƴ���.
		std::vector<TileIndex> CheckTileIndex;
		CheckTileIndex.push_back(TileIndex(MapInfo_.RoomInfo_[i].minIndexX_, RoomCenterTileIndex.Y_) + TileIndex(-1,  0));	// ���
		CheckTileIndex.push_back(TileIndex(RoomCenterTileIndex.X_, MapInfo_.RoomInfo_[i].minIndexY_) + TileIndex( 0, -1));	// ���
		CheckTileIndex.push_back(TileIndex(MapInfo_.RoomInfo_[i].maxIndexX_ - 1, RoomCenterTileIndex.Y_) + TileIndex( 1,  0));	// �ϴ�
		CheckTileIndex.push_back(TileIndex(RoomCenterTileIndex.X_, MapInfo_.RoomInfo_[i].maxIndexY_ - 1) + TileIndex( 0,  1));	// �´�

		for (int j = 0; j < static_cast<int>(CheckTileIndex.size()); ++j)
		{
			// �� ���⺰ ������ ���� ���ο� ���� ������ ����/�̼���
			// ��, ��/�ϴ� ������ �����Ǿ��ٸ� L/R Ÿ���� ����Ÿ���� �����ǰ�
			//     ��/��� ������ �����Ǿ��ٸ� T/B Ÿ���� ����Ÿ���� �����ȴ�.
			if (true == DoorInfoSettingCheck(CheckTileIndex[j], MapInfo_.RoomInfo_[i].RoomNo_))
			{
				TileIndex DoorTileIndex;

				// ���
				if (j == 0)
				{
					DoorTileIndex = TileIndex(MapInfo_.RoomInfo_[i].minIndexX_, RoomCenterTileIndex.Y_);

					// �ش� Ÿ�Ͽ� ���ϴ� ��� ��Ÿ���� ã�Ƴ��� Ÿ���� ����
					float4 CurFloorTilePos = GetFloorTileIndexToPos(DoorTileIndex);
					TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);

					bool Flag = false;
					for (int y = 0; y < 3; ++y)
					{
						for (auto& WallTile : MapInfo_.WallInfo_)
						{
							if (WallTile.WallTileIndex_ == WallTileIndex)
							{
								WallTile.WallBasicType_ = RandomWallBasicType::DOOR;
								if (WallTile.WallTileIndex_.Y_ % 2 == 0)
								{
									if (false == Flag)
									{
										WallTile.WallDetailType_ = RandomWallDetailType::DR_RT_R;
										WallTile.WallTile1ImageIndex_ = 10;
										Flag = true;
									}
									else
									{
										WallTile.WallDetailType_ = RandomWallDetailType::DR_RT_L;
										WallTile.WallTile1ImageIndex_ = 11;
									}
								}
								else
								{
									WallTile.WallDetailType_ = RandomWallDetailType::NORMAL;
								}
								break;
							}
						}

						WallTileIndex = WallTileIndex + TileIndex(0, 1);
					}
				}
				// ���
				else if (j == 1)
				{
					DoorTileIndex = TileIndex(RoomCenterTileIndex.X_, MapInfo_.RoomInfo_[i].minIndexY_);

					float4 CurFloorTilePos = GetFloorTileIndexToPos(DoorTileIndex);
					TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);

					bool Flag = false;
					for (int x = 0; x < 3; ++x)
					{
						for (auto& WallTile : MapInfo_.WallInfo_)
						{
							if (WallTile.WallTileIndex_ == WallTileIndex)
							{
								WallTile.WallBasicType_ = RandomWallBasicType::DOOR;
								if (WallTile.WallTileIndex_.X_ % 2 == 0)
								{
									if (false == Flag)
									{
										WallTile.WallDetailType_ = RandomWallDetailType::DR_RB_T;
										WallTile.WallTile1ImageIndex_ = 3;
										Flag = true;
									}
									else
									{
										WallTile.WallDetailType_ = RandomWallDetailType::DR_RB_B;
										WallTile.WallTile1ImageIndex_ = 2;
									}
								}
								else
								{
									WallTile.WallDetailType_ = RandomWallDetailType::NORMAL;
								}
								break;
							}
						}

						WallTileIndex = WallTileIndex + TileIndex(1, 0);
					}
				}
				// �ϴ�
				else if (j == 2)
				{
					DoorTileIndex = TileIndex(MapInfo_.RoomInfo_[i].maxIndexX_ - 1, RoomCenterTileIndex.Y_);

					float4 CurFloorTilePos = GetFloorTileIndexToPos(DoorTileIndex);
					TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);
					WallTileIndex.X_ += 2;

					bool Flag = false;
					for (int y = 0; y < 3; ++y)
					{
						for (auto& WallTile : MapInfo_.WallInfo_)
						{
							if (WallTile.WallTileIndex_ == WallTileIndex)
							{
								WallTile.WallBasicType_ = RandomWallBasicType::DOOR;
								if (WallTile.WallTileIndex_.Y_ % 2 == 0)
								{
									if (false == Flag)
									{
										WallTile.WallDetailType_ = RandomWallDetailType::DR_RT_R;
										WallTile.WallTile1ImageIndex_ = 10;
										Flag = true;
									}
									else
									{
										WallTile.WallDetailType_ = RandomWallDetailType::DR_RT_L;
										WallTile.WallTile1ImageIndex_ = 11;
									}
								}
								else
								{
									WallTile.WallDetailType_ = RandomWallDetailType::NORMAL;
								}
								break;
							}
						}

						WallTileIndex = WallTileIndex + TileIndex(0, 1);
					}
				}
				// �´�
				else if (j == 3)
				{
					DoorTileIndex = TileIndex(RoomCenterTileIndex.X_, MapInfo_.RoomInfo_[i].maxIndexY_ - 1);

					float4 CurFloorTilePos = GetFloorTileIndexToPos(DoorTileIndex);
					TileIndex WallTileIndex = GetWallTileIndex(CurFloorTilePos);
					WallTileIndex.Y_ += 2;

					bool Flag = false;
					for (int x = 0; x < 3; ++x)
					{
						for (auto& WallTile : MapInfo_.WallInfo_)
						{
							if (WallTile.WallTileIndex_ == WallTileIndex)
							{
								WallTile.WallBasicType_ = RandomWallBasicType::DOOR;
								if (WallTile.WallTileIndex_.X_ % 2 == 0)
								{
									if (false == Flag)
									{
										WallTile.WallDetailType_ = RandomWallDetailType::DR_RB_T;
										WallTile.WallTile1ImageIndex_ = 3;
										Flag = true;
									}
									else
									{
										WallTile.WallDetailType_ = RandomWallDetailType::DR_RB_B;
										WallTile.WallTile1ImageIndex_ = 2;
									}
								}
								else
								{
									WallTile.WallDetailType_ = RandomWallDetailType::NORMAL;
								}
								break;
							}
						}

						WallTileIndex = WallTileIndex + TileIndex(1, 0);
					}
				}
			}
		}
	}
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

bool EditorRandomMap::Wall8WaySearch(TileIndex _TileIndex)
{
	int WallCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallCnt; ++i)
	{
		// Ÿ���� �����Ѵٸ� true ��ȯ
		if (MapInfo_.WallInfo_[i].WallTileIndex_ == _TileIndex)
		{
			return true;
		}
	}

	return false;
}

bool EditorRandomMap::DoorInfoSettingCheck(TileIndex _CheckTile, int _CurRoomNo)
{
	// ��/���� Ÿ�� ����� Ž���Ͽ� �ش� Ÿ���� Ÿ���� �˾Ƴ���.
	// ��, Ÿ���� �������������� ������ ���� �Ұ� ����

	// ���� ��� Ž��
	for (auto& CorridorTile : MapInfo_.CorridorInfo_.AllIndexLists_)
	{
		if (CorridorTile == _CheckTile)
		{
			// �ش� Ÿ���� ã�Ҵٸ� �ش� Ÿ���� �����̹Ƿ� ������ ���ᰡ�� �Ǵ�
			return true;
		}
	}

	// �� ��� Ž��
	for (auto& Room : MapInfo_.RoomInfo_)
	{
		for (auto& RoomTile : Room.AllIndexLists_)
		{
			if (RoomTile == _CheckTile)
			{
				// �ش� Ÿ���� ã�Ҵٸ� �ش� Ÿ���� ���̹Ƿ� ������ ���ᰡ�� �Ǵ�
				// ��, ���� üũ�ϴ� ���� ��ȣ�� �ٸ� ��쿡�� ������ ���ᰡ�� �Ǵ�
				if (Room.RoomNo_ != _CurRoomNo)
				{
					return true;
				}

				return false;
			}
		}
	}

	return false;
}

void EditorRandomMap::WallGridRendering()
{
	int WallCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallCnt; ++i)
	{
		SetWallGrid(MapInfo_.WallInfo_[i].WallTileIndex_, MapInfo_.WallInfo_[i].WallBasicType_, MapInfo_.WallInfo_[i].WallDetailType_);
	}
}

void EditorRandomMap::FloorTileTextureMatching()
{
	// ����
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		SetFloorTile(MapInfo_.CorridorInfo_.AllIndexLists_[i], MapInfo_.CorridorInfo_.TileImageIndex);
	}

	// ��
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			SetFloorTile(MapInfo_.RoomInfo_[i].AllIndexLists_[j], MapInfo_.RoomInfo_[i].TileImageIndex);
		}
	}
}

void EditorRandomMap::WallTileTextureMatching()
{
	int WallCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallCnt; ++i)
	{
		if (MapInfo_.WallInfo_[i].WallBasicType_ == RandomWallBasicType::WALL)
		{
			if (MapInfo_.WallInfo_[i].WallDetailType_ != RandomWallDetailType::NORMAL &&
				MapInfo_.WallInfo_[i].WallDetailType_ != RandomWallDetailType::NONE)
			{
				SetWallTile(MapInfo_.WallInfo_[i].WallTileIndex_, MapInfo_.WallInfo_[i].WallTile1ImageIndex_, MapInfo_.WallInfo_[i].WallDetailType_, MapInfo_.WallInfo_[i].WallTile2ImageIndex_);
			}
		}
	}
}

void EditorRandomMap::DoorTileTextureMatching()
{
	int WallCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallCnt; ++i)
	{
		// ��Ÿ�� Ÿ���� ������ ������
		if (MapInfo_.WallInfo_[i].WallBasicType_ == RandomWallBasicType::DOOR)
		{
			if (MapInfo_.WallInfo_[i].WallDetailType_ != RandomWallDetailType::NORMAL &&
				MapInfo_.WallInfo_[i].WallDetailType_ != RandomWallDetailType::NONE)
			{
				SetWallTile(MapInfo_.WallInfo_[i].WallTileIndex_, MapInfo_.WallInfo_[i].WallTile1ImageIndex_, MapInfo_.WallInfo_[i].WallDetailType_, MapInfo_.WallInfo_[i].WallTile2ImageIndex_);
			}
		}
	}
}

#pragma endregion
