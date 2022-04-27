#include "PreCompile.h"
#include "TownMap.h"

#include <GameEngine/GameEngineTileMapRenderer.h>
#include <GameEngine/GameEngineGUI.h>

TownMap::TownMap() :
	MapType_(MapType::FIXED),
	TileSize_(float4(160.f, 80.f)),
	DebugRendererFlag_(false)
{
}

TownMap::~TownMap()
{
	if (nullptr != Navigation_)
	{
		delete Navigation_;
		Navigation_ = nullptr;
	}
}

void TownMap::Start()
{
#pragma region �׽�ƮŰ
	if (false == GameEngineInput::GetInst().IsKey("NavigationSwitch"))
	{
		GameEngineInput::GetInst().CreateKey("NavigationSwitch", '1');
	}
#pragma endregion
}

void TownMap::Update(float _DeltaTime)
{
#pragma region ����׷�����
	TownLevelNavigationDebugRender();

	if (true == GameEngineInput::GetInst().Down("NavigationSwitch"))
	{
		if (false == DebugRendererFlag_)
		{
			DebugRendererFlag_ = true;
		}
		else
		{
			DebugRendererFlag_ = false;
		}
	}
#pragma endregion
}

float4 TownMap::GetTileIndexToPos(TileIndex _TileIndex)
{
	// �׺���̼� Ÿ���ε����� ������� ��ġ������ ��ȯ�ؼ� ��ȯ
	float4 TilePos = float4::ZERO;
	TilePos.x = (_TileIndex.X_ - _TileIndex.Y_) * TileSize_.halffloat4().halffloat4().x;
	TilePos.y = (_TileIndex.X_ + _TileIndex.Y_) * -TileSize_.halffloat4().halffloat4().y;
	
	return TilePos;
}

float4 TownMap::GetTileIndexToPos(int _IndexX, int _IndexY)
{
	// �׺���̼� Ÿ���ε����� ������� ��ġ������ ��ȯ�ؼ� ��ȯ
	float4 TilePos = float4::ZERO;
	TilePos.x = (_IndexX - _IndexY) * TileSize_.halffloat4().halffloat4().x;
	TilePos.y = (_IndexX + _IndexY) * -TileSize_.halffloat4().halffloat4().y;

	return TilePos;
}

TileIndex TownMap::GetPosToTileIndex(float4 _Pos)
{
	TileIndex Index = {};

	float RatioX = ((_Pos.x / TileSize_.halffloat4().halffloat4().x) - (_Pos.y / TileSize_.halffloat4().halffloat4().y)) / 2.0f;
	float RatioY = ((_Pos.y / TileSize_.halffloat4().halffloat4().y) + (_Pos.x / TileSize_.halffloat4().halffloat4().x)) / -2.0f;

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

void TownMap::MapInfoAllClear()
{
}

void TownMap::MapTextureCutting()
{
	// �ٴ�Ÿ��
	GameEngineTexture* FloorTile = GameEngineTextureManager::GetInst().Find("Town_Floor.png");
	FloorTile->Cut(5, 37);

	// ��Ÿ��
	GameEngineTexture* WallTile = GameEngineTextureManager::GetInst().Find("Town_Wall.png");
	WallTile->Cut(31, 1);

	// ������ƮŸ��
	GameEngineTexture* ObjectTile = GameEngineTextureManager::GetInst().Find("Town_Object.png");
	ObjectTile->Cut(53, 1);
}

bool TownMap::TownLevel_FixedMapLoad()
{
	// �������� Ŭ����
	MapInfoAllClear();

	// �ʰ��� �ؽ��� ����
	MapTextureCutting();

	// ������ ��η� �̵�
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("MapFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "TownLevel_Map.dat";

	// ���� ����
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	// �ٴ����� �ε�
	int FloorYIndex = 1;
	pFile.Read(FloorYIndex);
	TownMap_FloorTileInfo_.resize(FloorYIndex);

	int FloorXIndex = 1;
	pFile.Read(FloorXIndex);
	for (int y = 0; y < FloorYIndex; ++y)
	{
		TownMap_FloorTileInfo_[y].resize(FloorXIndex);

		for (int x = 0; x < FloorXIndex; ++x)
		{
			// �ε�������
			pFile.Read(TownMap_FloorTileInfo_[y][x].FloorIndexX);
			pFile.Read(TownMap_FloorTileInfo_[y][x].FloorIndexY);
			pFile.Read(TownMap_FloorTileInfo_[y][x].FloorImageIndex);

			// ������ ����
			pFile.Read(TownMap_FloorTileInfo_[y][x].FloorTextureName);

			// float4 Data

			// FloorTileSize
			int FloorTileSizeX = 0;
			int FloorTileSizeY = 0;
			int FloorTileSizeZ = 0;
			pFile.Read(FloorTileSizeX);
			pFile.Read(FloorTileSizeY);
			pFile.Read(FloorTileSizeZ);
			TownMap_FloorTileInfo_[y][x].FloorTileSize = float4(static_cast<float>(FloorTileSizeX), static_cast<float>(FloorTileSizeY), static_cast<float>(FloorTileSizeZ));

			// FloorRenderSize
			int FloorRenderSizeX = 0;
			int FloorRenderSizeY = 0;
			int FloorRenderSizeZ = 0;
			pFile.Read(FloorRenderSizeX);
			pFile.Read(FloorRenderSizeY);
			pFile.Read(FloorRenderSizeZ);
			TownMap_FloorTileInfo_[y][x].FloorRenderSize = float4(static_cast<float>(FloorRenderSizeX), static_cast<float>(FloorRenderSizeY), static_cast<float>(FloorRenderSizeZ));

			// FloorRenderPivotPos
			int FloorRenderPivotPosX = 0;
			int FloorRenderPivotPosY = 0;
			int FloorRenderPivotPosZ = 0;
			pFile.Read(FloorRenderPivotPosX);
			pFile.Read(FloorRenderPivotPosY);
			pFile.Read(FloorRenderPivotPosZ);
			TownMap_FloorTileInfo_[y][x].FloorRenderPivotPos = float4(static_cast<float>(FloorRenderPivotPosX), static_cast<float>(FloorRenderPivotPosY), static_cast<float>(FloorRenderPivotPosZ));
		}
	}

	// ������ �ε�
	int WallYIndex = 1;
	pFile.Read(WallYIndex);
	TownMap_WallTileInfo_.resize(WallYIndex);

	int WallXIndex = 1;
	pFile.Read(WallXIndex);
	for (int y = 0; y < WallYIndex; ++y)
	{
		TownMap_WallTileInfo_[y].resize(WallXIndex);

		for (int x = 0; x < WallXIndex; ++x)
		{
			// �ε��� �� Ÿ������
			pFile.Read(TownMap_WallTileInfo_[y][x].WallIndexX);
			pFile.Read(TownMap_WallTileInfo_[y][x].WallIndexY);
			pFile.Read(TownMap_WallTileInfo_[y][x].WallTile1ImageIndex);
			pFile.Read(TownMap_WallTileInfo_[y][x].WallTile2ImageIndex);

			int WallBasicType_ = 0;
			pFile.Read(WallBasicType_);
			TownMap_WallTileInfo_[y][x].WallBasicType = static_cast<WallBasicType>(WallBasicType_);

			int WallDetailType_ = 0;
			pFile.Read(WallDetailType_);
			TownMap_WallTileInfo_[y][x].WallDetailType = static_cast<WallDetailType>(WallDetailType_);

			// ������ ����
			pFile.Read(TownMap_WallTileInfo_[y][x].WallTextureName);

			// float4 Data

			// WallTileSize
			int WallTileSizeX = 0;
			int WallTileSizeY = 0;
			int WallTileSizeZ = 0;
			pFile.Read(WallTileSizeX);
			pFile.Read(WallTileSizeY);
			pFile.Read(WallTileSizeZ);
			TownMap_WallTileInfo_[y][x].WallTileSize = float4(static_cast<float>(WallTileSizeX), static_cast<float>(WallTileSizeY), static_cast<float>(WallTileSizeZ));

			// WallRenderSize
			int WallRenderSizeX = 0;
			int WallRenderSizeY = 0;
			int WallRenderSizeZ = 0;
			pFile.Read(WallRenderSizeX);
			pFile.Read(WallRenderSizeY);
			pFile.Read(WallRenderSizeZ);
			TownMap_WallTileInfo_[y][x].WallRenderSize = float4(static_cast<float>(WallRenderSizeX), static_cast<float>(WallRenderSizeY), static_cast<float>(WallRenderSizeZ));

			// WallRenderPivotPos
			int WallRenderPivotPosX = 0;
			int WallRenderPivotPosY = 0;
			int WallRenderPivotPosZ = 0;
			pFile.Read(WallRenderPivotPosX);
			pFile.Read(WallRenderPivotPosY);
			pFile.Read(WallRenderPivotPosZ);
			TownMap_WallTileInfo_[y][x].WallRenderPivotPos = float4(static_cast<float>(WallRenderPivotPosX), static_cast<float>(WallRenderPivotPosY), static_cast<float>(WallRenderPivotPosZ));
		}
	}

	// ������Ʈ���� �ε�
	int ObjectYIndex = 1;
	pFile.Read(ObjectYIndex);
	TownMap_ObjectTileInfo_.resize(ObjectYIndex);

	int ObjectXIndex = 1;
	pFile.Read(ObjectXIndex);
	for (int y = 0; y < ObjectYIndex; ++y)
	{
		TownMap_ObjectTileInfo_[y].resize(ObjectXIndex);

		for (int x = 0; x < ObjectXIndex; ++x)
		{
			// �ε��� �� Ÿ������
			pFile.Read(TownMap_ObjectTileInfo_[y][x].ObjectIndexX);
			pFile.Read(TownMap_ObjectTileInfo_[y][x].ObjectIndexY);
			pFile.Read(TownMap_ObjectTileInfo_[y][x].ObjectImageIndex);

			int ObjectBasicType_ = 0;
			pFile.Read(ObjectBasicType_);
			TownMap_ObjectTileInfo_[y][x].ObjectBasicType = static_cast<ObjectBasicType>(ObjectBasicType_);

			// ������ ����
			pFile.Read(TownMap_ObjectTileInfo_[y][x].ObjectTextureName);

			// float4 Data

			// ObjectTileSize
			int ObjectTileSizeX = 0;
			int ObjectTileSizeY = 0;
			int ObjectTileSizeZ = 0;
			pFile.Read(ObjectTileSizeX);
			pFile.Read(ObjectTileSizeY);
			pFile.Read(ObjectTileSizeZ);
			TownMap_ObjectTileInfo_[y][x].ObjectTileSize = float4(static_cast<float>(ObjectTileSizeX), static_cast<float>(ObjectTileSizeY), static_cast<float>(ObjectTileSizeZ));

			// ObjectRenderSize
			int ObjectRenderSizeX = 0;
			int ObjectRenderSizeY = 0;
			int ObjectRenderSizeZ = 0;
			pFile.Read(ObjectRenderSizeX);
			pFile.Read(ObjectRenderSizeY);
			pFile.Read(ObjectRenderSizeZ);
			TownMap_ObjectTileInfo_[y][x].ObjectRenderSize = float4(static_cast<float>(ObjectRenderSizeX), static_cast<float>(ObjectRenderSizeY), static_cast<float>(ObjectRenderSizeZ));

			// ObjectRenderPivotPos
			int ObjectRenderPivotPosX = 0;
			int ObjectRenderPivotPosY = 0;
			int ObjectRenderPivotPosZ = 0;
			pFile.Read(ObjectRenderPivotPosX);
			pFile.Read(ObjectRenderPivotPosY);
			pFile.Read(ObjectRenderPivotPosZ);
			TownMap_ObjectTileInfo_[y][x].ObjectRenderPivotPos = float4(static_cast<float>(ObjectRenderPivotPosX), static_cast<float>(ObjectRenderPivotPosY), static_cast<float>(ObjectRenderPivotPosZ));
		}
	}

	pFile.Close();

	// �����ε� �Ϸ� �� ������ ��������
	CreatedAfterLoadingTiles();

	// ������ �����Ϸ� �� �ش� ���� �׺���̼� ���� ��������
	CreateNavigationInfo();

	// �ش� �ʿ� ���� ��ġ

	return true;
}

void TownMap::CreatedAfterLoadingTiles()
{
	// ���̰� ���� : �ٴ� -> �� -> ������Ʈ
	CreatedAfterFloorTiles();
	CreatedAfterWallTiles();
	CreatedAfterObjectTiles();

	// ������Ʈ���� ���̰� ����
	TileMapDepthUpdate();
}

void TownMap::CreatedAfterFloorTiles()
{
	// �ٴڷ����� ����
	//std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;
	int YInfoCnt = static_cast<int>(TownMap_FloorTileInfo_.size());
	int XInfoCnt = static_cast<int>(TownMap_FloorTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(TownMap_FloorTileInfo_[y][x].FloorIndexX, TownMap_FloorTileInfo_[y][x].FloorIndexY);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * TownMap_FloorTileInfo_[y][x].FloorTileSize.halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -TownMap_FloorTileInfo_[y][x].FloorTileSize.halffloat4().y;

			Renderer->SetImage(TownMap_FloorTileInfo_[y][x].FloorTextureName);
			Renderer->GetTransform()->SetLocalScaling(TownMap_FloorTileInfo_[y][x].FloorRenderSize);
			Renderer->GetTransform()->SetLocalPosition(TownMap_FloorTileInfo_[y][x].FloorRenderPivotPos + Pos);
			Renderer->GetTransform()->SetLocalZOrder(100.f);
			Renderer->SetIndex(TownMap_FloorTileInfo_[y][x].FloorImageIndex);
			FloorTiles_.insert(std::make_pair(Index.Index_, Renderer));
		}
	}
}

void TownMap::CreatedAfterWallTiles()
{
	// �������� ����
	//std::unordered_map<__int64, WallTileRenderer> WallTiles_;
	int YInfoCnt = static_cast<int>(TownMap_WallTileInfo_.size());
	int XInfoCnt = static_cast<int>(TownMap_WallTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(TownMap_WallTileInfo_[y][x].WallIndexX, TownMap_WallTileInfo_[y][x].WallIndexY);

			WallTileRenderer WallTiles = {};

			WallTiles.WallTiles1_ = CreateTransformComponent<GameEngineTileMapRenderer>();
			WallTiles.WallTiles2_ = nullptr;

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * TownMap_WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -TownMap_WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().y;

			WallTiles.WallTiles1_->SetImage(TownMap_WallTileInfo_[y][x].WallTextureName);
			WallTiles.WallTiles1_->GetTransform()->SetLocalScaling(TownMap_WallTileInfo_[y][x].WallRenderSize);
			WallTiles.WallTiles1_->GetTransform()->SetLocalPosition(TownMap_WallTileInfo_[y][x].WallRenderPivotPos + Pos);

			// ��Ÿ�Ժ� �̹���
			// ��, Normal, None�̸� �������� ������������
			if (TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::NONE || TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::NORMAL)
			{
				WallTiles.WallTiles1_->Death();
				if (nullptr != WallTiles.WallTiles2_)
				{
					WallTiles.WallTiles2_->Death();
				}
			}
			// BENT_MULTI�̸� ������ 2��
			else if (TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_MULTI)
			{
				WallTiles.WallTiles1_->SetIndex(TownMap_WallTileInfo_[y][x].WallTile1ImageIndex);

				WallTiles.WallTiles2_ = CreateTransformComponent<GameEngineTileMapRenderer>();
				WallTiles.WallTiles2_->SetImage(TownMap_WallTileInfo_[y][x].WallTextureName);
				WallTiles.WallTiles2_->GetTransform()->SetLocalScaling(TownMap_WallTileInfo_[y][x].WallRenderSize);
				WallTiles.WallTiles2_->GetTransform()->SetLocalPosition(TownMap_WallTileInfo_[y][x].WallRenderPivotPos + Pos);
				WallTiles.WallTiles2_->GetTransform()->SetLocalZOrder(99.f);
				WallTiles.WallTiles2_->SetIndex(TownMap_WallTileInfo_[y][x].WallTile2ImageIndex);

				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else
			{
				// ��Ÿ�Ժ� ���̰� ���� :	RT_B -> RB_R
				//							 -> BENT_S -> RB_L -> RT_T
				if (TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T ||
					TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T_LE ||
					TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T_RE)
				{
					WallTiles.WallTiles1_->GetTransform()->SetLocalZOrder(99.f);
				}
				else if (TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B ||
					TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B_LE ||
					TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B_RE)
				{
				}
				else if (TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L ||
					TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L_TE ||
					TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L_BE)
				{
				}
				else if (TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R ||
					TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R_TE ||
					TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R_BE)
				{
					WallTiles.WallTiles1_->GetTransform()->SetLocalZOrder(99.f);
				}
				else if (TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_MULTI)
				{
					WallTiles.WallTiles1_->GetTransform()->SetLocalZOrder(99.f);
				}
				else if (TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_SINGLE)
				{
				}
				else // �׿�
				{
					WallTiles.WallTiles1_->GetTransform()->SetLocalZOrder(99.f);
				}

				WallTiles.WallTiles1_->SetIndex(TownMap_WallTileInfo_[y][x].WallTile1ImageIndex);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
		}
	}
}

void TownMap::CreatedAfterObjectTiles()
{
	// ������Ʈ������ ����
	//std::unordered_map<__int64, GameEngineTileMapRenderer*> ObjectTiles_;
	int YInfoCnt = static_cast<int>(TownMap_ObjectTileInfo_.size());
	int XInfoCnt = static_cast<int>(TownMap_ObjectTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(TownMap_ObjectTileInfo_[y][x].ObjectIndexX, TownMap_ObjectTileInfo_[y][x].ObjectIndexY);

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * TownMap_ObjectTileInfo_[y][x].ObjectTileSize.halffloat4().halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -TownMap_ObjectTileInfo_[y][x].ObjectTileSize.halffloat4().halffloat4().y;

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			Renderer->SetImage(TownMap_ObjectTileInfo_[y][x].ObjectTextureName);
			Renderer->GetTransform()->SetLocalScaling(TownMap_ObjectTileInfo_[y][x].ObjectRenderSize);
			Renderer->GetTransform()->SetLocalPosition(TownMap_ObjectTileInfo_[y][x].ObjectRenderPivotPos + Pos);

			// -1 == ObjectTileInfo_[y][x].ObjectImageIndex�̸� ������Ʈ�� ��ġ�Ǿ��������� Ÿ�Ϸ� �Ǵ�
			if (-1 != TownMap_ObjectTileInfo_[y][x].ObjectImageIndex)
			{
				Renderer->SetIndex(TownMap_ObjectTileInfo_[y][x].ObjectImageIndex);
				ObjectTiles_.insert(std::make_pair(Index.Index_, Renderer));
			}
			else
			{
				Renderer->Death();
			}
		}
	}
}

void TownMap::TileMapDepthUpdate()
{
	// �÷��̾�� ���̹��ۿ� ���� ó���� �ʿ��ϱ⶧���� ObjectŸ�ϸ���� �о�鿩
	// Ÿ���� Object�� Ÿ���ε����� �ٴ�Ÿ���� ���Ͽ� �ش� Ÿ���� ���̰��� ����
	int YInfoCnt = static_cast<int>(TownMap_ObjectTileInfo_.size());
	int XInfoCnt = static_cast<int>(TownMap_ObjectTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			if (ObjectBasicType::OBJECT == TownMap_ObjectTileInfo_[y][x].ObjectBasicType)
			{
				// �ش� Ÿ���� ������ �ٴ�Ÿ���� ��� ã�Ƴ��� ���̰��� 0���� �����Ѵ�.





			}
		}
	}
}

void TownMap::CreateNavigationInfo()
{
	// �ش� �ʿ� �����ϴ� ��� ����(NPC, �÷��̾�, ...)���� ��ã�� �˰����� ������ �����ϱ� ����
	// �׺���̼� ������ ����

	// �������� ������Ʈ������ �̿��Ͽ� �׺����̼� ������ ����
	// �������� ������Ʈ������ Ÿ�ϱ��� �����ϸ�, �� Ÿ�Ժ� �̵��Ұ����� �Ǵ��Ͽ�
	// �׺���̼� ������ �����Ѵ�.
	int YInfoCnt = static_cast<int>(TownMap_WallTileInfo_.size());
	int XInfoCnt = static_cast<int>(TownMap_WallTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index;
			Index.X_ = TownMap_WallTileInfo_[y][x].WallIndexX;
			Index.Y_ = TownMap_WallTileInfo_[y][x].WallIndexY;

			// ��Ÿ�� �� �븻 Ÿ���� �̵���������
			if (TownMap_WallTileInfo_[y][x].WallBasicType == WallBasicType::NORMAL)
			{
				NavTownMap_.insert(std::make_pair(Index.Index_, NavigationType::NOR));
			}
			else
			{
				NavTownMap_.insert(std::make_pair(Index.Index_, NavigationType::WALL));
			}

			// ������ƮŸ�� �� �븻 Ÿ���� ������ Ÿ���� ������ �Ǵ�
			if (TownMap_ObjectTileInfo_[y][x].ObjectBasicType == ObjectBasicType::WALL ||
				TownMap_ObjectTileInfo_[y][x].ObjectBasicType == ObjectBasicType::OBJECT)
			{
				// �̹� �����ϴ� �ε����� Ÿ�Ը� ���� �ƴϸ� �߰�
				if (NavTownMap_.end() != NavTownMap_.find(Index.Index_))
				{
					NavTownMap_[Index.Index_] = NavigationType::WALL;
				}
				else
				{
					NavTownMap_.insert(std::make_pair(Index.Index_, NavigationType::WALL));
				}
			}
		}
	}

	// �׺���̼� ����
	Navigation_ = new GameEnginePathFind();
}

void TownMap::TownLevelNavigationDebugRender()
{
	// ��������忡���� Ȯ�ο����� ���
	if (true == DebugRendererFlag_)
	{
		//if (false == ObjectTiles_.empty())
		//{
			//std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = ObjectTiles_.begin();
			//std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = ObjectTiles_.end();
			//for (; StartIter != EndIter; ++StartIter)
			//{
			//	GetLevel()->PushDebugRender((*StartIter).second->GetTransform(), CollisionType::Rect);
			//}
		//}
	}
}

TileIndex TownMap::GetFloorTileIndex(float4 _MousePos)
{
	TileIndex Index = {};

	float RatioX = ((_MousePos.x / TileSize_.halffloat4().x) - (_MousePos.y / TileSize_.halffloat4().y)) / 2.0f;
	float RatioY = ((_MousePos.y / TileSize_.halffloat4().y) + (_MousePos.x / TileSize_.halffloat4().x)) / -2.0f;

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

TileIndex TownMap::GetNavigationIndex(float4 _MousePos)
{
	TileIndex Index = {};

	float RatioX = ((_MousePos.x / TileSize_.halffloat4().halffloat4().x) - (_MousePos.y / TileSize_.halffloat4().halffloat4().y)) / 2.0f;
	float RatioY = ((_MousePos.y / TileSize_.halffloat4().halffloat4().y) + (_MousePos.x / TileSize_.halffloat4().halffloat4().x)) / -2.0f;

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

NavigationType TownMap::GetTileToNaviType(float4 _MousePos)
{
	TileIndex TileIndex = GetNavigationIndex(_MousePos);

	if (NavTownMap_.end() != NavTownMap_.find(TileIndex.Index_))
	{
		return NavTownMap_[TileIndex.Index_];
	}

	return NavigationType();
}

bool TownMap::Moveable4WaysCheck(PathIndex _PathIndex)
{
	TileIndex CheckTileIndex;
	CheckTileIndex.X_ = _PathIndex.X_;
	CheckTileIndex.Y_ = _PathIndex.Y_;

	// �׺���̼� �ε��� Ÿ�Կ� �����ϴ� �ε����̸�, WallŸ���̸� �̵��Ұ�����
	if (NavTownMap_.end() != NavTownMap_.find(CheckTileIndex.Index_))
	{
		if (NavTownMap_[CheckTileIndex.Index_] == NavigationType::WALL)
		{
			return true;
		}
	}

	return false;
}

bool TownMap::Moveable8WaysCheck(PathIndex _PathIndex)
{
	TileIndex CheckTileIndex;
	CheckTileIndex.X_ = _PathIndex.X_;
	CheckTileIndex.Y_ = _PathIndex.Y_;

	// �׺���̼� �ε��� Ÿ�Կ� �����ϴ� �ε����̸�, WallŸ���̸� �̵��Ұ�����
	if (NavTownMap_.end() != NavTownMap_.find(CheckTileIndex.Index_))
	{
		if (NavTownMap_[CheckTileIndex.Index_] == NavigationType::WALL)
		{
			return true;
		}
		else // non or nor Ÿ���϶�
		{
			// �̵��Ϸ��� Ÿ�� �̿�Ÿ���� �˻��Ͽ�
			// ���� �������� �����ϴ� Ÿ���̸� �̵��Ұ��Ǵ�

		}
	}

	return false;
}

std::list<PathIndex> TownMap::NavgationFind4Way(float4 _StartPos, float4 _MouseClickPos)
{
	if (nullptr != Navigation_)
	{
		// �÷��̾��� ������ġ�� �̿��Ͽ� Ÿ���ε��� ���
		TileIndex StartIndex = GetPosToTileIndex(_StartPos);

		// ���콺���ʹ�ưŬ�� ��ġ�� �̿��Ͽ� Ÿ���ε��� ���
		float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
		TileIndex TargetIndex = GetPosToTileIndex(_MouseClickPos + CamPos);

		return Navigation_->AStarFind4Way(PathIndex(StartIndex.X_, StartIndex.Y_), PathIndex(TargetIndex.X_, TargetIndex.Y_), std::bind(&TownMap::Moveable4WaysCheck, this, std::placeholders::_1));
	}

	return std::list<PathIndex>();
}

std::list<PathIndex> TownMap::NavgationFind8Way(float4 _StartPos, float4 _MouseClickPos)
{
	if (nullptr != Navigation_)
	{
		// �÷��̾��� ������ġ�� �̿��Ͽ� Ÿ���ε��� ���
		TileIndex StartIndex = GetPosToTileIndex(_StartPos);

		// ���콺���ʹ�ưŬ�� ��ġ�� �̿��Ͽ� Ÿ���ε��� ���
		float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition();
		TileIndex TargetIndex = GetPosToTileIndex(_MouseClickPos + CamPos);

		return Navigation_->AStarFind8Way(PathIndex(StartIndex.X_, StartIndex.Y_), PathIndex(TargetIndex.X_, TargetIndex.Y_), std::bind(&TownMap::Moveable8WaysCheck, this, std::placeholders::_1));
	}

	return std::list<PathIndex>();
}
