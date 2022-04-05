#include "PreCompile.h"
#include "IsoTileMap.h"
#include <GameEngine/GameEngineTileMapRenderer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

IsoTileMap::IsoTileMap() :
	CurTileIndex_(0)
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

	GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();
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

	GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();
	Renderer->SetImage(FloorTile_);
	Renderer->SetIndex(CurTileIndex_);
	Renderer->GetTransform()->SetLocalScaling(TileSize);
	Renderer->GetTransform()->SetLocalPosition(IndexPivotPos + Pos);

	Tiles_.insert(std::make_pair(Index.Index_, Renderer));
}

void IsoTileMap::DelTile(float4 _Pos)
{
	TileIndex Index = GetIndex(_Pos);

	// 타일이 존재하지않다면 리턴
	if (Tiles_.end() == Tiles_.find(Index.Index_))
	{
		return;
	}

	// 존재한다면 해당 타일 삭제
	std::unordered_map<__int64, GameEngineImageRenderer*>::iterator StartIter = Tiles_.begin();
	std::unordered_map<__int64, GameEngineImageRenderer*>::iterator EndIter = Tiles_.end();
	for (; StartIter != EndIter;)
	{
		if ((*StartIter).first == Index.Index_)
		{
			// 세컨드 데스처리
			(*StartIter).second->Death();

			// 맵에서 제거
			Tiles_.erase(StartIter++);
			EndIter = Tiles_.end();
		}
		else
		{
			++StartIter;
		}
	}
}

TileIndex IsoTileMap::GetIndex(float4 _Pos)
{
	TileIndex Index = {};

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