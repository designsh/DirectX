#include "PreCompile.h"
#include "IsoTileMap.h"
#include <GameEngine/GameEngineImageRenderer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

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
	Renderer->SetImage(FloorTile_);
	Renderer->SetIndex(0);
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
	// 카메라위치 더하기
	float RatioX = ((_Pos.x / TileSizeHalf.x) - (_Pos.y / TileSizeHalf.y)) / 2.0f;
	float RatioY = ((_Pos.y / TileSizeHalf.y) + (_Pos.x / TileSizeHalf.x)) / -2.0f;

	if (0 > RatioX)
	{
		RatioX += -1;
	}

	if (0 > RatioY)
	{
		RatioY += -1;
	}

	Index.X_ = static_cast<int>(RatioX);
	Index.Y_ = static_cast<int>(RatioY);

	return Index;
}

float4 IsoTileMap::GetIsoPos(float4 _Pos)
{
	return { ((_Pos.x / TileSizeHalf.x) - (_Pos.y / TileSizeHalf.y)) / 2.0f ,((_Pos.y / TileSizeHalf.y) + (_Pos.x / TileSizeHalf.x)) / -2.0f };
}