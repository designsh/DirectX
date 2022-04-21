#include "PreCompile.h"
#include "MapEditorLevel.h"

#include "CreateTileMapWindow.h"
#include "TileMap.h"
#include "UserGame.h"

#include <GameEngine/CameraComponent.h>
#include <GameEngine/CameraActor.h>

#include <GameEngine/GameEngineTextureManager.h>
#include <GameEngine/GameEngineTexture.h>

bool MapEditorLevel::ResourceLoadEndCheck = false;

MapEditorLevel::MapEditorLevel() :
	TileMap_(nullptr),
	TileMapWindow_(nullptr),
	MoveSpeed_(1000.f)
{
}

MapEditorLevel::~MapEditorLevel()
{
}

void MapEditorLevel::CreateLevelActor()
{
#pragma region TileTexture Cutting
	GameEngineTexture* FloorTile = GameEngineTextureManager::GetInst().Find("Town_Floor.png");
	FloorTile->Cut(5, 37);
	GameEngineTexture* WallTile = GameEngineTextureManager::GetInst().Find("Town_Wall.png");
	WallTile->Cut(31, 1);
	GameEngineTexture* ObjectTile = GameEngineTextureManager::GetInst().Find("Town_Object.png");
	ObjectTile->Cut(53, 1);

	// 일반그리드
	GameEngineTexture* FloorGridNor = GameEngineTextureManager::GetInst().Find("FloorGrid_Normal.png");
	FloorGridNor->Cut(1, 1);
	GameEngineTexture* WallGridNor = GameEngineTextureManager::GetInst().Find("WallGrid_Normal.png");
	WallGridNor->Cut(1, 1);

	// 센터그리드
	GameEngineTexture* FloorGridCenter = GameEngineTextureManager::GetInst().Find("FloorGrid_Center.png");
	FloorGridCenter->Cut(1, 1);
	GameEngineTexture* WallGridCenter = GameEngineTextureManager::GetInst().Find("WallGrid_Center.png");
	WallGridCenter->Cut(1, 1);

	// 특수그리드
	// NONE
	GameEngineTexture* WallGridNone = GameEngineTextureManager::GetInst().Find("WallGrid_None.png");
	WallGridNone->Cut(1, 1);

	// RT_T
	GameEngineTexture* WallGridRT_T = GameEngineTextureManager::GetInst().Find("WallGrid_RT_T.png");
	WallGridRT_T->Cut(1, 1);
	GameEngineTexture* WallGridRT_T_LE = GameEngineTextureManager::GetInst().Find("WallGrid_RT_T_LE.png");
	WallGridRT_T_LE->Cut(1, 1);
	GameEngineTexture* WallGridRT_T_RE = GameEngineTextureManager::GetInst().Find("WallGrid_RT_T_RE.png");
	WallGridRT_T_RE->Cut(1, 1);

	// RT_B
	GameEngineTexture* WallGridRT_B = GameEngineTextureManager::GetInst().Find("WallGrid_RT_B.png");
	WallGridRT_B->Cut(1, 1);
	GameEngineTexture* WallGridRT_B_LE = GameEngineTextureManager::GetInst().Find("WallGrid_RT_B_LE.png");
	WallGridRT_B_LE->Cut(1, 1);
	GameEngineTexture* WallGridRT_B_RE = GameEngineTextureManager::GetInst().Find("WallGrid_RT_B_RE.png");
	WallGridRT_B_RE->Cut(1, 1);

	// RB_L
	GameEngineTexture* WallGridRB_L = GameEngineTextureManager::GetInst().Find("WallGrid_RB_L.png");
	WallGridRB_L->Cut(1, 1);
	GameEngineTexture* WallGridRB_L_TE = GameEngineTextureManager::GetInst().Find("WallGrid_RB_L_TE.png");
	WallGridRB_L_TE->Cut(1, 1);
	GameEngineTexture* WallGridRB_L_BE = GameEngineTextureManager::GetInst().Find("WallGrid_RB_L_BE.png");
	WallGridRB_L_BE->Cut(1, 1);

	// RB_R
	GameEngineTexture* WallGridRB_R = GameEngineTextureManager::GetInst().Find("WallGrid_RB_R.png");
	WallGridRB_R->Cut(1, 1);
	GameEngineTexture* WallGridRB_R_TE = GameEngineTextureManager::GetInst().Find("WallGrid_RB_R_TE.png");
	WallGridRB_R_TE->Cut(1, 1);
	GameEngineTexture* WallGridRB_R_BE = GameEngineTextureManager::GetInst().Find("WallGrid_RB_R_BE.png");
	WallGridRB_R_BE->Cut(1, 1);

	// BENT
	GameEngineTexture* WallGridBentMulti = GameEngineTextureManager::GetInst().Find("WallGrid_Bent_Multi.png");
	WallGridBentMulti->Cut(1, 1);
	GameEngineTexture* WallGridBentSingle = GameEngineTextureManager::GetInst().Find("WallGrid_Bent_Single.png");
	WallGridBentSingle->Cut(1, 1);

#pragma endregion

#pragma region IsoTileMap Create & Setting
	TileMap_ = CreateActor<TileMap>();
	TileMapWindow_->TileMap_ = TileMap_;
	TileMap_->SetFloorTileTexture("Town_Floor.png");
	TileMap_->SetWallTileTexture("Town_Wall.png");
	TileMap_->SetObjectTileTexture("Town_Object.png");
#pragma endregion
}

void MapEditorLevel::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("CreateTileMapWindow");
	if (nullptr != Ptr)
	{
		Ptr->Off();
	}
}

void MapEditorLevel::LevelChangeStartEvent(GameEngineLevel* _PrevLevel)
{
	GameEngineGUIWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow("CreateTileMapWindow");
	if (nullptr != Ptr)
	{
		Ptr->On();
	}
}

void MapEditorLevel::LevelStart()
{
#pragma region SetMainCamera
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCameraActor()->GetTransform()->SetLocalPosition(float4(0.f, 0.f, -100.f));
#pragma endregion

#pragma region Editor Window
	// CreateTileMap Window
	TileMapWindow_ = GameEngineGUI::GetInst()->CreateGUIWindow<CreateTileMapWindow>("CreateTileMapWindow");
	TileMapWindow_->Off();
#pragma endregion

#pragma region CreateKey
	if (false == GameEngineInput::GetInst().IsKey("CameraUp"))
	{
		GameEngineInput::GetInst().CreateKey("CameraUp", VK_UP);
	}

	if (false == GameEngineInput::GetInst().IsKey("CameraDown"))
	{
		GameEngineInput::GetInst().CreateKey("CameraDown", VK_DOWN);
	}

	if (false == GameEngineInput::GetInst().IsKey("CameraLeft"))
	{
		GameEngineInput::GetInst().CreateKey("CameraLeft", VK_LEFT);
	}

	if (false == GameEngineInput::GetInst().IsKey("CameraRight"))
	{
		GameEngineInput::GetInst().CreateKey("CameraRight", VK_RIGHT);
	}
#pragma endregion

#pragma region 테스트키
	//// 테스트키 생성
	//if (false == GameEngineInput::GetInst().IsKey("FreeCamera"))
	//{
	//	GameEngineInput::GetInst().CreateKey("FreeCamera", 'p');
	//}
#pragma endregion

#pragma region 그리드 ON/OFF
	// 바닥타일 그리드 On/Off
	if (false == GameEngineInput::GetInst().IsKey("FloorGrideSwitching"))
	{
		GameEngineInput::GetInst().CreateKey("FloorGrideSwitching", 'i');
	}

	// 벽타일 그리드 On/Off
	if (false == GameEngineInput::GetInst().IsKey("WallGrideSwitching"))
	{
		GameEngineInput::GetInst().CreateKey("WallGrideSwitching", 'o');
	}

	// 오브젝트타일 그리드 On/Off
	if (false == GameEngineInput::GetInst().IsKey("ObjectGrideSwitching"))
	{
		GameEngineInput::GetInst().CreateKey("ObjectGrideSwitching", 'p');
	}
#pragma endregion
}

void MapEditorLevel::LevelUpdate(float _DeltaTime)
{
#pragma region 그리드 ON/OFF
	// 바닥타일 그리드 On/Off
	if (true == GameEngineInput::GetInst().Down("FloorGrideSwitching"))
	{
		if (nullptr != TileMap_)
		{
			TileMap_->FloorGridesSwitching();
		}
	}

	// 벽타일 그리드 On/Off
	if (true == GameEngineInput::GetInst().Down("WallGrideSwitching"))
	{
		if (nullptr != TileMap_)
		{
			TileMap_->WallGridesSwitching();
		}
	}

	// 오브젝트타일 그리드 On/Off
	if (true == GameEngineInput::GetInst().Down("ObjectGrideSwitching"))
	{
		if (nullptr != TileMap_)
		{
			TileMap_->ObjectGridesSwitching();
		}
	}
#pragma endregion

#pragma region ResourceLoadingEndCheck
	// 이미지 로딩이 완료되면 액터생성
	if (false == ResourceLoadEndCheck && 0 >= UserGame::LoadingImageFolder)
	{
		CreateLevelActor();
		ResourceLoadEndCheck = true;
	}
#pragma endregion

	if (true == GameEngineWindow::GetInst().IsWindowRangeOut(GameEngineInput::GetInst().GetMousePos()))
	{
		return;
	}

#pragma region 카메라이동 키체크
	
	if (true == GameEngineInput::GetInst().Press("CameraUp"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(float4::UP * MoveSpeed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst().Press("CameraDown"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(float4::DOWN * MoveSpeed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst().Press("CameraLeft"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(float4::LEFT * MoveSpeed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst().Press("CameraRight"))
	{
		GetMainCameraActor()->GetTransform()->SetWorldMove(float4::RIGHT * MoveSpeed_ * _DeltaTime);
	}

#pragma endregion

#pragma region 매뉴얼맵생성모드관련
	// 타일생성
	if (true == GameEngineInput::GetInst().Press("MouseLButton"))
	{
		CreateTileMapWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow<CreateTileMapWindow>("CreateTileMapWindow");

		float4 WindowPos = GameEngineInput::GetInst().GetMousePos();

		if (0 > WindowPos.x)
		{
			return;
		}

		if (0 > WindowPos.y)
		{
			return;
		}

		if (WindowPos.x > GameEngineWindow::GetInst().GetSize().x)
		{
			return;
		}

		if (WindowPos.y > GameEngineWindow::GetInst().GetSize().y)
		{
			return;
		}

		// 카메라 이동을 더한다.
		float4 TilePos = GameEngineInput::GetInst().GetMouse3DPos();
		float4 CameraPos = GetMainCamera()->GetTransform()->GetWorldPosition();
		switch (Ptr->SelectMode_)
		{
			case TileType::FLOOR:
			{
				if (FloorRenderingType::TILE == TileMap_->GetCurFloorRenderType())
				{
					TileMap_->SetFloorTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				else
				{
					TileMap_->SetFloorGird((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				break;
			}
			case TileType::WALL:
			{
				if (WallRenderingType::TILE1 == TileMap_->GetCurWallRenderType() || WallRenderingType::TILE2 == TileMap_->GetCurWallRenderType())
				{
					TileMap_->SetWallTile((TilePos* GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				else
				{
					TileMap_->SetWallGird((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				break;
			}
			case TileType::OBJECT:
			{
				if (ObjectRenderingType::TILE == TileMap_->GetCurObjectRenderType())
				{
					TileMap_->SetObjectTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				else
				{
					TileMap_->SetObjectGird((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos, Ptr->SelectTileIndex_);
				}
				break;
			}
		}
	}

	// 타일제거
	if (true == GameEngineInput::GetInst().Press("MouseRButton"))
	{
		CreateTileMapWindow* Ptr = GameEngineGUI::GetInst()->FindGUIWindow<CreateTileMapWindow>("CreateTileMapWindow");
		float4 WindowPos = GameEngineInput::GetInst().GetMousePos();

		if (0 > WindowPos.x)
		{
			return;
		}

		if (0 > WindowPos.y)
		{
			return;
		}

		if (WindowPos.x > GameEngineWindow::GetInst().GetSize().x)
		{
			return;
		}

		if (WindowPos.y > GameEngineWindow::GetInst().GetSize().y)
		{
			return;
		}

		// 해당 위치의 인덱스 타일 목록에서 제거
		float4 TilePos = GameEngineInput::GetInst().GetMouse3DPos();
		float4 CameraPos = GetMainCamera()->GetTransform()->GetWorldPosition();
		switch (Ptr->SelectMode_)
		{
			case TileType::FLOOR:
			{
				if (FloorRenderingType::TILE == TileMap_->GetCurFloorRenderType())
				{
					TileMap_->DelFloorTile((TilePos* GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				else
				{
					TileMap_->DelFloorGird((TilePos* GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				break;
			}
			case TileType::WALL:
			{
				if (WallRenderingType::TILE1 == TileMap_->GetCurWallRenderType() || WallRenderingType::TILE2 == TileMap_->GetCurWallRenderType())
				{
					TileMap_->DelWallTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				else
				{
					TileMap_->DelWallGird((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				break;
			}
			case TileType::OBJECT:
			{
				if (ObjectRenderingType::TILE == TileMap_->GetCurObjectRenderType())
				{
					TileMap_->DelObjectTile((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				else
				{
					TileMap_->DelObjectGird((TilePos * GetMainCamera()->GetZoomValue()) + CameraPos);
				}
				break;
			}
		}
	}

#pragma endregion

#pragma region 자동맵생성모드관련





#pragma endregion

#pragma region 랜덤맵생성모드관련







#pragma endregion

#pragma region 테스트키
	if (true == GameEngineInput::GetInst().Down("FreeCamera"))
	{
		//GetMainCameraActor()->FreeCameraModeSwitch();
	}
#pragma endregion
}
