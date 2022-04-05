#include "PreCompile.h"
#include "IsoTileMap.h"
#include <GameEngine/GameEngineTileMapRenderer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

IsoTileMap::IsoTileMap() :
	CurTileIndex_(0),
	CurTileType_(TileType::FLOOR)
{
}

IsoTileMap::~IsoTileMap() 
{
}

void IsoTileMap::Start()
{
	// 랜덤
	RandomStartPos_ = float4::ZERO;

	// 바닥타일
	FloorTileSize_ = { 160.0f, 80.f };
	FloorTileSizeHalf_ = FloorTileSize_.halffloat4();
	FloorTileIndexPivotPos_ = { 0.0f, -FloorTileSizeHalf_.y  };

	// 벽타일
	WallTileSize_ = { 160.0f, 320.f };
	WallTileSizeHalf_ = WallTileSize_.halffloat4();
	WallTileIndexPivotPos_ = { 0.0f, -WallTileSizeHalf_.y };
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
	Pos.x = (Index.X_ - Index.Y_) * FloorTileSizeHalf_.x;
	Pos.y = (Index.X_ + Index.Y_) * -FloorTileSizeHalf_.y;

	GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();
	
	// 선택된 텍스쳐 구분(0: Floor, 1: Wall)
	if (TileType::FLOOR == CurTileType_)
	{
		Renderer->SetImage(FloorTileTextureName_);
		Renderer->GetTransform()->SetLocalScaling(FloorTileSize_);
		Renderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
	}
	else
	{
		Renderer->SetImage(WallTileTextureName_);
		Renderer->GetTransform()->SetLocalScaling(WallTileSize_);
		Renderer->GetTransform()->SetLocalPosition(WallTileIndexPivotPos_ + Pos);
	}
	Renderer->SetIndex(CurTileIndex_);
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
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = Tiles_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = Tiles_.end();
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

void IsoTileMap::AllTileClear()
{
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = Tiles_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = Tiles_.end();
	for (; StartIter != EndIter;)
	{
		// 세컨드 데스처리
		(*StartIter).second->Death();

		// 맵에서 제거
		Tiles_.erase(StartIter++);
		EndIter = Tiles_.end();
	}
	Tiles_.clear();

	// 랜덤맵 시작점 초기화
	RandomStartPos_ = float4::ZERO;
}

TileIndex IsoTileMap::GetIndex(float4 _Pos)
{
	TileIndex Index = {};

	float RatioX = ((_Pos.x / FloorTileSizeHalf_.x) - (_Pos.y / FloorTileSizeHalf_.y)) / 2.0f;
	float RatioY = ((_Pos.y / FloorTileSizeHalf_.y) + (_Pos.x / FloorTileSizeHalf_.x)) / -2.0f;

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
	return { ((_Pos.x / FloorTileSizeHalf_.x) - (_Pos.y / FloorTileSizeHalf_.y)) / 2.0f ,((_Pos.y / FloorTileSizeHalf_.y) + (_Pos.x / FloorTileSizeHalf_.x)) / -2.0f };
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

	int DirIndex = NextRange[Random_.RandomInt(0, static_cast<int>(NextRange.size()) - 1)];

	float4 Dir = Range[DirIndex];

	for (size_t i = 0; i < _Count; i++)
	{
		SetTile(TileIndex{ RandomStartPos_.ix(), RandomStartPos_.iy() });
		RandomStartPos_ += Dir;
	}

	IgnoreRange = ReversRange[DirIndex];
	NextRange.clear();
}
