#include "PreCompile.h"
#include "EditorTileMap.h"

#include <GameEngineBase/GameEngineFile.h>

#include <GameEngine/GameEngineTileMapRenderer.h>

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

#include "GlobalEnumClass.h"

EditorTileMap::EditorTileMap() :
	FloorRenderingType_(FloorRenderingType::TILE),
	WallRenderingType_(WallRenderingType::TILE1),
	ObjectRenderingType_(ObjectRenderingType::TILE),
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

EditorTileMap::~EditorTileMap()
{
}

void EditorTileMap::Start()
{
	// 에디터 사용 기본 정보 초기화

	// 타일
	TileSize_ = float4(160.f, 80.f);
	TileSizeHalf_ = TileSize_.halffloat4();
	TileSizeHHalf_ = TileSizeHalf_.halffloat4();

	// 바닥타일
	FloorTileImageSize_ = { 160.0f, 80.f };

	FloorTileImageSizeHalf_ = FloorTileImageSize_.halffloat4();
	FloorTileIndexPivotPos_ = { 0.0f, -TileSizeHalf_.y };

	// 벽타일
	WallTileImageSize_ = { 160.0f, 320.f };

	WallTileImageSizeHalf_ = WallTileImageSize_.halffloat4();
	WallTileIndexPivotPos_ = { 0.0f, TileSize_.y };

	// 오브젝트타일
	ObjectTileImageSize_ = { 160.0f, 320.f };

	ObjectTileImageSizeHalf_ = ObjectTileImageSize_.halffloat4();
	ObjectTileIndexPivotPos_ = { 0.0f, TileSize_.y };
}

void EditorTileMap::FloorGridesSwitching()
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

void EditorTileMap::WallGridesSwitching()
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

void EditorTileMap::ObjectGridesSwitching()
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

#pragma region 편의기능관련

void EditorTileMap::SetFloorRenderingMode(FloorRenderingType _FloorRenderingType)
{
	FloorRenderingType_ = _FloorRenderingType;
}

void EditorTileMap::SetWallRenderingMode(WallRenderingType _WallRenderingType)
{
	WallRenderingType_ = _WallRenderingType;
}

void EditorTileMap::SetObjectRenderingMode(ObjectRenderingType _ObjectRenderingType)
{
	ObjectRenderingType_ = _ObjectRenderingType;
}

#pragma endregion

#pragma region IMGUI표시용

float4 EditorTileMap::GetFloorIsoPos(float4 _Pos)
{
	return { ((_Pos.x / TileSizeHalf_.x) - (_Pos.y / TileSizeHalf_.y)) / 2.0f ,((_Pos.y / TileSizeHalf_.y) + (_Pos.x / TileSizeHalf_.x)) / -2.0f };
}

float4 EditorTileMap::GetWallIsoPos(float4 _Pos)
{
	return { ((_Pos.x / TileSizeHHalf_.x) - (_Pos.y / TileSizeHHalf_.y)) / 2.0f, ((_Pos.y / TileSizeHHalf_.y) + (_Pos.x / TileSizeHHalf_.x)) / -2.0f };
}

float4 EditorTileMap::GetObjectIsoPos(float4 _Pos)
{
	return { ((_Pos.x / TileSizeHHalf_.x) - (_Pos.y / TileSizeHHalf_.y)) / 2.0f, ((_Pos.y / TileSizeHHalf_.y) + (_Pos.x / TileSizeHHalf_.x)) / -2.0f };
}

#pragma endregion

#pragma region GetTileIndex(Floor/Wall)

TileIndex EditorTileMap::GetFloorTileIndex(float4 _Pos)
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

TileIndex EditorTileMap::GetWallTileIndex(float4 _Pos)
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

TileIndex EditorTileMap::GetObjectTileIndex(float4 _Pos)
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

void EditorTileMap::SetFloorTile(float4 _Pos, int CurTileIndex_)
{
	SetFloorTile(GetFloorTileIndex(_Pos), CurTileIndex_);
}

void EditorTileMap::SetFloorTile(TileIndex _Index, int CurTileIndex_)
{
	// 타일타입일때만 처리
	if (FloorRenderingType::TILE == FloorRenderingType_)
	{
		// 동일 타일이 있으면 현재렌더러의 텍스쳐를 변경하고, 
		// 바닥타일정보를 갱신
		if (FloorTiles_.end() != FloorTiles_.find(_Index.Index_))
		{
			// 렌더러 갱신
			FloorTiles_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);

			// 정보가 존재할때 갱신
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
		FloorTileRenderer->GetTransform()->SetLocalZOrder(100.f);
		FloorTileRenderer->SetIndex(CurTileIndex_);
		FloorTiles_.insert(std::make_pair(_Index.Index_, FloorTileRenderer));

		// 정보를 날리지않으므로 현재 정보를 갱신
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

void EditorTileMap::SetWallTile(float4 _Pos, int CurTileIndex_)
{
	SetWallTile(GetWallTileIndex(_Pos), CurTileIndex_);
}

void EditorTileMap::SetWallTile(TileIndex _Index, int CurTileIndex_)
{
	// 타일타입일때만 처리
	if (WallRenderingType::TILE1 == WallRenderingType_ || WallRenderingType::TILE2 == WallRenderingType_)
	{
		if (WallTiles_.end() != WallTiles_.find(_Index.Index_))
		{
			// 현재 렌더러 텍스쳐 인덱스 교체
			if (WallRenderingType::TILE1 == WallRenderingType_)
			{
				WallTiles_.find(_Index.Index_)->second.Tiles1_->SetIndex(CurTileIndex_);
			}
			else if (WallRenderingType::TILE2 == WallRenderingType_)
			{
				// BENT_MULTI TYPE일때만 TILES2를 생성한다.
				if (nullptr != WallTiles_.find(_Index.Index_)->second.Tiles2_)
				{
					WallTiles_.find(_Index.Index_)->second.Tiles2_->SetIndex(CurTileIndex_);
				}
			}

			// 정보가 존재할때 갱신
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
		NewRenderer.Tiles1_->GetTransform()->SetLocalZOrder(99.f);
		NewRenderer.Tiles1_->SetIndex(CurTileIndex_);

		WallTiles_.insert(std::make_pair(_Index.Index_, NewRenderer));

		// 정보를 날리지않으므로 현재 정보를 갱신
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

void EditorTileMap::SetObjectTile(float4 _Pos, int CurTileIndex_)
{
	SetObjectTile(GetObjectTileIndex(_Pos), CurTileIndex_);
}

void EditorTileMap::SetObjectTile(TileIndex _Index, int CurTileIndex_)
{
	if (ObjectRenderingType::TILE == ObjectRenderingType_)
	{
		if (ObjectTiles_.end() != ObjectTiles_.find(_Index.Index_))
		{
			// 렌더러 갱신
			ObjectTiles_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);

			// 정보가 존재할때 갱신
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

void EditorTileMap::DelFloorTile(float4 _Pos)
{
	// 타일모드일때 처리
	if (FloorRenderingType::TILE == FloorRenderingType_)
	{
		TileIndex Index = GetFloorTileIndex(_Pos);

		// 타일
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TileFindIter = FloorTiles_.find(Index.Index_);
		if (FloorTiles_.end() != TileFindIter)
		{
			TileFindIter->second->Death();
			FloorTiles_.erase(TileFindIter);
		}
	}
}

void EditorTileMap::DelWallTile(float4 _Pos)
{
	// 타일모드일때 처리
	if (WallRenderingType::TILE1 == WallRenderingType_ || WallRenderingType::TILE2 == WallRenderingType_)
	{
		TileIndex Index = GetWallTileIndex(_Pos);

		// 타일
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

void EditorTileMap::DelObjectTile(float4 _Pos)
{
	// 타일모드일때 처리
	if (ObjectRenderingType::TILE == ObjectRenderingType_)
	{
		TileIndex Index = GetObjectTileIndex(_Pos);

		// 타일
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TileFindIter = ObjectTiles_.find(Index.Index_);
		if (ObjectTiles_.end() != TileFindIter)
		{
			TileFindIter->second->Death();
			ObjectTiles_.erase(TileFindIter);
		}

		// 오브젝트타일정보의 이미지인덱스 -1로 변경
		int YIndex = static_cast<int>(ObjectTileInfo_.size());
		if (0 < YIndex)
		{
			int XIndex = static_cast<int>(ObjectTileInfo_[YIndex - 1].size());
			for (int y = 0; y < YIndex; ++y)
			{
				for (int x = 0; x < XIndex; ++x)
				{
					if (Index.X_ == ObjectTileInfo_[y][x].ObjectIndexX &&
						Index.Y_ == ObjectTileInfo_[y][x].ObjectIndexY)
					{
						ObjectTileInfo_[y][x].ObjectImageIndex = -1;
						ObjectTileInfo_[y][x].ObjectBasicType = ObjectBasicType::NORMAL;
						return;
					}
				}
			}
		}
	}
}

#pragma endregion

#pragma region SetGrid/DelGrid(Floor/Wall)

void EditorTileMap::SetFloorGird(float4 _Pos, int CurTileIndex_)
{
	SetFloorGird(GetFloorTileIndex(_Pos), CurTileIndex_);
}

void EditorTileMap::SetFloorGird(TileIndex _Index, int CurTileIndex_)
{
	// 타일모드가 아닐때 처리
	if (FloorRenderingType::TILE != FloorRenderingType_)
	{
		// 같은 인덱스가 존재하면 리턴
		if (FloorGrides_.end() != FloorGrides_.find(_Index.Index_))
		{
			// 그리드 타입이 한개이므로 바로 리턴
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
		FloorGridRenderer->GetTransform()->SetLocalZOrder(-99.f);
		FloorGrides_.insert(std::make_pair(_Index.Index_, FloorGridRenderer));
	}
}

void EditorTileMap::SetWallGird(float4 _Pos, int CurTileIndex_)
{
	SetWallGird(GetWallTileIndex(_Pos), CurTileIndex_);
}

void EditorTileMap::SetWallGird(TileIndex _Index, int CurTileIndex_)
{
	// 타일모드가 아닐때 처리
	if (WallRenderingType::TILE1 != WallRenderingType_ && WallRenderingType::TILE2 != WallRenderingType_)
	{
		if (WallGrides_.end() != WallGrides_.find(_Index.Index_))
		{
			// 현재 그리드렌더러 이미지 변경
			float4 ChangePos = float4::ZERO;
			ChangePos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
			ChangePos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

			// 렌더타입별 이미지 셋팅
			if (WallRenderingType::GRID_NOR == WallRenderingType_)
			{
				// 센터 바닥타일 이미지
				if (_Index.Y_ == 0 && _Index.X_ == 0)
				{
					WallGrides_.find(_Index.Index_)->second->SetImage("WallGrid_Center.png");
				}
				else // 일반 바닥타일 이미지
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

			// 정보갱신
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

		// 렌더타입별 이미지 셋팅
		if (WallRenderingType::GRID_NOR == WallRenderingType_)
		{
			// 센터 바닥타일 이미지
			if (_Index.Y_ == 0 && _Index.X_ == 0)
			{
				Renderer->SetImage("WallGrid_Center.png");
			}
			else // 일반 바닥타일 이미지
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

void EditorTileMap::SetObjectGird(float4 _Pos, int CurTileIndex_)
{
	SetObjectGird(GetObjectTileIndex(_Pos), CurTileIndex_);
}

void EditorTileMap::SetObjectGird(TileIndex _Index, int CurTileIndex_)
{
	// 타일모드가 아닐때 처리
	if (ObjectRenderingType::TILE != ObjectRenderingType_)
	{
		if (ObjectGrides_.end() != ObjectGrides_.find(_Index.Index_))
		{
			// 그리드 타입변환
			if (ObjectRenderingType::GRID_NORMAL == ObjectRenderingType_)
			{
				// 센터 바닥타일 이미지
				if (_Index.Y_ == 0 && _Index.X_ == 0)
				{
					ObjectGrides_.find(_Index.Index_)->second->SetImage("WallGrid_Center.png");
				}
				else // 일반 바닥타일 이미지
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

			// 정보갱신
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

			// 렌더타입별 이미지 셋팅
			if (ObjectRenderingType::GRID_NORMAL == ObjectRenderingType_)
			{
				// 센터 바닥타일 이미지
				if (_Index.Y_ == 0 && _Index.X_ == 0)
				{
					Renderer->SetImage("WallGrid_Center.png");
				}
				else // 일반 바닥타일 이미지
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

void EditorTileMap::DelFloorGird(float4 _Pos)
{
	// 타일모드가 아닐때 처리
	if (FloorRenderingType::TILE != FloorRenderingType_)
	{
		TileIndex Index = GetFloorTileIndex(_Pos);

		// 타일
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridFindIter = FloorGrides_.find(Index.Index_);
		if (FloorGrides_.end() != GridFindIter)
		{
			GridFindIter->second->Death();
			FloorGrides_.erase(GridFindIter);
		}
	}
}

void EditorTileMap::DelWallGird(float4 _Pos)
{
	// 타일모드가 아닐때 처리
	if (WallRenderingType::TILE1 != WallRenderingType_ && WallRenderingType::TILE2 != WallRenderingType_)
	{
		TileIndex Index = GetWallTileIndex(_Pos);

		// 타일
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridFindIter = WallGrides_.find(Index.Index_);
		if (WallGrides_.end() != GridFindIter)
		{
			GridFindIter->second->Death();
			WallGrides_.erase(GridFindIter);
		}
	}
}

void EditorTileMap::DelObjectGird(float4 _Pos)
{
	// 타일모드가 아닐때 처리
	if (ObjectRenderingType::TILE != ObjectRenderingType_)
	{
		TileIndex Index = GetObjectTileIndex(_Pos);

		// 타일
		std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridFindIter = ObjectGrides_.find(Index.Index_);
		if (ObjectGrides_.end() != GridFindIter)
		{
			GridFindIter->second->Death();
			ObjectGrides_.erase(GridFindIter);
		}
	}
}

#pragma endregion

#pragma region 자동모드관련

// 자동모드 정보생성
void EditorTileMap::CreateFloorTileInfo(int _HeightTileCount, int _WidthTileCount, int _ImageIndex)
{
	// 만약 다른모드에서 바닥타일정보나 바닥타일렌더링정보를 생성한것을 재사용하는것을 방지하기 위하여 기존 정보 모두 클리어하고 생성 시작
	AllClearFloorTile();

	// 인자로 수신한 갯수만큼 바닥타일정보 생성
	FloorTileInfo_.resize(_WidthTileCount);

	// 시작인덱스, 종료인덱스 계산
	int YStartIndex = 0;
	int YEndIndex = 0;
	int XStartIndex = 0;
	int XEndIndex = 0;
	if (_WidthTileCount % 2 == 0) // _HeightTileCount / 2 가 짝수이면 End
	{
		// 시작인덱스, 종료인덱스 계산
		YStartIndex = -(_WidthTileCount / 2);
		YEndIndex = _WidthTileCount / 2;
	}
	else // _HeightTileCount / 2 가 홀수이면 End + 1
	{
		// 시작인덱스, 종료인덱스 계산
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

			// 바닥타일 정보 생성
			FloorTileInfo NewFloorTileInfo = {};
			NewFloorTileInfo.FloorIndexX = y;
			NewFloorTileInfo.FloorIndexY = x;
			NewFloorTileInfo.FloorImageIndex = _ImageIndex;	// 초기 선택된 텍스쳐로 모두 셋팅
			NewFloorTileInfo.FloorTextureName = FloorTileTextureName_;
			NewFloorTileInfo.FloorTileSize = TileSize_;
			NewFloorTileInfo.FloorRenderSize = FloorTileImageSize_;
			NewFloorTileInfo.FloorRenderPivotPos = FloorTileIndexPivotPos_;

			FloorTileInfo_[YIndex].push_back(NewFloorTileInfo);
		}

		++YIndex;
	}

	// 정보 생성완료 후 레퍼런스렌더링(그리드)
	int YInfoCnt = static_cast<int>(FloorTileInfo_.size());
	int XInfoCnt = static_cast<int>(FloorTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(FloorTileInfo_[y][x].FloorIndexX, FloorTileInfo_[y][x].FloorIndexY);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			// 센터 바닥타일 이미지
			if (Index.Y_ == 0 && Index.X_ == 0)
			{
				Renderer->SetImage("FloorGrid_Center.png");
			}
			else // 일반 바닥타일 이미지
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

void EditorTileMap::CreateWallTileInfo()
{
	// 만약 다른모드에서 바닥타일정보나 바닥타일렌더링정보를 생성한것을 재사용하는것을 방지하기 위하여 기존 정보 모두 클리어하고 생성 시작
	AllClearWallTile();

	// 벽타일의 갯수는 바닥타일 갯수에 비례하여 생성된다.
	// 단, 자동모드생성일때는 바탁타일정보가 생성되어야만 벽타일정보생성가능!!!!
	if (false == FloorTileInfo_.empty())
	{
		// 바닥타일 한개기준 벽타일은 3x3 총 9개가 생성된다.
		int HeightFloorTileCnt = static_cast<int>(FloorTileInfo_.size());
		int WidthFloorTileCnt = static_cast<int>(FloorTileInfo_[HeightFloorTileCnt - 1].size());

		// 벽타일생성 기준 : 바닥타일갯수 * 2 + 1
		int YIndexCnt = (WidthFloorTileCnt * 2) + 1;
		int XIndexCnt = (HeightFloorTileCnt * 2) + 1;

		int YStartIndex = 0;
		int YEndIndex = 0;
		int XStartIndex = 0;
		int XEndIndex = 0;

		// 바닥타일이 짝수인지 홀수인지 체크
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

		// 벽타입을 위한 체크 인덱스 생성
		int YIndexChkM = 0;
		int YIndexChkP = 0;
		int XIndexChkM = 0;
		int XIndexChkP = 0;

		// -. 바닥타일 기준으로 조건 생성
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

		// 벽타일 조건체크에 의한 정보 생성
		WallTileInfo_.resize(YIndexCnt);

		int YIndex = 0;
		for (int y = YStartIndex; y < YEndIndex; ++y)
		{
			for (int x = XStartIndex; x < XEndIndex; ++x)
			{
				TileIndex Index = {};

				// 조건체크는 벽의 기본타입, 상세타입을 결정한다.
				WallTileInfo NewWallTileInfo = {};

				NewWallTileInfo.WallIndexX = x;
				NewWallTileInfo.WallIndexY = y;
				NewWallTileInfo.WallTile1ImageIndex = 0; // 초기 0으로 셋팅(추후 이미지갱신시점에 각 벽타입을체크하여 이미지타일 결정)
				NewWallTileInfo.WallTile2ImageIndex = 0; // 초기 0으로 셋팅(추후 이미지갱신시점에 각 벽타입을체크하여 이미지타일 결정)

				// 벽 기본타입 조건체크(타일의 인덱스로 조건체크) - 마을맵 생성기준

				// 1. 벽으로 렌더링해야하는 구간인지 아닌지 판단
				// 2. 벽으로 렌더링해야한다면 우상단(좌하단)방향인지 우하단(좌상단)방향의 벽인지 판단
				//    1) 중심(0,0)기준 위쪽벽인지 아래쪽벽인지 판단(우상단(좌하단)방향)
				//       [1] 우상단방향으로 벽의 끝인지 판단
				//       [2] 좌하단방향으로 벽의 끝인지 판단
				//    2) 중심(0,0)기준 왼쪽벽인지 오른쪽벽인지 판단(우하단(좌상단)방향)
				//       [1] 우하단방향으로 벽의 끝인지 판단
				//       [2] 좌상단방향으로 벽의 끝인지 판단
				// 3. 벽으로 렌더링해야하고, 꺽이는벽을 렌더링해야하는지 판단
				//    1) 중심(0,0)기준 우상단 꺽이는 벽인지 판단(RT_T_RE와 RB_R_TE가 만나는지 판단)
				//    2) 중심(0,0)기준 좌하단 꺽이는 벽인지 판단(RT_B_LE와 RB_L_BE가 만나는지 판단)

				// (1) 벤트구간 타입체크
				//     1) 우상단(RT_T_RE와 RB_R_TE가 만나기 직전지점)
				if (x == XIndexChkM && y == YIndexChkM)
				{
					NewWallTileInfo.WallBasicType = WallBasicType::BENT_MULTI;
				}
				//     2) 좌하단(RT_B_LE와 RB_L_BE가 만나기 직전지점
				else if (x == XIndexChkP && y == YIndexChkP)
				{
					NewWallTileInfo.WallBasicType = WallBasicType::BENT_SINGLE;
				}
				// (2) 연속벽 및 벽끝 체크
				else
				{
					// 1) RT_T구간 타입체크
					if (x == XIndexChkM)
					{
						if (y % 2 == 0 && x % 2 == 0)
						{
							// [1] 왼쪽끝벽인지 체크
							if (x == XIndexChkM && y == YIndexChkP - 2)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_T_LE;
							}
							// [2] RT_T로 들어오나, RB_L의 위쪽끝벽이 되는경우
							else if (x == XIndexChkM && y == YIndexChkP)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_L_TE;
							}
							// [3] 오른쪽끝벽인지 체크
							else if (x == XIndexChkM && y == YIndexChkM + 2)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_T_RE;
							}
							// [4] 연속벽인지 체크
							else
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_T;
							}
						}
						// [5] 벽이라고판단하지만 렌더링하지않는구간인지 체크
						else
						{
							NewWallTileInfo.WallBasicType = WallBasicType::NONE;
						}
					}
					// 2) RT_B구간 타입체크
					else if (x == XIndexChkP)
					{
						if (y % 2 == 0 && x % 2 == 0)
						{
							// [1] 왼쪽끝벽인지 체크
							if (x == XIndexChkP && y == YIndexChkP - 2)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_B_LE;
							}
							// [2] 오른쪽끝벽인지 체크
							else if (x == XIndexChkP && y == YIndexChkM)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_B_RE;
							}
							// [3] 연속벽인지 체크
							else
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RT_B;
							}
						}
						// [4] 벽이라고판단하지만 렌더링하지않는구간인지 체크
						else
						{
							NewWallTileInfo.WallBasicType = WallBasicType::NONE;
						}
					}
					// 3) RB_L구간 타입체크
					else if (y == YIndexChkP)
					{
						if (y % 2 == 0 && x % 2 == 0)
						{
							// [1] 아래쪽끝벽인지 체크
							if (x == XIndexChkP - 2 && y == YIndexChkP)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_L_BE;
							}
							// [2] 연속벽인지 체크
							else
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_L;
							}
						}
						// [3] 벽이라고판단하지만 렌더링하지않는구간인지 체크
						else
						{
							NewWallTileInfo.WallBasicType = WallBasicType::NONE;
						}
					}
					// 4) RB_R구간 타입체크
					else if (y == YIndexChkM)
					{
						if (y % 2 == 0 && x % 2 == 0)
						{
							// [1] 위쪽끝벽인지 체크
							if (x == XIndexChkM + 2 && y == YIndexChkM)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_R_TE;
							}
							// [2] 아래쪽끝벽인지 체크
							else if (x == XIndexChkP - 2 && y == YIndexChkM)
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_R_BE;
							}
							// [3] 연속벽인지 체크
							else
							{
								NewWallTileInfo.WallBasicType = WallBasicType::RB_R;
							}
						}
						// [4] 벽이라고판단하지만 렌더링하지않는구간인지 체크
						else
						{
							NewWallTileInfo.WallBasicType = WallBasicType::NONE;
						}
					}
					// 5) 위 조건에 모두 맞지않다면 일반타일로 벽이라 판단하지않는벽
					else
					{
						NewWallTileInfo.WallBasicType = WallBasicType::NORMAL;
					}
				}

				// 벽 상세타입 조건체크(타일의 인덱스로 조건체크) - 마을맵 생성기준
				//NORMAL,		// 일반벽
				//DOOR,			// 문
				NewWallTileInfo.WallDetailType = WallDetailType::NORMAL;

				// 기본 렌더링 정보 생성
				NewWallTileInfo.WallTextureName = WallTileTextureName_;
				NewWallTileInfo.WallTileSize = TileSize_;
				NewWallTileInfo.WallRenderSize = WallTileImageSize_;
				NewWallTileInfo.WallRenderPivotPos = WallTileIndexPivotPos_;

				WallTileInfo_[YIndex].push_back(NewWallTileInfo);
			}

			++YIndex;
		}

		// 정보 생성완료 후 레퍼런스렌더링(그리드)
		int YInfoCnt = static_cast<int>(WallTileInfo_.size());
		int XInfoCnt = static_cast<int>(WallTileInfo_[YInfoCnt - 1].size());
		for (int y = 0; y < YInfoCnt; ++y)
		{
			for (int x = 0; x < XInfoCnt; ++x)
			{
				TileIndex Index = TileIndex(WallTileInfo_[y][x].WallIndexX, WallTileInfo_[y][x].WallIndexY);

				GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

				// 벽타입별 이미지
				if (WallTileInfo_[y][x].WallBasicType == WallBasicType::NORMAL)
				{
					// 센터 바닥타일 이미지
					if (Index.Y_ == 0 && Index.X_ == 0)
					{
						Renderer->SetImage("WallGrid_Center.png");
					}
					else // 일반 바닥타일 이미지
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

#pragma region 오브젝트타일관련
		// 벽타일정보 및 그리드생성이 완료되고, 오브젝트타일정보 및 그리드를 생성한다.
		CreateObjectTileInfo();
#pragma endregion
	}
}

void EditorTileMap::CreateObjectTileInfo()
{
	// 벽타일정보가 있다면 생성함(벽타일과 같은기준으로 타일정보를 가진다.)
	if (false == WallTileInfo_.empty())
	{
		// 만약 기존의 오브젝트관련 정보나 타일정보가 남아있다면 제거
		AllClearObjectTile();

		// 벽타일정보 기준으로 똑같이 생성
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

					// WallTile의 인덱스 정보를 그대로 사용한다.
					NewObjectTileInfo.ObjectIndexX = WallTileInfo_[y][x].WallIndexX;
					NewObjectTileInfo.ObjectIndexY = WallTileInfo_[y][x].WallIndexY;

					// Object의 기본 이미지 인덱스는 -1로 설정한다(추후 수정모드에서 오브젝트배치시 선택한 이미지인덱스로 저장된다.)
					NewObjectTileInfo.ObjectImageIndex = -1;

					// 벽이아닌 타일이면 타입은 NORMAL타입을 가진다.
					if (WallTileInfo_[y][x].WallBasicType == WallBasicType::NORMAL)
					{
						NewObjectTileInfo.ObjectBasicType = ObjectBasicType::NORMAL;
					}
					// 벽이거나 벽취급은하지만 렌더링하지않는 타입이라면 오브젝트를 배치할수없는 WALL TYPE을 가진다.
					else
					{
						NewObjectTileInfo.ObjectBasicType = ObjectBasicType::WALL;
					}

					// 기본 렌더링 정보 생성
					NewObjectTileInfo.ObjectTextureName = ObjectTileTextureName_;
					NewObjectTileInfo.ObjectTileSize = TileSize_;
					NewObjectTileInfo.ObjectRenderSize = ObjectTileImageSize_;
					NewObjectTileInfo.ObjectRenderPivotPos = ObjectTileIndexPivotPos_;

					ObjectTileInfo_[y].push_back(NewObjectTileInfo);
				}
			}

			// 정보 생성완료 후 레퍼런스렌더링(그리드)
			int YInfoCnt = static_cast<int>(ObjectTileInfo_.size());
			int XInfoCnt = static_cast<int>(ObjectTileInfo_[YInfoCnt - 1].size());
			for (int y = 0; y < YInfoCnt; ++y)
			{
				for (int x = 0; x < XInfoCnt; ++x)
				{
					TileIndex Index = TileIndex(ObjectTileInfo_[y][x].ObjectIndexX, ObjectTileInfo_[y][x].ObjectIndexY);

					GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

					// 벽타입별 이미지
					if (ObjectTileInfo_[y][x].ObjectBasicType == ObjectBasicType::NORMAL)
					{
						// 센터 바닥타일 이미지
						if (Index.Y_ == 0 && Index.X_ == 0)
						{
							Renderer->SetImage("WallGrid_Center.png");
						}
						else // 일반 바닥타일 이미지
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

// 자동모드 타일텍스쳐 매칭
void EditorTileMap::UpdateFloorTileInfo()
{
	// 바닥타일정보를 읽어들여 이미지 인덱스를 매칭하여 화면에 렌더링한다.
	// 현재 사용자가 선택한 바닥타일 이미지로 컨텍된다.
	// 또한, 수동맵모드에서 이미지 매칭을 수정할 수 있다.
	// 주의!!!! 자동모드에서 현재 지정된 바닥타일의 이미지를 확인!!!!
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

void EditorTileMap::SetTownWallTexture()
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

void EditorTileMap::SetCatacombsWallTexture()
{
}

void EditorTileMap::SetChaosSanctuaryWallTexture()
{
}

void EditorTileMap::UpdateWallTileInfo()
{
	// 벽타일 그리드 정보를 읽어들여 이미지 인덱스를 매칭하여 화면에 렌더링한다.
	// 단, BENT타입의 경우 렌더러 2개를 가지며 또한 각 방향(RT/RB)는 연속된 벽이미지인덱스를 컨텍하여
	// 화면에 렌더링한다.
	// 또한, 수동맵모드에서 이미지 매칭을 수정할 수 있다.
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

			// 벽타입별 이미지
			
			// 1. RT_T
			if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_T_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RT_T_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T_LE)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_T_LE_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RT_T_LE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_T_RE)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_T_RE_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RT_T_RE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			// 2. RT_B
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_B_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RT_B_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B_LE)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_B_LE_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RT_B_LE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT_B_RE)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RT_B_RE_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RT_B_RE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			// 3. RB_L
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_L_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RB_L_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L_TE)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_L_TE_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RB_L_TE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_L_BE)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_L_BE_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RB_L_BE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			// 4. RB_R
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_R_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RB_R_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R_TE)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_R_TE_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RB_R_TE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB_R_BE)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_RB_R_BE_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_RB_R_BE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			// 5. BENT_SINGLE
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_SINGLE)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_BENT_SINGLE_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				WallTiles.Tiles1_->SetIndex(Wall_BENT_SINGLE_ImageIndex_);
				WallTiles_.insert(std::make_pair(Index.Index_, WallTiles));
			}
			// 6. BENT_MULTI
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_MULTI)
			{
				// 정보 변경 후
				WallTileInfo_[y][x].WallTile1ImageIndex = Wall_BENT_MULTI1_ImageIndex_;

				// 현재 렌더러 정보 셋팅
				
				// BENT_MULTI는 렌더러 2개를 가진다.
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
			// 타입을 찾을수 없으면 생성된 렌더러 바로 죽임
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

void EditorTileMap::AutoModeTileAllClear()
{
	// 자동으로 생성한 맵 정보 및 그리드, 타일렌더 모두 클리어
	AllClear();
}

#pragma endregion

#pragma region 정보/렌더링정보삭제기능
void EditorTileMap::AllClear()
{
	// 바닥타일관련 클리어
	AllClearFloorTile();

	// 벽타일관련 클리어
	AllClearWallTile();

	// 오브젝트타일관련 클리어
	AllClearObjectTile();
}

void EditorTileMap::AllClearFloorTile()
{
	// 타일정보 클리어
	AllClearFloorTileInfo();

	// 타일렌더링정보 클리어
	AllClearFloorTileMapRenderer();
}

void EditorTileMap::AllClearFloorTileInfo()
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

void EditorTileMap::AllClearFloorTileMapRenderer()
{
	// 타일
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesStartIter = FloorTiles_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesEndIter = FloorTiles_.end();
	for (; TilesStartIter != TilesEndIter; ++TilesStartIter)
	{
		// 세컨드 데스처리
		(*TilesStartIter).second->Death();
	}
	FloorTiles_.clear();

	// 그리드
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsStartIter = FloorGrides_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsEndIter = FloorGrides_.end();
	for (; GridsStartIter != GridsEndIter; ++GridsStartIter)
	{
		// 세컨드 데스처리
		(*GridsStartIter).second->Death();
	}
	FloorGrides_.clear();

	// ON/OFF Flag해제
	FloorGridesActive_ = true;
}

void EditorTileMap::AllClearWallTile()
{
	// 타일정보 클리어
	AllClearWallTileInfo();

	// 타일렌더링정보 클리어
	AllClearWallTileMapRenderer();
}

void EditorTileMap::AllClearWallTileInfo()
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

void EditorTileMap::AllClearWallTileMapRenderer()
{
	// 타일
	std::unordered_map<__int64, WallTileRender>::iterator TilesStartIter = WallTiles_.begin();
	std::unordered_map<__int64, WallTileRender>::iterator TilesEndIter = WallTiles_.end();
	for (; TilesStartIter != TilesEndIter; ++TilesStartIter)
	{
		// 세컨드 데스처리
		(*TilesStartIter).second.Tiles1_->Death();

		if (nullptr != (*TilesStartIter).second.Tiles2_)
		{
			(*TilesStartIter).second.Tiles2_->Death();
		}
	}
	WallTiles_.clear();

	// 그리드
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsStartIter = WallGrides_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsEndIter = WallGrides_.end();
	for (; GridsStartIter != GridsEndIter; ++GridsStartIter)
	{
		// 세컨드 데스처리
		(*GridsStartIter).second->Death();
	}
	WallGrides_.clear();

	// ON/OFF Flag해제
	WallGridesActive_ = true;
}

void EditorTileMap::AllClearObjectTile()
{
	// 타일정보 클리어
	AllClearObjectTileInfo();

	// 타일렌더링정보 클리어
	AllClearObjectTileMapRenderer();
}

void EditorTileMap::AllClearObjectTileInfo()
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

void EditorTileMap::AllClearObjectTileMapRenderer()
{
	// 타일
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesStartIter = ObjectTiles_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesEndIter = ObjectTiles_.end();
	for (; TilesStartIter != TilesEndIter; ++TilesStartIter)
	{
		// 세컨드 데스처리
		(*TilesStartIter).second->Death();
	}
	ObjectTiles_.clear();

	// 그리드
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsStartIter = ObjectGrides_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GridsEndIter = ObjectGrides_.end();
	for (; GridsStartIter != GridsEndIter; ++GridsStartIter)
	{
		// 세컨드 데스처리
		(*GridsStartIter).second->Death();
	}
	ObjectGrides_.clear();

	// ON/OFF Flag해제
	ObjectGridesActive_ = false;
}

#pragma endregion

void EditorTileMap::MapFileSave(const std::string& _FileName)
{
	// 파일생성 위치로 디렉터리 이동
	if (true == _FileName.empty())
	{
		return;
	}

	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("MapFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += _FileName;
	FullPath += ".dat";

	// 파일 열기
	GameEngineFile pFile = GameEngineFile(FullPath, "wb");
	
	// 바닥타일정보 저장
	int FloorYIndex = static_cast<int>(FloorTileInfo_.size());
	if (0 < FloorYIndex)
	{
		int FloorXIndex = static_cast<int>(FloorTileInfo_[FloorYIndex - 1].size());

		// Y인덱스 저장
		pFile.Write(FloorYIndex);

		// X인덱스 저장
		pFile.Write(FloorXIndex);

		for (int y = 0; y < FloorYIndex; ++y)
		{
			for (int x = 0; x < FloorXIndex; ++x)
			{
				// 인덱스 정보
				pFile.Write(FloorTileInfo_[y][x].FloorIndexX);
				pFile.Write(FloorTileInfo_[y][x].FloorIndexY);
				pFile.Write(FloorTileInfo_[y][x].FloorImageIndex);

				// 렌더링정보
				pFile.Write(FloorTileInfo_[y][x].FloorTextureName);

				// float4 정보

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

	// 벽타일정보 저장
	int WallYIndex = static_cast<int>(WallTileInfo_.size());
	if (0 < WallYIndex)
	{
		int WallXIndex = static_cast<int>(WallTileInfo_[WallYIndex - 1].size());

		// Y인덱스 저장
		pFile.Write(WallYIndex);

		// X인덱스 저장
		pFile.Write(WallXIndex);

		for (int y = 0; y < WallYIndex; ++y)
		{
			for (int x = 0; x < WallXIndex; ++x)
			{
				// 인덱스 및 타입정보
				pFile.Write(WallTileInfo_[y][x].WallIndexX);
				pFile.Write(WallTileInfo_[y][x].WallIndexY);
				pFile.Write(WallTileInfo_[y][x].WallTile1ImageIndex);
				pFile.Write(WallTileInfo_[y][x].WallTile2ImageIndex);
				pFile.Write(static_cast<int>(WallTileInfo_[y][x].WallBasicType));
				pFile.Write(static_cast<int>(WallTileInfo_[y][x].WallDetailType));

				// 렌더링 정보
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

	// 오브젝트타일정보 저장
	int ObjectYIndex = static_cast<int>(ObjectTileInfo_.size());
	if (0 < ObjectYIndex)
	{
		int ObjectXIndex = static_cast<int>(ObjectTileInfo_[ObjectYIndex - 1].size());

		// Y인덱스 저장
		pFile.Write(ObjectYIndex);

		// X인덱스 저장
		pFile.Write(ObjectXIndex);

		for (int y = 0; y < ObjectYIndex; ++y)
		{
			for (int x = 0; x < ObjectXIndex; ++x)
			{
				// 인덱스 및 타입정보
				pFile.Write(ObjectTileInfo_[y][x].ObjectIndexX);
				pFile.Write(ObjectTileInfo_[y][x].ObjectIndexY);
				pFile.Write(ObjectTileInfo_[y][x].ObjectImageIndex);
				pFile.Write(static_cast<int>(ObjectTileInfo_[y][x].ObjectBasicType));

				// 렌더링 정보
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

	// 파일종료
	pFile.Close();
}

void EditorTileMap::MapFileLoad(const std::string& _FileName)
{
	// 정보로드전 모든 데이터 및 렌더러 클리어
	AllClear();

	// 파일로드 위치로 디렉터리 이동
	GameEngineDirectory DataFileDir;
	DataFileDir.MoveParent("DirectX");
	DataFileDir.MoveChild("Resources");
	DataFileDir.MoveChild("MapFile");
	std::string FullPath = DataFileDir.GetFullPath();
	FullPath += "\\";
	FullPath += _FileName;
	FullPath += ".dat";

	// 파일 열기
	GameEngineFile pFile = GameEngineFile(FullPath, "rb");

	// 바닥타일정보 로드
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
			// 인덱스정보
			pFile.Read(FloorTileInfo_[y][x].FloorIndexX);
			pFile.Read(FloorTileInfo_[y][x].FloorIndexY);
			pFile.Read(FloorTileInfo_[y][x].FloorImageIndex);

			// 렌더링 정보
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
	
	// 벽타일정보 로드
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
			// 인덱스 및 타입정보
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

			// 렌더링 정보
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

	// 오브젝트타일정보 로드
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
			// 인덱스 및 타입정보
			pFile.Read(ObjectTileInfo_[y][x].ObjectIndexX);
			pFile.Read(ObjectTileInfo_[y][x].ObjectIndexY);
			pFile.Read(ObjectTileInfo_[y][x].ObjectImageIndex);

			int ObjectBasicType_ = 0;
			pFile.Read(ObjectBasicType_);
			ObjectTileInfo_[y][x].ObjectBasicType = static_cast<ObjectBasicType>(ObjectBasicType_);

			// 렌더링 정보
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
			ObjectTileInfo_[y][x].ObjectRenderPivotPos = float4(static_cast<float>(ObjectRenderPivotPosX), static_cast<float>(ObjectRenderPivotPosY), static_cast<float>(ObjectRenderPivotPosZ));
		}
	}

	pFile.Close();

	// 모든 정보 로딩완료시 화면에 렌더링하는 렌더러 생성
	CreatedAfterLoading();
}

void EditorTileMap::CreatedAfterLoading()
{
	// 모든 정보 로딩완료시 화면에 렌더링하는 렌더러 생성

	// 그리드 생성
	CreatedAfterLoading_FloorGrides();
	CreatedAfterLoading_WallGrides();
	CreatedAfterLoading_ObjectGrides();

	// 타일 생성
	CreatedAfterLoading_FloorTiles();
	CreatedAfterLoading_WallTiles();
	CreatedAfterLoading_ObjectTiles();
}

void EditorTileMap::CreatedAfterLoading_FloorGrides()
{
	// 바닥 타일
	int YInfoCnt = static_cast<int>(FloorTileInfo_.size());
	int XInfoCnt = static_cast<int>(FloorTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(FloorTileInfo_[y][x].FloorIndexX, FloorTileInfo_[y][x].FloorIndexY);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			// 센터 바닥타일 이미지
			if (Index.Y_ == 0 && Index.X_ == 0)
			{
				Renderer->SetImage("FloorGrid_Center.png");
			}
			else // 일반 바닥타일 이미지
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

void EditorTileMap::CreatedAfterLoading_WallGrides()
{
	// 벽 타일
	int YInfoCnt = static_cast<int>(WallTileInfo_.size());
	int XInfoCnt = static_cast<int>(WallTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(WallTileInfo_[y][x].WallIndexX, WallTileInfo_[y][x].WallIndexY);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			// 벽타입별 이미지
			if (WallTileInfo_[y][x].WallBasicType == WallBasicType::NORMAL)
			{
				// 센터 바닥타일 이미지
				if (Index.Y_ == 0 && Index.X_ == 0)
				{
					Renderer->SetImage("WallGrid_Center.png");
				}
				else // 일반 바닥타일 이미지
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

void EditorTileMap::CreatedAfterLoading_ObjectGrides()
{
	// 오브젝트 타일
	int YInfoCnt = static_cast<int>(ObjectTileInfo_.size());
	int XInfoCnt = static_cast<int>(ObjectTileInfo_[YInfoCnt - 1].size());
	for (int y = 0; y < YInfoCnt; ++y)
	{
		for (int x = 0; x < XInfoCnt; ++x)
		{
			TileIndex Index = TileIndex(ObjectTileInfo_[y][x].ObjectIndexX, ObjectTileInfo_[y][x].ObjectIndexY);

			GameEngineTileMapRenderer* Renderer = CreateTransformComponent<GameEngineTileMapRenderer>();

			// 벽타입별 이미지
			if (ObjectTileInfo_[y][x].ObjectBasicType == ObjectBasicType::NORMAL)
			{
				// 센터 바닥타일 이미지
				if (Index.Y_ == 0 && Index.X_ == 0)
				{
					Renderer->SetImage("WallGrid_Center.png");
				}
				else // 일반 바닥타일 이미지
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

void EditorTileMap::CreatedAfterLoading_FloorTiles()
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

void EditorTileMap::CreatedAfterLoading_WallTiles()
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

			// 벽타입별 이미지
			// 단, Normal, None이면 렌더러를 생성하지않음
			if (WallTileInfo_[y][x].WallBasicType == WallBasicType::NONE || WallTileInfo_[y][x].WallBasicType == WallBasicType::NORMAL)
			{
				WallTiles.Tiles1_->Death();
				if (nullptr != WallTiles.Tiles2_)
				{
					WallTiles.Tiles2_->Death();
				}
			}
			// BENT_MULTI이면 렌더러 2개
			else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT_MULTI)
			{
				WallTiles.Tiles1_->SetIndex(WallTileInfo_[y][x].WallTile1ImageIndex);

				WallTiles.Tiles2_ = CreateTransformComponent<GameEngineTileMapRenderer>();
				WallTiles.Tiles2_->SetImage(WallTileInfo_[y][x].WallTextureName);
				WallTiles.Tiles2_->GetTransform()->SetLocalScaling(WallTileInfo_[y][x].WallRenderSize);
				WallTiles.Tiles2_->GetTransform()->SetLocalPosition(WallTileInfo_[y][x].WallRenderPivotPos + Pos);
				WallTiles.Tiles2_->GetTransform()->SetLocalZOrder(-3.f);
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

void EditorTileMap::CreatedAfterLoading_ObjectTiles()
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

			// -1 == ObjectTileInfo_[y][x].ObjectImageIndex이면 오브젝트가 배치되어있지않은 타일로 판단
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
