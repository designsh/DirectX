#include "PreCompile.h"
#include "IsoTileMap.h"
#include <GameEngine/GameEngineTileMapRenderer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

#include "GlobalEnumClass.h"

bool IsoTileMap::FirstRandomLoad_ = false;
std::vector<int> IsoTileMap::IgnoreRange;
std::vector<std::vector<float4>> IsoTileMap::RandomRange;
std::vector<std::vector<int>> IsoTileMap::RandomReversRange;
std::vector<std::vector<int>> IsoTileMap::RandomNextRange;

IsoTileMap::IsoTileMap()
{
}

IsoTileMap::~IsoTileMap() 
{
}

void IsoTileMap::Start()
{
	// 타일
	TileSize_ = float4(160.f, 80.f);			// Floor Tile Index 계산기준값
	TileSizeHalf_ = TileSize_.halffloat4();		// Wall Tile Index 계산기준값
	TileSizeHHalf_ = TileSizeHalf_.halffloat4();

	// 바닥타일
	FloorTileImageSize_ = { 160.0f, 80.f };

	FloorTileImageSizeHalf_ = FloorTileImageSize_.halffloat4();
	FloorTileIndexPivotPos_ = { 0.0f, -TileSizeHalf_.y  };

	// 벽타일
	WallTileImageSize_ = { 160.0f, 320.f };

	WallTileImageSizeHalf_ = WallTileImageSize_.halffloat4();
	WallTileIndexPivotPos_ = { 0.0f, TileSize_.y };

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

void IsoTileMap::SetFloorTile(float4 _Pos, int CurTileIndex_)
{
	SetFloorTile(GetFloorTileIndex(_Pos), CurTileIndex_);
}

void IsoTileMap::SetFloorTile(TileIndex Index, int CurTileIndex_)
{
	if (FloorTiles_.end() != FloorTiles_.find(Index.Index_))
	{
		FloorTiles_.find(Index.Index_)->second->SetIndex(CurTileIndex_);
		return;
	}

	float4 Pos;
	Pos.x = (Index.X_ - Index.Y_) * TileSizeHalf_.x;
	Pos.y = (Index.X_ + Index.Y_) * -TileSizeHalf_.y;

	GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();
	
	Renderer->SetImage(FloorTileTextureName_);
	Renderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
	Renderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
	Renderer->SetIndex(CurTileIndex_);
	FloorTiles_.insert(std::make_pair(Index.Index_, Renderer));
}

void IsoTileMap::SetWallTile(float4 _Pos, int CurTileIndex_)
{
	SetWallTile(GetWallTileIndex(_Pos), CurTileIndex_);
}

void IsoTileMap::SetWallTile(TileIndex _Index, int CurTileIndex_)
{
	if (WallTiles_.end() != WallTiles_.find(_Index.Index_))
	{
		WallTiles_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);
		return;
	}

	float4 Pos;
	Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
	Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

	GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

	//Renderer->SetImage("WallGrid.png"); // 테스트용
	//Renderer->GetTransform()->SetLocalScaling(TileSizeHalf_);

	Renderer->SetImage(WallTileTextureName_);
	Renderer->GetTransform()->SetLocalScaling(WallTileImageSize_);
	Renderer->GetTransform()->SetLocalPosition(WallTileIndexPivotPos_ + Pos);
	Renderer->SetIndex(CurTileIndex_);
	WallTiles_.insert(std::make_pair(_Index.Index_, Renderer));
}

void IsoTileMap::DelWallTile(float4 _Pos) 
{
	TileIndex Index = GetWallTileIndex(_Pos);

	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator FindIter = WallTiles_.find(Index.Index_);

	// 타일이 존재하지않다면 리턴
	if (WallTiles_.end() == FindIter)
	{
		return;
	}

	FindIter->second->Death();
	WallTiles_.erase(FindIter);
}

void IsoTileMap::DelFloorTile(float4 _Pos)
{
	TileIndex Index = GetFloorTileIndex(_Pos);

	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator FindIter = FloorTiles_.find(Index.Index_);

	// 타일이 존재하지않다면 리턴
	if (FloorTiles_.end() == FindIter)
	{
		return;
	}

	FindIter->second->Death();
	FloorTiles_.erase(FindIter);
}

void IsoTileMap::AllTileClear()
{
	{
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = WallTiles_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = WallTiles_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			// 세컨드 데스처리
			(*StartIter).second->Death();
		}
		WallTiles_.clear();
	}

	{
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = FloorTiles_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = FloorTiles_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			// 세컨드 데스처리
			(*StartIter).second->Death();
		}
		FloorTiles_.clear();
	}

	// 랜덤맵 시작점 초기화
	RandomStartPos_.clear();
	RandomStartPos_ = { {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, {float4::ZERO}, };

	// 랜덤 로드(길) 생성 Flag 초기화
	FirstRandomLoad_ = false;
}

TileIndex IsoTileMap::GetFloorTileIndex(float4 _Pos)
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

TileIndex IsoTileMap::GetWallTileIndex(float4 _Pos)
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

float4 IsoTileMap::GetFloorIsoPos(float4 _Pos)
{
	return { ((_Pos.x / TileSizeHalf_.x) - (_Pos.y / TileSizeHalf_.y)) / 2.0f ,((_Pos.y / TileSizeHalf_.y) + (_Pos.x / TileSizeHalf_.x)) / -2.0f };
}

float4 IsoTileMap::GetWallIsoPos(float4 _Pos)
{
	return { ((_Pos.x / TileSizeHHalf_.x) - (_Pos.y / TileSizeHHalf_.y)) / 2.0f, ((_Pos.y / TileSizeHHalf_.y) + (_Pos.x / TileSizeHHalf_.x)) / -2.0f };
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
			SetFloorTile(TileIndex{ RandomStartPos_[0].ix(), RandomStartPos_[0].iy()}, 0);
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
				SetFloorTile(TileIndex{ RandomStartPos_[i].ix(), RandomStartPos_[i].iy()}, 0);
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

			for (int i = 0; i < 4; ++i)
			{
				DirIndex[i] = RandomNextRange[i][Random_.RandomInt(0, static_cast<int>(RandomNextRange[i].size()) - 1)];
				Dir[i] = RandomRange[i][DirIndex[i]];
				SetFloorTile(TileIndex{ RandomStartPos_[i].ix(), RandomStartPos_[i].iy()}, 0);
				RandomStartPos_[i] += Dir[i];

				IgnoreRange[i] = RandomReversRange[i][DirIndex[i]];
				RandomNextRange[i].clear();
			}

			DirIndex.clear();
			Dir.clear();
		}
	}
}

#pragma region 테스트용 그리드 생성 및 제거

void IsoTileMap::CreateFloorGrid(int _X, int _Y)
{
	// 바닥 타일 그리드 생성
	for (int y = 0; y < _Y; ++y)
	{
		for (int x = 0; x < _X; ++x)
		{
			TileIndex Index = {};

			float4 Pos = float4::ZERO;
			Pos.x = (x - y) * TileSizeHalf_.x;
			Pos.y = (x + y) * -TileSizeHalf_.y;


			float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
			Index = GetFloorTileIndex((Pos * GetLevel()->GetMainCamera()->GetZoomValue()) + CameraPos);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			Renderer->SetImage("FloorGrid.png");
			Renderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
			Renderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
			FloorGrides_.insert(std::make_pair(Index.Index_, Renderer));
		}
	}
}

void IsoTileMap::ClearFloorGrid()
{
	// 생성된 바닥타일 그리드 모두 제거
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = FloorGrides_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = FloorGrides_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// 세컨드 데스처리
		(*StartIter).second->Death();
	}
	FloorGrides_.clear();
}

void IsoTileMap::CreateWallGrid(int _X, int _Y)
{
	// 벽 타일 그리드 생성
	for (int y = 0; y < _Y; ++y)
	{
		for (int x = 0; x < _X; ++x)
		{
			TileIndex Index = {};

			float4 Pos = float4::ZERO;
			Pos.x = (x - y) * TileSizeHHalf_.x;
			Pos.y = (x + y) * -TileSizeHHalf_.y;


			float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
			Index = GetWallTileIndex((Pos * GetLevel()->GetMainCamera()->GetZoomValue()) + CameraPos);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			Renderer->SetImage("WallGrid.png");
			Renderer->GetTransform()->SetLocalScaling(TileSizeHalf_);
			Renderer->GetTransform()->SetLocalPosition(WallTileIndexPivotPos_ + Pos);
			Renderer->GetTransform()->SetZOrder(-1.f);
			WallGrides_.insert(std::make_pair(Index.Index_, Renderer));
		}
	}
}

void IsoTileMap::ClearWallGrid()
{
	// 생성된 벽타일 그리드 모두 제거
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = WallGrides_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = WallGrides_.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		// 세컨드 데스처리
		(*StartIter).second->Death();
	}
	WallGrides_.clear();
}

#pragma endregion

#pragma region 맵 저장 및 로드
void IsoTileMap::MapSave()
{

}

void IsoTileMap::MapLoad()
{

}
#pragma endregion
