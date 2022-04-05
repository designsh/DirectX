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
	RandomStart = float4::ZERO;
	TileSize = { 160.0f, 80 };
	TileSizeHalf = TileSize.halffloat4();
	IndexPivotPos = { 0.0f, -TileSizeHalf.y  };
}

void IsoTileMap::SetTile(float4 _Pos)
{
	SetTile(GetIndex(_Pos));
}

void IsoTileMap::SetTile(TileIndex Index)
{

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

void IsoTileMap::RandomRoad(int _Count) 
{
	static int IgnoreRange = 0;
	static std::vector<float4> Range = { float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN };
	static std::vector<int> ReversRange = { 1, 0, 3, 2 };
	static std::vector<int> NextRange;

	for (int i = 0; i < 4; i++)
	{
		if (i == IgnoreRange)
		{
			continue;
		}

		NextRange.push_back(i);
	}

	int DirIndex = NextRange[Random.RandomInt(0, NextRange.size() -1)];

	float4 Dir = Range[DirIndex];

	for (size_t i = 0; i < _Count; i++)
	{
		SetTile(TileIndex{ RandomStart.ix(), RandomStart.iy() });
		RandomStart += Dir;
	}

	IgnoreRange = ReversRange[DirIndex];
	NextRange.clear();
}
