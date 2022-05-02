#pragma once
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>

#include "RandomTileMap_Common.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTileMapRenderer;
class EditorRandomMap : public GameEngineActor
{
private: // Ÿ������
	float4 TileSize_;
	float4 TileSizeHalf_;
	float4 TileSizeHHalf_;
	float4 TileSizeHHHalf_;

private: // �ٴ�Ÿ������
	float4 FloorTileImageSizeHalf_;
	float4 FloorTileImageSize_;
	float4 FloorTileIndexPivotPos_;

private: // ��Ÿ������
	float4 WallTileImageSizeHalf_;
	float4 WallTileImageSize_;
	float4 WallTileIndexPivotPos_;

private: // ������ƮŸ������
	float4 ObjectTileImageSizeHalf_;
	float4 ObjectTileImageSize_;
	float4 ObjectTileIndexPivotPos_;

private:



public:
	EditorRandomMap();
	~EditorRandomMap();

protected:		// delete constructer
	EditorRandomMap(const EditorRandomMap& _other) = delete;
	EditorRandomMap(EditorRandomMap&& _other) noexcept = delete;

private:		//delete operator
	EditorRandomMap& operator=(const EditorRandomMap& _other) = delete;
	EditorRandomMap& operator=(const EditorRandomMap&& _other) = delete;

private:
	void Start() override;

public:
	TileIndex GetFloorTileIndex(float4 _Pos);
	TileIndex GetWallTileIndex(float4 _Pos);

public: // �ٴ�Ÿ������ ����(�׸��� ǥ��)
	void CreateSplitDungeon(int _Width, int _Height);					// ���ҵ� ���� ����(�����Ǵ� ���� �ִ�ũ�⸦ ���ڷ� ���´�.) -> ���ҿϷ�� ȭ�鿡 �׸������·� ������
	void CreateRoomintheDungeon();										// ���ҵ� �������� �����(�������� Ÿ��2�� �������� ���� ����) -> �� ��ġ�Ϸ�� ȭ�鿡 �׸������·� ������
	void ConnectTheRoom();												// ��� ���� ���� -> ��� �뿬��Ϸ�� ȭ�鿡 �׸������·� ������

public: // ��Ÿ������ ��������(�׸���ǥ��)
	void CreateWall();													// �ٴ�Ÿ���� üũ�Ͽ� ��Ÿ���� �����Ѵ�.
																		// ��, ������ üũ�ϴ� ������ ���� Ÿ��(2)�� �����ϰ�,
																		// ������ RT_T, RT_B, RB_L, RB_R, BENT_MULTI, BENT_SINGLE Ÿ������ �����Ͽ� �����Ѵ�.
																		// -> ��� ��Ÿ�������� �̿��� ��Ÿ�� �����Ϸ�� ȭ�鿡 �׸������·� ������

public: // ������ ������ �ٴ�/��Ÿ�� ������ �̿��Ͽ� �������� ��Ī
	void RandomMapTileMatching();										// �� Ÿ�Ժ� ����Ʈ �ؽ��Ŀ� ��Ī�Ͽ� ������ -> ��� �ؽ��� ��Ī�Ϸ�� ȭ�鿡 ������

};

