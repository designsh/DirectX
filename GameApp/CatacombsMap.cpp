#include "PreCompile.h"
#include "CatacombsMap.h"

#include <GameEngine/GameEngineTileMapRenderer.h>

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
	// ���� ���� �� ������ ����
	AllCorridorClear();

	// �� ���� �� ������ ����
	AllRoomClear();

	// ��/�� ���� �� ������ ����
	AllWallClear();
}

void CatacombsMap::AllCorridorClear()
{	
	// ���� Ÿ�� ������ ����
	int CorridorTileCnt = static_cast<int>(MapInfo_.CorridorInfo_.AllIndexLists_.size());
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		TileIndex CurTile = MapInfo_.CorridorInfo_.AllIndexLists_[i];

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

	// ���� ���� ����
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		MapInfo_.CorridorInfo_.AllIndexLists_.clear();
	}
	MapInfo_.CorridorInfo_ = {};
}

void CatacombsMap::AllRoomClear()
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

	// ������ ����
	MapInfo_.RoomInfo_.clear();
}

void CatacombsMap::AllWallClear()
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

	// ��/�� ���� ����
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
	// ���� ������ Ŭ����
	MapInfoAllClear();

	// �ʰ��� �ؽ��� ����
	MapTextureCutting();

	// ���� ���� �ε�
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("MapFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "CatacombsLevel_Map.dat";

	// ���� ����
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	// 0. ������ �⺻���� ����

	// �ٴ�Ÿ�� �ؽ��ĸ�
	pFile.Read(MapInfo_.FloorTileTextureName_);

	// ��Ÿ�� �ؽ��ĸ�
	pFile.Read(MapInfo_.WallTileTextureName_);

	// 1. ���� ���� ����

	// Ÿ��Ÿ��(����)
	int CorridorType;
	pFile.Read(CorridorType);
	MapInfo_.CorridorInfo_.CorridorType_ = static_cast<RandomMapTileType>(CorridorType);

	// ���� Ÿ���� �̹����ε���
	pFile.Read(MapInfo_.CorridorInfo_.TileImageIndex);

	// ���� ������ ������ ��� Ÿ�� �ε���(�������뵵)
	int CorridorTileCnt;
	pFile.Read(CorridorTileCnt);
	MapInfo_.CorridorInfo_.AllIndexLists_.resize(CorridorTileCnt);
	for (int i = 0; i < CorridorTileCnt; ++i)
	{
		pFile.Read(MapInfo_.CorridorInfo_.AllIndexLists_[i].X_);
		pFile.Read(MapInfo_.CorridorInfo_.AllIndexLists_[i].Y_);
	}

	// 2. �� ���� ����

	// �ش� ���� �� ���
	int RoomCnt;
	pFile.Read(RoomCnt);
	MapInfo_.RoomInfo_.resize(RoomCnt);
	for (int i = 0; i < RoomCnt; ++i)
	{
		// Ÿ��Ÿ��(��)
		int TileType;
		pFile.Read(TileType);
		MapInfo_.RoomInfo_[i].TileType_ = static_cast<RandomMapTileType>(TileType);

		// �� ��ȣ(������ȣ)
		pFile.Read(MapInfo_.RoomInfo_[i].RoomNo_);

		// �� Ÿ���� �̹����ε���
		pFile.Read(MapInfo_.RoomInfo_[i].TileImageIndex);

		// ���� ũ�� ����(Ÿ���� Y�ε���) �ε���
		pFile.Read(MapInfo_.RoomInfo_[i].WidthIndex_);

		// ���� ũ�� ����(Ÿ���� X�ε���) �ε���
		pFile.Read(MapInfo_.RoomInfo_[i].HeightIndex_);

		// ���� �����ϴ� �ε��� X�� �ּ� �ε���
		pFile.Read(MapInfo_.RoomInfo_[i].minIndexX_);

		// ���� �����ϴ� �ε��� Y�� �ִ� �ε���
		pFile.Read(MapInfo_.RoomInfo_[i].maxIndexX_);

		// ���� �����ϴ� �ε��� X�� �ּ� �ε���
		pFile.Read(MapInfo_.RoomInfo_[i].minIndexY_);

		// ���� �����ϴ� �ε��� Y�� �ִ� �ε���
		pFile.Read(MapInfo_.RoomInfo_[i].maxIndexY_);

		// ���� ���� �ε���
		pFile.Read(MapInfo_.RoomInfo_[i].RoomCenterIndex_.X_);
		pFile.Read(MapInfo_.RoomInfo_[i].RoomCenterIndex_.Y_);

		// ���� ������ ���� ��� Ÿ�� �ε���
		int RoomTileCnt = 0;
		pFile.Read(RoomTileCnt);
		MapInfo_.RoomInfo_[i].AllIndexLists_.resize(RoomTileCnt);
		for (int j = 0; j < RoomTileCnt; ++j)
		{
			pFile.Read(MapInfo_.RoomInfo_[i].AllIndexLists_[j].X_);
			pFile.Read(MapInfo_.RoomInfo_[i].AllIndexLists_[j].Y_);
		}

		// ���� ��� ���� �ָ� �������ִ� ���ȣ
		pFile.Read(MapInfo_.RoomInfo_[i].TheFarthestRoomNo_);
	}

	// 3. �� ���� ����(�׺���̼� ������ ���)
	int WallCnt = 0;
	pFile.Read(WallCnt);
	MapInfo_.WallInfo_.resize(WallCnt);
	for (int i = 0; i < WallCnt; ++i)
	{
		// Ÿ���ε���
		pFile.Read(MapInfo_.WallInfo_[i].WallTileIndex_.X_);
		pFile.Read(MapInfo_.WallInfo_[i].WallTileIndex_.Y_);

		// ���� ���� Ÿ�ϱ��� 4���� Ÿ���� üũ�Ͽ� 
		// �ٴ�Ÿ�� ���翩�ο� ���� Flag�� ����
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

		// ��Ÿ�� �⺻Ÿ��
		int BasicType;
		pFile.Read(BasicType);
		MapInfo_.WallInfo_[i].WallBasicType_ = static_cast<RandomWallBasicType>(BasicType);

		// ��Ÿ�� ��Ÿ��
		int DetailType;
		pFile.Read(DetailType);
		MapInfo_.WallInfo_[i].WallDetailType_ = static_cast<RandomWallDetailType>(DetailType);

		// �Ϲ����� ���� �Ѱ��� �������� ����
		pFile.Read(MapInfo_.WallInfo_[i].WallTile1ImageIndex_);

		// Ư���� ���� 2���� �������� ����
		pFile.Read(MapInfo_.WallInfo_[i].WallTile2ImageIndex_);

		// ���ؽ��� �̸�
		pFile.Read(MapInfo_.WallInfo_[i].WallTextureName_);

		// ��Ÿ�� ũ��
		int TileSizeX = 0;
		int TileSizeY = 0;
		int TileSizeZ = 0;
		pFile.Read(TileSizeX);
		pFile.Read(TileSizeY);
		pFile.Read(TileSizeZ);
		MapInfo_.WallInfo_[i].WallTileSize_ = float4(static_cast<float>(TileSizeX), static_cast<float>(TileSizeY), static_cast<float>(TileSizeZ));

		// ��Ÿ�� ������ũ��
		int RenderSizeX = 0;
		int RenderSizeY = 0;
		int RenderSizeZ = 0;
		pFile.Read(RenderSizeX);
		pFile.Read(RenderSizeY);
		pFile.Read(RenderSizeZ);
		MapInfo_.WallInfo_[i].WallRenderSize_ = float4(static_cast<float>(RenderSizeX), static_cast<float>(RenderSizeY), static_cast<float>(RenderSizeZ));

		// ��Ÿ�� ������ �ǹ�
		int RenderPivotPosX = 0;
		int RenderPivotPosY = 0;
		int RenderPivotPosZ = 0;
		pFile.Read(RenderPivotPosX);
		pFile.Read(RenderPivotPosY);
		pFile.Read(RenderPivotPosZ);
		MapInfo_.WallInfo_[i].WallRenderPivotPos_ = float4(static_cast<float>(RenderPivotPosX), static_cast<float>(RenderPivotPosY), static_cast<float>(RenderPivotPosZ));
	}

	pFile.Close();

	// �������̿��Ͽ� ������ ����
	MapRendering();

	// �׺���̼� ���� ����
	CreateNavigationInfo();
}

void CatacombsMap::MapRendering()
{
	// �ٴ�Ÿ�� ������
	FloorTileTextureMatching();

	// ��Ÿ�� ������
	WallTileTextureMatching();

	// ��Ÿ�� ������
	DoorTileTextureMatching();
}

void CatacombsMap::FloorTileTextureMatching()
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

void CatacombsMap::CreateNavigationInfo()
{
	// �׺���̼���������






	// �׺���̼� ����
	Navigation_ = new GameEnginePathFind();
}

bool CatacombsMap::Moveable4WaysCheck(PathIndex _PathIndex)
{
	TileIndex CheckTileIndex;
	CheckTileIndex.X_ = _PathIndex.X_;
	CheckTileIndex.Y_ = _PathIndex.Y_;

	// �׺���̼� �ε��� Ÿ�Կ� �����ϴ� �ε����̸�, WallŸ���̸� �̵��Ұ�����
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

	// �׺���̼� �ε��� Ÿ�Կ� �����ϴ� �ε����̸�, WallŸ���̸� �̵��Ұ�����
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
		// �÷��̾��� ������ġ�� �̿��Ͽ� Ÿ���ε��� ���
		TileIndex StartIndex = GetWallTileIndex(_StartPos);

		// ���콺���ʹ�ưŬ�� ��ġ�� �̿��Ͽ� Ÿ���ε��� ���
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
		// �÷��̾��� ������ġ�� �̿��Ͽ� Ÿ���ε��� ���
		TileIndex StartIndex = GetWallTileIndex(_StartPos);

		// ���콺���ʹ�ưŬ�� ��ġ�� �̿��Ͽ� Ÿ���ε��� ���
		float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
		TileIndex TargetIndex = GetWallTileIndex(_MouseClickPos + CamPos);

		return Navigation_->AStarFind8Way(PathIndex(StartIndex.X_, StartIndex.Y_), PathIndex(TargetIndex.X_, TargetIndex.Y_), std::bind(&CatacombsMap::Moveable8WaysCheck, this, std::placeholders::_1));
	}

	return std::list<PathIndex>();
}