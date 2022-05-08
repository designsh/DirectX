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
	// 타일
	TileSize_ = float4(160.f, 80.f);
	TileSizeHalf_ = TileSize_.halffloat4();
	TileSizeHHalf_ = TileSizeHalf_.halffloat4();

	// 바닥타일
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
	// 카타콤 텍스쳐로 셋팅
	FloorTileTextureName_ = "Catacombs_Floor.png";
	WallTileTextureName_ = "Catacombs_Wall.png";

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

	// 벽타일
	WallTileImageSize_ = { 160.0f, 480.f };
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
	if (false == _Multidirectional) // 한방향 랜덤 로드(길) 생성
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
	else // 다방향 랜덤 로드(길) 생성
	{
		if (false == FirstRandomLoad_)
		{
			// 최초 생성 Flag On
			FirstRandomLoad_ = true;

			// 최초 생성되었으므로 최대 4방향 랜덤 로드 생성
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
			// 최대 3방향 랜덤 로드 생성
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
	// 인덱스를 이용하여 현재 맵의 범위를 계산
	
	// 기존 맵범위 그리드 Clear
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsStartIter = MapMaxScale_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsEndIter = MapMaxScale_.end();
	for (; GridsStartIter != GridsEndIter; ++GridsStartIter)
	{
		// 세컨드 데스처리
		(*GridsStartIter).second->Death();
	}
	MapMaxScale_.clear();

	// 맵 정보 저장
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

	// 현재 맵 범위의 그리드로 렌더링
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
	// 룸관련
	AllRoomClear();

	// 복도관련
	AllCorridorClear();

	// 

}

void EditorRandomMap::AllRoomClear()
{
	// 방정보 제거
	AllRoomInfomationClear();

	// 방 렌더러 제거
	AllRoomRendererClear();

	// 룸 갯수 초기화
	RoomCnt_ = 0;
}

void EditorRandomMap::AllRoomInfomationClear()
{
	// 방정보 제거
	std::vector<RandomRoomInfo>::iterator StartIter = MapInfo_.RoomInfo_.begin();
	std::vector<RandomRoomInfo>::iterator EndIter = MapInfo_.RoomInfo_.end();
	for (; StartIter != EndIter;)
	{
		MapInfo_.RoomInfo_.erase(StartIter);
		StartIter = MapInfo_.RoomInfo_.begin();
		EndIter = MapInfo_.RoomInfo_.end();
	}
	MapInfo_.RoomInfo_.clear();

	// 룸 갯수 초기화
	RoomCnt_ = 0;
}

void EditorRandomMap::AllRoomRendererClear()
{
	// 방 렌더러 제거
	for (int i = 0; i < static_cast<int>(RoomRenderer_.size()); ++i)
	{
		// 렌더러 삭제
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = RoomRenderer_[i].TileRenderer_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = RoomRenderer_[i].TileRenderer_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			// 세컨드 데스처리
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
		// 세컨드 데스처리
		(*StartIter).second->Death();
	}
	RoomRenderer_[_Index].TileRenderer_.clear();

	std::vector<RoomRender>::iterator RendererStartIter = RoomRenderer_.begin() + _Index;
	RoomRenderer_.erase(RendererStartIter);
}

void EditorRandomMap::AllCorridorClear()
{
	// 복도정보 제거
	AllCorridorInfomationClear();

	// 복도 렌더러 제거
	AllCorridorRendererClear();
}

void EditorRandomMap::AllCorridorInfomationClear()
{
	// 복도정보 제거
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
	// 복도 렌더러 제거
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = CorridorRenderer_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = CorridorRenderer_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// 세컨드 데스처리
		(*StartIter).second->Death();
	}
	CorridorRenderer_.clear();
}

void EditorRandomMap::TotalMapRendererClear()
{
	// 임시주석
	//std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsStartIter = MapMaxScale_.begin();
	//std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsEndIter = MapMaxScale_.end();
	//for (; GridsStartIter != GridsEndIter; ++GridsStartIter)
	//{
	//	// 세컨드 데스처리
	//	(*GridsStartIter).second->Death();
	//}
	//MapMaxScale_.clear();
}

void EditorRandomMap::RandomRoom(int _RoomCnt, int _WidthIndex, int _HeightIndex)
{
	// 생성하려는 룸 갯수에 따라 처리
	if (0 >= _RoomCnt)
	{
		// 사용자가 원하는 시점에 방생성
		CreateRoomManual(_WidthIndex, _HeightIndex);
	}
	else
	{
		// 사용자의 한번의 동작으로 모든 룸을 생성 및 배치
		RoomCnt_ = _RoomCnt;
		CreateRoomAuto(_WidthIndex, _HeightIndex);
	}
}

bool EditorRandomMap::RoomArrangeCheck(int _WidthIndex, int _HeightIndex, int _RoomCnt)
{
	// 너비/높이 랜덤 지정(최소 맵크기 3x3)
	int RandomWidth = RoomRandom_.RandomInt(6, _WidthIndex);
	int RandomHeight = RoomRandom_.RandomInt(6, _HeightIndex);

	// 현재 맵 제한 범위의 랜덤한 위치에 룸의 센터 생성
	int CenterIndexX = RoomRandom_.RandomInt(MapInfo_.minIndexX_, MapInfo_.maxIndexX_);
	int CenterIndexY = RoomRandom_.RandomInt(MapInfo_.minIndexY_, MapInfo_.maxIndexY_);

	// 현재 지정된 센터 인덱스를 기준으로 너비/높이의 방의 크기가 배치가능한지 판단
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

	// 현재 생성한 룸의센터 기준인덱스로 변환
	RoomStartX += CenterIndexX;
	RoomEndX += CenterIndexX;
	RoomStartY += CenterIndexY;
	RoomEndY += CenterIndexY;

	// 현재 생성된 제한된 범위내에 존재하는 룸일때만 생성
	if (MapInfo_.minIndexX_ <= RoomStartX && MapInfo_.maxIndexX_ > RoomEndX &&
		MapInfo_.minIndexY_ <= RoomStartY && MapInfo_.maxIndexY_ > RoomEndY)
	{
		// 룸에 정보 저장
		RandomRoomInfo NewRoom = {};
		NewRoom.TileType_ = RandomMapTileType::ROOM;
		NewRoom.RoomNo_ = _RoomCnt + 1;

		// 현재 생성된 룸의 범위
		NewRoom.minIndexX_ = RoomStartX;
		NewRoom.maxIndexX_ = RoomEndX;
		NewRoom.minIndexY_ = RoomStartY;
		NewRoom.maxIndexY_ = RoomEndY;

		// 현재 생성된 룸의 센터
		NewRoom.RoomCenterIndex_ = TileIndex(CenterIndexX, CenterIndexY);

		// 현재 생성된 룸의 크기
		NewRoom.WidthIndex_ = RandomWidth;
		NewRoom.HeightIndex_ = RandomHeight;

		// 현재 생성된 룸의 모든 타일인덱스 저장
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
		// 자동으로 룸 갯수만큼 생성
		if(false == RoomArrangeCheck(_WidthIndex, _HeightIndex, RoomCnt_ - RoomCnt))
		{
			// 룸 생성 실패로 리턴
			continue;
		}

		--RoomCnt;
	}

	// 자동으로 생성된 룸을 화면에 렌더링
	RenderingAutoRoom();
}

void EditorRandomMap::RenderingAutoRoom()
{
	// 룸을 한번에 렌더링
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
	// 동작마다 룸 생성

	// 현재 생성되는 룸이 현재 맵의 제한범위내 존재하는지 체크
	if(false == RoomArrangeCheck(_WidthIndex, _HeightIndex, RoomCnt_))
	{
		// 룸 생성 실패로 리턴
		return;
	}

	// 생성된 룸의 정보를 이용하여 화면에 렌더링
	RenderingManualRoom();

	// 생성된 룸갯수 갱신
	++RoomCnt_;
}

void EditorRandomMap::RenderingManualRoom()
{
	// 룸정보를 이용하여 화면에 렌더링
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
	// 기존 룸 렌더러 모두 삭제
	AllRoomRendererClear();

	// 현재 생성된 룸정보들을 검사하여 룸이 서로 겹치는 룸은 서로 밀어내기 처리
	int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCnt; ++i)
	{
		// 룸 한개 선택
		RandomRoomInfo CurRoomInfo = MapInfo_.RoomInfo_[i];

		// 룸 이동방향 결정
#pragma region 이동방향결정
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

		// 모든 룸을 검사하여 겹쳐지지않는곳까지 이동
		if (true == RoomIntersectsMoveCheck(i, TileMoveDir))
		{
		}
	}

	// 재배치 룸정보 모두 완료시 전체맵 제한 렌더링 삭제
	TotalMapRendererClear();

	// 현재 검사가 종료된 모든 룸 렌더링
	RenderingAutoRoom();
}

bool EditorRandomMap::RoomIntersectsMoveCheck(int _CurIndex, float4 _Dir)
{
	bool MoveChkFlag = false;
	int StandardRoomTileListsCnt = static_cast<int>(MapInfo_.RoomInfo_[_CurIndex].AllIndexLists_.size());
	while (true)
	{
		// 본인을 제외한 모든 방과 겹쳐지는지 체크
		// 한개의 룸이라도 겹쳐진다면 계속하여 이동
		int AllRoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
		for (int k = 0; k < AllRoomCnt; ++k)
		{
			MoveChkFlag = false;

			// 본인 룸 제외
			if (MapInfo_.RoomInfo_[_CurIndex].RoomNo_ == MapInfo_.RoomInfo_[k].RoomNo_)
			{
				continue;
			}

			// 본인룸이 아닌데도 현재 겹쳐있다면 이동
			int CompareRoomTileListsCnt = static_cast<int>(MapInfo_.RoomInfo_[k].AllIndexLists_.size());
			for (int i = 0; i < StandardRoomTileListsCnt; ++i)
			{
				for (int j = 0; j < CompareRoomTileListsCnt; ++j)
				{
					// 현재 룸의 이동방향에 따라 
					if (MapInfo_.RoomInfo_[_CurIndex].AllIndexLists_[i].X_ == MapInfo_.RoomInfo_[k].AllIndexLists_[j].X_ + _Dir.ix() &&
						MapInfo_.RoomInfo_[_CurIndex].AllIndexLists_[i].Y_ == MapInfo_.RoomInfo_[k].AllIndexLists_[j].Y_ + _Dir.iy())
					{
						MoveChkFlag = true;

						// 타일을 2칸씩 이동
						MapInfo_.RoomInfo_[_CurIndex].minIndexX_ += _Dir.ix();
						MapInfo_.RoomInfo_[_CurIndex].maxIndexX_ += _Dir.ix();
						MapInfo_.RoomInfo_[_CurIndex].minIndexY_ += _Dir.iy();
						MapInfo_.RoomInfo_[_CurIndex].maxIndexY_ += _Dir.iy();

						// 현재 룸의 센터위치 재설정
						MapInfo_.RoomInfo_[_CurIndex].RoomCenterIndex_ = MapInfo_.RoomInfo_[_CurIndex].RoomCenterIndex_ + TileIndex(_Dir.ix(), _Dir.iy());

						// 현재 타일의 인덱스 정보 갱신
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
	// 각 룸에서의 다른 룸과의 거리 목록을 생성
	int RoomCount = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCount; ++i)
	{
		// 가장 인접한 룸과 가장 멀리있는 룸의 No를 저장
		SearchRoomDistance(i);
	}

	// 모든 룸의 거리목록을 이용하여 현재룸의 인접룸과 가장 멀리떨어져있는 룸을 찾아내서 저장
	for (int i = 0; i < RoomCount; ++i)
	{
		// 현재 체크하는 룸 Get
		RandomRoomInfo CurCheckRoom = MapInfo_.RoomInfo_[i];

		// 연결가능한 모든 룸을 탐색 후 인접룸, 가장멀리 있는 룸 셋팅


		






		// 220509 SJH 임시용
		// 정렬되었으므로 벡터의 0번째가 가장 인접한 룸
		MapInfo_.RoomInfo_[i].AdjacentRoomNo_ = CurCheckRoom.AllRoomDistList_[0].first;

		// 마지막번째가 가장 멀리있는 룸
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
		// 본인 룸 제외
		if (MapInfo_.RoomInfo_[_CheckIndex].RoomNo_ == MapInfo_.RoomInfo_[i].RoomNo_)
		{
			continue;
		}

		// 모든 룸과의 거리 측정(각 룸의 센터인덱스 기준)
		float4 CheckRoomPos = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[i].RoomCenterIndex_);

		// 기준 인덱스의 위치와 현재 거리체크하는 인덱스의 거리를 계산
		// => 두 벡터사이의 거리측정 후 목록에 저장
		float Length = float4::Distance(CurRoomPos, CheckRoomPos);
		RoomDistanceMap.insert(std::make_pair(MapInfo_.RoomInfo_[i].RoomNo_, Length));
	}

	// 룸번호로 정렬한 작성된 목록을 거리를 이용하여 재정렬
	std::vector<std::pair<int, float>> ReSortVector(RoomDistanceMap.begin(), RoomDistanceMap.end());
	std::sort(ReSortVector.begin(), ReSortVector.end(), EditorRandomMap::Compare);

	// 현재 체크하는 룸과 각각의 모든 룸과의 거리를 측정하여 목록 저장
	MapInfo_.RoomInfo_[_CheckIndex].AllRoomDistList_ = ReSortVector;
}

void EditorRandomMap::RoomConnection()
{
	// 룸센터-룸센터 복도 연결
	// 룸의 센터인덱스정보를 이용하여 룸과룸의 센터를 연결하는 복도 생성
	int RoomCount = static_cast<int>(MapInfo_.RoomInfo_.size());
	for (int i = 0; i < RoomCount; ++i)
	{
		// 룸 선택
		RandomRoomInfo CurRoomInfo = MapInfo_.RoomInfo_[i];

		// 룸(방)이 가장 인접한 룸을 알고있기 때문에 가장 인접한 룸과 연결을 하고,
		// 연결된 룸의 번호를 목록(ConnectionRoomList_)에 저장한다.
		if (0 < CurRoomInfo.AdjacentRoomNo_)
		{
			RoomConnectionStart(CurRoomInfo.RoomNo_ - 1, CurRoomInfo.AdjacentRoomNo_ - 1);
		}
	}

	// 현재 생성된 모든 복도 렌더링
	AllCorridorRendering();
}

void EditorRandomMap::RoomConnectionStart(int _CurIndex, int _ConnectionIndex)
{
	// 현재 연결하려는 룸과 이미 연결되어있는지 체크
	int ConnectionRoomCnt = static_cast<int>(MapInfo_.RoomInfo_[_ConnectionIndex].ConnectionRoomList_.size());
	for (int i = 0; i < ConnectionRoomCnt; ++i)
	{
		// 이미 연결되어있다면 리턴
		if (MapInfo_.RoomInfo_[_ConnectionIndex].ConnectionRoomList_[i] == MapInfo_.RoomInfo_[_CurIndex].RoomNo_)
		{
			return;
		}
	}

	// 연결하려는 룸의 위치에따라 현재 룸에서 복도를 뚫은 구간을 선택
	ConnectRoomDir(_CurIndex, _ConnectionIndex);

	// 진행 방향 결정 완료되었으므로 현재룸에서 연결하려는 룸의 센터까지 연결시작
	SetCorridorTile(_CurIndex, _ConnectionIndex);
}

void EditorRandomMap::ConnectRoomDir(int _CurIndex, int _ConnectionIndex)
{
	float4 CurRoomCenter = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[_CurIndex].RoomCenterIndex_);
	float4 ConnectionRoomCenter = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_);
	float4 Dir = (ConnectionRoomCenter - CurRoomCenter).NormalizeReturn3D();

	// 1. 좌상단
	if (Dir.x < 0.f && Dir.y >= 0.f)
	{
		MapInfo_.RoomInfo_[_CurIndex].CenterType_ = RoomCenterDirType::DIRTC_T;
	}
	// 2. 우상단
	else if (Dir.x >= 0.f && Dir.y >= 0.f)
	{
		MapInfo_.RoomInfo_[_CurIndex].CenterType_ = RoomCenterDirType::DIRTC_R;
	}
	// 3. 우하단
	else if (Dir.x >= 0.f && Dir.y < 0.f)
	{
		MapInfo_.RoomInfo_[_CurIndex].CenterType_ = RoomCenterDirType::DIRTC_B;
	}
	// 4. 좌하단
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
				// 1. x인덱스 감소(목표타일 인덱스까지), y인덱스 현재룸의 센터 인덱스와 동일
				if (CorridorTileIndex.X_ != MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.X_)
				{
					CorridorTileIndex.X_ -= 1;

					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. 모두 완료되었다면 연결된 복도를 2줄로 만든다


						// 4. 완료된 복도 정보 모두 저장
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// 타일 정보 저장
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
				// 2. 목표타일 위치까지 x인덱스가 모두 감소하였다면 y인덱스를 목표 인덱스까지 이동
				else
				{
					// 목표타일인덱스까지 연결하는데 증가해야하는지 감소해야하는지 판단
					if (CorridorTileIndex.Y_ < MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.Y_)
					{
						// y 인덱스 증가
						CorridorTileIndex.Y_ += 1;
					}
					else
					{
						// y인덱스 감소
						CorridorTileIndex.Y_ -= 1;
					}

					// 현재 생성된 복도타일의 인덱스가 목표타일인덱스와 동일하면 반복문 중단
					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. 모두 완료되었다면 연결된 복도를 2줄로 만든다


						// 4. 완료된 복도 정보 모두 저장
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// 타일 정보 저장
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
			}
			break;
		}
		case RoomCenterDirType::DIRTC_B:
		{
			while (true)
			{
				// 1. x인덱스 증가(목표타일 인덱스까지), y인덱스 현재룸의 센터 인덱스와 동일
				if (CorridorTileIndex.X_ != MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.X_)
				{
					CorridorTileIndex.X_ += 1;

					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. 모두 완료되었다면 연결된 복도를 2줄로 만든다


						// 4. 완료된 복도 정보 모두 저장
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// 타일 정보 저장
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
				// 2. 목표타일 위치까지 x인덱스가 모두 감소하였다면 y인덱스를 목표 인덱스까지 이동
				else
				{
					// 목표타일인덱스까지 연결하는데 증가해야하는지 감소해야하는지 판단
					if (CorridorTileIndex.Y_ < MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.Y_)
					{
						// y 인덱스 증가
						CorridorTileIndex.Y_ += 1;
					}
					else
					{
						// y인덱스 감소
						CorridorTileIndex.Y_ -= 1;
					}

					// 현재 생성된 복도타일의 인덱스가 목표타일인덱스와 동일하면 반복문 중단
					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. 모두 완료되었다면 연결된 복도를 2줄로 만든다


						// 4. 완료된 복도 정보 모두 저장
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// 타일 정보 저장
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
			}
			break;
		}
		case RoomCenterDirType::DIRTC_L:
		{
			while (true)
			{
				// 1. y인덱스 증가(목표타일 인덱스까지), x인덱스 현재룸의 센터 인덱스와 동일
				if (CorridorTileIndex.Y_ != MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.Y_)
				{
					CorridorTileIndex.Y_ += 1;

					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. 모두 완료되었다면 연결된 복도를 2줄로 만든다


						// 4. 완료된 복도 정보 모두 저장
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// 타일 정보 저장
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
				// 2. 목표타일 위치까지 y인덱스가 모두 감소하였다면 x인덱스를 목표 인덱스까지 이동
				else
				{
					// 목표타일인덱스까지 연결하는데 증가해야하는지 감소해야하는지 판단
					if (CorridorTileIndex.X_ < MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.X_)
					{
						// y 인덱스 증가
						CorridorTileIndex.X_ += 1;
					}
					else
					{
						// y인덱스 감소
						CorridorTileIndex.X_ -= 1;
					}

					// 현재 생성된 복도타일의 인덱스가 목표타일인덱스와 동일하면 반복문 중단
					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. 모두 완료되었다면 연결된 복도를 2줄로 만든다


						// 4. 완료된 복도 정보 모두 저장
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// 타일 정보 저장
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
			}
			break;
		}
		case RoomCenterDirType::DIRTC_R:
		{
			while (true)
			{
				// 1. y인덱스 감소(목표타일 인덱스까지), x인덱스 현재룸의 센터 인덱스와 동일
				if (CorridorTileIndex.Y_ != MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.Y_)
				{
					CorridorTileIndex.Y_ -= 1;

					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. 모두 완료되었다면 연결된 복도를 2줄로 만든다


						// 4. 완료된 복도 정보 모두 저장
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// 타일 정보 저장
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
				// 2. 목표타일 위치까지 y인덱스가 모두 감소하였다면 x인덱스를 목표 인덱스까지 이동
				else
				{
					// 목표타일인덱스까지 연결하는데 증가해야하는지 감소해야하는지 판단
					if (CorridorTileIndex.X_ < MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_.X_)
					{
						// y 인덱스 증가
						CorridorTileIndex.X_ += 1;
					}
					else
					{
						// y인덱스 감소
						CorridorTileIndex.X_ -= 1;
					}

					// 현재 생성된 복도타일의 인덱스가 목표타일인덱스와 동일하면 반복문 중단
					if (CorridorTileIndex == MapInfo_.RoomInfo_[_ConnectionIndex].RoomCenterIndex_)
					{
						// 3. 모두 완료되었다면 연결된 복도를 2줄로 만든다


						// 4. 완료된 복도 정보 모두 저장
						MapInfo_.CorridorInfo_.push_back(NewCorridorInfo);
						break;
					}

					// 타일 정보 저장
					NewCorridorInfo.AllIndexLists_.push_back(CorridorTileIndex);
				}
			}
			break;
		}
	}

	// 연결 완료되었다면 연결된 룸의 번호를 목록(ConnectionRoomList_)에 저장
	MapInfo_.RoomInfo_[_CurIndex].ConnectionRoomList_.push_back(MapInfo_.RoomInfo_[_ConnectionIndex].RoomNo_);
}

void EditorRandomMap::CorridorRendering(int _Index)
{
	// 복도 렌더링
	int TileIndexCnt = static_cast<int>(MapInfo_.CorridorInfo_[_Index].AllIndexLists_.size());
	for (int i = 0; i < TileIndexCnt; ++i)
	{
		TileIndex Index = MapInfo_.CorridorInfo_[_Index].AllIndexLists_[i];

		// 겹치는 타일인덱스가 존재하면 렌더링 안함
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

			// 겹치는 타일인덱스가 존재하면 렌더링 안함
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
	// 룸/복도 벽정보 생성


}

void EditorRandomMap::CreateDoor()
{
	// 룸-복도-룸 진입점에 문정보 생성


}
