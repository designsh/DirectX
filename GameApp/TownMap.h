#pragma once
#include <GameEngine/GameEngineActor.h>
#include "TileMap_Common.h"
#include "Navigation_Common.h"

// �з� : ��(MAP)
// �뵵 : ������
// ���� : �ٴ�,��,������Ʈ ������ �ε��Ͽ� ȭ�鿡 ���� �������ϸ�, �ش� �������� �̿��Ͽ� 
//        �ʳ��� �����ϴ� ����(NPC, PLAYER, ...)�� �������� �����ϴ� �׺���̼������� �����Ѵ�.

class GameEngineTileMapRenderer;
class TownMap : public GameEngineActor
{
private:
	class WallTileRenderer
	{
	public:
		GameEngineTileMapRenderer* WallTiles1_;
		GameEngineTileMapRenderer* WallTiles2_;

		WallTileRenderer() : WallTiles1_(nullptr), WallTiles2_(nullptr)
		{
		}
	};

private:	// member Var
	MapType MapType_;

private: // ���� �� Ÿ�Ժ�(�ٴ�,��,������Ʈ) ����
	std::vector<std::vector<FloorTileInfo>> TownMap_FloorTileInfo_;
	std::vector<std::vector<WallTileInfo>> TownMap_WallTileInfo_;
	std::vector<std::vector<ObjectTileInfo>> TownMap_ObjectTileInfo_;

private: // Ÿ�� ������
	std::unordered_map<__int64, GameEngineTileMapRenderer*> FloorTiles_;
	std::unordered_map<__int64, WallTileRenderer> WallTiles_;
	std::unordered_map<__int64, GameEngineTileMapRenderer*> ObjectTiles_;

private: // �ش� ���� �׺���̼� ����(������ + ������Ʈ����)
	std::vector<std::vector<NavigationType>> TownMap_Navi_;

private: // Ÿ��ũ��(�ε��� ����)
	float4 TileSize_;

private: // ����׷����� ����Ī Flag
	bool DebugRendererFlag_;

public:
	TownMap();
	~TownMap();

protected:		// delete constructer
	TownMap(const TownMap& _other) = delete;
	TownMap(TownMap&& _other) noexcept = delete;

private:		//delete operator
	TownMap& operator=(const TownMap& _other) = delete;
	TownMap& operator=(const TownMap&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 GetNavigationIndexToPos(TileIndex _TileIndex);

private:
	void MapInfoAllClear();
	void MapTextureCutting();

public:
	bool TownLevel_FixedMapLoad();

#pragma region ����ó��
private: // Ÿ�Ϸ����� ����
	void CreatedAfterLoadingTiles();
	void CreatedAfterFloorTiles();
	void CreatedAfterWallTiles();
	void CreatedAfterObjectTiles();

private: // �׺���̼���������
	void CreateNavigationInfo();

private: // ���� ������ ���� �̿��Ͽ� ��� ���� ��ġ
	void TownLevelArrangeActor();

private: // ����׷����� ǥ��/ǥ�þ���
	void TownLevelNavigationDebugRender();
#pragma endregion

#pragma region Ȯ�ο�
public:
	TileIndex GetFloorTileIndex(float4 _MousePos);
	TileIndex GetNavigationIndex(float4 _MousePos);
	NavigationType GetTileToNaviType(float4 _MousePos);
#pragma endregion
};

