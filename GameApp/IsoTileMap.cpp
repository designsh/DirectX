#include "PreCompile.h"
#include "IsoTileMap.h"
#include <GameEngine/GameEngineTileMapRenderer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

bool IsoTileMap::FirstRandomLoad_ = false;
std::vector<int> IsoTileMap::IgnoreRange;
std::vector<std::vector<float4>> IsoTileMap::RandomRange;
std::vector<std::vector<int>> IsoTileMap::RandomReversRange;
std::vector<std::vector<int>> IsoTileMap::RandomNextRange;

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
	// 바닥타일
	FloorTileSize_ = { 160.0f, 80.f };
	FloorTileSizeHalf_ = FloorTileSize_.halffloat4();
	FloorTileIndexPivotPos_ = { 0.0f, -FloorTileSizeHalf_.y  };

	// 벽타일
	WallTileSize_ = { 160.0f, 320.f };
	WallTileSizeHalf_ = WallTileSize_.halffloat4();
	//WallTileIndexPivotPos_ = { 0.0f, -WallTileSizeHalf_.y };
	WallTileIndexPivotPos_ = { 0.0f, 0.0f };

#pragma region RandomLoad 관련
	RandomStartPos_.clear();
	RandomStartPos_ = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };

	IgnoreRange.resize(4);
	RandomNextRange.resize(4);
	RandomRange = { {float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN},
					{float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN},
					{float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN},
					{float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN}, };
	RandomReversRange = { {1, 0, 3, 2},
						  {1, 0, 3, 2},
						  {1, 0, 3, 2},
						  {1, 0, 3, 2}, };

#pragma endregion
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
	RandomStartPos_.clear();
	RandomStartPos_ = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };

	// 랜덤 로드(길) 생성 Flag 초기화
	FirstRandomLoad_ = false;
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

// _Multidirectional = true 이면 _DirCnt에 따라 방향수를 결정
// 최초진행시 최대 4방향 진행, 진행중 최대 3방향진행
void IsoTileMap::RandomRoad(int _Count, bool _Multidirectional)
{
	if (false == _Multidirectional) // 한방향 랜덤 로드(길) 생성
	{
		for (int i = 0; i < 4; i++)
		{
			if (i == IgnoreRange[0])
			{
				continue;
			}

			RandomNextRange[0].push_back(i);
		}

		int DirIndex = RandomNextRange[0][Random_.RandomInt(0, static_cast<int>(RandomNextRange[0].size()) - 1)];

		float4 Dir = RandomRange[0][DirIndex];

		for (size_t i = 0; i < _Count; i++)
		{
			SetTile(TileIndex{ RandomStartPos_[0].ix(), RandomStartPos_[0].iy()});
			RandomStartPos_[0] += Dir;
		}

		IgnoreRange[0] = RandomReversRange[0][DirIndex];
		RandomNextRange[0].clear();
	}
	else // 다방향 랜덤 로드(길) 생성
	{
		if (false == FirstRandomLoad_)
		{
			// 최초 생성 Flag On
			FirstRandomLoad_ = true;

			// 최초 생성되었으므로 최대 4방향 랜덤 로드 생성
			for (int i = 0; i < 4; ++i)
			{
				RandomNextRange[i].push_back(i);
			}
			
			std::vector<int> DirIndex = { {-1}, {-1}, {-1}, {-1}, };
			std::vector<float4> Dir = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };
			
			for (int i = 0; i < 4; ++i)
			{
				DirIndex[i] = RandomNextRange[i][Random_.RandomInt(0, static_cast<int>(RandomNextRange[i].size()) - 1)];
				Dir[i] = RandomRange[i][DirIndex[i]];
				SetTile(TileIndex{ RandomStartPos_[i].ix(), RandomStartPos_[i].iy()});
				RandomStartPos_[i] += Dir[i];
			}

			for (int i = 0; i < 4; ++i)
			{
				IgnoreRange[i] = RandomReversRange[i][DirIndex[i]];
				RandomNextRange[i].clear();
			}
			
			DirIndex.clear();
			Dir.clear();
		}
		else
		{
			// 최대 3방향 랜덤 로드 생성
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 3; j++)
				{
					if (j == IgnoreRange[i])
					{
						continue;
					}

					RandomNextRange[i].push_back(j);
				}
			}

			std::vector<int> DirIndex = { {-1}, {-1}, {-1}, {-1}, };
			std::vector<float4> Dir = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };

			int a = 0;

			for (int i = 0; i < 4; ++i)
			{
				DirIndex[i] = RandomNextRange[i][Random_.RandomInt(0, static_cast<int>(RandomNextRange[i].size()) - 1)];
				Dir[i] = RandomRange[i][DirIndex[i]];
				SetTile(TileIndex{ RandomStartPos_[i].ix(), RandomStartPos_[i].iy()});
				RandomStartPos_[i] += Dir[i];

				IgnoreRange[i] = RandomReversRange[i][DirIndex[i]];
				RandomNextRange[i].clear();
			}

			DirIndex.clear();
			Dir.clear();
		}
	}
}

void IsoTileMap::MapSave()
{
}

void IsoTileMap::MapLoad()
{
}
