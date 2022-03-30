#include "PreCompile.h"
#include "IsoTileMap.h"
#include <GameEngine\GameEngineImageRenderer.h>

IsoTileMap::IsoTileMap() 
{
}

IsoTileMap::~IsoTileMap() 
{
}


void IsoTileMap::Start()
{
	TileSize = { 160.0f, 80 };
	TileSizeHalf = TileSize.halffloat4();
	IndexPivotPos = { 0.0f, -TileSizeHalf.y  };


	GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer->SetImage("TileLine.png");
	Renderer->GetTransform()->SetLocalPosition(IndexPivotPos);

	// Yindex == (WorldPosY / TileSizeYHalf –(WorldPosX / TileSizeXHalf)) / 2
	// Xindex == (WorldPosX / TileSizeXHalf + (WorldPosY / TileSizeYHalf)) / 2

}



void IsoTileMap::SetTile(float4 _Pos)
{
	TileIndex Index = GetIndex(_Pos);

	if (Tiles_.end() != Tiles_.find(Index.Index_))
	{
		return;
	}

	float4 Pos;

	Pos.x = (Index.X_ - Index.Y_) * TileSizeHalf.x;
	Pos.y = (Index.X_ + Index.Y_) * -TileSizeHalf.y;

	GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>();
	Renderer->SetImage("TileLine.png");
	Renderer->GetTransform()->SetLocalPosition(IndexPivotPos + Pos);

	Tiles_.insert(std::make_pair(Index.Index_, Renderer));
}

TileIndex IsoTileMap::GetIndex(float4 _Pos) 
{
	TileIndex Index = {};

	//Xindex가 1 증가하면 x는 80증가 한다.
	//Xindex가 1 증가하면 y는 40감소 한다.

	//Yindex가 1 증가하면 x는 80감소 한다.
	//Yindex가 1 증가하면 y는 40감가 한다
	
	// 좌상단 기준 좌하단쪽으로갈수록 y인덱스 증가 우하단쪽으로 갈수록 x인덱스증가
	//        00
	//     01    10
	//   02        20
	Index.X_ = static_cast<int>(((_Pos.x / TileSizeHalf.x) - (_Pos.y / TileSizeHalf.y)) / 2.0f);
	Index.Y_ = static_cast<int>(((_Pos.y / TileSizeHalf.y) + (_Pos.x / TileSizeHalf.x)) / -2.0f);

	return Index;
}