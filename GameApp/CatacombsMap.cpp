#include "PreCompile.h"
#include "CatacombsMap.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineTileMapRenderer.h>
#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"
#include "MainPlayer.h"
#include "Andariel.h"

CatacombsMap::CatacombsMap() :
	MapInfo_{},
	Navigation_(nullptr)
{
}

CatacombsMap::~CatacombsMap()
{
	if (nullptr != Navigation_)
	{
		delete Navigation_;
		Navigation_ = nullptr;
	}
}

void CatacombsMap::Start()
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
}

void CatacombsMap::Update(float _DeltaTime)
{
}

TileIndex CatacombsMap::GetFloorTileIndex(float4 _Pos)
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

TileIndex CatacombsMap::GetWallTileIndex(float4 _Pos)
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

float4 CatacombsMap::GetWallTileIndexToPos(TileIndex _TileIndex)
{
	// 네비게이션 타일인덱스를 월드상의 위치값으로 변환해서 반환
	float4 TilePos = float4::ZERO;
	TilePos.x = (_TileIndex.X_ - _TileIndex.Y_) * TileSize_.halffloat4().halffloat4().x;
	TilePos.y = (_TileIndex.X_ + _TileIndex.Y_) * -TileSize_.halffloat4().halffloat4().y;

	return TilePos;
}

float4 CatacombsMap::GetFloorTileIndexToPos(TileIndex _TileIndex)
{
	float4 TilePos = float4::ZERO;
	TilePos.x = (_TileIndex.X_ - _TileIndex.Y_) * TileSize_.halffloat4().x;
	TilePos.y = (_TileIndex.X_ + _TileIndex.Y_) * -TileSize_.halffloat4().y;

	return TilePos;
}

void CatacombsMap::SetFloorTile(float4 _Pos, int CurTileIndex_)
{
	SetFloorTile(GetFloorTileIndex(_Pos), CurTileIndex_);
}

void CatacombsMap::SetFloorTile(TileIndex _Index, int CurTileIndex_)
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
	//FloorTileRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
	//FloorTileRenderer->GetTransform()->SetLocalZOrder(-static_cast<float>(_Index.X_ + _Index.Y_));

	float4 FloorPos = FloorTileIndexPivotPos_ + Pos;
	FloorPos.z = 9000000.f;
	FloorTileRenderer->GetTransform()->SetLocalPosition(FloorPos);


	FloorTileRenderer->SetIndex(CurTileIndex_);
	FloorTiles_.insert(std::make_pair(_Index.Index_, FloorTileRenderer));
}

void CatacombsMap::SetWallTile(float4 _Pos, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex)
{
	SetWallTile(GetWallTileIndex(_Pos), CurTileIndex_, _Type, _Multi2TileIndex);
}

void CatacombsMap::SetWallTile(TileIndex _Index, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex)
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

void CatacombsMap::MapInfoAllClear()
{
	// 복도 정보 및 렌더러 제거
	AllCorridorClear();

	// 룸 정보 및 렌더러 제거
	AllRoomClear();

	// 벽/문 정보 및 렌더러 제거
	AllWallClear();
}

void CatacombsMap::AllCorridorClear()
{	
	// 복도 타일 렌더러 제거
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		TileIndex CurTile = MapInfo_.CorridorInfo_.AllIndexLists_[i];

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

	// 복도 정보 제거
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		MapInfo_.CorridorInfo_.AllIndexLists_.clear();
	}
	MapInfo_.CorridorInfo_ = {};
}

void CatacombsMap::AllRoomClear()
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

	// 룸정보 제거
	MapInfo_.RoomInfo_.clear();
}

void CatacombsMap::AllWallClear()
{
	// 벽/문은 벽타일 렌더러 제거
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

	// 벽/문 정보 삭제
	MapInfo_.WallInfo_.clear();
}

void CatacombsMap::MapTextureCutting()
{
	GameEngineTexture* CatacombsFloorTile = GameEngineTextureManager::GetInst().Find("Catacombs_Floor.png");
	CatacombsFloorTile->Cut(5, 15);
	GameEngineTexture* CatacombsWallTile = GameEngineTextureManager::GetInst().Find("Catacombs_Wall.png");
	CatacombsWallTile->Cut(47, 1);
	GameEngineTexture* CatacombsObjectTile = GameEngineTextureManager::GetInst().Find("Catacombs_Object.png");
	CatacombsObjectTile->Cut(25, 1);
}

void CatacombsMap::CatacombsMapLoad()
{
	// 기존 맵정보 클리어
	MapInfoAllClear();

	// 맵관련 텍스쳐 컷팅
	MapTextureCutting();

	// 현재 맵을 로드
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("MapFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "CatacombsLevel_Map.dat";

	// 파일 열기
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	// 0. 랜덤맵 기본정보 저장

	// 바닥타일 텍스쳐명
	pFile.Read(MapInfo_.FloorTileTextureName_);

	// 벽타일 텍스쳐명
	pFile.Read(MapInfo_.WallTileTextureName_);

	// 1. 복도 관련 정보

	// 타일타입(복도)
	int CorridorType;
	pFile.Read(CorridorType);
	MapInfo_.CorridorInfo_.CorridorType_ = static_cast<RandomMapTileType>(CorridorType);

	// 복도 타일의 이미지인덱스
	pFile.Read(MapInfo_.CorridorInfo_.TileImageIndex);

	// 현재 생성된 복도의 모든 타일 인덱스(렌더링용도)
	int CorridorTileCnt;
	pFile.Read(CorridorTileCnt);
	MapInfo_.CorridorInfo_.AllIndexLists_.resize(CorridorTileCnt);
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		pFile.Read(MapInfo_.CorridorInfo_.AllIndexLists_[i].X_);
		pFile.Read(MapInfo_.CorridorInfo_.AllIndexLists_[i].Y_);
	}

	// 2. 룸 관련 정보

	// 해당 맵의 룸 목록
	int RoomCnt;
	pFile.Read(RoomCnt);
	MapInfo_.RoomInfo_.resize(RoomCnt);
	for (int i = 0; i < RoomCnt; ++i)
	{
		// 타일타입(룸)
		int TileType;
		pFile.Read(TileType);
		MapInfo_.RoomInfo_[i].TileType_ = static_cast<RandomMapTileType>(TileType);

		// 룸 번호(생성번호)
		pFile.Read(MapInfo_.RoomInfo_[i].RoomNo_);

		// 룸 타일의 이미지인덱스
		pFile.Read(MapInfo_.RoomInfo_[i].TileImageIndex);

		// 룸의 크기 가로(타일의 Y인덱스) 인덱스
		pFile.Read(MapInfo_.RoomInfo_[i].WidthIndex_);

		// 룸의 크기 세로(타일의 X인덱스) 인덱스
		pFile.Read(MapInfo_.RoomInfo_[i].HeightIndex_);

		// 룸이 차지하는 인덱스 X의 최소 인덱스
		pFile.Read(MapInfo_.RoomInfo_[i].minIndexX_);

		// 룸이 차지하는 인덱스 Y의 최대 인덱스
		pFile.Read(MapInfo_.RoomInfo_[i].maxIndexX_);

		// 룸이 차지하는 인덱스 X의 최소 인덱스
		pFile.Read(MapInfo_.RoomInfo_[i].minIndexY_);

		// 룸이 차지하는 인덱스 Y의 최대 인덱스
		pFile.Read(MapInfo_.RoomInfo_[i].maxIndexY_);

		// 룸의 센터 인덱스
		pFile.Read(MapInfo_.RoomInfo_[i].RoomCenterIndex_.X_);
		pFile.Read(MapInfo_.RoomInfo_[i].RoomCenterIndex_.Y_);

		// 현재 생성된 룸의 모든 타일 인덱스
		int RoomTileCnt = 0;
		pFile.Read(RoomTileCnt);
		MapInfo_.RoomInfo_[i].AllIndexLists_.resize(RoomTileCnt);
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			pFile.Read(MapInfo_.RoomInfo_[i].AllIndexLists_[j].X_);
			pFile.Read(MapInfo_.RoomInfo_[i].AllIndexLists_[j].Y_);
		}

		// 현재 룸과 가장 멀리 떨어져있는 룸번호
		pFile.Read(MapInfo_.RoomInfo_[i].TheFarthestRoomNo_);
	}

	// 3. 벽 관련 정보(네비게이션 정보로 사용)
	int WallCnt = 0;
	pFile.Read(WallCnt);
	MapInfo_.WallInfo_.resize(WallCnt);
	for (int i = 0; i < WallCnt; ++i)
	{
		// 타일인덱스
		pFile.Read(MapInfo_.WallInfo_[i].WallTileIndex_.X_);
		pFile.Read(MapInfo_.WallInfo_[i].WallTileIndex_.Y_);

		// 현재 벽의 타일기준 4방향 타일을 체크하여 
		// 바닥타일 존재여부에 따라 Flag를 저장
		int SearchCnt = 0;
		pFile.Read(SearchCnt);
		MapInfo_.WallInfo_[i].SearchTileFlag_.resize(SearchCnt);
		for (int j = 0; j < SearchCnt; ++j)
		{
			int Flag = 0;
			pFile.Read(Flag);
			if (1 == Flag)
			{
				MapInfo_.WallInfo_[i].SearchTileFlag_[j] = true;
			}
			else
			{
				MapInfo_.WallInfo_[i].SearchTileFlag_[j] = false;
			}
		}

		// 벽타일 기본타입
		int BasicType;
		pFile.Read(BasicType);
		MapInfo_.WallInfo_[i].WallBasicType_ = static_cast<RandomWallBasicType>(BasicType);

		// 벽타일 상세타입
		int DetailType;
		pFile.Read(DetailType);
		MapInfo_.WallInfo_[i].WallDetailType_ = static_cast<RandomWallDetailType>(DetailType);

		// 일반적인 벽은 한개의 렌더링만 가짐
		pFile.Read(MapInfo_.WallInfo_[i].WallTile1ImageIndex_);

		// 특수한 벽은 2개의 렌더링을 가짐
		pFile.Read(MapInfo_.WallInfo_[i].WallTile2ImageIndex_);

		// 벽텍스쳐 이름
		pFile.Read(MapInfo_.WallInfo_[i].WallTextureName_);

		// 벽타일 크기
		int TileSizeX = 0;
		int TileSizeY = 0;
		int TileSizeZ = 0;
		pFile.Read(TileSizeX);
		pFile.Read(TileSizeY);
		pFile.Read(TileSizeZ);
		MapInfo_.WallInfo_[i].WallTileSize_ = float4(static_cast<float>(TileSizeX), static_cast<float>(TileSizeY), static_cast<float>(TileSizeZ));

		// 벽타일 렌더링크기
		int RenderSizeX = 0;
		int RenderSizeY = 0;
		int RenderSizeZ = 0;
		pFile.Read(RenderSizeX);
		pFile.Read(RenderSizeY);
		pFile.Read(RenderSizeZ);
		MapInfo_.WallInfo_[i].WallRenderSize_ = float4(static_cast<float>(RenderSizeX), static_cast<float>(RenderSizeY), static_cast<float>(RenderSizeZ));

		// 벽타일 렌더링 피벗
		int RenderPivotPosX = 0;
		int RenderPivotPosY = 0;
		int RenderPivotPosZ = 0;
		pFile.Read(RenderPivotPosX);
		pFile.Read(RenderPivotPosY);
		pFile.Read(RenderPivotPosZ);
		MapInfo_.WallInfo_[i].WallRenderPivotPos_ = float4(static_cast<float>(RenderPivotPosX), static_cast<float>(RenderPivotPosY), static_cast<float>(RenderPivotPosZ));
	}

	pFile.Close();

	// 정보를이용하여 렌더링 시작
	MapRendering();

	// 플레이어 위치 갱신
	MainPlayerRoomArrange();

	// 네비게이션 정보 생성
	CreateNavigationInfo();
}

void CatacombsMap::MapRendering()
{
	// 바닥타일 렌더링
	FloorTileTextureMatching();

	// 벽타일 렌더링
	WallTileTextureMatching();

	// 문타일 렌더링
	DoorTileTextureMatching();
}

void CatacombsMap::FloorTileTextureMatching()
{
	// 복도
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		SetFloorTile(MapInfo_.CorridorInfo_.AllIndexLists_[i], MapInfo_.CorridorInfo_.TileImageIndex);
	}

	// 룸
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

void CatacombsMap::WallTileTextureMatching()
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

void CatacombsMap::DoorTileTextureMatching()
{
	int WallCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallCnt; ++i)
	{
		// 문타일 타입인 정보만 렌더링
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

void CatacombsMap::MainPlayerRoomArrange()
{
	// 현재 맵의 룸 중에 랜덤으로 룸을 결정하여 플레이어 위치 결정 및 정보갱신
	// 정보 : 이동용 네비게이션맵, 위치정보, ...

	// 최초 플레이어 배치 룸번호 결정(랜덤)
	GameEngineRandom RandomRoom;
	int PlayerArrRoomNo = RandomRoom.RandomInt(0, static_cast<int>(MapInfo_.RoomInfo_.size() - 1));

	// 플레이어 존재시 플레이어를 랜덤한 룸의 센터에 배치
	if (nullptr != GlobalValue::CurPlayer)
	{
		// 최초 플레이어 배치 룸번호 저장
		GlobalValue::CurPlayer->ArrangeRoomNo_ = MapInfo_.RoomInfo_[PlayerArrRoomNo].RoomNo_;

		// 플레이어 랜덤한 룸의 센터로 이동
		float4 PlayerPos = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[PlayerArrRoomNo].RoomCenterIndex_);
		GlobalValue::CurPlayer->GetTransform()->SetWorldPosition(PlayerPos);
		GetLevel()->GetMainCameraActor()->GetTransform()->SetWorldPosition(GlobalValue::CurPlayer->GetTransform()->GetLocalPosition());

		// 플레이어가 배치된 룸을 제외한 모든룸에 몬스터 배치
		// 플레이어가 배치된 룸과 가장멀리 떨어져있는 룸에 보스몬스터 배치
		int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
		for (int i = 0; i < RoomCnt; ++i)
		{
			// 플레이어가 배치된 룸을 제외한 모든룸에 몬스터 배치 처리
			if (GlobalValue::CurPlayer->ArrangeRoomNo_ != MapInfo_.RoomInfo_[i].RoomNo_)
			{
				// 플레이어가 최초 배치된 룸과 가장멀리 떨어져있는 룸이라면
				if (MapInfo_.RoomInfo_[GlobalValue::CurPlayer->ArrangeRoomNo_ - 1].TheFarthestRoomNo_ == MapInfo_.RoomInfo_[i].RoomNo_)
				{
					// 보스 배치


					// GlobalValue::Andariel


					// 일반 몬스터 배치


					int a = 0;
				}
				// 아닌경우
				else
				{
					// 일반몬스터 배치


					int a = 0;
				}
			}
			else
			{
				int a = 0;
			}
		}
	}
}

void CatacombsMap::CreateNavigationInfo()
{
	// 네비게이션정보생성
	int WallInfoCnt = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallInfoCnt; ++i)
	{
		if (MapInfo_.WallInfo_[i].WallDetailType_ == RandomWallDetailType::NORMAL)
		{
			NavCatacombsMap_.insert(std::make_pair(MapInfo_.WallInfo_[i].WallTileIndex_.Index_, NavigationType::NOR));
		}
		else if (MapInfo_.WallInfo_[i].WallDetailType_ == RandomWallDetailType::DR_RT_L)
		{
			NavCatacombsMap_.insert(std::make_pair(MapInfo_.WallInfo_[i].WallTileIndex_.Index_, NavigationType::NOR));
		}
		else if (MapInfo_.WallInfo_[i].WallDetailType_ == RandomWallDetailType::DR_RB_B)
		{
			NavCatacombsMap_.insert(std::make_pair(MapInfo_.WallInfo_[i].WallTileIndex_.Index_, NavigationType::NOR));
		}
		else
		{
			NavCatacombsMap_.insert(std::make_pair(MapInfo_.WallInfo_[i].WallTileIndex_.Index_, NavigationType::WALL));
		}
	}

	// 네비게이션 생성
	Navigation_ = new GameEnginePathFind();
}

bool CatacombsMap::Moveable4WaysCheck(PathIndex _PathIndex)
{
	TileIndex CheckTileIndex;
	CheckTileIndex.X_ = _PathIndex.X_;
	CheckTileIndex.Y_ = _PathIndex.Y_;

	// 네비게이션 인덱스 타입에 존재하는 인덱스이며, Wall타입이면 이동불가판정
	if (NavCatacombsMap_.end() != NavCatacombsMap_.find(CheckTileIndex.Index_))
	{
		if (NavCatacombsMap_[CheckTileIndex.Index_] == NavigationType::WALL)
		{
			return true;
		}
	}

	return false;
}

bool CatacombsMap::Moveable8WaysCheck(PathIndex _PathIndex)
{
	TileIndex CheckTileIndex;
	CheckTileIndex.X_ = _PathIndex.X_;
	CheckTileIndex.Y_ = _PathIndex.Y_;

	// 네비게이션 인덱스 타입에 존재하는 인덱스이며, Wall타입이면 이동불가판정
	if (NavCatacombsMap_.end() != NavCatacombsMap_.find(CheckTileIndex.Index_))
	{
		if (NavCatacombsMap_[CheckTileIndex.Index_] == NavigationType::WALL)
		{
			return true;
		}
	}

	return false;
}

std::list<PathIndex> CatacombsMap::NavgationFind4Way(float4 _StartPos, float4 _MouseClickPos)
{
	if (nullptr != Navigation_)
	{
		// 플레이어의 현재위치를 이용하여 타일인덱스 계산
		TileIndex StartIndex = GetWallTileIndex(_StartPos);

		// 마우스왼쪽버튼클릭 위치를 이용하여 타일인덱스 계산
		float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
		TileIndex TargetIndex = GetWallTileIndex(_MouseClickPos + CamPos);

		return Navigation_->AStarFind4Way(PathIndex(StartIndex.X_, StartIndex.Y_), PathIndex(TargetIndex.X_, TargetIndex.Y_), std::bind(&CatacombsMap::Moveable4WaysCheck, this, std::placeholders::_1));
	}

	return std::list<PathIndex>();
}

std::list<PathIndex> CatacombsMap::NavgationFind8Way(float4 _StartPos, float4 _MouseClickPos)
{
	if (nullptr != Navigation_)
	{
		// 플레이어의 현재위치를 이용하여 타일인덱스 계산
		TileIndex StartIndex = GetWallTileIndex(_StartPos);

		// 마우스왼쪽버튼클릭 위치를 이용하여 타일인덱스 계산
		float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
		TileIndex TargetIndex = GetWallTileIndex(_MouseClickPos + CamPos);

		return Navigation_->AStarFind8Way(PathIndex(StartIndex.X_, StartIndex.Y_), PathIndex(TargetIndex.X_, TargetIndex.Y_), std::bind(&CatacombsMap::Moveable8WaysCheck, this, std::placeholders::_1));
	}

	return std::list<PathIndex>();
}
