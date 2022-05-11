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
	// 타일
	TileSize_ = float4(160.f, 80.f);
	TileSizeHalf_ = TileSize_.halffloat4();
	TileSizeHHalf_ = TileSizeHalf_.halffloat4();

	// 바닥타일
	FloorTileImageSize_ = { 160.0f, 80.f };
	FloorTileImageSizeHalf_ = FloorTileImageSize_.halffloat4();
	FloorTileIndexPivotPos_ = { 0.0f, -TileSizeHalf_.y };

	// 벽타일
	WallTileImageSize_ = { 160.0f, 320.f };
	WallTileImageSizeHalf_ = WallTileImageSize_.halffloat4();
	WallTileIndexPivotPos_ = { 0.0f, TileSize_.y };

	// 랜덤 복도 생성관련 초기화
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
	// 카타콤 텍스쳐로 셋팅
	FloorTileTextureName_ = "Catacombs_Floor.png";
	WallTileTextureName_ = "Catacombs_Wall.png";

	// 맵정보 갱신
	MapInfo_.FloorTileTextureName_ = FloorTileTextureName_;
	MapInfo_.WallTileTextureName_ = WallTileTextureName_;

	// 타일
	TileSize_ = float4(160.f, 80.f);
	TileSizeHalf_ = TileSize_.halffloat4();
	TileSizeHHalf_ = TileSizeHalf_.halffloat4();

	// 바닥타일
	FloorTileImageSize_ = { 160.0f, 80.f };
	FloorTileImageSizeHalf_ = FloorTileImageSize_.halffloat4();
	FloorTileIndexPivotPos_ = { 0.0f, -TileSizeHalf_.y };

	// 벽타일
	WallTileImageSize_ = { 160.0f, 320.f };
	WallTileImageSizeHalf_ = WallTileImageSize_.halffloat4();
	WallTileIndexPivotPos_ = { 0.0f, TileSize_.y };

	// 현재 선택된 레벨 타입 변경
	CurLevelType = LevelType::Catacombs;
}

void EditorRandomMap::ChaosSanctuaryTextrueSetting()
{
	// 카오스 생츄어리 텍스쳐로 셋팅
	FloorTileTextureName_ = "ChaosSanctuary_Floor.png";
	WallTileTextureName_ = "ChaosSanctuary_Wall.png";

	// 맵정보 갱신
	MapInfo_.FloorTileTextureName_ = FloorTileTextureName_;
	MapInfo_.WallTileTextureName_ = WallTileTextureName_;

	// 타일
	TileSize_ = float4(160.f, 80.f);
	TileSizeHalf_ = TileSize_.halffloat4();
	TileSizeHHalf_ = TileSizeHalf_.halffloat4();

	// 바닥타일
	FloorTileImageSize_ = { 160.0f, 80.f };
	FloorTileImageSizeHalf_ = FloorTileImageSize_.halffloat4();
	FloorTileIndexPivotPos_ = { 0.0f, -TileSizeHalf_.y };

	// 벽타일
	WallTileImageSize_ = { 160.0f, 320.f };
	WallTileImageSizeHalf_ = WallTileImageSize_.halffloat4();
	WallTileIndexPivotPos_ = { 0.0f, TileSize_.y };

	// 현재 선택된 레벨 타입 변경
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

void EditorRandomMap::SetFloorGrid(float4 _Pos, RandomMapTileType _TileType, bool _CenterFlag)
{
	SetFloorGrid(GetFloorTileIndex(_Pos), _TileType, _CenterFlag);
}

void EditorRandomMap::SetFloorGrid(TileIndex _Index, RandomMapTileType _TileType, bool _CenterFlag)
{
	if (FloorGrides_.end() != FloorGrides_.find(_Index.Index_))
	{
		return;
	}

	float4 Pos = float4::ZERO;
	Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHalf_.x;
	Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHalf_.y;

	GameEngineTileMapRenderer* FloorGirdRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();

	// 1. 복도타입의 타일인 경우
	if (_TileType == RandomMapTileType::CORRIDOR)
	{
		FloorGirdRenderer->SetImage("FloorGrid_Corridor.png");
	}
	// 2. 룸타입의 타일인 경우
	else if (_TileType == RandomMapTileType::ROOM)
	{
		// 1) 룸타입의 센터타일인 경우
		if (true == _CenterFlag)
		{
			FloorGirdRenderer->SetImage("FloorGrid_Center.png");
		}
		// 2) 아닌경우
		else
		{
			FloorGirdRenderer->SetImage("FloorGrid_Normal.png");
		}
	}
	
	FloorGirdRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
	FloorGirdRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
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

	// 각 타일의 타입에 따른 텍스쳐 변경

	// 1. 벽인 경우
	if (_BasicType == RandomWallBasicType::WALL)
	{
		// 각 방향별 텍스쳐 셋팅

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
		else if (_DetailType == RandomWallDetailType::WL_BENT_MULTI1 ||
			_DetailType == RandomWallDetailType::WL_BENT_MULTI2)
		{
			NewRenderer->SetImage("WallGrid_Bent_Multi.png");
		}
	}
	// 2. 문인 경우
	else if (_BasicType == RandomWallBasicType::DOOR)
	{
		// 각 방향별 텍스쳐 셋팅
		
		// 1) 룸 센터기준 상단 우상단방향 문의 왼쪽 텍스쳐(DR_RT_L)
		if(_DetailType == RandomWallDetailType::DR_RT_L)
		{
			NewRenderer->SetImage("DoorGrid_RT_L.png");
		}
		// 2) 룸 센터기준 상단 우상단방향 문의 오른쪽 텍스쳐(DR_RT_R)
		else if (_DetailType == RandomWallDetailType::DR_RT_R)
		{
			NewRenderer->SetImage("DoorGrid_RT_R.png");
		}
		// 3) 룸 센터기준 좌단 우하단방향 문의 위쪽 텍스쳐(DR_RB_T)
		else if (_DetailType == RandomWallDetailType::DR_RB_T)
		{
			NewRenderer->SetImage("DoorGrid_RB_T.png");
		}
		// 4) 룸 센터기준 좌단 우하단방향 문의 아래쪽 텍스쳐(DR_RB_B)
		else if (_DetailType == RandomWallDetailType::DR_RB_B)
		{
			NewRenderer->SetImage("DoorGrid_RB_B.png");
		}
	}

	NewRenderer->GetTransform()->SetLocalScaling(TileSizeHalf_);
	NewRenderer->GetTransform()->SetLocalPosition(Pos);
	NewRenderer->GetTransform()->SetLocalZOrder(-15.f);
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
	TilePos.x = (_TileIndex.X_ - _TileIndex.Y_) * TileSize_.halffloat4().halffloat4().x;
	TilePos.y = (_TileIndex.X_ + _TileIndex.Y_) * -TileSize_.halffloat4().halffloat4().y;

	return TilePos;
}

#pragma region 현재버전 랜덤맵 생성 함수

// 0. 정보 클리어관련
void EditorRandomMap::AllClear()
{
	// 복도 정보 및 렌더러 제거
	AllCorridorClear();

	// 룸 정보 및 렌더러 제거
	AllRoomClear();

	// 벽/문 정보 및 렌더러 제거
	AllWallClear();
}

void EditorRandomMap::AllCorridorClear()
{
	// 복도는 바닥타일

	// 복도 타일 렌더러 제거
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		TileIndex CurTile = MapInfo_.CorridorInfo_.AllIndexLists_[i];

		// 해당 타일 제거
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator DelTile = FloorTiles_.find(CurTile.Index_);
		if(FloorTiles_.end() != DelTile)
		{
			// 렌더러 죽이고
			(*DelTile).second->Death();

			// 목록에서 제거
			FloorTiles_.erase(DelTile);
		}
	}

	// 복도 그리드 렌더러 제거
	int CorridorGridCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorGridCnt; ++i)
	{
		TileIndex CurTile = MapInfo_.CorridorInfo_.AllIndexLists_[i];

		// 해당 타일 제거
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator DelTile = FloorGrides_.find(CurTile.Index_);
		if (FloorGrides_.end() != DelTile)
		{
			// 렌더러 죽이고
			(*DelTile).second->Death();

			// 목록에서 제거
			FloorGrides_.erase(DelTile);
		}
	}

	// 복도 정보 제거
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		MapInfo_.CorridorInfo_.AllIndexLists_.clear();
	}
	MapInfo_.CorridorInfo_ = {};

	// 시작위치 초기화
	RandomStartPos_ = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };
}

void EditorRandomMap::AllRoomClear()
{
	// 룸은 바닥타일

	// 룸 타일 렌더러 제거
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			TileIndex CurTile = MapInfo_.RoomInfo_[i].AllIndexLists_[j];

			// 해당 타일 제거
			std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator DelTile = FloorTiles_.find(CurTile.Index_);
			if (FloorTiles_.end() != DelTile)
			{
				// 렌더러 죽이고
				(*DelTile).second->Death();

				// 목록에서 제거
				FloorTiles_.erase(DelTile);
			}
		}
	}

	// 룸 그리드 렌더러 제거
	for (int i = 0; i < RoomCnt; ++i)
	{
		int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			TileIndex CurTile = MapInfo_.RoomInfo_[i].AllIndexLists_[j];

			// 해당 타일 제거
			std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator DelTile = FloorGrides_.find(CurTile.Index_);
			if (FloorGrides_.end() != DelTile)
			{
				// 렌더러 죽이고
				(*DelTile).second->Death();

				// 목록에서 제거
				FloorGrides_.erase(DelTile);
			}
		}
	}

	// 룸정보 제거
	MapInfo_.RoomInfo_.clear();
}

void EditorRandomMap::AllWallClear()
{
	// 벽/문은 벽타일 렌더러 제거
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = WallTiles_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = WallTiles_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter).second->Death();
	}
	WallTiles_.clear();

	// 벽/문은 벽타일 그리드 렌더러 제거
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridesStartIter = WallGrides_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridesEndIter = WallGrides_.end();
	for (; GridesStartIter != GridesEndIter; ++GridesStartIter)
	{
		(*GridesStartIter).second->Death();
	}
	WallGrides_.clear();

	// 벽/문 정보 삭제
	MapInfo_.WallInfo_.clear();
}

// 1. 랜덤 복도 생성
void EditorRandomMap::CreateRandomCorridor(int _Create, int _Thickness, int _LenTileCount, int _DirCnt)
{
	// 복도 정보 생성
	CreateRandomCorridorInfo(_Create, _Thickness, _LenTileCount, _DirCnt);

	// 복도 정보를 이용하여 화면에 렌더링
	CorridorGridRendering();
}

void EditorRandomMap::CreateRandomCorridorInfo(int _Create, int _Thickness, int _LenTileCount, int _DirCnt)
{
	// 타일타입 셋팅(복도)
	MapInfo_.CorridorInfo_.CorridorType_ = RandomMapTileType::CORRIDOR;
	MapInfo_.CorridorInfo_.TileImageIndex = SelectFloorTileIndex_;
	
	// 복도 정보 생성
	for (int k = 0; k < _Create; ++k) // 생성반복
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
					// 조건1 : 이미 존재하는 타일은 추가하지않는다.
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

void EditorRandomMap::CorridorGridRendering()
{
	// 복도 정보를 이용하여 렌더링
	// 단, 동일한 타일인덱스가 존재한다면 다시 렌더링 안함
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		SetFloorGrid(MapInfo_.CorridorInfo_.AllIndexLists_[i], MapInfo_.CorridorInfo_.CorridorType_);
	}
}

// 2. 복도를 기준으로 룸정보 생성
void EditorRandomMap::CreateRoomArrange(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex)
{
	// 룸 배치 정보 생성
	CreateRoomArrangeInfo(_RoomCount, _MaxWidthIndex, _MaxHeightIndex);

	// 룸 배치정보를 이용하여 화면에 렌더링
	RoomGridRendering();
}

void EditorRandomMap::CreateRoomArrangeInfo(int _RoomCount, int _MaxWidthIndex, int _MaxHeightIndex)
{
	// 복도 정보를 이용하여 룸배치
	GameEngineRandom RoomRandom;

	// 0. 배치하려는 룸갯수만큼 반복
	int RoomCnt = 0;
	for (;;)
	{
		if (_RoomCount <= RoomCnt)
		{
			break;
		}

		// 0. 복도타일정보를 이용하여 룸의 중심타일을 설정
		int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());

		// 조건1: 복도타일정보가 1개만 존재할때
		int RandomIndex = RoomRandom.RandomInt(0, CorridorTileCnt) - 1;
		if (RandomIndex < 0)
		{
			RandomIndex = 0;
		}

		// 조건2: 룸의 센터인덱스가 겹치면 재검색
		TileIndex CenterTile = MapInfo_.CorridorInfo_.AllIndexLists_[RandomIndex];
		if (true == RoomOverlapCheck(CenterTile))
		{
			continue;
		}

		// 2. 룸의 기본정보 셋팅
		RandomRoomInfo NewRoom = {};

		NewRoom.TileType_ = RandomMapTileType::ROOM;
		NewRoom.RoomNo_ = RoomCnt + 1;
		NewRoom.TileImageIndex = SelectFloorTileIndex_;

		// 3. 룸의 크기는 랜덤으로 정해진다(최소 1x1의 룸크기를 만들어낸다.
		int RandomWidthIndex = RoomRandom.RandomInt(1, _MaxWidthIndex);
		int RandomHeightIndex = RoomRandom.RandomInt(1, _MaxHeightIndex);
		NewRoom.WidthIndex_ = RandomWidthIndex;
		NewRoom.HeightIndex_ = RandomHeightIndex;

		// 4. 룸의 중심 설정
		NewRoom.RoomCenterIndex_ = CenterTile;

		// 5. 룸의 중심을 기준으로 룸의 X,Y 최소/최대인덱스를 계산 후 저장
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

		// 6. 현재 생성한 룸의센터 기준인덱스로 변환
		RoomStartX += NewRoom.RoomCenterIndex_.X_;
		RoomEndX += NewRoom.RoomCenterIndex_.X_;
		RoomStartY += NewRoom.RoomCenterIndex_.Y_;
		RoomEndY += NewRoom.RoomCenterIndex_.Y_;

		NewRoom.minIndexX_ = RoomStartX;
		NewRoom.maxIndexX_ = RoomEndX;
		NewRoom.minIndexY_ = RoomStartY;
		NewRoom.maxIndexY_ = RoomEndY;

		// 7. 룸이 차지하는 모든 타일인덱스를 저장
		for (int y = NewRoom.minIndexY_; y < NewRoom.maxIndexY_; ++y)
		{
			for (int x = NewRoom.minIndexX_; x < NewRoom.maxIndexX_; ++x)
			{
				NewRoom.AllIndexLists_.push_back(TileIndex(x, y));
			}
		}

		MapInfo_.RoomInfo_.push_back(NewRoom);

		// 8. CurRoom Cnt 증가
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

bool EditorRandomMap::CorridorOverlapTileIndexCheck(TileIndex _TileIndex)
{
	// 룸 설치시 복도 타일목록에 동일한 타일이 존재하면 복도타일목록에서 제거 후
	// 룸을 설치
	

	return false;
}

void EditorRandomMap::RoomGridRendering()
{
	// 생성된 룸정보를 이용하여 화면에 렌더링
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			// 룸의 센터타일인 경우
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

// 3. 복도/룸 정보를 이용하여 벽/문 정보 생성
void EditorRandomMap::CreateWall()
{
	// 벽/문 정보 생성
	CreateWallInfo();

	// 벽/문 정보를 이용하여 화면에 렌더링
	WallGridRendering();
}

void EditorRandomMap::CreateWallInfo()
{
	// 1. 룸의 벽과 문정보 생성
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		int RoomTileCnt = static_cast<int>(MapInfo_.RoomInfo_[i].AllIndexLists_.size());
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			// 바닥타일은 타일의 중심좌표가 0,0
			float4 FloorCenterPos = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[i].AllIndexLists_[j]);

			// 바닥타일 1개기준 벽타일은 3x3개 생성
			TileIndex WallTileIndex = GetWallTileIndex(FloorCenterPos);

			// 벽타일은 타일의 상단점이 0,0
			for (int y = 0; y < 3; ++y)
			{
				for (int x = 0; x < 3; ++x)
				{
					// 조건1: 이미 존재하는 타일인덱스는 목록에 추가하지않는다.
					if (true == WallOverlapCheck(WallTileIndex))
					{
						WallTileIndex.X_ += 1;
						continue;
					}

					RandomWallInfo NewWall = {};

					// 벽은 바닥타일의 중심을 기점으로 8방향 +1 or -1로 찍힌다.
					NewWall.WallTileIndex_ = WallTileIndex;

					NewWall.WallBasicType_ = RandomWallBasicType::WALL;
					NewWall.WallDetailType_ = RandomWallDetailType::NORMAL; // 초기생성시 Normal타입으로 생성

					NewWall.WallTile1ImageIndex = 0;
					NewWall.WallTile2ImageIndex = 0;
					NewWall.WallTextureName = WallTileTextureName_;
					NewWall.WallTileSize = TileSize_;
					NewWall.WallRenderSize = WallTileImageSize_;
					NewWall.WallRenderPivotPos = WallTileIndexPivotPos_;

					MapInfo_.WallInfo_.push_back(NewWall);

					WallTileIndex.X_ += 1;
				}

				WallTileIndex.X_ = GetWallTileIndex(FloorCenterPos).X_;
				WallTileIndex.Y_ += 1;
			}
		}
	}
	
	// 2. 복도의 벽정보 생성
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		// 바닥타일은 타일의 중심좌표가 0,0
		float4 FloorCenterPos = GetFloorTileIndexToPos(MapInfo_.CorridorInfo_.AllIndexLists_[i]);

		// 바닥타일 1개기준 벽타일은 3x3개 생성
		TileIndex WallTileIndex = GetWallTileIndex(FloorCenterPos);

		// 벽타일은 타일의 상단점이 0,0
		for (int y = 0; y < 3; ++y)
		{
			for (int x = 0; x < 3; ++x)
			{
				// 조건1: 이미 존재하는 타일인덱스는 목록에 추가하지않는다.
				if (true == WallOverlapCheck(WallTileIndex))
				{
					WallTileIndex.X_ += 1;
					continue;
				}

				RandomWallInfo NewWall = {};

				// 벽은 바닥타일의 중심을 기점으로 8방향 +1 or -1로 찍힌다.
				NewWall.WallTileIndex_ = WallTileIndex;

				NewWall.WallBasicType_ = RandomWallBasicType::WALL;
				NewWall.WallDetailType_ = RandomWallDetailType::NORMAL; // 초기생성시 Normal타입으로 생성

				NewWall.WallTile1ImageIndex = 0;
				NewWall.WallTile2ImageIndex = 0;
				NewWall.WallTextureName = WallTileTextureName_;
				NewWall.WallTileSize = TileSize_;
				NewWall.WallRenderSize = WallTileImageSize_;
				NewWall.WallRenderPivotPos = WallTileIndexPivotPos_;

				MapInfo_.WallInfo_.push_back(NewWall);

				WallTileIndex.X_ += 1;
			}

			WallTileIndex.X_ = GetWallTileIndex(FloorCenterPos).X_;
			WallTileIndex.Y_ += 1;
		}
	}

	// 3. 조건에 따라 벽의 기본타입과 상세타입을 결정한다.

	// 1) 복도를 따라서 외곽벽을 설정
	//		WL_RT_T,							// 우상단(좌하단)방향(연속된벽) - 중심기준(0,0) 윗벽
	//		WL_RT_T_RE,							// 우상단방향으로 윗벽의 끝(BENT와 연결되는 벽)
	//		WL_RT_T_LE,							// 좌하단방향으로 윗벽의 끝(BENT직전에 RT가 끝)
	//		WL_RT_B,							// 우상단(좌하단)방향(연속된벽) - 중심기준(0,0) 아랫벽
	//		WL_RT_B_RE,							// 우상단방향으로 아랫벽의 끝(BENT가 끝)
	//		WL_RT_B_LE,							// 좌하단방향으로 아랫벽의 끝(BENT직전에 RT가 끝)
	//		WL_RB_L,							// 우하단(좌상단)방향(연속된벽) - 중심기준(0,0) 왼쪽벽
	//		WL_RB_L_BE,							// 우하단방향으로 왼쪽벽의 끝(BENT직전에 RB가 끝)
	//		WL_RB_L_TE,							// 좌상단방향으로 왼쪽벽의 끝(BENT가 끝)
	//		WL_RB_R,							// 우하단(좌상단)방향(연속된벽) - 중심기준(0,0) 오른쪽벽
	//		WL_RB_R_BE,							// 우하단방향으로 오른쪽벽의 끝(BENT직전에 RB가 끝)
	//		WL_RB_R_TE,							// 좌상단방향으로 오른쪽벽의 끝(BENT와 연결되는 벽)
	//		WL_BENT_MULTI1,						// 꺽이는벽(렌더러를 2개 가진다) - 중심기준(0,0) 우상단꺽이는벽 => RT_T_RE와 RB_R_TE가 만나려고하는 벽(멀티렌더러)
	//		WL_BENT_MULTI2,						// 꺽이는벽(렌더러를 2개 가진다) - 중심기준(0,0) 우상단꺽이는벽 => RT_T_RE와 RB_R_TE가 만나려고하는 벽(멀티렌더러)
	//		WL_BENT_SINGLE,						// 꺽이는벽(렌더러를 1개 가진다) - 중심기준(0,0) 좌하단꺽이는벽 => RT_B_LE와 RB_L_BE가 만나려고하는 벽(단독렌더러)
	int AllWallCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < AllWallCnt; ++i)
	{
		// 현재 벽타일인덱스 Get
		TileIndex CurWallTile = MapInfo_.WallInfo_[i].WallTileIndex_;

		// 현재 타일인덱스의 주변타일을 검사하여 바닥타일이 존재하지않을때를 찾아낸다.
		// 1) 상단 타일만 없는경우(x-1) => RT_T
		

		// 2) 하단 타일만 없는경우(x+1) => RT_B


		// 3) 좌단 타일만 없는경우(y+1) => RB_L


		// 4) 우단 타일만 없는경우(y-1) => RB_R


		// 5) 그외


	}

	// 2) 룸의 벽을 설정
	// 단, 이미 Normal or None Type이라면 벽을 설치안함







	// 3) 룸과 복도를 연결하는 문을 설정






	// 4) 랜덤맵의 내부를 다시 쪼갬

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

void EditorRandomMap::WallGridRendering()
{
	int WallCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallCnt; ++i)
	{
		SetWallGrid(MapInfo_.WallInfo_[i].WallTileIndex_, MapInfo_.WallInfo_[i].WallBasicType_, MapInfo_.WallInfo_[i].WallDetailType_);
	}
}

void EditorRandomMap::TextureMatchingTileRendering()
{
	// 위의 과정에서 현재맵의 모든 정보 및 타일의 타입이 결정났으므로 지정된 텍스쳐와 텍스쳐인덱스로
	// 타일을 렌더링


	// 1. 바닥타일 매칭



	// 2. 벽타일 매칭



}
#pragma endregion
