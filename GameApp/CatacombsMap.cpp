#include "PreCompile.h"
#include "CatacombsMap.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineTileMapRenderer.h>
#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalValue.h"

#include "MainPlayer.h"

#include "Andariel.h"
#include "Fallen.h"
#include "SpikeFiend.h"
#include "Tainted.h"
#include "Zombie.h"

CatacombsMap::CatacombsMap() :
	MapInfo_{}
{
}

CatacombsMap::~CatacombsMap()
{
	std::map<NavigationObjectType, std::vector<GameEnginePathFind*>>::iterator StartIter = Navigation_.begin();
	std::map<NavigationObjectType, std::vector<GameEnginePathFind*>>::iterator EndIter = Navigation_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		int NavigationCnt = static_cast<int>((*StartIter).second.size());
		for (int i = 0; i < NavigationCnt; ++i)
		{
			delete (*StartIter).second[i];
			(*StartIter).second[i] = nullptr;
		}
	}
	Navigation_.clear();
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

	// ������� �۷ι� ������ ����
	GlobalValue::CatacombsMap = this;
}

void CatacombsMap::Update(float _DeltaTime)
{
	if (nullptr != GlobalValue::CurPlayer)
	{
		AdjustTheTransparencyAroundThePlayer();
	}
}

void CatacombsMap::AdjustTheTransparencyAroundThePlayer()
{
	// ��� ��Ÿ�� ���� �ʱ�ȭ
	for (auto& WallTile : MapInfo_.WallInfo_)
	{
		if (WallTile.WallDetailType_ != RandomWallDetailType::NONE &&
			WallTile.WallDetailType_ != RandomWallDetailType::NORMAL)
		{
			WallTiles_.find(WallTile.WallTileIndex_.Index_)->second.Tiles1_->SetAlpha(1.f);
			if (nullptr != WallTiles_.find(WallTile.WallTileIndex_.Index_)->second.Tiles2_)
			{
				WallTiles_.find(WallTile.WallTileIndex_.Index_)->second.Tiles2_->SetAlpha(1.f);
			}
		}
	}

	// ���� �÷��̾��� ��ġ�� Ÿ���ε��� Get
	TileIndex PlayerTile = GetWallTileIndex(GlobalValue::CurPlayer->GetTransform()->GetWorldPosition());

	// �÷��̾� 8������ Ÿ�ϸ���� ����
	std::vector<TileIndex> PlayerAroundTile;
	PlayerAroundTile.clear();
	PlayerAroundTile.push_back(PlayerTile + TileIndex( 1, -1));		// ���
	PlayerAroundTile.push_back(PlayerTile + TileIndex( 2, -2));		// ���2s
	PlayerAroundTile.push_back(PlayerTile + TileIndex( 1,  0));		// ���ϴ�
	PlayerAroundTile.push_back(PlayerTile + TileIndex( 2,  0));		// ���ϴ�2
	PlayerAroundTile.push_back(PlayerTile + TileIndex( 1,  1));		// �ϴ�
	PlayerAroundTile.push_back(PlayerTile + TileIndex( 2,  2));		// �ϴ�2
	PlayerAroundTile.push_back(PlayerTile + TileIndex( 0,  1));		// ���ϴ�
	PlayerAroundTile.push_back(PlayerTile + TileIndex( 0,  2));		// ���ϴ�2
	PlayerAroundTile.push_back(PlayerTile + TileIndex(-1,  1));		// �´�
	PlayerAroundTile.push_back(PlayerTile + TileIndex(-2,  2));		// �´�2

	// ��� ��Ÿ���� NONE, NORMAL�� �ƴ� Ÿ�ϵ��� ��� �˻��Ͽ� ���� ����
	for (auto& AroundTile : PlayerAroundTile)
	{
		for (auto& WallTile : MapInfo_.WallInfo_)
		{
			if (WallTile.WallDetailType_ != RandomWallDetailType::NONE &&
				WallTile.WallDetailType_ != RandomWallDetailType::NORMAL)
			{
				if (AroundTile == WallTile.WallTileIndex_)
				{
					WallTiles_.find(AroundTile.Index_)->second.Tiles1_->SetAlpha(0.5f);
					if (nullptr != WallTiles_.find(AroundTile.Index_)->second.Tiles2_)
					{
						WallTiles_.find(AroundTile.Index_)->second.Tiles2_->SetAlpha(0.5f);
					}
				}
			}
		}
	}
}

GameEngineActor* CatacombsMap::MonsterTileIndexCheck(TileIndex _CheckTile)
{
	for (auto& Fallen : FallenList_)
	{
		TileIndex FallenTile = GetWallTileIndex(Fallen->GetTransform()->GetWorldPosition());
		if (FallenTile == _CheckTile)
		{
			if (Fallen_FSMState::FL_DEAD != Fallen->GetCurState() &&
				Fallen_FSMState::FL_DEATH != Fallen->GetCurState())
			{
				return Fallen;
			}

			return nullptr;
		}
	}

	for (auto& SpikeFiend : SpikeFiendList_)
	{
		TileIndex SpikeFiendTile = GetWallTileIndex(SpikeFiend->GetTransform()->GetWorldPosition());
		if (SpikeFiendTile == _CheckTile)
		{
			if (SpikeFiend_FSMState::SF_DEAD != SpikeFiend->GetCurState() &&
				SpikeFiend_FSMState::SF_DEATH != SpikeFiend->GetCurState())
			{
				return SpikeFiend;
			}

			return nullptr;
		}
	}

	for (auto& Tainted : TaintedList_)
	{
		TileIndex TaintedTile = GetWallTileIndex(Tainted->GetTransform()->GetWorldPosition());
		if (TaintedTile == _CheckTile)
		{
			if (Tainted_FSMState::TT_DEAD != Tainted->GetCurState() &&
				Tainted_FSMState::TT_DEATH != Tainted->GetCurState())
			{
				return Tainted;
			}

			return nullptr;
		}
	}

	for (auto& Zombie : ZombieList_)
	{
		TileIndex ZombieTile = GetWallTileIndex(Zombie->GetTransform()->GetWorldPosition());
		if (ZombieTile == _CheckTile)
		{
			if (Zombie_FSMState::ZB_DEAD != Zombie->GetCurState() &&
				Zombie_FSMState::ZB_DEATH != Zombie->GetCurState())
			{
				return Zombie;
			}

			return nullptr;
		}
	}

	for (auto& Andariel : AndarielList_)
	{
		TileIndex AndarielTile = GetWallTileIndex(Andariel->GetTransform()->GetWorldPosition());
		if (AndarielTile == _CheckTile)
		{
			if (Andariel_FSMState::AD_DEAD != Andariel->GetCurState() &&
				Andariel_FSMState::AD_DEATH != Andariel->GetCurState())
			{
				return Andariel;
			}

			return nullptr;
		}
	}

	return nullptr;
}

void CatacombsMap::MonsterDeathToListDelete(GameEngineActor* _DeathMonster)
{
	std::string DeathMonsterName = _DeathMonster->GetName();
	if (std::string::npos != DeathMonsterName.find("Fallen"))
	{
		std::vector<Fallen*>::iterator StartIter = FallenList_.begin();
		std::vector<Fallen*>::iterator EndIter = FallenList_.end();
		{
			for (; StartIter != EndIter; ++StartIter)
			{
				if ((*StartIter) == _DeathMonster)
				{
					FallenList_.erase(StartIter);
					break;
				}
			}
		}
	}
	else if (std::string::npos != DeathMonsterName.find("SpikeFiend"))
	{
		std::vector<SpikeFiend*>::iterator StartIter = SpikeFiendList_.begin();
		std::vector<SpikeFiend*>::iterator EndIter = SpikeFiendList_.end();
		{
			for (; StartIter != EndIter; ++StartIter)
			{
				if ((*StartIter) == _DeathMonster)
				{
					SpikeFiendList_.erase(StartIter);
					break;
				}
			}
		}
	}
	else if (std::string::npos != DeathMonsterName.find("Tainted"))
	{
		std::vector<Tainted*>::iterator StartIter = TaintedList_.begin();
		std::vector<Tainted*>::iterator EndIter = TaintedList_.end();
		{
			for (; StartIter != EndIter; ++StartIter)
			{
				if ((*StartIter) == _DeathMonster)
				{
					TaintedList_.erase(StartIter);
					break;
				}
			}
		}
	}
	else if (std::string::npos != DeathMonsterName.find("Zombie"))
	{
		std::vector<Zombie*>::iterator StartIter = ZombieList_.begin();
		std::vector<Zombie*>::iterator EndIter = ZombieList_.end();
		{
			for (; StartIter != EndIter; ++StartIter)
			{
				if ((*StartIter) == _DeathMonster)
				{
					ZombieList_.erase(StartIter);
					break;
				}
			}
		}
	}
	else if (std::string::npos != DeathMonsterName.find("Andariel"))
	{
		std::vector<Andariel*>::iterator StartIter = AndarielList_.begin();
		std::vector<Andariel*>::iterator EndIter = AndarielList_.end();
		{
			for (; StartIter != EndIter; ++StartIter)
			{
				if ((*StartIter) == _DeathMonster)
				{
					AndarielList_.erase(StartIter);
					break;
				}
			}
		}
	}
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
	// �׺���̼� Ÿ���ε����� ������� ��ġ������ ��ȯ�ؼ� ��ȯ
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

	// �÷��̾� ��ġ ����
	CurLevelActorRoomArrange();

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

void CatacombsMap::CurLevelActorRoomArrange()
{
	// ���� �ʿ� �����ϴ� ��� ���Ͱ��� ���� �� ������ �뿡 ��ġ

	// ���� �÷��̾� ��ġ ���ȣ ����(����)
	GameEngineRandom RandomRoom;
	int PlayerArrRoomNo = RandomRoom.RandomInt(0, static_cast<int>(MapInfo_.RoomInfo_.size() - 1));

	// �÷��̾� ����� �÷��̾ ������ ���� ���Ϳ� ��ġ
	if (nullptr != GlobalValue::CurPlayer)
	{
		// ���� �÷��̾� ��ġ ���ȣ ����
		GlobalValue::CurPlayer->ArrangeRoomNo_ = MapInfo_.RoomInfo_[PlayerArrRoomNo].RoomNo_;

		// �÷��̾� ������ ���� ���ͷ� �̵�
		float4 PlayerPos = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[PlayerArrRoomNo].RoomCenterIndex_);
		GlobalValue::CurPlayer->GetTransform()->SetWorldPosition(PlayerPos);
		GetLevel()->GetMainCameraActor()->GetTransform()->SetWorldPosition(float4(GlobalValue::CurPlayer->GetTransform()->GetLocalPosition().x, GlobalValue::CurPlayer->GetTransform()->GetLocalPosition().y));

		// �÷��̾ ��ġ�� ���� ������ ���뿡 ���� ��ġ
		// �÷��̾ ��ġ�� ��� ����ָ� �������ִ� �뿡 �������� ��ġz
		int RoomCnt = static_cast<int>(MapInfo_.RoomInfo_.size());
		for (int i = 0; i < RoomCnt; ++i)
		{
			// �÷��̾ ��ġ�� ���� ������ ���뿡 ���� ��ġ ó��
			// ��, �÷��̾ ��ġ�� �뿡�� ��� ���͵� ��ġ�Ұ� ����
			if (GlobalValue::CurPlayer->ArrangeRoomNo_ != MapInfo_.RoomInfo_[i].RoomNo_)
			{
				// �÷��̾ ���� ��ġ�� ��� ����ָ� �������ִ� ���̶��
				if (MapInfo_.RoomInfo_[PlayerArrRoomNo].TheFarthestRoomNo_ == MapInfo_.RoomInfo_[i].RoomNo_)
				{
					// ���� ��ġ(�ȴٸ���) - �ش� ���� ����
					Andariel* NewAndariel = GetLevel()->CreateActor<Andariel>();
					NewAndariel->SetName("Andariel" + std::to_string(AndarielList_.size()));
					NewAndariel->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(MapInfo_.RoomInfo_[i].RoomCenterIndex_));
					NewAndariel->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[i].RoomNo_);
					AndarielList_.push_back(NewAndariel);

					// �Ϲ� ���� ��ġ - ���� ���͸� ������ 3x3�� ��ġ(��, ���ͱ��� 3x3)
					GameEngineRandom MonsterTypeRandom;
					MonsterClassType MonsterType = static_cast<MonsterClassType>(MonsterTypeRandom.RandomInt(0, 3));

					for (int y = -1; y <= 1; ++y)
					{
						for (int x = -1; x <= 1; ++x)
						{
							TileIndex SpawnTile = MapInfo_.RoomInfo_[i].RoomCenterIndex_ + TileIndex(x, y);
							if (SpawnTile == MapInfo_.RoomInfo_[i].RoomCenterIndex_)
							{
								// ���Ϳ� ������ �����ǹǷ� ����
								continue;
							}

							switch (MonsterType)
							{
								case MonsterClassType::SpikeFiend:
								{
									SpikeFiend* NewSpikeFiend = GetLevel()->CreateActor<SpikeFiend>();
									NewSpikeFiend->SetName("SpikeFiend" + std::to_string(SpikeFiendList_.size()));
									NewSpikeFiend->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(SpawnTile));
									NewSpikeFiend->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[i].RoomNo_);
									SpikeFiendList_.push_back(NewSpikeFiend);
									break;
								}
								case MonsterClassType::Zombie:
								{
									Zombie* NewZombie = GetLevel()->CreateActor<Zombie>();
									NewZombie->SetName("Zombie" + std::to_string(ZombieList_.size()));
									NewZombie->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(SpawnTile));
									NewZombie->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[i].RoomNo_);
									ZombieList_.push_back(NewZombie);
									break;
								}
								case MonsterClassType::Fallen:
								{
									Fallen* NewFallen = GetLevel()->CreateActor<Fallen>();
									NewFallen->SetName("Fallen" + std::to_string(FallenList_.size()));
									NewFallen->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(SpawnTile));
									NewFallen->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[i].RoomNo_);
									FallenList_.push_back(NewFallen);
									break;
								}
								case MonsterClassType::Tainted:
								{
									Tainted* NewTainted = GetLevel()->CreateActor<Tainted>();
									NewTainted->SetName("Tainted" + std::to_string(TaintedList_.size()));
									NewTainted->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(SpawnTile));
									NewTainted->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[i].RoomNo_);
									TaintedList_.push_back(NewTainted);
									break;
								}
							}
						}
					}
				}
				// �ƴѰ��
				else
				{
					//// �׽�Ʈ
					//Andariel* NewAndariel = GetLevel()->CreateActor<Andariel>();
					//NewAndariel->SetName("Andariel" + std::to_string(AndarielList_.size()));
					//NewAndariel->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(MapInfo_.RoomInfo_[i].RoomCenterIndex_));
					//NewAndariel->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[i].RoomNo_);
					//AndarielList_.push_back(NewAndariel);

					GameEngineRandom MonsterTypeRandom;
					MonsterClassType MonsterType = static_cast<MonsterClassType>(MonsterTypeRandom.RandomInt(0, 3));

					// ���� ���ͱ��� 3x3�� ���� ��ȯ
					for (int y = -1; y <= 1; ++y)
					{
						for (int x = -1; x <= 1; ++x)
						{
							TileIndex SpawnTile = MapInfo_.RoomInfo_[i].RoomCenterIndex_ + TileIndex(x, y);

							switch (MonsterType)
							{
								case MonsterClassType::SpikeFiend:
								{
									SpikeFiend* NewSpikeFiend = GetLevel()->CreateActor<SpikeFiend>();
									NewSpikeFiend->SetName("SpikeFiend" + std::to_string(SpikeFiendList_.size()));
									NewSpikeFiend->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(SpawnTile));
									NewSpikeFiend->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[i].RoomNo_);
									SpikeFiendList_.push_back(NewSpikeFiend);
									break;
								}
								case MonsterClassType::Zombie:
								{
									Zombie* NewZombie = GetLevel()->CreateActor<Zombie>();
									NewZombie->SetName("Zombie" + std::to_string(ZombieList_.size()));
									NewZombie->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(SpawnTile));
									NewZombie->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[i].RoomNo_);
									ZombieList_.push_back(NewZombie);
									break;
								}
								case MonsterClassType::Fallen:
								{
									Fallen* NewFallen = GetLevel()->CreateActor<Fallen>();
									NewFallen->SetName("Fallen" + std::to_string(FallenList_.size()));
									NewFallen->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(SpawnTile));
									NewFallen->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[i].RoomNo_);
									FallenList_.push_back(NewFallen);
									break;
								}
								case MonsterClassType::Tainted:
								{
									Tainted* NewTainted = GetLevel()->CreateActor<Tainted>();
									NewTainted->SetName("Tainted" + std::to_string(TaintedList_.size()));
									NewTainted->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(SpawnTile));
									NewTainted->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[i].RoomNo_);
									TaintedList_.push_back(NewTainted);
									break;
								}
							}
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 10; ++i)
				{
					// �÷��̾� ���� �뿡�� �� ������ ��ü ��ġ(�� 42���� : ���� 20���� ��ȯ��, ������ 20���� ��ȯ��)
					// �����Ǵ� ���ʹ� �����̸�, ����Ÿ�ϱ��� ���̾ƴ� Ÿ�Ͽ� ��ġ�ȴ�.
					GameEngineRandom MonsterTypeRandom;
					MonsterClassType MonsterType = static_cast<MonsterClassType>(MonsterTypeRandom.RandomInt(0, 3));

					// �뿡�� ��ġ ���� Ÿ�� ����
					int MaxAllTiles = static_cast<int>(MapInfo_.RoomInfo_[PlayerArrRoomNo].AllIndexLists_.size());
					GameEngineRandom TileRandom;

					float4 SpawnTilePos = GetFloorTileIndexToPos(MapInfo_.RoomInfo_[PlayerArrRoomNo].AllIndexLists_[TileRandom.RandomInt(0, MaxAllTiles - 1)]);
					switch (MonsterType)
					{
						case MonsterClassType::SpikeFiend:
						{
							SpikeFiend* NewSpikeFiend = GetLevel()->CreateActor<SpikeFiend>();
							NewSpikeFiend->SetName("SpikeFiend" + std::to_string(SpikeFiendList_.size()));
							NewSpikeFiend->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(MapInfo_.RoomInfo_[PlayerArrRoomNo].RoomCenterIndex_));
							NewSpikeFiend->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[PlayerArrRoomNo].RoomNo_);
							NewSpikeFiend->SpawnToDeath();
							SpikeFiendList_.push_back(NewSpikeFiend);
							break;
						}
						case MonsterClassType::Zombie:
						{
							Zombie* NewZombie = GetLevel()->CreateActor<Zombie>();
							NewZombie->SetName("Zombie" + std::to_string(ZombieList_.size()));
							NewZombie->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(MapInfo_.RoomInfo_[PlayerArrRoomNo].RoomCenterIndex_));
							NewZombie->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[PlayerArrRoomNo].RoomNo_);
							NewZombie->SpawnToDeath();
							ZombieList_.push_back(NewZombie);
							break;
						}
						case MonsterClassType::Fallen:
						{
							Fallen* NewFallen = GetLevel()->CreateActor<Fallen>();
							NewFallen->SetName("Fallen" + std::to_string(FallenList_.size()));
							NewFallen->GetTransform()->SetWorldPosition(GetFloorTileIndexToPos(MapInfo_.RoomInfo_[PlayerArrRoomNo].RoomCenterIndex_));
							NewFallen->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[PlayerArrRoomNo].RoomNo_);
							NewFallen->SpawnToDeath();
							FallenList_.push_back(NewFallen);
							break;
						}
						case MonsterClassType::Tainted:
						{
							Tainted* NewTainted = GetLevel()->CreateActor<Tainted>();
							NewTainted->SetName("Tainted" + std::to_string(TaintedList_.size()));
							NewTainted->GetTransform()->SetWorldPosition(SpawnTilePos);
							NewTainted->SetEnterTheRoomDetectList(MapInfo_.RoomInfo_[PlayerArrRoomNo].RoomNo_);
							NewTainted->SpawnToDeath();
							TaintedList_.push_back(NewTainted);
							break;
						}
					}
				}
			}
		}
	}

	// ������ ����, ������Ʈ ��ġ�Ϸ� �� �� �׺���̼� ����
	
	// Fallen
	std::vector<GameEnginePathFind*> FallenNav;
	int FallenCnt = static_cast<int>(FallenList_.size());
	for (int i = 0; i < FallenCnt; ++i)
	{
		FallenNav.push_back(new GameEnginePathFind());
	}
	Navigation_[NavigationObjectType::Fallen] = FallenNav;

	// SpikeFiend
	std::vector<GameEnginePathFind*> SpikeFiendNav;
	int SpikeFiendCnt = static_cast<int>(SpikeFiendList_.size());
	for (int i = 0; i < SpikeFiendCnt; ++i)
	{
		SpikeFiendNav.push_back(new GameEnginePathFind());
	}
	Navigation_[NavigationObjectType::SpikeFiend] = SpikeFiendNav;

	// Tainted
	std::vector<GameEnginePathFind*> TaintedNav;
	int TaintedCnt = static_cast<int>(TaintedList_.size());
	for (int i = 0; i < TaintedCnt; ++i)
	{
		TaintedNav.push_back(new GameEnginePathFind());
	}
	Navigation_[NavigationObjectType::Tainted] = TaintedNav;

	// Zombie
	std::vector<GameEnginePathFind*> ZombieNav;
	int ZombieCnt = static_cast<int>(ZombieList_.size());
	for (int i = 0; i < ZombieCnt; ++i)
	{
		ZombieNav.push_back(new GameEnginePathFind());
	}
	Navigation_[NavigationObjectType::Zombie] = ZombieNav;

	// Andariel
	std::vector<GameEnginePathFind*> AndarielNav;
	int AndarielCnt = static_cast<int>(AndarielList_.size());
	for (int i = 0; i < AndarielCnt; ++i)
	{
		AndarielNav.push_back(new GameEnginePathFind());
	}
	Navigation_[NavigationObjectType::Andariel] = AndarielNav;
}

void CatacombsMap::CreateNavigationInfo()
{
	// �׺���̼���������
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

	// �׺���̼� ����(���� 1�� ���� - �÷��̾� ���)
	std::vector<GameEnginePathFind*> NewPathFind;
	NewPathFind.push_back(new GameEnginePathFind());
	Navigation_[NavigationObjectType::Player] = NewPathFind;
}

bool CatacombsMap::CurTileIndexWallCheck(TileIndex _CurTile)
{
	int WallInfo = static_cast<int>(MapInfo_.WallInfo_.size());
	for (int i = 0; i < WallInfo; ++i)
	{
		if (MapInfo_.WallInfo_[i].WallTileIndex_ == _CurTile)
		{
			if (MapInfo_.WallInfo_[i].WallDetailType_ != RandomWallDetailType::NORMAL)
			{
				return true;
			}
		}
	}

	return false;
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

std::list<PathIndex> CatacombsMap::NavgationFind4Way(NavigationObjectType _ObjectType, int _NavigationNo, float4 _StartPos, float4 _MouseClickPos)
{
	if (nullptr != Navigation_[_ObjectType][_NavigationNo])
	{
		TileIndex StartIndex = GetWallTileIndex(_StartPos);

		float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
		TileIndex TargetIndex = GetWallTileIndex(_MouseClickPos + CamPos);

		return Navigation_[_ObjectType][_NavigationNo]->AStarFind4Way(PathIndex(StartIndex.X_, StartIndex.Y_), PathIndex(TargetIndex.X_, TargetIndex.Y_), std::bind(&CatacombsMap::Moveable4WaysCheck, this, std::placeholders::_1));
	}

	return std::list<PathIndex>();
}

std::list<PathIndex> CatacombsMap::NavgationFind8Way(NavigationObjectType _ObjectType, int _NavigationNo, float4 _StartPos, float4 _MouseClickPos)
{
	if (nullptr != Navigation_[_ObjectType][_NavigationNo])
	{
		TileIndex StartIndex = GetWallTileIndex(_StartPos);

		float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
		TileIndex TargetIndex = GetWallTileIndex(_MouseClickPos + CamPos);

		return Navigation_[_ObjectType][_NavigationNo]->AStarFind8Way(PathIndex(StartIndex.X_, StartIndex.Y_), PathIndex(TargetIndex.X_, TargetIndex.Y_), std::bind(&CatacombsMap::Moveable8WaysCheck, this, std::placeholders::_1));
	}

	return std::list<PathIndex>();
}

void CatacombsMap::CreateNavitaion(NavigationObjectType _ObjectType, int _NavigationNo)
{
	int CurNaviSize = static_cast<int>(Navigation_[_ObjectType].size());
	if (_NavigationNo <= CurNaviSize - 1)
	{
		return;
	}

	// �ش� �׺���̼� ��ü ����
	Navigation_[_ObjectType].push_back(new GameEnginePathFind());
}
