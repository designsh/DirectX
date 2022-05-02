#include "PreCompile.h"
#include "EditorRandomMap.h"

#include "Dungeon.h"

EditorRandomMap::EditorRandomMap()
{
}

EditorRandomMap::~EditorRandomMap()
{
}

void EditorRandomMap::Start()
{
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

	// ������ƮŸ��
	ObjectTileImageSize_ = { 160.0f, 320.f };
	ObjectTileImageSizeHalf_ = ObjectTileImageSize_.halffloat4();
	ObjectTileIndexPivotPos_ = { 0.0f, TileSize_.y };
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

void EditorRandomMap::CreateSplitDungeon(int _Width, int _Height)
{
	// ���� ���� ����


	// ���� ������������ ���� ����

}

void EditorRandomMap::CreateRoomintheDungeon()
{
	// ���� ������ �Ϸ�Ǿ����Ƿ� ���ҵ� �������� ���� ����

}

void EditorRandomMap::ConnectTheRoom()
{
	// ��� ���� �����Ϸ�Ǿ����Ƿ� ��� ���� ����


}

void EditorRandomMap::CreateWall()
{
	// ��� ������ �����Ǿ����Ƿ� �ٴ�Ÿ�������� �̿��Ͽ� ��Ÿ�������� ����



}

void EditorRandomMap::RandomMapTileMatching()
{
	// ��� Ÿ�������� �����Ϸ�Ǿ����Ƿ� �� Ÿ���� Ÿ�Կ� �°� ����Ʈ�ؽ��� ��Ī�Ͽ� ������ ����



}

