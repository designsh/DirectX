#include "PreCompile.h"
#include "TileMap.h"

#include <GameEngine/GameEngineTileMapRenderer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

#include "GlobalEnumClass.h"

TileMap::TileMap() :
	TileRenderingType_(TileRenderingType::GRID)
{
}

TileMap::~TileMap()
{
}

void TileMap::Start()
{
	// ������ ��� �⺻ ���� �ʱ�ȭ

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

}

#pragma region ���Ǳ�ɰ���

void TileMap::SetTileRenderingMode(TileRenderingType _RenderingType)
{
	TileRenderingType_ = _RenderingType;
}

#pragma endregion

#pragma region IMGUIǥ�ÿ�

float4 TileMap::GetFloorIsoPos(float4 _Pos)
{
	return { ((_Pos.x / TileSizeHalf_.x) - (_Pos.y / TileSizeHalf_.y)) / 2.0f ,((_Pos.y / TileSizeHalf_.y) + (_Pos.x / TileSizeHalf_.x)) / -2.0f };
}

float4 TileMap::GetWallIsoPos(float4 _Pos)
{
	return { ((_Pos.x / TileSizeHHalf_.x) - (_Pos.y / TileSizeHHalf_.y)) / 2.0f, ((_Pos.y / TileSizeHHalf_.y) + (_Pos.x / TileSizeHHalf_.x)) / -2.0f };
}

#pragma endregion

#pragma region GetTileIndex(Floor/Wall)

TileIndex TileMap::GetFloorTileIndex(float4 _Pos)
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

TileIndex TileMap::GetWallTileIndex(float4 _Pos)
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

#pragma endregion

#pragma region SetTile(Floor/Wall)

void TileMap::SetFloorTile(float4 _Pos, int CurTileIndex_)
{
	SetFloorTile(GetFloorTileIndex(_Pos), CurTileIndex_);
}

void TileMap::SetFloorTile(TileIndex _Index, int CurTileIndex_)
{
	// ������ Ÿ���ε����� �����ϸ� �ش� Ÿ���ε����� Ÿ���̹����� ���� ���õ� �̹����� ����
	if (FloorTiles_.end() != FloorTiles_.find(_Index.Index_))
	{
		FloorTiles_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);
		return;
	}

	float4 Pos = float4::ZERO;
	Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHalf_.x;
	Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHalf_.y;

	GameEngineTileMapRenderer* FloorTileRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
	GameEngineTileMapRenderer* FloorGridRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();

	// ������ Ÿ�� üũ
	switch (TileRenderingType_)
	{
		case TileRenderingType::ALL:
		{
			if (_Index.X_ == 0 && _Index.Y_ == 0)
			{
				FloorGridRenderer->SetImage("FloorGrid_Center.png");
			}
			else
			{
				FloorGridRenderer->SetImage("FloorGrid_Normal.png");
			}
			FloorGridRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
			FloorGridRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
			FloorGridRenderer->GetTransform()->SetLocalZOrder(-1.f);
			FloorGrides_.insert(std::make_pair(_Index.Index_, FloorGridRenderer));

			FloorTileRenderer->SetImage(FloorTileTextureName_);
			FloorTileRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
			FloorTileRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
			FloorTileRenderer->SetIndex(CurTileIndex_);
			FloorTiles_.insert(std::make_pair(_Index.Index_, FloorTileRenderer));
			break;
		}
		case TileRenderingType::GRID:
		{
			if (_Index.X_ == 0 && _Index.Y_ == 0)
			{
				FloorGridRenderer->SetImage("FloorGrid_Center.png");
			}
			else
			{
				FloorGridRenderer->SetImage("FloorGrid_Normal.png");
			}
			FloorGridRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
			FloorGridRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
			FloorGridRenderer->GetTransform()->SetLocalZOrder(-1.f);
			FloorGrides_.insert(std::make_pair(_Index.Index_, FloorGridRenderer));
			break;
		}
		case TileRenderingType::TILE:
		{
			FloorTileRenderer->SetImage(FloorTileTextureName_);
			FloorTileRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
			FloorTileRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
			FloorTileRenderer->SetIndex(CurTileIndex_);
			FloorTiles_.insert(std::make_pair(_Index.Index_, FloorTileRenderer));
			break;
		}
	}
}

void TileMap::SetWallTile(float4 _Pos, int CurTileIndex_)
{
	SetWallTile(GetWallTileIndex(_Pos), CurTileIndex_);
}

void TileMap::SetWallTile(TileIndex _Index, int CurTileIndex_)
{
	// ������ Ÿ���ε����� �����ϸ� �ش� Ÿ���ε����� Ÿ���̹����� ���� ���õ� �̹����� ����
	if (WallTiles_.end() != WallTiles_.find(_Index.Index_))
	{
		WallTiles_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);
		return;
	}

	float4 Pos = float4::ZERO;
	Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
	Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;


	GameEngineTileMapRenderer* WallTileRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
	GameEngineTileMapRenderer* WallGridRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();

	// ������ Ÿ�� üũ
	switch (TileRenderingType_)
	{
		case TileRenderingType::ALL:
		{
			if (_Index.X_ == 0 && _Index.Y_ == 0)
			{
				WallGridRenderer->SetImage("WallGrid_Center.png");
			}
			else
			{
				WallGridRenderer->SetImage("WallGrid_Normal.png");
			}
			WallGridRenderer->GetTransform()->SetLocalScaling(TileSizeHalf_);
			WallGridRenderer->GetTransform()->SetLocalPosition(Pos);
			WallGridRenderer->GetTransform()->SetLocalZOrder(-3.f);
			WallGrides_.insert(std::make_pair(_Index.Index_, WallGridRenderer));

			WallTileRenderer->SetImage(WallTileTextureName_);
			WallTileRenderer->GetTransform()->SetLocalScaling(WallTileImageSize_);
			WallTileRenderer->GetTransform()->SetLocalPosition(WallTileIndexPivotPos_ + Pos);
			WallTileRenderer->GetTransform()->SetLocalZOrder(-2.f);
			WallTileRenderer->SetIndex(CurTileIndex_);
			WallTiles_.insert(std::make_pair(_Index.Index_, WallTileRenderer));
			break;
		}
		case TileRenderingType::GRID:
		{
			if (_Index.X_ == 0 && _Index.Y_ == 0)
			{
				WallGridRenderer->SetImage("WallGrid_Center.png");
			}
			else
			{
				WallGridRenderer->SetImage("WallGrid_Normal.png");
			}
			WallGridRenderer->GetTransform()->SetLocalScaling(TileSizeHalf_);
			WallGridRenderer->GetTransform()->SetLocalPosition(Pos);
			WallGridRenderer->GetTransform()->SetLocalZOrder(-3.f);
			WallGrides_.insert(std::make_pair(_Index.Index_, WallGridRenderer));
			break;
		}
		case TileRenderingType::TILE:
		{
			WallTileRenderer->SetImage(WallTileTextureName_);
			WallTileRenderer->GetTransform()->SetLocalScaling(WallTileImageSize_);
			WallTileRenderer->GetTransform()->SetLocalPosition(WallTileIndexPivotPos_ + Pos);
			WallTileRenderer->GetTransform()->SetLocalZOrder(-2.f);
			WallTileRenderer->SetIndex(CurTileIndex_);
			WallTiles_.insert(std::make_pair(_Index.Index_, WallTileRenderer));
			break;
		}
	}
}

void TileMap::DelFloorTile(float4 _Pos)
{
	TileIndex Index = GetFloorTileIndex(_Pos);

	// Ÿ��
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TileFindIter = FloorTiles_.find(Index.Index_);
	if (FloorTiles_.end() != TileFindIter)
	{
		TileFindIter->second->Death();
		FloorTiles_.erase(TileFindIter);
	}

	// �׸���
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GrideFindIter = FloorGrides_.find(Index.Index_);
	if (FloorGrides_.end() != GrideFindIter)
	{
		GrideFindIter->second->Death();
		FloorGrides_.erase(GrideFindIter);
	}
}

void TileMap::DelWallTile(float4 _Pos)
{
	TileIndex Index = GetWallTileIndex(_Pos);

	// Ÿ��
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TileFindIter = WallTiles_.find(Index.Index_);
	if (WallTiles_.end() != TileFindIter)
	{
		TileFindIter->second->Death();
		WallTiles_.erase(TileFindIter);
	}

	// �׸���
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GirdFindIter = WallGrides_.find(Index.Index_);
	if (WallGrides_.end() != GirdFindIter)
	{
		GirdFindIter->second->Death();
		WallGrides_.erase(GirdFindIter);
	}
}

#pragma endregion

#pragma region �ڵ�������

// �ڵ���� ��������
void TileMap::CreateFloorTileInfo(int _WidthTileCount, int _HeightTileCount)
{
	// ���� �ٸ���忡�� �ٴ�Ÿ�������� �ٴ�Ÿ�Ϸ����������� �����Ѱ��� �����ϴ°��� �����ϱ� ���Ͽ� ���� ���� ��� Ŭ�����ϰ� ���� ����
	AllClearFloorTile();

	// ���ڷ� ������ ������ŭ �ٴ�Ÿ������ ����
	for (int y = 0; y < _HeightTileCount; ++y)
	{
		for (int x = 0; x < _WidthTileCount; ++x)
		{
			//float4 FloorTileSize;
			//int FloorIndex;
			//int FloorIndexX;
			//int FloorIndexY;
			//int FloorImageIndex;
			//std::string FloorTextureName;
			//float4 FloorRenderSize;
			//float4 FloorRenderPivotPos;
			
			// �ٴ�Ÿ�� ���� ����
			FloorTileInfo NewFloorTileInfo = {};
			NewFloorTileInfo.FloorTileSize = TileSize_;






			//TileIndex Index = {};

			//float4 Pos = float4::ZERO;
			//Pos.x = (x - y) * TileSizeHalf_.x;
			//Pos.y = (x + y) * -TileSizeHalf_.y;

			//float4 CameraPos = GetLevel()->GetMainCamera()->GetTransform()->GetWorldPosition();
			//Index = GetFloorTileIndex((Pos * GetLevel()->GetMainCamera()->GetZoomValue()) + CameraPos);

			//GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			//Renderer->SetImage("FloorGrid.png");
			//Renderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
			//Renderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
			//FloorGrides_.insert(std::make_pair(Index.Index_, Renderer));
		}
	}

	// ���� �����Ϸ� �� ���۷���������(�׸���)



}

void TileMap::CreateWallTileInfo()
{
	// ��Ÿ���� ������ �ٴ�Ÿ�� ������ ����Ͽ� �����ȴ�.
	// ��, �ڵ��������϶��� ��ŹŸ�������� �����Ǿ�߸� ��Ÿ��������������!!!!



}

// �ڵ���� Ÿ���ؽ��� ��Ī
void TileMap::UpdateFloorTileInfo(int _DefaultTileIndex)
{

}

void TileMap::UpdateWallTileInfo(int _DefaultTileIndex)
{

}

#pragma endregion

#pragma region ����/�����������������
void TileMap::AllClear()
{
	// �ٴ�Ÿ�ϰ��� Ŭ����
	AllClearFloorTile();

	// ��Ÿ�ϰ��� Ŭ����
	AllClearWallTileInfo();
	AllClearWallTileMapRenderer();
}

void TileMap::AllClearFloorTile()
{
	// Ÿ������ Ŭ����
	AllClearFloorTileInfo();

	// Ÿ�Ϸ��������� Ŭ����
	AllClearFloorTileMapRenderer();
}

void TileMap::AllClearFloorTileInfo()
{
	if (false == FloorTileInfo_.empty())
	{
		FloorTileInfo_.clear();
	}
}

void TileMap::AllClearFloorTileMapRenderer()
{
	// Ÿ��
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesStartIter = FloorTiles_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesEndIter = FloorTiles_.end();
	for (; TilesStartIter != TilesEndIter; ++TilesStartIter)
	{
		// ������ ����ó��
		(*TilesStartIter).second->Death();
	}
	FloorTiles_.clear();

	// �׸���
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsStartIter = FloorGrides_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsEndIter = FloorGrides_.end();
	for (; GridsStartIter != GridsEndIter; ++GridsStartIter)
	{
		// ������ ����ó��
		(*GridsStartIter).second->Death();
	}
	FloorGrides_.clear();
}

void TileMap::AllClearWallTile()
{
	// Ÿ������ Ŭ����
	AllClearWallTileInfo();

	// Ÿ�Ϸ��������� Ŭ����
	AllClearWallTileMapRenderer();
}

void TileMap::AllClearWallTileInfo()
{
	if (false == WallTileInfo_.empty())
	{
		WallTileInfo_.clear();
	}
}

void TileMap::AllClearWallTileMapRenderer()
{
	// Ÿ��
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesStartIter = WallTiles_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesEndIter = WallTiles_.end();
	for (; TilesStartIter != TilesEndIter; ++TilesStartIter)
	{
		// ������ ����ó��
		(*TilesStartIter).second->Death();
	}
	WallTiles_.clear();

	// �׸���
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsStartIter = WallGrides_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsEndIter = WallGrides_.end();
	for (; GridsStartIter != GridsEndIter; ++GridsStartIter)
	{
		// ������ ����ó��
		(*GridsStartIter).second->Death();
	}
	WallGrides_.clear();
}
#pragma endregion

