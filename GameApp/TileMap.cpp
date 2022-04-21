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

}

#pragma region 편의기능관련

void TileMap::SetTileRenderingMode(TileRenderingType _RenderingType)
{
	TileRenderingType_ = _RenderingType;
}

#pragma endregion

#pragma region IMGUI표시용

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
	// 동일한 타일인덱스가 존재하면 해당 타일인덱스의 타일이미지를 현재 선택된 이미지로 변경
	if (FloorTiles_.end() != FloorTiles_.find(_Index.Index_))
	{
		FloorTiles_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);
	}

	if (FloorGrides_.end() != FloorGrides_.find(_Index.Index_))
	{
		FloorGrides_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);
		return;
	}

	float4 Pos = float4::ZERO;
	Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHalf_.x;
	Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHalf_.y;

	GameEngineTileMapRenderer* FloorTileRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
	GameEngineTileMapRenderer* FloorGridRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();

	// 렌더링 타입 체크
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
	// 동일한 타일인덱스가 존재하면 해당 타일인덱스의 타일이미지를 현재 선택된 이미지로 변경
	if (WallTiles_.end() != WallTiles_.find(_Index.Index_))
	{
		WallTiles_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);
	}

	if (WallGrides_.end() != WallGrides_.find(_Index.Index_))
	{
		WallGrides_.find(_Index.Index_)->second->SetIndex(CurTileIndex_);
		return;
	}

	float4 Pos = float4::ZERO;
	Pos.x = (_Index.X_ - _Index.Y_) * TileSizeHHalf_.x;
	Pos.y = (_Index.X_ + _Index.Y_) * -TileSizeHHalf_.y;

	GameEngineTileMapRenderer* WallTileRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();
	GameEngineTileMapRenderer* WallGridRenderer = CreateTransformComponent<GameEngineTileMapRenderer>();

	// 렌더링 타입 체크
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

	// 타일
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TileFindIter = FloorTiles_.find(Index.Index_);
	if (FloorTiles_.end() != TileFindIter)
	{
		TileFindIter->second->Death();
		FloorTiles_.erase(TileFindIter);
	}

	// 그리드
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

	// 타일
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TileFindIter = WallTiles_.find(Index.Index_);
	if (WallTiles_.end() != TileFindIter)
	{
		TileFindIter->second->Death();
		WallTiles_.erase(TileFindIter);
	}

	// 그리드
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator GirdFindIter = WallGrides_.find(Index.Index_);
	if (WallGrides_.end() != GirdFindIter)
	{
		GirdFindIter->second->Death();
		WallGrides_.erase(GirdFindIter);
	}
}

#pragma endregion

#pragma region 자동모드관련

// 자동모드 정보생성
void TileMap::CreateFloorTileInfo(int _HeightTileCount, int _WidthTileCount)
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
			NewFloorTileInfo.FloorImageIndex = 0;	// 초기 0으로 셋팅(추후 갱신때 각 이미지타일 갱신)
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

void TileMap::CreateWallTileInfo()
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
				NewWallTileInfo.WallImageIndex = 0; // 초기 0으로 셋팅(추후 갱신때 각 벽타입을체크하여 이미지타일 결정)

				// 벽 기본타입 조건체크(타일의 인덱스로 조건체크) - 마을맵 생성기준
				//NONE,			// 벽으로판단하나, 렌더링없음
				//NORMAL,		// 벽으로판단하지않고, 렌더링없음
				//RT,			// 우상단(좌하단)방향
				//RB,			// 우하단(좌상단)방향
				//BENT,			// 꺽이는벽

				// 1. 벽으로 렌더링해야하는 구간인지 아닌지 판단
				// 2. 벽으로 렌더링해야한다면 우상단방향인지 우하단방향의 벽인지 판단
				// 3. 벽으로 렌더링해야하고, 꺽이는벽을 렌더링해야하는지 판단
				if ((x == XIndexChkP && y == YIndexChkP) || (x == XIndexChkM && y == YIndexChkM) || (x == XIndexChkP && y == YIndexChkM) || (x == XIndexChkM && y == YIndexChkP))
				{
					NewWallTileInfo.WallBasicType = WallBasicType::BENT;
				}
				else
				{
					if (x == XIndexChkP || x == XIndexChkM)
					{
						if (y % 2 == 0 && x % 2 == 0)
						{
							NewWallTileInfo.WallBasicType = WallBasicType::RT;
						}
						else
						{
							NewWallTileInfo.WallBasicType = WallBasicType::NONE;
						}
					}
					else if (y == YIndexChkM || y == YIndexChkP)
					{
						if (y % 2 == 0 && x % 2 == 0)
						{
							NewWallTileInfo.WallBasicType = WallBasicType::RB;
						}
						else
						{
							NewWallTileInfo.WallBasicType = WallBasicType::NONE;
						}
					}
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
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RT)
				{
					Renderer->SetImage("WallGrid_RT.png");
				}
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::RB)
				{
					Renderer->SetImage("WallGrid_RB.png");
				}
				else if (WallTileInfo_[y][x].WallBasicType == WallBasicType::BENT)
				{
					Renderer->SetImage("WallGrid_Bent.png");
				}
				else
				{
					Renderer->SetImage("WallGrid_None.png");
				}

				float4 Pos = float4::ZERO;
				//Pos.x = (Index.X_ - Index.Y_) * -WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().x;
				Pos.x = (Index.X_ - Index.Y_) * WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().x;
				Pos.y = (Index.X_ + Index.Y_) * -WallTileInfo_[y][x].WallTileSize.halffloat4().halffloat4().y;

				Renderer->GetTransform()->SetLocalScaling(WallTileInfo_[y][x].WallTileSize.halffloat4());
				Renderer->GetTransform()->SetLocalPosition(Pos);
				Renderer->GetTransform()->SetLocalZOrder(-3.f);
				WallGrides_.insert(std::make_pair(Index.Index_, Renderer));
			}
		}

		int a = 0;
	}
}

// 자동모드 타일텍스쳐 매칭
void TileMap::UpdateFloorTileInfo(int _DefaultTileIndex)
{

}

void TileMap::UpdateWallTileInfo(int _DefaultTileIndex)
{

}

#pragma endregion

#pragma region 정보/렌더링정보삭제기능
void TileMap::AllClear()
{
	// 바닥타일관련 클리어
	AllClearFloorTile();

	// 벽타일관련 클리어
	AllClearWallTileInfo();
	AllClearWallTileMapRenderer();
}

void TileMap::AllClearFloorTile()
{
	// 타일정보 클리어
	AllClearFloorTileInfo();

	// 타일렌더링정보 클리어
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
}

void TileMap::AllClearWallTile()
{
	// 타일정보 클리어
	AllClearWallTileInfo();

	// 타일렌더링정보 클리어
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
	// 타일
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesStartIter = WallTiles_.begin();
	std::unordered_map<__int64, GameEngineTileMapRenderer*>::iterator TilesEndIter = WallTiles_.end();
	for (; TilesStartIter != TilesEndIter; ++TilesStartIter)
	{
		// 세컨드 데스처리
		(*TilesStartIter).second->Death();
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
}
#pragma endregion

