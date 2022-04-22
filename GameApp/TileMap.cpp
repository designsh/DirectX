#include "PreCompile.h"
#include "TileMap.h"

#include <GameEngineBase/GameEngineFile.h>

#include <GameEngine/GameEngineTileMapRenderer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

#include "GlobalEnumClass.h"

TileMap::TileMap() :
	FloorRenderingType_(FloorRenderingType::GRID),
	WallRenderingType_(WallRenderingType::GRID_NOR),
	ObjectRenderingType_(ObjectRenderingType::GRID_NORMAL),
	FloorGridesActive_(true),
	WallGridesActive_(true),
	ObjectGridesActive_(false),
	Wall_RT_T_ImageIndex_(1),
	Wall_RT_T_LE_ImageIndex_(9),
	Wall_RT_T_RE_ImageIndex_(2),
	Wall_RT_B_ImageIndex_(1),
	Wall_RT_B_LE_ImageIndex_(9),
	Wall_RT_B_RE_ImageIndex_(11),
	Wall_RB_L_ImageIndex_(4),
	Wall_RB_L_TE_ImageIndex_(26),
	Wall_RB_L_BE_ImageIndex_(3),
	Wall_RB_R_ImageIndex_(4),
	Wall_RB_R_TE_ImageIndex_(5),
	Wall_RB_R_BE_ImageIndex_(3),
	Wall_BENT_SINGLE_ImageIndex_(29),
	Wall_BENT_MULTI1_ImageIndex_(7),
	Wall_BENT_MULTI2_ImageIndex_(6)
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

	// ������ƮŸ��
	ObjectTileImageSize_ = { 160.0f, 320.f };

	ObjectTileImageSizeHalf_ = ObjectTileImageSize_.halffloat4();
	ObjectTileIndexPivotPos_ = { 0.0f, TileSize_.y };
}

void TileMap::FloorGridesSwitching()
{
	if (false == FloorGridesActive_)
	{
		FloorGridesActive_ = true;

		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = FloorGrides_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = FloorGrides_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			(*StartIter).second->On();
		}
	}
	else
	{
		FloorGridesActive_ = false;

		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = FloorGrides_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = FloorGrides_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			(*StartIter).second->Off();
		}
	}
}

void TileMap::WallGridesSwitching()
{
	if (false == WallGridesActive_)
	{
		WallGridesActive_ = true;

		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = WallGrides_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = WallGrides_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			(*StartIter).second->On();
		}
	}
	else
	{
		WallGridesActive_ = false;

		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = WallGrides_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = WallGrides_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			(*StartIter).second->Off();
		}
	}
}

void TileMap::ObjectGridesSwitching()
{
	if (false == ObjectGridesActive_)
	{
		ObjectGridesActive_ = true;

		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = ObjectGrides_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = ObjectGrides_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			(*StartIter).second->On();
		}
	}
	else
	{
		ObjectGridesActive_ = false;

		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator StartIter = ObjectGrides_.begin();
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator EndIter = ObjectGrides_.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			(*StartIter).second->Off();
		}
	}
}

#pragma region ���Ǳ�ɰ���

void TileMap::SetFloorRenderingMode(FloorRenderingType _FloorRenderingType)
{
	FloorRenderingType_ = _FloorRenderingType;
}

void TileMap::SetWallRenderingMode(WallRenderingType _WallRenderingType)
{
	WallRenderingType_ = _WallRenderingType;
}

void TileMap::SetObjectRenderingMode(ObjectRenderingType _ObjectRenderingType)
{
	ObjectRenderingType_ = _ObjectRenderingType;
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

float4 TileMap::GetObjectIsoPos(float4 _Pos)
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

TileIndex TileMap::GetObjectTileIndex(float4 _Pos)
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

#pragma region SetTile/DelTile(Floor/Wall)

void TileMap::SetFloorTile(float4 _Pos, int CurTileIndex_)
{
	SetFloorTile(GetFloorTileIndex(_Pos), CurTileIndex_);
}

void TileMap::SetFloorTile(TileIndex _Index, int CurTileIndex_)
{
	// Ÿ��Ÿ���϶��� ó��
	if (FloorRenderingType::TILE == FloorRenderingType_)
	{
		// ���� Ÿ���� ������ ���緻������ �ؽ��ĸ� �����ϰ�, 
		// �ٴ�Ÿ�������� ����
		if (FloorTiles_.end() != FloorTiles_.find(_Index.Index_))
		{
			// ������ ����
			FloorTiles_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);

			// ������ �����Ҷ� ����
			int YIndex = static_cast<int>(FloorTileInfo_.size());
			if (0 < YIndex)
			{
				int XIndex = static_cast<int>(FloorTileInfo_[YIndex - 1].size());
				for (int y = 0; y < YIndex; ++y)
				{
					for (int x = 0; x < XIndex; ++x)
					{
						if (_Index.X_ == FloorTileInfo_[y][x].FloorIndexX &&
							_Index.Y_ == FloorTileInfo_[y][x].FloorIndexY)
						{
							FloorTileInfo_[y][x].FloorImageIndex = CurTileIndex_;
							return;
						}
					}
				}
			}
			return;
		}

		float4 Pos = float4::ZERO;
		Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHalf_.x;
		Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHalf_.y;

		GameEngineTileMapRenderer* FloorTileRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
		FloorTileRenderer->SetImage(FloorTileTextureName_);
		FloorTileRenderer->GetTransform()->SetLocalScaling(FloorTileImageSize_);
		FloorTileRenderer->GetTransform()->SetLocalPosition(FloorTileIndexPivotPos_ + Pos);
		FloorTileRenderer->SetIndex(CurTileIndex_);
		FloorTiles_.insert(std::make_pair(_Index.Index_, FloorTileRenderer));

		// ������ �����������Ƿ� ���� ������ ����
		int YIndex = static_cast<int>(FloorTileInfo_.size());
		if (0 < YIndex)
		{
			int XIndex = static_cast<int>(FloorTileInfo_[YIndex - 1].size());
			for (int y = 0; y < YIndex; ++y)
			{
				for (int x = 0; x < XIndex; ++x)
				{
					if (_Index.X_ == FloorTileInfo_[y][x].FloorIndexX &&
						_Index.Y_ == FloorTileInfo_[y][x].FloorIndexY)
					{
						FloorTileInfo_[y][x].FloorImageIndex = CurTileIndex_;
						return;
					}
				}
			}
		}
	}
}

void TileMap::SetWallTile(float4 _Pos, int CurTileIndex_)
{
	SetWallTile(GetWallTileIndex(_Pos), CurTileIndex_);
}

void TileMap::SetWallTile(TileIndex _Index, int CurTileIndex_)
{
	// Ÿ��Ÿ���϶��� ó��
	if (WallRenderingType::TILE1 == WallRenderingType_ || WallRenderingType::TILE2 == WallRenderingType_)
	{
		if (WallTiles_.end() != WallTiles_.find(_Index.Index_))
		{
			// ���� ������ �ؽ��� �ε��� ��ü
			if (WallRenderingType::TILE1 == WallRenderingType_)
			{
				WallTiles_.find(_Index.Index_)->second.Tiles1_->SetIndex(CurTileIndex_);
			}
			else if (WallRenderingType::TILE2 == WallRenderingType_)
			{
				// BENT_MULTI TYPE�϶��� TILES2�� �����Ѵ�.
				if (nullptr != WallTiles_.find(_Index.Index_)->second.Tiles2_)
				{
					WallTiles_.find(_Index.Index_)->second.Tiles2_->SetIndex(CurTileIndex_);
				}
			}

			// ������ �����Ҷ� ����
			int YIndex = static_cast<int>(WallTileInfo_.size());
			if (0 < YIndex)
			{
				int XIndex = static_cast<int>(WallTileInfo_[YIndex - 1].size());
				for (int y = 0; y < YIndex; ++y)
				{
					for (int x = 0; x < XIndex; ++x)
					{
						if (_Index.X_ == WallTileInfo_[y][x].WallIndexX &&
							_Index.Y_ == WallTileInfo_[y][x].WallIndexY)
						{
							if (WallRenderingType::TILE1 == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallTile1ImageIndex = CurTileIndex_;
							}
							else if (WallRenderingType::TILE2 == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallTile2ImageIndex = CurTileIndex_;
							}
							return;
						}
					}
				}
			}
			return;
		}

		// 
		float4 Pos = float4::ZERO;
		Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
		Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

		WallTileRender NewRenderer = {};

		NewRenderer.Tiles1_ = CreateTransformComponent<GameEngineTileMapRenderer>();
		NewRenderer.Tiles2_ = nullptr;

		NewRenderer.Tiles1_->SetImage(WallTileTextureName_);
		NewRenderer.Tiles1_->GetTransform()->SetLocalScaling(WallTileImageSize_);
		NewRenderer.Tiles1_->GetTransform()->SetLocalPosition(WallTileIndexPivotPos_ + Pos);
		NewRenderer.Tiles1_->GetTransform()->SetLocalZOrder(-2.f);
		NewRenderer.Tiles1_->SetIndex(CurTileIndex_);

		WallTiles_.insert(std::make_pair(_Index.Index_, NewRenderer));

		// ������ �����������Ƿ� ���� ������ ����
		int YIndex = static_cast<int>(WallTileInfo_.size());
		if (0 < YIndex)
		{
			int XIndex = static_cast<int>(WallTileInfo_[YIndex - 1].size());
			for (int y = 0; y < YIndex; ++y)
			{
				for (int x = 0; x < XIndex; ++x)
				{
					if (_Index.X_ == WallTileInfo_[y][x].WallIndexX &&
						_Index.Y_ == WallTileInfo_[y][x].WallIndexY)
					{
						if (WallRenderingType::TILE1 == WallRenderingType_)
						{
							WallTileInfo_[y][x].WallTile1ImageIndex = CurTileIndex_;
						}
						else if (WallRenderingType::TILE2 == WallRenderingType_)
						{
							WallTileInfo_[y][x].WallTile2ImageIndex = CurTileIndex_;
						}
						return;
					}
				}
			}
		}
	}
}

void TileMap::SetObjectTile(float4 _Pos, int CurTileIndex_)
{
	SetObjectTile(GetObjectTileIndex(_Pos), CurTileIndex_);
}

void TileMap::SetObjectTile(TileIndex _Index, int CurTileIndex_)
{
	if (ObjectRenderingType::TILE == ObjectRenderingType_)
	{
		if (ObjectTiles_.end() != ObjectTiles_.find(_Index.Index_))
		{
			// ������ ����
			ObjectTiles_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);

			// ������ �����Ҷ� ����
			int YIndex = static_cast<int>(ObjectTileInfo_.size());
			if (0 < YIndex)
			{
				int XIndex = static_cast<int>(ObjectTileInfo_[YIndex - 1].size());
				for (int y = 0; y < YIndex; ++y)
				{
					for (int x = 0; x < XIndex; ++x)
					{
						if (_Index.X_ == ObjectTileInfo_[y][x].ObjectIndexX &&
							_Index.Y_ == ObjectTileInfo_[y][x].ObjectIndexY)
						{
							ObjectTileInfo_[y][x].ObjectImageIndex = CurTileIndex_;
							return;
						}
					}
				}
			}
			return;
		}

		float4 Pos = float4::ZERO;
		Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
		Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

		GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

		Renderer->SetImage(ObjectTileTextureName_);
		Renderer->GetTransform()->SetLocalScaling(ObjectTileImageSize_);
		Renderer->GetTransform()->SetLocalPosition(ObjectTileIndexPivotPos_ + Pos);
		Renderer->GetTransform()->SetLocalZOrder(-4.f);
		Renderer->SetIndex(CurTileIndex_);
		ObjectTiles_.insert(std::make_pair(_Index.Index_, Renderer));

		// 
		int YIndex = static_cast<int>(ObjectTileInfo_.size());
		if (0 < YIndex)
		{
			int XIndex = static_cast<int>(ObjectTileInfo_[YIndex - 1].size());
			for (int y = 0; y < YIndex; ++y)
			{
				for (int x = 0; x < XIndex; ++x)
				{
					if (_Index.X_ == ObjectTileInfo_[y][x].ObjectIndexX &&
						_Index.Y_ == ObjectTileInfo_[y][x].ObjectIndexY)
					{
						ObjectTileInfo_[y][x].ObjectImageIndex = CurTileIndex_;
						return;
					}
				}
			}
		}
	}
}

void TileMap::DelFloorTile(float4 _Pos)
{
	// Ÿ�ϸ���϶� ó��
	if (FloorRenderingType::TILE == FloorRenderingType_)
	{
		TileIndex Index = GetFloorTileIndex(_Pos);

		// Ÿ��
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TileFindIter = FloorTiles_.find(Index.Index_);
		if (FloorTiles_.end() != TileFindIter)
		{
			TileFindIter->second->Death();
			FloorTiles_.erase(TileFindIter);
		}
	}
}

void TileMap::DelWallTile(float4 _Pos)
{
	// Ÿ�ϸ���϶� ó��
	if (WallRenderingType::TILE1 == WallRenderingType_ || WallRenderingType::TILE2 == WallRenderingType_)
	{
		TileIndex Index = GetWallTileIndex(_Pos);

		// Ÿ��
		std::unordered_map<__int64, WallTileRender>::iterator TileFindIter = WallTiles_.find(Index.Index_);
		if (WallTiles_.end() != TileFindIter)
		{
			TileFindIter->second.Tiles1_->Death();
			if (nullptr != TileFindIter->second.Tiles2_)
			{
				TileFindIter->second.Tiles2_->Death();
			}

			WallTiles_.erase(TileFindIter);
		}
	}
}

void TileMap::DelObjectTile(float4 _Pos)
{
	// Ÿ�ϸ���϶� ó��
	if (ObjectRenderingType::TILE == ObjectRenderingType_)
	{
		TileIndex Index = GetObjectTileIndex(_Pos);

		// Ÿ��
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TileFindIter = ObjectTiles_.find(Index.Index_);
		if (ObjectTiles_.end() != TileFindIter)
		{
			TileFindIter->second->Death();
			ObjectTiles_.erase(TileFindIter);
		}
	}
}

#pragma endregion

#pragma region SetGrid/DelGrid(Floor/Wall)

void TileMap::SetFloorGird(float4 _Pos, int CurTileIndex_)
{
	SetFloorGird(GetFloorTileIndex(_Pos), CurTileIndex_);
}

void TileMap::SetFloorGird(TileIndex _Index, int CurTileIndex_)
{
	// Ÿ�ϸ�尡 �ƴҶ� ó��
	if (FloorRenderingType::TILE != FloorRenderingType_)
	{
		// ���� �ε����� �����ϸ� ����
		if (FloorGrides_.end() != FloorGrides_.find(_Index.Index_))
		{
			// �׸��� Ÿ���� �Ѱ��̹Ƿ� �ٷ� ����
			return;
		}

		float4 Pos = float4::ZERO;
		Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHalf_.x;
		Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHalf_.y;

		GameEngineTileMapRenderer* FloorGridRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
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
	}
}

void TileMap::SetWallGird(float4 _Pos, int CurTileIndex_)
{
	SetWallGird(GetWallTileIndex(_Pos), CurTileIndex_);
}

void TileMap::SetWallGird(TileIndex _Index, int CurTileIndex_)
{
	// Ÿ�ϸ�尡 �ƴҶ� ó��
	if (WallRenderingType::TILE1 != WallRenderingType_ && WallRenderingType::TILE2 != WallRenderingType_)
	{
		if (WallGrides_.end() != WallGrides_.find(_Index.Index_))
		{
			// ���� �׸��巻���� �̹��� ����
			float4 ChangePos = float4::ZERO;
			ChangePos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
			ChangePos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

			// ����Ÿ�Ժ� �̹��� ����
			if (WallRenderingType::GRID_NOR == WallRenderingType_)
			{
				// ���� �ٴ�Ÿ�� �̹���
				if (_Index.Y_ == 0 && _Index.X_ == 0)
				{
					WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_Center.png");
				}
				else // �Ϲ� �ٴ�Ÿ�� �̹���
				{
					WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_Normal.png");
				}
			}
			// RT_T
			else if (WallRenderingType::GRID_RT_T == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RT_T.png");
			}
			else if (WallRenderingType::GRID_RT_T_RE == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RT_T_RE.png");
			}
			else if (WallRenderingType::GRID_RT_T_LE == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RT_T_LE.png");
			}
			// RT_B
			else if (WallRenderingType::GRID_RT_B == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RT_B.png");
			}
			else if (WallRenderingType::GRID_RT_B_RE == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RT_B_RE.png");
			}
			else if (WallRenderingType::GRID_RT_B_LE == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RT_B_LE.png");
			}
			// RB_L
			else if (WallRenderingType::GRID_RB_L == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RB_L.png");
			}
			else if (WallRenderingType::GRID_RB_L_BE == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RB_L_BE.png");
			}
			else if (WallRenderingType::GRID_RB_L_TE == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RB_L_TE.png");
			}
			// RB_R
			else if (WallRenderingType::GRID_RB_R == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RB_R.png");
			}
			else if (WallRenderingType::GRID_RB_R_BE == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RB_R_BE.png");
			}
			else if (WallRenderingType::GRID_RB_R_TE == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_RB_R_TE.png");
			}
			// BENT_SINGLE
			else if (WallRenderingType::GRID_BENT_SINGLE == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_Bent_Single.png");
			}
			// BENT_MULTI1
			else if (WallRenderingType::GRID_BENT_MULTI1 == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_Bent_Multi.png");
			}
			// BENT_MULTI2
			else if (WallRenderingType::GRID_BENT_MULTI2 == WallRenderingType_)
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_Bent_Multi.png");
			}
			else
			{
				WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_None.png");
			}

			WallGrides_.find(_Index.Index_)->second->GetTransform()->SetLocalScaling(TileSizeHalf_);
			WallGrides_.find(_Index.Index_)->second->GetTransform()->SetLocalPosition(ChangePos);
			WallGrides_.find(_Index.Index_)->second->GetTransform()->SetLocalZOrder(-3.f);

			// ��������
			int YIndex = static_cast<int>(WallTileInfo_.size());
			if (0 < YIndex)
			{
				int XIndex = static_cast<int>(WallTileInfo_[YIndex - 1].size());
				for (int y = 0; y < YIndex; ++y)
				{
					for (int x = 0; x < XIndex; ++x)
					{
						if (_Index.X_ == WallTileInfo_[y][x].WallIndexX &&
							_Index.Y_ == WallTileInfo_[y][x].WallIndexY)
						{
							if (WallRenderingType::GRID_BENT_MULTI1 == WallRenderingType_ || WallRenderingType::GRID_BENT_MULTI2 == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::BENT_MULTI;
							}
							else if (WallRenderingType::GRID_BENT_SINGLE == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::BENT_SINGLE;
							}
							else if(WallRenderingType::GRID_NONE == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::NONE;
							}
							else if (WallRenderingType::GRID_NOR == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::NORMAL;
							}
							// RT_T
							else if (WallRenderingType::GRID_RT_T == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RT_T;
							}
							else if (WallRenderingType::GRID_RT_T_LE == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RT_T_LE;
							}
							else if (WallRenderingType::GRID_RT_T_RE == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RT_T_RE;
							}
							// RT_B
							else if (WallRenderingType::GRID_RT_B == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RT_B;
							}
							else if (WallRenderingType::GRID_RT_B_LE == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RT_B_LE;
							}
							else if (WallRenderingType::GRID_RT_B_RE == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RT_B_RE;
							}
							// RB_L
							else if (WallRenderingType::GRID_RB_L == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RB_L;
							}
							else if (WallRenderingType::GRID_RB_L_TE == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RB_L_TE;
							}
							else if (WallRenderingType::GRID_RB_L_BE == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RB_L_BE;
							}
							// RB_R
							else if (WallRenderingType::GRID_RB_R == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RB_R;
							}
							else if (WallRenderingType::GRID_RB_R_TE == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RB_R_TE;
							}
							else if (WallRenderingType::GRID_RB_R_BE == WallRenderingType_)
							{
								WallTileInfo_[y][x].WallBasicType = WallBasicType::RB_R_BE;
							}
							return;
						}
					}
				}
			}
			return;
		}

		float4 Pos = float4::ZERO;
		Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
		Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

		GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

		// ����Ÿ�Ժ� �̹��� ����
		if (WallRenderingType::GRID_NOR == WallRenderingType_)
		{
			// ���� �ٴ�Ÿ�� �̹���
			if (_Index.Y_ == 0 && _Index.X_ == 0)
			{
				Renderer->SetImage("WallGrid_Center.png");
			}
			else // �Ϲ� �ٴ�Ÿ�� �̹���
			{
				Renderer->SetImage("WallGrid_Normal.png");
			}
		}
		// RT_T
		else if (WallRenderingType::GRID_RT_T == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RT_T.png");
		}
		else if (WallRenderingType::GRID_RT_T_RE == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RT_T_RE.png");
		}
		else if (WallRenderingType::GRID_RT_T_LE == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RT_T_LE.png");
		}
		// RT_B
		else if (WallRenderingType::GRID_RT_B == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RT_B.png");
		}
		else if (WallRenderingType::GRID_RT_B_RE == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RT_B_RE.png");
		}
		else if (WallRenderingType::GRID_RT_B_LE == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RT_B_LE.png");
		}
		// RB_L
		else if (WallRenderingType::GRID_RB_L == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RB_L.png");
		}
		else if (WallRenderingType::GRID_RB_L_BE == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RB_L_BE.png");
		}
		else if (WallRenderingType::GRID_RB_L_TE == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RB_L_TE.png");
		}
		// RB_R
		else if (WallRenderingType::GRID_RB_R == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RB_R.png");
		}
		else if (WallRenderingType::GRID_RB_R_BE == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RB_R_BE.png");
		}
		else if (WallRenderingType::GRID_RB_R_TE == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_RB_R_TE.png");
		}
		// BENT_SINGLE
		else if (WallRenderingType::GRID_BENT_SINGLE == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_Bent_Single.png");
		}
		// BENT_MULTI1
		else if (WallRenderingType::GRID_BENT_MULTI1 == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_Bent_Multi.png");
		}
		// BENT_MULTI2
		else if (WallRenderingType::GRID_BENT_MULTI2 == WallRenderingType_)
		{
			Renderer->SetImage("WallGrid_Bent_Multi.png");
		}
		else
		{
			Renderer->SetImage("WallGrid_None.png");
		}

		Renderer->GetTransform()->SetLocalScaling(TileSizeHalf_);
		Renderer->GetTransform()->SetLocalPosition(Pos);
		Renderer->GetTransform()->SetLocalZOrder(-3.f);
		WallGrides_.insert(std::make_pair(_Index.Index_, Renderer));
	}
}

void TileMap::SetObjectGird(float4 _Pos, int CurTileIndex_)
{
	SetObjectGird(GetObjectTileIndex(_Pos), CurTileIndex_);
}

void TileMap::SetObjectGird(TileIndex _Index, int CurTileIndex_)
{
	// Ÿ�ϸ�尡 �ƴҶ� ó��
	if (ObjectRenderingType::TILE != ObjectRenderingType_)
	{
		if (ObjectGrides_.end() != ObjectGrides_.find(_Index.Index_))
		{
			// �׸��� Ÿ�Ժ�ȯ
			if (ObjectRenderingType::GRID_NORMAL == ObjectRenderingType_)
			{
				// ���� �ٴ�Ÿ�� �̹���
				if (_Index.Y_ == 0 && _Index.X_ == 0)
				{
					ObjectGrides_.find(_Index.Index_)->second->SetImage("WallGrid_Center.png");
				}
				else // �Ϲ� �ٴ�Ÿ�� �̹���
				{
					ObjectGrides_.find(_Index.Index_)->second->SetImage("WallGrid_Normal.png");
				}
			}
			else if (ObjectRenderingType::GRID_OBJECT == ObjectRenderingType_)
			{
				ObjectGrides_.find(_Index.Index_)->second->SetImage("ObjectGrid_Object.png");
			}
			else
			{
				ObjectGrides_.find(_Index.Index_)->second->SetImage("WallGrid_None.png");
			}

			float4 ChangePos = float4::ZERO;
			ChangePos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
			ChangePos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

			ObjectGrides_.find(_Index.Index_)->second->GetTransform()->SetLocalScaling(TileSizeHalf_);
			ObjectGrides_.find(_Index.Index_)->second->GetTransform()->SetLocalPosition(ChangePos);
			ObjectGrides_.find(_Index.Index_)->second->GetTransform()->SetLocalZOrder(-4.f);

			// ��������
			int YIndex = static_cast<int>(ObjectTileInfo_.size());
			if (0 < YIndex)
			{
				int XIndex = static_cast<int>(ObjectTileInfo_[YIndex - 1].size());
				for (int y = 0; y < YIndex; ++y)
				{
					for (int x = 0; x < XIndex; ++x)
					{
						if (_Index.X_ == ObjectTileInfo_[y][x].ObjectIndexX &&
							_Index.Y_ == ObjectTileInfo_[y][x].ObjectIndexY)
						{
							if (ObjectRenderingType::GRID_NORMAL == ObjectRenderingType_)
							{
								ObjectTileInfo_[y][x].ObjectBasicType = ObjectBasicType::NORMAL;
							}
							else if (ObjectRenderingType::GRID_OBJECT == ObjectRenderingType_)
							{
								ObjectTileInfo_[y][x].ObjectBasicType = ObjectBasicType::OBJECT;
							}
							else
							{
								ObjectTileInfo_[y][x].ObjectBasicType = ObjectBasicType::WALL;
							}
							return;
						}
					}
				}
				return;
			}

			float4 Pos = float4::ZERO;
			Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
			Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			// ����Ÿ�Ժ� �̹��� ����
			if (ObjectRenderingType::GRID_NORMAL == ObjectRenderingType_)
			{
				// ���� �ٴ�Ÿ�� �̹���
				if (_Index.Y_ == 0 && _Index.X_ == 0)
				{
					Renderer->SetImage("WallGrid_Center.png");
				}
				else // �Ϲ� �ٴ�Ÿ�� �̹���
				{
					Renderer->SetImage("WallGrid_Normal.png");
				}
			}
			// OBJECT
			else if (ObjectRenderingType::GRID_OBJECT == ObjectRenderingType_)
			{
				Renderer->SetImage("ObjectGrid_Object.png");
			}
			// WALL
			else
			{
				Renderer->SetImage("WallGrid_None.png");
			}

			Renderer->GetTransform()->SetLocalScaling(TileSizeHalf_);
			Renderer->GetTransform()->SetLocalPosition(Pos);
			Renderer->GetTransform()->SetLocalZOrder(-4.f);
			ObjectGrides_.insert(std::make_pair(_Index.Index_, Renderer));
		}
	}
}

void TileMap::DelFloorGird(float4 _Pos)
{
	// Ÿ�ϸ�尡 �ƴҶ� ó��
	if (FloorRenderingType::TILE != FloorRenderingType_)
	{
		TileIndex Index = GetFloorTileIndex(_Pos);

		// Ÿ��
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridFindIter = FloorGrides_.find(Index.Index_);
		if (FloorGrides_.end() != GridFindIter)
		{
			GridFindIter->second->Death();
			FloorGrides_.erase(GridFindIter);
		}
	}
}

void TileMap::DelWallGird(float4 _Pos)
{
	// Ÿ�ϸ�尡 �ƴҶ� ó��
	if (WallRenderingType::TILE1 != WallRenderingType_ && WallRenderingType::TILE2 != WallRenderingType_)
	{
		TileIndex Index = GetWallTileIndex(_Pos);

		// Ÿ��
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridFindIter = WallGrides_.find(Index.Index_);
		if (WallGrides_.end() != GridFindIter)
		{
			GridFindIter->second->Death();
			WallGrides_.erase(GridFindIter);
		}
	}
}

void TileMap::DelObjectGird(float4 _Pos)
{
	// Ÿ�ϸ�尡 �ƴҶ� ó��
	if (ObjectRenderingType::TILE != ObjectRenderingType_)
	{
		TileIndex Index = GetObjectTileIndex(_Pos);

		// Ÿ��
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridFindIter = ObjectGrides_.find(Index.Index_);
		if (ObjectGrides_.end() != GridFindIter)
		{
			GridFindIter->second->Death();
			ObjectGrides_.erase(GridFindIter);
		}
	}
}

#pragma endregion

#pragma region �ڵ�������

// �ڵ���� ��������
void TileMap::CreateFloorTileInfo(int _HeightTileCount, int _WidthTileCount, int _ImageIndex)
{
	// ���� �ٸ���忡�� �ٴ�Ÿ�������� �ٴ�Ÿ�Ϸ����������� �����Ѱ��� �����ϴ°��� �����ϱ� ���Ͽ� ���� ���� ��� Ŭ�����ϰ� ���� ����
	AllClearFloorTile();

	// ���ڷ� ������ ������ŭ �ٴ�Ÿ������ ����
	FloorTileInfo_.resize(_WidthTileCount);

	// �����ε���, �����ε��� ���
	int YStartIndex = 0;
	int YEndIndex = 0;
	int XStartIndex = 0;
	int XEndIndex = 0;
	if (_WidthTileCount % 2 == 0) // _HeightTileCount / 2 �� ¦���̸� End
	{
		// �����ε���, �����ε��� ���
		YStartIndex = -(_WidthTileCount / 2);
		YEndIndex = _WidthTileCount / 2;
	}
	else // _HeightTileCount / 2 �� Ȧ���̸� End + 1
	{
		// �����ε���, �����ε��� ���
		YStartIndex = -(_WidthTileCount / 2);
		YEndIndex = (_WidthTileCount / 2) + 1;
	}

	if (_HeightTileCount % 2 == 0)
	{
		XStartIndex = -(_HeightTileCount / 2);
		XEndIndex = _HeightTileCount / 2;
	}
	else
	{
		XStartIndex = -(_HeightTileCount / 2);
		XEndIndex = (_HeightTileCount / 2) + 1;
	}

	int YIndex = 0;
	for (int y = YStartIndex; y < YEndIndex; ++y)
	{
		for (int x = XStartIndex; x < XEndIndex; ++x)
		{
			TileIndex Index = {};

			// �ٴ�Ÿ�� ���� ����
			FloorTileInfo NewFloorTileInfo = {};
			NewFloorTileInfo.FloorIndexX = y;
			NewFloorTileInfo.FloorIndexY = x;
			NewFloorTileInfo.FloorImageIndex = _ImageIndex;	// �ʱ� ���õ� �ؽ��ķ� ��� ����
			NewFloorTileInfo.FloorTextureName = FloorTileTextureName_;
			NewFloorTileInfo.FloorTileSize = TileSize_;
			NewFloorTileInfo.FloorRenderSize = FloorTileImageSize_;
			NewFloorTileInfo.FloorRenderPivotPos = FloorTileIndexPivotPos_;

			FloorTileInfo_[YIndex].push_back(NewFloorTileInfo);
		}

		++YIndex;
	}

	// ���� �����Ϸ� �� ���۷���������(�׸���)
	int YInfoCnt = static_cast<int>(FloorTileInfo_.size());
	int XInfoCnt = static_cast<int>(FloorTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(FloorTileInfo_[y][x].FloorIndexX, FloorTileInfo_[y][x].FloorIndexY);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			// ���� �ٴ�Ÿ�� �̹���
			if (Index.Y_ == 0 && Index.X_ == 0)
			{
				Renderer->SetImage("FloorGrid_Center.png");
			}
			else // �Ϲ� �ٴ�Ÿ�� �̹���
			{
				Renderer->SetImage("FloorGrid_Normal.png");
			}

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * FloorTileInfo_[y][x].FloorTileSize.halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -FloorTileInfo_[y][x].FloorTileSize.halffloat4().y;

			Renderer->GetTransform()->SetLocalScaling(FloorTileInfo_[y][x].FloorRenderSize);
			Renderer->GetTransform()->SetLocalPosition(FloorTileInfo_[y][x].FloorRenderPivotPos + Pos);
			FloorGrides_.insert(std::make_pair(Index.Index_, Renderer));
		}
	}
}

void TileMap::CreateWallTileInfo()
{
	// ���� �ٸ���忡�� �ٴ�Ÿ�������� �ٴ�Ÿ�Ϸ����������� �����Ѱ��� �����ϴ°��� �����ϱ� ���Ͽ� ���� ���� ��� Ŭ�����ϰ� ���� ����
	AllClearWallTile();

	// ��Ÿ���� ������ �ٴ�Ÿ�� ������ ����Ͽ� �����ȴ�.
	// ��, �ڵ��������϶��� ��ŹŸ�������� �����Ǿ�߸� ��Ÿ��������������!!!!
	if (false == FloorTileInfo_.empty())
	{
		// �ٴ�Ÿ�� �Ѱ����� ��Ÿ���� 3x3 �� 9���� �����ȴ�.
		int HeightFloorTileCnt = static_cast<int>(FloorTileInfo_.size());
		int WidthFloorTileCnt = static_cast<int>(FloorTileInfo_[HeightFloorTileCnt - 1].size());

		// ��Ÿ�ϻ��� ���� : �ٴ�Ÿ�ϰ��� * 2 + 1
		int YIndexCnt = (WidthFloorTileCnt * 2) + 1;
		int XIndexCnt = (HeightFloorTileCnt * 2) + 1;

		int YStartIndex = 0;
		int YEndIndex = 0;
		int XStartIndex = 0;
		int XEndIndex = 0;

		// �ٴ�Ÿ���� ¦������ Ȧ������ üũ
		if (HeightFloorTileCnt % 2 == 0)
		{
			XStartIndex = -HeightFloorTileCnt;
			XEndIndex = HeightFloorTileCnt + 1;
		}
		else
		{
			XStartIndex = -HeightFloorTileCnt + 1;
			XEndIndex = HeightFloorTileCnt + 2;
		}

		if (WidthFloorTileCnt % 2 == 0)
		{
			YStartIndex = -WidthFloorTileCnt;
			YEndIndex = WidthFloorTileCnt + 1;
		}
		else
		{
			YStartIndex = -WidthFloorTileCnt + 1;
			YEndIndex = WidthFloorTileCnt + 2;
		}

		// ��Ÿ���� ���� üũ �ε��� ����
		int YIndexChkM = 0;
		int YIndexChkP = 0;
		int XIndexChkM = 0;
		int XIndexChkP = 0;

		// -. �ٴ�Ÿ�� �������� ���� ����
		if (HeightFloorTileCnt % 2 == 0)
		{
			XIndexChkM = XStartIndex;
			XIndexChkP = -XStartIndex;
		}
		else
		{
			XIndexChkM = XStartIndex;
			XIndexChkP = XEndIndex - 1;
		}

		if (WidthFloorTileCnt % 2 == 0)
		{
			YIndexChkM = YStartIndex;
			YIndexChkP = -YStartIndex;
		}
		else
		{
			YIndexChkM = YStartIndex;
			YIndexChkP = YEndIndex - 1;
		}

		// ��Ÿ�� ����üũ�� ���� ���� ����
		WallTileInfo_.resize(YIndexCnt);

		int YIndex = 0;
		for (int y = YStartIndex; y < YEndIndex; ++y)
		{
			for (int x = XStartIndex; x < XEndIndex; ++x)
			{
				TileIndex Index = {};

				// ����üũ�� ���� �⺻Ÿ��, ��Ÿ���� �����Ѵ�.
				WallTileInfo NewWallTileInfo = {};

				NewWallTileInfo.WallIndexX = x;
				NewWallTileInfo.WallIndexY = y;
				NewWallTileInfo.WallTile1ImageIndex = 0; // �ʱ� 0���� ����(���� �̹������Ž����� �� ��Ÿ����üũ�Ͽ� �̹���Ÿ�� ����)
				NewWallTileInfo.WallTile2ImageIndex = 0; // �ʱ� 0���� ����(���� �̹������Ž����� �� ��Ÿ����üũ�Ͽ� �̹���Ÿ�� ����)

				// �� �⺻Ÿ�� ����üũ(Ÿ���� �ε����� ����üũ) - ������ ��������

				// 1. ������ �������ؾ��ϴ� �������� �ƴ��� �Ǵ�
				// 2. ������ �������ؾ��Ѵٸ� ����(���ϴ�)�������� ���ϴ�(�»��)������ ������ �Ǵ�
				//    1) �߽�(0,0)���� ���ʺ����� �Ʒ��ʺ����� �Ǵ�(����(���ϴ�)����)
				//       [1] ���ܹ������� ���� ������ �Ǵ�
				//       [2] ���ϴܹ������� ���� ������ �Ǵ�
				//    2) �߽�(0,0)���� ���ʺ����� �����ʺ����� �Ǵ�(���ϴ�(�»��)����)
				//       [1] ���ϴܹ������� ���� ������ �Ǵ�
				//       [2] �»�ܹ������� ���� ������ �Ǵ�
				// 3. ������ �������ؾ��ϰ�, ���̴º��� �������ؾ��ϴ��� �Ǵ�
				//    1) �߽�(0,0)���� ���� ���̴� ������ �Ǵ�(RT_T_RE�� RB_R_TE�� �������� �Ǵ�)
				//    2) �߽�(0,0)���� ���ϴ� ���̴� ������ �Ǵ�(RT_B_LE�� RB_L_BE�� �������� �Ǵ�)

				// (1) ��Ʈ���� Ÿ��üũ
				//     1) ����(RT_T_RE�� RB_R_TE�� ������ ��������)
				if (x == XIndexChkM && y == YIndexChkM)
				{
					NewWallTileInfo.WallBasicType = WallBasicType::BENT_MULTI;
				}
				//     2) ���ϴ�(RT_B_LE�� RB_L_BE�� ������ ��������
				else if (x == XIndexChkP && y == YIndexChkP)
				{
					NewWallTileInfo.WallBasicType = WallBasicType::BENT_SINGLE;
				}
				// (2) ���Ӻ� �� ���� üũ
				else
				{
					// 1) RT_T���� Ÿ��üũ
					if (x == XIndexChkM)
					{
						if (y % 2 == 0 && x % 2 == 0)
						{
							// [1] ���ʳ������� üũ
							if (x == XIndexChkM && y == YIndexChkP - 2)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_T_LE;
							}
							// [2] RT_T�� ������, RB_L�� ���ʳ����� �Ǵ°��
							else if (x == XIndexChkM && y == YIndexChkP)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_L_TE;
							}
							// [3] �����ʳ������� üũ
							else if (x == XIndexChkM && y == YIndexChkM + 2)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_T_RE;
							}
							// [4] ���Ӻ����� üũ
							else
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_T;
							}
						}
						// [5] ���̶���Ǵ������� �����������ʴ±������� üũ
						else
						{
							NewWallTileInfo.WallBasicType = WallBasicType::NONE;
						}
					}
					// 2) RT_B���� Ÿ��üũ
					else if (x == XIndexChkP)
					{
						if (y % 2 == 0 && x % 2 == 0)
						{
							// [1] ���ʳ������� üũ
							if (x == XIndexChkP && y == YIndexChkP - 2)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_B_LE;
							}
							// [2] �����ʳ������� üũ
							else if (x == XIndexChkP && y == YIndexChkM)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_B_RE;
							}
							// [3] ���Ӻ����� üũ
							else
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_B;
							}
						}
						// [4] ���̶���Ǵ������� �����������ʴ±������� üũ
						else
						{
							NewWallTileInfo.WallBasicType = WallBasicType::NONE;
						}
					}
					// 3) RB_L���� Ÿ��üũ
					else if (y == YIndexChkP)
					{
						if (y % 2 == 0 && x % 2 == 0)
						{
							// [1] �Ʒ��ʳ������� üũ
							if (x == XIndexChkP - 2 && y == YIndexChkP)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_L_BE;
							}
							// [2] ���Ӻ����� üũ
							else
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_L;
							}
						}
						// [3] ���̶���Ǵ������� �����������ʴ±������� üũ
						else
						{
							NewWallTileInfo.WallBasicType = WallBasicType::NONE;
						}
					}
					// 4) RB_R���� Ÿ��üũ
					else if (y == YIndexChkM)
					{
						if (y % 2 == 0 && x % 2 == 0)
						{
							// [1] ���ʳ������� üũ
							if (x == XIndexChkM + 2 && y == YIndexChkM)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_R_TE;
							}
							// [2] �Ʒ��ʳ������� üũ
							else if (x == XIndexChkP - 2 && y == YIndexChkM)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_R_BE;
							}
							// [3] ���Ӻ����� üũ
							else
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_R;
							}
						}
						// [4] ���̶���Ǵ������� �����������ʴ±������� üũ
						else
						{
							NewWallTileInfo.WallBasicType = WallBasicType::NONE;
						}
					}
					// 5) �� ���ǿ� ��� �����ʴٸ� �Ϲ�Ÿ�Ϸ� ���̶� �Ǵ������ʴº�
					else
					{
						NewWallTileInfo.WallBasicType = WallBasicType::NORMAL;
					}
				}

				// �� ��Ÿ�� ����üũ(Ÿ���� �ε����� ����üũ) - ������ ��������
				//NORMAL,		// �Ϲݺ�
				//DOOR,			// ��
				NewWallTileInfo.WallDetailType = WallDetailType::NORMAL;

				// �⺻ ������ ���� ����
				NewWallTileInfo.WallTextureName = WallTileTextureName_;
				NewWallTileInfo.WallTileSize = TileSize_;
				NewWallTileInfo.WallRenderSize = WallTileImageSize_;
				NewWallTileInfo.WallRenderPivotPos = WallTileIndexPivotPos_;

				WallTileInfo_[YIndex].push_back(NewWallTileInfo);
			}

			++YIndex;
		}

		// ���� �����Ϸ� �� ���۷���������(�׸���)
		int YInfoCnt = static_cast<int>(WallTileInfo_.size());
		int XInfoCnt = static_cast<int>(WallTileInfo_[YInfoCnt - 1].size());
		for (int y = 0; y < YInfoCnt; ++y)
		{
			for (int x = 0; x < XInfoCnt; ++x)
			{
				TileIndex Index = TileIndex(WallTileInfo_[y][x].WallIndexX, WallTileInfo_[y][x].WallIndexY);

				GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

				// ��Ÿ�Ժ� �̹���
				if (WallTileInfo_[y][x].WallBasicType == WallBasicType::NORMAL)
				{
					// ���� �ٴ�Ÿ�� �̹���
					if (Index.Y_ == 0 && Index.X_ == 0)
					{
						Renderer->SetImage("WallGrid_Center.png");
					}
					else // �Ϲ� �ٴ�Ÿ�� �̹���
					{
						Renderer->SetImage("WallGrid_Normal.png");
					}
				}
				// RT_T
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T)
				{
					Renderer->SetImage("WallGrid_RT_T.png");
				}
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T_RE)
				{
					Renderer->SetImage("WallGrid_RT_T_RE.png");
				}
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T_LE)
				{
					Renderer->SetImage("WallGrid_RT_T_LE.png");
				}
				// RT_B
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B)
				{
					Renderer->SetImage("WallGrid_RT_B.png");
				}
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B_RE)
				{
					Renderer->SetImage("WallGrid_RT_B_RE.png");
				}
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B_LE)
				{
					Renderer->SetImage("WallGrid_RT_B_LE.png");
				}
				// RB_L
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L)
				{
					Renderer->SetImage("WallGrid_RB_L.png");
				}
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L_BE)
				{
					Renderer->SetImage("WallGrid_RB_L_BE.png");
				}
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L_TE)
				{
					Renderer->SetImage("WallGrid_RB_L_TE.png");
				}
				// RB_R
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R)
				{
					Renderer->SetImage("WallGrid_RB_R.png");
				}
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R_BE)
				{
					Renderer->SetImage("WallGrid_RB_R_BE.png");
				}
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R_TE)
				{
					Renderer->SetImage("WallGrid_RB_R_TE.png");
				}
				// BENT_SINGLE
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_SINGLE)
				{
					Renderer->SetImage("WallGrid_Bent_Single.png");
				}
				// BENT_MULTI
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_MULTI)
				{
					Renderer->SetImage("WallGrid_Bent_Multi.png");
				}
				else
				{
					Renderer->SetImage("WallGrid_None.png");
				}

				float4 Pos = float4::ZERO;
				Pos.x = (Index.X_ - Index.Y_) * WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().x;
				Pos.y = (Index.X_ + Index.Y_) * -WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().y;

				Renderer->GetTransform()->SetLocalScaling(WallTileInfo_[y][x].WallTileSize.halffloat4());
				Renderer->GetTransform()->SetLocalPosition(Pos);
				Renderer->GetTransform()->SetLocalZOrder(-3.f);
				WallGrides_.insert(std::make_pair(Index.Index_, Renderer));
			}
		}

#pragma region ������ƮŸ�ϰ���
		// ��Ÿ������ �� �׸�������� �Ϸ�ǰ�, ������ƮŸ������ �� �׸��带 �����Ѵ�.
		CreateObjectTileInfo();
#pragma endregion
	}
}

void TileMap::CreateObjectTileInfo()
{
	// ��Ÿ�������� �ִٸ� ������(��Ÿ�ϰ� ������������ Ÿ�������� ������.)
	if (false == WallTileInfo_.empty())
	{
		// ���� ������ ������Ʈ���� ������ Ÿ�������� �����ִٸ� ����
		AllClearObjectTile();

		// ��Ÿ������ �������� �Ȱ��� ����
		int WallYIndexCnt = static_cast<int>(WallTileInfo_.size());
		if (0 < WallYIndexCnt)
		{
			int WallXIndexCnt = static_cast<int>(WallTileInfo_[WallYIndexCnt - 1].size());

			ObjectTileInfo_.resize(WallYIndexCnt);
			for (int y = 0; y < WallYIndexCnt; ++y)
			{
				for (int x = 0; x < WallXIndexCnt; ++x)
				{
					ObjectTileInfo NewObjectTileInfo = {};

					// WallTile�� �ε��� ������ �״�� ����Ѵ�.
					NewObjectTileInfo.ObjectIndexX = WallTileInfo_[y][x].WallIndexX;
					NewObjectTileInfo.ObjectIndexY = WallTileInfo_[y][x].WallIndexY;

					// Object�� �⺻ �̹��� �ε����� -1�� �����Ѵ�(���� ������忡�� ������Ʈ��ġ�� ������ �̹����ε����� ����ȴ�.)
					NewObjectTileInfo.ObjectImageIndex = -1;

					// ���̾ƴ� Ÿ���̸� Ÿ���� NORMALŸ���� ������.
					if (WallTileInfo_[y][x].WallBasicType == WallBasicType::NORMAL)
					{
						NewObjectTileInfo.ObjectBasicType = ObjectBasicType::NORMAL;
					}
					// ���̰ų� ������������� �����������ʴ� Ÿ���̶�� ������Ʈ�� ��ġ�Ҽ����� WALL TYPE�� ������.
					else
					{
						NewObjectTileInfo.ObjectBasicType = ObjectBasicType::WALL;
					}

					// �⺻ ������ ���� ����
					NewObjectTileInfo.ObjectTextureName = ObjectTileTextureName_;
					NewObjectTileInfo.ObjectTileSize = TileSize_;
					NewObjectTileInfo.ObjectRenderSize = ObjectTileImageSize_;
					NewObjectTileInfo.ObjectRenderPivotPos = ObjectTileIndexPivotPos_;

					ObjectTileInfo_[y].push_back(NewObjectTileInfo);
				}
			}

			// ���� �����Ϸ� �� ���۷���������(�׸���)
			int YInfoCnt = static_cast<int>(ObjectTileInfo_.size());
			int XInfoCnt = static_cast<int>(ObjectTileInfo_[YInfoCnt - 1].size());
			for (int y = 0; y < YInfoCnt; ++y)
			{
				for (int x = 0; x < XInfoCnt; ++x)
				{
					TileIndex Index = TileIndex(ObjectTileInfo_[y][x].ObjectIndexX, ObjectTileInfo_[y][x].ObjectIndexY);

					GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

					// ��Ÿ�Ժ� �̹���
					if (ObjectTileInfo_[y][x].ObjectBasicType == ObjectBasicType::NORMAL)
					{
						// ���� �ٴ�Ÿ�� �̹���
						if (Index.Y_ == 0 && Index.X_ == 0)
						{
							Renderer->SetImage("WallGrid_Center.png");
						}
						else // �Ϲ� �ٴ�Ÿ�� �̹���
						{
							Renderer->SetImage("WallGrid_Normal.png");
						}
					}
					else if (ObjectTileInfo_[y][x].ObjectBasicType == ObjectBasicType::OBJECT)
					{
						Renderer->SetImage("ObjectGrid_Object.png");
					}
					else
					{
						Renderer->SetImage("WallGrid_None.png");
					}

					float4 Pos = float4::ZERO;
					Pos.x = (Index.X_ - Index.Y_) * ObjectTileInfo_[y][x].ObjectTileSize.halffloat4().halffloat4().x;
					Pos.y = (Index.X_ + Index.Y_) * -ObjectTileInfo_[y][x].ObjectTileSize.halffloat4().halffloat4().y;

					Renderer->GetTransform()->SetLocalScaling(ObjectTileInfo_[y][x].ObjectTileSize.halffloat4());
					Renderer->GetTransform()->SetLocalPosition(Pos);
					Renderer->GetTransform()->SetLocalZOrder(-4.f);
					Renderer->Off();
					ObjectGrides_.insert(std::make_pair(Index.Index_, Renderer));
				}
			}
		}
	}
}

// �ڵ���� Ÿ���ؽ��� ��Ī
void TileMap::UpdateFloorTileInfo()
{
	// �ٴ�Ÿ�������� �о�鿩 �̹��� �ε����� ��Ī�Ͽ� ȭ�鿡 �������Ѵ�.
	// ���� ����ڰ� ������ �ٴ�Ÿ�� �̹����� ���صȴ�.
	// ����, �����ʸ�忡�� �̹��� ��Ī�� ������ �� �ִ�.
	// ����!!!! �ڵ���忡�� ���� ������ �ٴ�Ÿ���� �̹����� Ȯ��!!!!
	int YInfoCnt = static_cast<int>(FloorTileInfo_.size());
	int XInfoCnt = static_cast<int>(FloorTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(FloorTileInfo_[y][x].FloorIndexX, FloorTileInfo_[y][x].FloorIndexY);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * FloorTileInfo_[y][x].FloorTileSize.halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -FloorTileInfo_[y][x].FloorTileSize.halffloat4().y;

			Renderer->SetImage(FloorTileTextureName_);
			Renderer->GetTransform()->SetLocalScaling(FloorTileInfo_[y][x].FloorRenderSize);
			Renderer->GetTransform()->SetLocalPosition(FloorTileInfo_[y][x].FloorRenderPivotPos + Pos);
			Renderer->SetIndex(FloorTileInfo_[y][x].FloorImageIndex);
			FloorTiles_.insert(std::make_pair(Index.Index_, Renderer));
		}
	}
}

void TileMap::SetTownWallTexture()
{
	// RT_T
	Wall_RT_T_ImageIndex_ = 1;
	Wall_RT_T_LE_ImageIndex_ = 9;
	Wall_RT_T_RE_ImageIndex_ = 2;

	// RT_B
	Wall_RT_B_ImageIndex_ = 1;
	Wall_RT_B_LE_ImageIndex_ = 9;
	Wall_RT_B_RE_ImageIndex_ = 11;

	// RB_L
	Wall_RB_L_ImageIndex_ = 4;
	Wall_RB_L_TE_ImageIndex_ = 26;
	Wall_RB_L_BE_ImageIndex_ = 3;

	// RB_R
	Wall_RB_R_ImageIndex_ = 4;
	Wall_RB_R_TE_ImageIndex_ = 5;
	Wall_RB_R_BE_ImageIndex_ = 3;

	// BENT_SINGLE
	Wall_BENT_SINGLE_ImageIndex_ = 29;

	// BENT_MULTI1
	Wall_BENT_MULTI1_ImageIndex_ = 7;

	// BENT_MULTI2
	Wall_BENT_MULTI2_ImageIndex_ = 6;
}

void TileMap::SetCatacombsWallTexture()
{
}

void TileMap::SetChaosSanctuaryWallTexture()
{
}

void TileMap::UpdateWallTileInfo()
{
	// ��Ÿ�� �׸��� ������ �о�鿩 �̹��� �ε����� ��Ī�Ͽ� ȭ�鿡 �������Ѵ�.
	// ��, BENTŸ���� ��� ������ 2���� ������ ���� �� ����(RT/RB)�� ���ӵ� ���̹����ε����� �����Ͽ�
	// ȭ�鿡 �������Ѵ�.
	// ����, �����ʸ�忡�� �̹��� ��Ī�� ������ �� �ִ�.
	int YInfoCnt = static_cast<int>(WallTileInfo_.size());
	int XInfoCnt = static_cast<int>(WallTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(WallTileInfo_[y][x].WallIndexX, WallTileInfo_[y][x].WallIndexY);

			WallTileRender WallTiles = {};

			WallTiles.Tiles1_ = CreateTransformComponent<GameEngineTileMapRenderer>();
			WallTiles.Tiles2_ = nullptr;

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().y;

			WallTiles.Tiles1_->SetImage(WallTileInfo_[y][x].WallTextureName);
			WallTiles.Tiles1_->GetTransform()->SetLocalScaling(WallTileInfo_[y][x].WallRenderSize);
			WallTiles.Tiles1_->GetTransform()->SetLocalPosition(WallTileInfo_[y][x].WallRenderPivotPos + Pos);
			WallTiles.Tiles1_->GetTransform()->SetLocalZOrder(-2.f);

			// ��Ÿ�Ժ� �̹���
			
			// 1. RT_T
			if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_T_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RT_T_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T_LE)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_T_LE_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RT_T_LE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T_RE)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_T_RE_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RT_T_RE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			// 2. RT_B
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_B_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RT_B_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B_LE)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_B_LE_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RT_B_LE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B_RE)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_B_RE_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RT_B_RE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			// 3. RB_L
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_L_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RB_L_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L_TE)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_L_TE_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RB_L_TE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L_BE)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_L_BE_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RB_L_BE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			// 4. RB_R
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_R_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RB_R_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R_TE)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_R_TE_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RB_R_TE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R_BE)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_R_BE_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_RB_R_BE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			// 5. BENT_SINGLE
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_SINGLE)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_BENT_SINGLE_ImageIndex_;

				// ���� ������ ���� ����
				WallTiles.Tiles1_->SetIndex(Wall_BENT_SINGLE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			// 6. BENT_MULTI
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_MULTI)
			{
				// ���� ���� ��
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_BENT_MULTI1_ImageIndex_;

				// ���� ������ ���� ����
				
				// BENT_MULTI�� ������ 2���� ������.
				WallTiles.Tiles1_->SetIndex(Wall_BENT_MULTI1_ImageIndex_);

				WallTileInfo_[y][x].WallTile2ImageIndex = Wall_BENT_MULTI2_ImageIndex_;

				WallTiles.Tiles2_ = CreateTransformComponent<GameEngineTileMapRenderer>();
				WallTiles.Tiles2_->SetImage(WallTileInfo_[y][x].WallTextureName);
				WallTiles.Tiles2_->GetTransform()->SetLocalScaling(WallTileInfo_[y][x].WallRenderSize);
				WallTiles.Tiles2_->GetTransform()->SetLocalPosition(WallTileInfo_[y][x].WallRenderPivotPos + Pos);
				WallTiles.Tiles2_->GetTransform()->SetLocalZOrder(-2.f);
				WallTiles.Tiles2_->SetIndex(Wall_BENT_MULTI2_ImageIndex_);

				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			// Ÿ���� ã���� ������ ������ ������ �ٷ� ����
			else
			{
				WallTiles.Tiles1_->Death();
				if (nullptr != WallTiles.Tiles2_)
				{
					WallTiles.Tiles2_->Death();
				}
			}
		}
	}
}

void TileMap::AutoModeTileAllClear()
{
	// �ڵ����� ������ �� ���� �� �׸���, Ÿ�Ϸ��� ��� Ŭ����
	AllClear();
}

#pragma endregion

#pragma region ����/�����������������
void TileMap::AllClear()
{
	// �ٴ�Ÿ�ϰ��� Ŭ����
	AllClearFloorTile();

	// ��Ÿ�ϰ��� Ŭ����
	AllClearWallTile();

	// ������ƮŸ�ϰ��� Ŭ����
	AllClearObjectTile();
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
	for (int y = 0; y < static_cast<int>(FloorTileInfo_.size()); ++y)
	{
		if (false == FloorTileInfo_[y].empty())
		{
			FloorTileInfo_[y].clear();
		}
	}
	FloorTileInfo_.clear();
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

	// ON/OFF Flag����
	FloorGridesActive_ = true;
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
	for (int y = 0; y < static_cast<int>(WallTileInfo_.size()); ++y)
	{
		if (false == WallTileInfo_[y].empty())
		{
			WallTileInfo_[y].clear();
		}
	}
	WallTileInfo_.clear();
}

void TileMap::AllClearWallTileMapRenderer()
{
	// Ÿ��
	std::unordered_map<__int64, WallTileRender>::iterator TilesStartIter = WallTiles_.begin();
	std::unordered_map<__int64, WallTileRender>::iterator TilesEndIter = WallTiles_.end();
	for (; TilesStartIter != TilesEndIter; ++TilesStartIter)
	{
		// ������ ����ó��
		(*TilesStartIter).second.Tiles1_->Death();

		if (nullptr != (*TilesStartIter).second.Tiles2_)
		{
			(*TilesStartIter).second.Tiles2_->Death();
		}
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

	// ON/OFF Flag����
	WallGridesActive_ = true;
}

void TileMap::AllClearObjectTile()
{
	// Ÿ������ Ŭ����
	AllClearObjectTileInfo();

	// Ÿ�Ϸ��������� Ŭ����
	AllClearObjectTileMapRenderer();
}

void TileMap::AllClearObjectTileInfo()
{
	for (int y = 0; y < static_cast<int>(ObjectTileInfo_.size()); ++y)
	{
		if (false == ObjectTileInfo_[y].empty())
		{
			ObjectTileInfo_[y].clear();
		}
	}
	ObjectTileInfo_.clear();
}

void TileMap::AllClearObjectTileMapRenderer()
{
	// Ÿ��
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesStartIter = ObjectTiles_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesEndIter = ObjectTiles_.end();
	for (; TilesStartIter != TilesEndIter; ++TilesStartIter)
	{
		// ������ ����ó��
		(*TilesStartIter).second->Death();
	}
	ObjectTiles_.clear();

	// �׸���
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsStartIter = ObjectGrides_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsEndIter = ObjectGrides_.end();
	for (; GridsStartIter != GridsEndIter; ++GridsStartIter)
	{
		// ������ ����ó��
		(*GridsStartIter).second->Death();
	}
	ObjectGrides_.clear();

	// ON/OFF Flag����
	ObjectGridesActive_ = true;
}

#pragma endregion

void TileMap::MapFileSave()
{
	// ���ϻ��� ��ġ�� ���͸� �̵�
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("MapFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "TownLevel_Map.dat";

	// ���� ����
	GameEngineFile pFile = GameEngineFile(FullPath, "wb");
	
	// �ٴ�Ÿ������ ����
	int FloorYIndex = static_cast<int>(FloorTileInfo_.size());
	if (0 < FloorYIndex)
	{
		int FloorXIndex = static_cast<int>(FloorTileInfo_[FloorYIndex - 1].size());

		// Y�ε��� ����
		pFile.Write(FloorYIndex);

		// X�ε��� ����
		pFile.Write(FloorXIndex);

		for (int y = 0; y < FloorYIndex; ++y)
		{
			for (int x = 0; x < FloorXIndex; ++x)
			{
				// �ε��� ����
				pFile.Write(FloorTileInfo_[y][x].FloorIndexX);
				pFile.Write(FloorTileInfo_[y][x].FloorIndexY);
				pFile.Write(FloorTileInfo_[y][x].FloorImageIndex);

				// ����������
				pFile.Write(FloorTileInfo_[y][x].FloorTextureName);

				// float4 ����

				// TileSize
				pFile.Write(FloorTileInfo_[y][x].FloorTileSize.ix());
				pFile.Write(FloorTileInfo_[y][x].FloorTileSize.iy());
				pFile.Write(FloorTileInfo_[y][x].FloorTileSize.iz());

				// RenderSize
				pFile.Write(FloorTileInfo_[y][x].FloorRenderSize.ix());
				pFile.Write(FloorTileInfo_[y][x].FloorRenderSize.iy());
				pFile.Write(FloorTileInfo_[y][x].FloorRenderSize.iz());

				// RenderPivotPos
				pFile.Write(FloorTileInfo_[y][x].FloorRenderPivotPos.ix());
				pFile.Write(FloorTileInfo_[y][x].FloorRenderPivotPos.iy());
				pFile.Write(FloorTileInfo_[y][x].FloorRenderPivotPos.iz());
			}
		}
	}

	// ��Ÿ������ ����
	int WallYIndex = static_cast<int>(WallTileInfo_.size());
	if (0 < WallYIndex)
	{
		int WallXIndex = static_cast<int>(WallTileInfo_[WallYIndex - 1].size());

		// Y�ε��� ����
		pFile.Write(WallYIndex);

		// X�ε��� ����
		pFile.Write(WallXIndex);

		for (int y = 0; y < WallYIndex; ++y)
		{
			for (int x = 0; x < WallXIndex; ++x)
			{
				// �ε��� �� Ÿ������
				pFile.Write(WallTileInfo_[y][x].WallIndexX);
				pFile.Write(WallTileInfo_[y][x].WallIndexY);
				pFile.Write(WallTileInfo_[y][x].WallTile1ImageIndex);
				pFile.Write(WallTileInfo_[y][x].WallTile2ImageIndex);
				pFile.Write(static_cast<int>(WallTileInfo_[y][x].WallBasicType));
				pFile.Write(static_cast<int>(WallTileInfo_[y][x].WallDetailType));

				// ������ ����
				pFile.Write(WallTileInfo_[y][x].WallTextureName);

				// float4 Data

				// WallTileSize
				pFile.Write(WallTileInfo_[y][x].WallTileSize.ix());
				pFile.Write(WallTileInfo_[y][x].WallTileSize.iy());
				pFile.Write(WallTileInfo_[y][x].WallTileSize.iz());

				// WallRenderSize
				pFile.Write(WallTileInfo_[y][x].WallRenderSize.ix());
				pFile.Write(WallTileInfo_[y][x].WallRenderSize.iy());
				pFile.Write(WallTileInfo_[y][x].WallRenderSize.iz());

				// WallRenderPivotPos
				pFile.Write(WallTileInfo_[y][x].WallRenderPivotPos.ix());
				pFile.Write(WallTileInfo_[y][x].WallRenderPivotPos.iy());
				pFile.Write(WallTileInfo_[y][x].WallRenderPivotPos.iz());
			}
		}
	}

	// ������ƮŸ������ ����
	int ObjectYIndex = static_cast<int>(ObjectTileInfo_.size());
	if (0 < ObjectYIndex)
	{
		int ObjectXIndex = static_cast<int>(ObjectTileInfo_[ObjectYIndex - 1].size());

		// Y�ε��� ����
		pFile.Write(ObjectYIndex);

		// X�ε��� ����
		pFile.Write(ObjectXIndex);

		for (int y = 0; y < ObjectYIndex; ++y)
		{
			for (int x = 0; x < ObjectXIndex; ++x)
			{
				// �ε��� �� Ÿ������
				pFile.Write(ObjectTileInfo_[y][x].ObjectIndexX);
				pFile.Write(ObjectTileInfo_[y][x].ObjectIndexY);
				pFile.Write(ObjectTileInfo_[y][x].ObjectImageIndex);
				pFile.Write(static_cast<int>(ObjectTileInfo_[y][x].ObjectBasicType));

				// ������ ����
				pFile.Write(ObjectTileInfo_[y][x].ObjectTextureName);

				// float4 Data

				// ObjectTileSize
				pFile.Write(ObjectTileInfo_[y][x].ObjectTileSize.ix());
				pFile.Write(ObjectTileInfo_[y][x].ObjectTileSize.iy());
				pFile.Write(ObjectTileInfo_[y][x].ObjectTileSize.iz());

				// ObjectRenderSize
				pFile.Write(ObjectTileInfo_[y][x].ObjectRenderSize.ix());
				pFile.Write(ObjectTileInfo_[y][x].ObjectRenderSize.iy());
				pFile.Write(ObjectTileInfo_[y][x].ObjectRenderSize.iz());

				// ObjectRenderPivotPos
				pFile.Write(ObjectTileInfo_[y][x].ObjectRenderPivotPos.ix());
				pFile.Write(ObjectTileInfo_[y][x].ObjectRenderPivotPos.iy());
				pFile.Write(ObjectTileInfo_[y][x].ObjectRenderPivotPos.iz());
			}
		}
	}

	// ��������
	pFile.Close();
}

void TileMap::MapFileLoad()
{
	// �����ε��� ��� ������ �� ������ Ŭ����
	AllClear();

	// ���Ϸε� ��ġ�� ���͸� �̵�
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("MapFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += "TownLevel_Map.dat";

	// ���� ����
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	// �ٴ�Ÿ������ �ε�
	int FloorYIndex = 1;
	pFile.Read(FloorYIndex);
	FloorTileInfo_.resize(FloorYIndex);

	int FloorXIndex = 1;
	pFile.Read(FloorXIndex);
	for (int y = 0; y < FloorYIndex; ++y)
	{
		FloorTileInfo_[y].resize(FloorXIndex);

		for (int x = 0; x < FloorXIndex; ++x)
		{
			// �ε�������
			pFile.Read(FloorTileInfo_[y][x].FloorIndexX);
			pFile.Read(FloorTileInfo_[y][x].FloorIndexY);
			pFile.Read(FloorTileInfo_[y][x].FloorImageIndex);

			// ������ ����
			pFile.Read(FloorTileInfo_[y][x].FloorTextureName);

			// float4 Data

			// FloorTileSize
			int FloorTileSizeX = 0;
			int FloorTileSizeY = 0;
			int FloorTileSizeZ = 0;
			pFile.Read(FloorTileSizeX);
			pFile.Read(FloorTileSizeY);
			pFile.Read(FloorTileSizeZ);
			FloorTileInfo_[y][x].FloorTileSize = float4(static_cast<float>(FloorTileSizeX), static_cast<float>(FloorTileSizeY), static_cast<float>(FloorTileSizeZ));

			// FloorRenderSize
			int FloorRenderSizeX = 0;
			int FloorRenderSizeY = 0;
			int FloorRenderSizeZ = 0;
			pFile.Read(FloorRenderSizeX);
			pFile.Read(FloorRenderSizeY);
			pFile.Read(FloorRenderSizeZ);
			FloorTileInfo_[y][x].FloorRenderSize = float4(static_cast<float>(FloorRenderSizeX), static_cast<float>(FloorRenderSizeY), static_cast<float>(FloorRenderSizeZ));

			// FloorRenderPivotPos
			int FloorRenderPivotPosX = 0;
			int FloorRenderPivotPosY = 0;
			int FloorRenderPivotPosZ = 0;
			pFile.Read(FloorRenderPivotPosX);
			pFile.Read(FloorRenderPivotPosY);
			pFile.Read(FloorRenderPivotPosZ);
			FloorTileInfo_[y][x].FloorRenderPivotPos = float4(static_cast<float>(FloorRenderPivotPosX), static_cast<float>(FloorRenderPivotPosY), static_cast<float>(FloorRenderPivotPosZ));
		}
	}
	
	// ��Ÿ������ �ε�
	int WallYIndex = 1;
	pFile.Read(WallYIndex);
	WallTileInfo_.resize(WallYIndex);

	int WallXIndex = 1;
	pFile.Read(WallXIndex);
	for (int y = 0; y < WallYIndex; ++y)
	{
		WallTileInfo_[y].resize(WallXIndex);

		for (int x = 0; x < WallXIndex; ++x)
		{
			// �ε��� �� Ÿ������
			pFile.Read(WallTileInfo_[y][x].WallIndexX);
			pFile.Read(WallTileInfo_[y][x].WallIndexY);
			pFile.Read(WallTileInfo_[y][x].WallTile1ImageIndex);
			pFile.Read(WallTileInfo_[y][x].WallTile2ImageIndex);

			int WallBasicType_ = 0;
			pFile.Read(WallBasicType_);
			WallTileInfo_[y][x].WallBasicType = static_cast<WallBasicType>(WallBasicType_);

			int WallDetailType_ = 0;
			pFile.Read(WallDetailType_);
			WallTileInfo_[y][x].WallDetailType = static_cast<WallDetailType>(WallDetailType_);

			// ������ ����
			pFile.Read(WallTileInfo_[y][x].WallTextureName);
			
			// float4 Data

			// WallTileSize
			int WallTileSizeX = 0;
			int WallTileSizeY = 0;
			int WallTileSizeZ = 0;
			pFile.Read(WallTileSizeX);
			pFile.Read(WallTileSizeY);
			pFile.Read(WallTileSizeZ);
			WallTileInfo_[y][x].WallTileSize = float4(static_cast<float>(WallTileSizeX), static_cast<float>(WallTileSizeY), static_cast<float>(WallTileSizeZ));

			// WallRenderSize
			int WallRenderSizeX = 0;
			int WallRenderSizeY = 0;
			int WallRenderSizeZ = 0;
			pFile.Read(WallRenderSizeX);
			pFile.Read(WallRenderSizeY);
			pFile.Read(WallRenderSizeZ);
			WallTileInfo_[y][x].WallRenderSize = float4(static_cast<float>(WallRenderSizeX), static_cast<float>(WallRenderSizeY), static_cast<float>(WallRenderSizeZ));

			// WallRenderPivotPos
			int WallRenderPivotPosX = 0;
			int WallRenderPivotPosY = 0;
			int WallRenderPivotPosZ = 0;
			pFile.Read(WallRenderPivotPosX);
			pFile.Read(WallRenderPivotPosY);
			pFile.Read(WallRenderPivotPosZ);
			WallTileInfo_[y][x].WallRenderPivotPos = float4(static_cast<float>(WallRenderPivotPosX), static_cast<float>(WallRenderPivotPosY), static_cast<float>(WallRenderPivotPosZ));
		}
	}

	// ������ƮŸ������ �ε�
	int ObjectYIndex = 1;
	pFile.Read(ObjectYIndex);
	ObjectTileInfo_.resize(ObjectYIndex);

	int ObjectXIndex = 1;
	pFile.Read(ObjectXIndex);
	for (int y = 0; y < ObjectYIndex; ++y)
	{
		ObjectTileInfo_[y].resize(ObjectXIndex);

		for (int x = 0; x < ObjectXIndex; ++x)
		{
			// �ε��� �� Ÿ������
			pFile.Read(ObjectTileInfo_[y][x].ObjectIndexX);
			pFile.Read(ObjectTileInfo_[y][x].ObjectIndexY);
			pFile.Read(ObjectTileInfo_[y][x].ObjectImageIndex);

			int ObjectBasicType_ = 0;
			pFile.Read(ObjectBasicType_);
			ObjectTileInfo_[y][x].ObjectBasicType = static_cast<ObjectBasicType>(ObjectBasicType_);

			// ������ ����
			pFile.Read(ObjectTileInfo_[y][x].ObjectTextureName);
			
			// float4 Data

			// ObjectTileSize
			int ObjectTileSizeX = 0;
			int ObjectTileSizeY = 0;
			int ObjectTileSizeZ = 0;
			pFile.Read(ObjectTileSizeX);
			pFile.Read(ObjectTileSizeY);
			pFile.Read(ObjectTileSizeZ);
			ObjectTileInfo_[y][x].ObjectTileSize = float4(static_cast<float>(ObjectTileSizeX), static_cast<float>(ObjectTileSizeY), static_cast<float>(ObjectTileSizeZ));

			// ObjectRenderSize
			int ObjectRenderSizeX = 0;
			int ObjectRenderSizeY = 0;
			int ObjectRenderSizeZ = 0;
			pFile.Read(ObjectRenderSizeX);
			pFile.Read(ObjectRenderSizeY);
			pFile.Read(ObjectRenderSizeZ);
			ObjectTileInfo_[y][x].ObjectRenderSize = float4(static_cast<float>(ObjectRenderSizeX), static_cast<float>(ObjectRenderSizeY), static_cast<float>(ObjectRenderSizeZ));

			// ObjectRenderPivotPos
			int ObjectRenderPivotPosX = 0;
			int ObjectRenderPivotPosY = 0;
			int ObjectRenderPivotPosZ = 0;
			pFile.Read(ObjectRenderPivotPosX);
			pFile.Read(ObjectRenderPivotPosY);
			pFile.Read(ObjectRenderPivotPosZ);
			ObjectTileInfo_[y][x].ObjectRenderSize = float4(static_cast<float>(ObjectRenderSizeX), static_cast<float>(ObjectRenderSizeY), static_cast<float>(ObjectRenderSizeZ));
		}
	}

	pFile.Close();

	// ��� ���� �ε��Ϸ�� ȭ�鿡 �������ϴ� ������ ����
	CreatedAfterLoading();
}

void TileMap::CreatedAfterLoading()
{
	// ��� ���� �ε��Ϸ�� ȭ�鿡 �������ϴ� ������ ����

	// �׸��� ����
	CreatedAfterLoading_FloorGrides();
	CreatedAfterLoading_WallGrides();
	CreatedAfterLoading_ObjectGrides();

	// Ÿ�� ����
	CreatedAfterLoading_FloorTiles();
	CreatedAfterLoading_WallTiles();
	CreatedAfterLoading_ObjectTiles();
}

void TileMap::CreatedAfterLoading_FloorGrides()
{
	// �ٴ� Ÿ��
	int YInfoCnt = static_cast<int>(FloorTileInfo_.size());
	int XInfoCnt = static_cast<int>(FloorTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(FloorTileInfo_[y][x].FloorIndexX, FloorTileInfo_[y][x].FloorIndexY);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			// ���� �ٴ�Ÿ�� �̹���
			if (Index.Y_ == 0 && Index.X_ == 0)
			{
				Renderer->SetImage("FloorGrid_Center.png");
			}
			else // �Ϲ� �ٴ�Ÿ�� �̹���
			{
				Renderer->SetImage("FloorGrid_Normal.png");
			}

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * FloorTileInfo_[y][x].FloorTileSize.halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -FloorTileInfo_[y][x].FloorTileSize.halffloat4().y;

			Renderer->GetTransform()->SetLocalScaling(FloorTileInfo_[y][x].FloorRenderSize);
			Renderer->GetTransform()->SetLocalPosition(FloorTileInfo_[y][x].FloorRenderPivotPos + Pos);
			FloorGrides_.insert(std::make_pair(Index.Index_, Renderer));
		}
	}
}

void TileMap::CreatedAfterLoading_WallGrides()
{
	// �� Ÿ��
	int YInfoCnt = static_cast<int>(WallTileInfo_.size());
	int XInfoCnt = static_cast<int>(WallTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(WallTileInfo_[y][x].WallIndexX, WallTileInfo_[y][x].WallIndexY);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			// ��Ÿ�Ժ� �̹���
			if (WallTileInfo_[y][x].WallBasicType == WallBasicType::NORMAL)
			{
				// ���� �ٴ�Ÿ�� �̹���
				if (Index.Y_ == 0 && Index.X_ == 0)
				{
					Renderer->SetImage("WallGrid_Center.png");
				}
				else // �Ϲ� �ٴ�Ÿ�� �̹���
				{
					Renderer->SetImage("WallGrid_Normal.png");
				}
			}
			// RT_T
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T)
			{
				Renderer->SetImage("WallGrid_RT_T.png");
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T_RE)
			{
				Renderer->SetImage("WallGrid_RT_T_RE.png");
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T_LE)
			{
				Renderer->SetImage("WallGrid_RT_T_LE.png");
			}
			// RT_B
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B)
			{
				Renderer->SetImage("WallGrid_RT_B.png");
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B_RE)
			{
				Renderer->SetImage("WallGrid_RT_B_RE.png");
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B_LE)
			{
				Renderer->SetImage("WallGrid_RT_B_LE.png");
			}
			// RB_L
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L)
			{
				Renderer->SetImage("WallGrid_RB_L.png");
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L_BE)
			{
				Renderer->SetImage("WallGrid_RB_L_BE.png");
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L_TE)
			{
				Renderer->SetImage("WallGrid_RB_L_TE.png");
			}
			// RB_R
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R)
			{
				Renderer->SetImage("WallGrid_RB_R.png");
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R_BE)
			{
				Renderer->SetImage("WallGrid_RB_R_BE.png");
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R_TE)
			{
				Renderer->SetImage("WallGrid_RB_R_TE.png");
			}
			// BENT_SINGLE
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_SINGLE)
			{
				Renderer->SetImage("WallGrid_Bent_Single.png");
			}
			// BENT_MULTI
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_MULTI)
			{
				Renderer->SetImage("WallGrid_Bent_Multi.png");
			}
			else
			{
				Renderer->SetImage("WallGrid_None.png");
			}

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().y;

			Renderer->GetTransform()->SetLocalScaling(WallTileInfo_[y][x].WallTileSize.halffloat4());
			Renderer->GetTransform()->SetLocalPosition(Pos);
			Renderer->GetTransform()->SetLocalZOrder(-3.f);
			WallGrides_.insert(std::make_pair(Index.Index_, Renderer));
		}
	}
}

void TileMap::CreatedAfterLoading_ObjectGrides()
{
	// ������Ʈ Ÿ��
	int YInfoCnt = static_cast<int>(ObjectTileInfo_.size());
	int XInfoCnt = static_cast<int>(ObjectTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(ObjectTileInfo_[y][x].ObjectIndexX, ObjectTileInfo_[y][x].ObjectIndexY);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			// ��Ÿ�Ժ� �̹���
			if (ObjectTileInfo_[y][x].ObjectBasicType == ObjectBasicType::NORMAL)
			{
				// ���� �ٴ�Ÿ�� �̹���
				if (Index.Y_ == 0 && Index.X_ == 0)
				{
					Renderer->SetImage("WallGrid_Center.png");
				}
				else // �Ϲ� �ٴ�Ÿ�� �̹���
				{
					Renderer->SetImage("WallGrid_Normal.png");
				}
			}
			else if (ObjectTileInfo_[y][x].ObjectBasicType == ObjectBasicType::OBJECT)
			{
				Renderer->SetImage("ObjectGrid_Object.png");
			}
			else
			{
				Renderer->SetImage("WallGrid_None.png");
			}

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * ObjectTileInfo_[y][x].ObjectTileSize.halffloat4().halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -ObjectTileInfo_[y][x].ObjectTileSize.halffloat4().halffloat4().y;

			Renderer->GetTransform()->SetLocalScaling(ObjectTileInfo_[y][x].ObjectTileSize.halffloat4());
			Renderer->GetTransform()->SetLocalPosition(Pos);
			Renderer->GetTransform()->SetLocalZOrder(-4.f);
			Renderer->Off();
			ObjectGrides_.insert(std::make_pair(Index.Index_, Renderer));
		}
	}
}

void TileMap::CreatedAfterLoading_FloorTiles()
{
	int YInfoCnt = static_cast<int>(FloorTileInfo_.size());
	int XInfoCnt = static_cast<int>(FloorTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(FloorTileInfo_[y][x].FloorIndexX, FloorTileInfo_[y][x].FloorIndexY);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * FloorTileInfo_[y][x].FloorTileSize.halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -FloorTileInfo_[y][x].FloorTileSize.halffloat4().y;

			Renderer->SetImage(FloorTileTextureName_);
			Renderer->GetTransform()->SetLocalScaling(FloorTileInfo_[y][x].FloorRenderSize);
			Renderer->GetTransform()->SetLocalPosition(FloorTileInfo_[y][x].FloorRenderPivotPos + Pos);
			Renderer->SetIndex(FloorTileInfo_[y][x].FloorImageIndex);
			FloorTiles_.insert(std::make_pair(Index.Index_, Renderer));
		}
	}
}

void TileMap::CreatedAfterLoading_WallTiles()
{
	int YInfoCnt = static_cast<int>(WallTileInfo_.size());
	int XInfoCnt = static_cast<int>(WallTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(WallTileInfo_[y][x].WallIndexX, WallTileInfo_[y][x].WallIndexY);

			WallTileRender WallTiles = {};

			WallTiles.Tiles1_ = CreateTransformComponent<GameEngineTileMapRenderer>();
			WallTiles.Tiles2_ = nullptr;

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().y;

			WallTiles.Tiles1_->SetImage(WallTileInfo_[y][x].WallTextureName);
			WallTiles.Tiles1_->GetTransform()->SetLocalScaling(WallTileInfo_[y][x].WallRenderSize);
			WallTiles.Tiles1_->GetTransform()->SetLocalPosition(WallTileInfo_[y][x].WallRenderPivotPos + Pos);
			WallTiles.Tiles1_->GetTransform()->SetLocalZOrder(-2.f);

			// ��Ÿ�Ժ� �̹���
			// ��, Normal, None�̸� �������� ������������
			if (WallTileInfo_[y][x].WallBasicType == WallBasicType::NONE || WallTileInfo_[y][x].WallBasicType == WallBasicType::NORMAL)
			{
				WallTiles.Tiles1_->Death();
				if (nullptr != WallTiles.Tiles2_)
				{
					WallTiles.Tiles2_->Death();
				}
			}
			// BENT_MULTI�̸� ������ 2��
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_MULTI)
			{
				WallTiles.Tiles1_->SetIndex(WallTileInfo_[y][x].WallTile1ImageIndex);

				WallTiles.Tiles2_ = CreateTransformComponent<GameEngineTileMapRenderer>();
				WallTiles.Tiles2_->SetImage(WallTileInfo_[y][x].WallTextureName);
				WallTiles.Tiles2_->GetTransform()->SetLocalScaling(WallTileInfo_[y][x].WallRenderSize);
				WallTiles.Tiles2_->GetTransform()->SetLocalPosition(WallTileInfo_[y][x].WallRenderPivotPos + Pos);
				WallTiles.Tiles2_->GetTransform()->SetLocalZOrder(-2.f);
				WallTiles.Tiles2_->SetIndex(WallTileInfo_[y][x].WallTile2ImageIndex);

				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else
			{
				WallTiles.Tiles1_->SetIndex(WallTileInfo_[y][x].WallTile1ImageIndex);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
		}
	}
}

void TileMap::CreatedAfterLoading_ObjectTiles()
{
	int YInfoCnt = static_cast<int>(ObjectTileInfo_.size());
	int XInfoCnt = static_cast<int>(ObjectTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(ObjectTileInfo_[y][x].ObjectIndexX, ObjectTileInfo_[y][x].ObjectIndexY);

			float4 Pos = float4::ZERO;
			Pos.x = (Index.X_ - Index.Y_) * ObjectTileInfo_[y][x].ObjectTileSize.halffloat4().halffloat4().x;
			Pos.y = (Index.X_ + Index.Y_) * -ObjectTileInfo_[y][x].ObjectTileSize.halffloat4().halffloat4().y;


			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			Renderer->SetImage(ObjectTileInfo_[y][x].ObjectTextureName);
			Renderer->GetTransform()->SetLocalScaling(ObjectTileInfo_[y][x].ObjectRenderSize);
			Renderer->GetTransform()->SetLocalPosition(ObjectTileInfo_[y][x].ObjectRenderPivotPos + Pos);
			Renderer->GetTransform()->SetLocalZOrder(-4.f);

			// -1 == ObjectTileInfo_[y][x].ObjectImageIndex�̸� ������Ʈ�� ��ġ�Ǿ��������� Ÿ�Ϸ� �Ǵ�
			if (-1 != ObjectTileInfo_[y][x].ObjectImageIndex)
			{
				Renderer->SetIndex(ObjectTileInfo_[y][x].ObjectImageIndex);
				ObjectTiles_.insert(std::make_pair(Index.Index_, Renderer));
			}
			else
			{
				Renderer->Death();
			}
		}
	}
}
