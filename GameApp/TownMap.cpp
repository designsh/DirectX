#include "PreCompile.h"
#include "TownMap.h"

#include <GameEngine/GameEngineTileMapRenderer.h>

TownMap::TownMap() :
	MapType_(MapType::FIXED)
{
}

TownMap::~TownMap()
{
}

void TownMap::Start()
{
}

void TownMap::Update(float _DeltaTime)
{
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

	return true;
}

void TownMap::CreatedAfterLoadingTiles()
{
	// �ٴڷ����� ����
	//std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;
	

	// �������� ����
	//std::unordered_map<__int64, WallTileRenderer> WallTiles_;
	

	// ������Ʈ������ ����
	//std::unordered_map<__int64, GameEngineTileMapRenderer*> ObjectTiles_;


}

void TownMap::CreateNavigationInfo()
{
}
