#pragma once
#include <GameEngineBase/GameEnginePathFind.h>
#include <GameEngine/GameEngineActor.h>

#include "GlobalEnumClass.h"
#include "RandomTileMap_Common.h"
#include "Navigation_Common.h"

class GameEngineTileMapRenderer;
struct RandomMapWallRenderer
{
	GameEngineTileMapRenderer* Tiles1_;
	GameEngineTileMapRenderer* Tiles2_;
};

// �з� : 
// �뵵 : 
// ���� : �����Ϳ��� �������� �� �÷��̷������� �ε��Ͽ� ���
class GameEngineTileMapRenderer;
class Fallen;
class SpikeFiend;
class Tainted;
class Zombie;
class Andariel;
class CatacombsMap : public GameEngineActor
{
private:	// member Var
	RandomMapInfo MapInfo_;

private:
	std::map<NavigationObjectType, std::vector<GameEnginePathFind*>> Navigation_;
	std::unordered_map<__int64, NavigationType> NavCatacombsMap_;

private: // ���� �ʿ� �����ϴ� ��� ����, ������Ʈ ���
	std::vector<Fallen*> FallenList_;
	std::vector<SpikeFiend*> SpikeFiendList_;
	std::vector<Tainted*> TaintedList_;
	std::vector<Zombie*> ZombieList_;
	std::vector<Andariel*> AndarielList_;
	
private:
	std::string FloorTileTextureName_;
	std::string WallTileTextureName_;

private: // Ÿ������
	float4 TileSize_;
	float4 TileSizeHalf_;
	float4 TileSizeHHalf_;

private: // �ٴ�Ÿ������
	float4 FloorTileImageSizeHalf_;
	float4 FloorTileImageSize_;
	float4 FloorTileIndexPivotPos_;

private: // ��Ÿ������
	float4 WallTileImageSizeHalf_;
	float4 WallTileImageSize_;
	float4 WallTileIndexPivotPos_;

private:
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;	// ����/�� Ÿ�� ������
	std::unordered_map<__int64, RandomMapWallRenderer> WallTiles_;			// ��/�� Ÿ�� ������

public:
	CatacombsMap();
	~CatacombsMap();

protected:		// delete constructer
	CatacombsMap(const CatacombsMap& _other) = delete;
	CatacombsMap(CatacombsMap&& _other) noexcept = delete;

private:		//delete operator
	CatacombsMap& operator=(const CatacombsMap& _other) = delete;
	CatacombsMap& operator=(const CatacombsMap&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private: // �÷��̾� �ֺ� ��Ÿ�� ����ȭ�۾�
	void AdjustTheTransparencyAroundThePlayer();

public: // ����(��) Ÿ�� üũ
	GameEngineActor* MonsterTileIndexCheck(TileIndex _CheckTile);
	void MonsterDeathToListDelete(GameEngineActor* _DeathMonster);

public:
	inline const RandomMapInfo& GetRandomMapInfo()
	{
		return MapInfo_;
	}

public:
	TileIndex GetFloorTileIndex(float4 _Pos);
	TileIndex GetWallTileIndex(float4 _Pos);
	float4 GetWallTileIndexToPos(TileIndex _TileIndex);
	float4 GetFloorTileIndexToPos(TileIndex _TileIndex);

private:
	void SetFloorTile(float4 _Pos, int CurTileIndex_);
	void SetFloorTile(TileIndex _Index, int CurTileIndex_);
	void SetWallTile(float4 _Pos, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex = 0);
	void SetWallTile(TileIndex _Index, int CurTileIndex_, RandomWallDetailType _Type, int _Multi2TileIndex = 0);

private:
	void MapInfoAllClear();
	void AllCorridorClear();
	void AllRoomClear();
	void AllWallClear();

private:
	void MapTextureCutting();

public:
	void CatacombsMapLoad();

private:
	void MapRendering();
	void FloorTileTextureMatching();
	void WallTileTextureMatching();
	void DoorTileTextureMatching();

private:
	void CurLevelActorRoomArrange();

private:
	void CreateNavigationInfo();

public:
	bool CurTileIndexWallCheck(TileIndex _CurTile);

private:
	bool Moveable4WaysCheck(PathIndex _PathIndex);
	bool Moveable8WaysCheck(PathIndex _PathIndex);

public:
	std::list<PathIndex> NavgationFind4Way(NavigationObjectType _ObjectType, int _NavigationNo, float4 _StartPos, float4 _MouseClickPos);
	std::list<PathIndex> NavgationFind8Way(NavigationObjectType _ObjectType, int _NavigationNo, float4 _StartPos, float4 _MouseClickPos);

public:
	void CreateNavitaion(NavigationObjectType _ObjectType, int _NavigationNo);
};

