#include "PreCompile.h"
#include "Portal.h"

#include <GameEngineBase/GameEngineSoundManager.h>
#include <GameEngineBase/GameEngineSoundPlayer.h>

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"
#include "UserGame.h"
#include "MainPlayer.h"

#include "FixedTileMap_Common.h"
#include "TownMap.h"
#include "CatacombsMap.h"

Portal::Portal() :
	PortalType_(PortalType::TOWN),
	InteractionFlag_(false),
	NextLevel_(nullptr),
	PortalEntityRenderer_(nullptr),
	PortalShadowRenderer_(nullptr),
	PortalCollision_(nullptr)
{
	// 생성과 동시 현재 레벨 결정
	CurLevel_ = GetLevel();
}

Portal::~Portal()
{
}

void Portal::Start()
{
	// Image Cutting

	// 일반포탈(파란색)
	// NorPortal_Entity_Open.png
	// NorPortal_Shadow_Open.png
	// NorPortal_Entity_Idle.png
	// NorPortal_Shadow_Idle.png
	GameEngineTexture* NorPortal_Entity_Open = GameEngineTextureManager::GetInst().Find("NorPortal_Entity_Open.png");
	NorPortal_Entity_Open->Cut(15, 1);

	GameEngineTexture* NorPortal_Shadow_Open = GameEngineTextureManager::GetInst().Find("NorPortal_Shadow_Open.png");
	NorPortal_Shadow_Open->Cut(15, 1);

	GameEngineTexture* NorPortal_Entity_Idle = GameEngineTextureManager::GetInst().Find("NorPortal_Entity_Idle.png");
	NorPortal_Entity_Idle->Cut(15, 1);

	GameEngineTexture* NorPortal_Shadow_Idle = GameEngineTextureManager::GetInst().Find("NorPortal_Shadow_Idle.png");
	NorPortal_Shadow_Idle->Cut(15, 1);


	// 보스포탈(붉은색)
	// BossPortal_Entity_Open.png
	// BossPortal_Shadow_Open.png
	// BossPortal_Entity_Idle.png
	// BossPortal_Shadow_Idle.png
	GameEngineTexture* BossPortal_Entity_Open = GameEngineTextureManager::GetInst().Find("BossPortal_Entity_Open.png");
	BossPortal_Entity_Open->Cut(15, 1);

	GameEngineTexture* BossPortal_Shadow_Open = GameEngineTextureManager::GetInst().Find("BossPortal_Shadow_Open.png");
	BossPortal_Shadow_Open->Cut(15, 1);

	GameEngineTexture* BossPortal_Entity_Idle = GameEngineTextureManager::GetInst().Find("BossPortal_Entity_Idle.png");
	BossPortal_Entity_Idle->Cut(15, 1);

	GameEngineTexture* BossPortal_Shadow_Idle = GameEngineTextureManager::GetInst().Find("BossPortal_Shadow_Idle.png");
	BossPortal_Shadow_Idle->Cut(15, 1);
}

void Portal::Update(float _DeltaTime)
{
	if (nullptr != PortalCollision_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(PortalCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		if (false == InteractionFlag_)
		{
			float4 MyPos = GetTransform()->GetLocalPosition();
			float4 CamPos = GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition();
			PortalCollision_->GetTransform()->SetWorldPosition(MyPos - CamPos);
		}

		// 마우스가 해당 포탈을 클릭한 상태에서 
		PortalCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Mouse), std::bind(&Portal::MouseLButtonClick, this, std::placeholders::_1));

		// 플레이어와 충돌시 레벨체인지
		PortalCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Player), std::bind(&Portal::PlayerCollisionCheck, this, std::placeholders::_1));
	}
}

void Portal::MouseLButtonClick(GameEngineCollision* _Other)
{
	// 마우스를 클릭 하면 플레이어와의 충돌체크 활성화
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		if (false == InteractionFlag_)
		{
			InteractionFlag_ = true;
		}
	}
}

void Portal::PlayerCollisionCheck(GameEngineCollision* _Other)
{
	if (true == InteractionFlag_)
	{
		if (nullptr != NextLevel_)
		{
			// 플레이어와 충돌체크 충돌성공시 레벨 체인지
			// 단, 이동가능 Flag 활성화 상태일때만 가능
			UserGame::LevelChange(NextLevel_->GetName());
		}
	}
}

void Portal::IdleAnimationEnd()
{
	PortalEntityRenderer_->SetChangeAnimation("IDLE");
	PortalShadowRenderer_->SetChangeAnimation("IDLE");
}

void Portal::CreateLevelChangePortal(PortalType _PortalType, GameEngineLevel* _NextLevel, bool _Open)
{
	// 정보저장
	PortalType_ = _PortalType;
	NextLevel_ = _NextLevel;

	if (PortalType::TOWN == PortalType_)
	{
		// 본체 렌더러 생성
		PortalEntityRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalEntityRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
		PortalEntityRenderer_->GetTransform()->SetLocalZOrder(9.f);

		PortalEntityRenderer_->CreateAnimation("NorPortal_Entity_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalEntityRenderer_->CreateAnimation("NorPortal_Entity_Idle.png", "IDLE", 0, 14, 0.1f);
		PortalEntityRenderer_->SetEndCallBack("OPEN", std::bind(&Portal::IdleAnimationEnd, this));

		// 충돌체 생성(본체기준)
		PortalCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Object));
		PortalCollision_->GetTransform()->SetLocalScaling(float4(80.f, 120.f));
		PortalCollision_->GetTransform()->SetLocalPosition(PortalEntityRenderer_->GetTransform()->GetLocalPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition());
		PortalCollision_->GetTransform()->SetLocalZOrder(-10.f);

		// 그림자 렌더러 생성
		PortalShadowRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalShadowRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
		PortalShadowRenderer_->GetTransform()->SetLocalZOrder(10.f);

		PortalShadowRenderer_->CreateAnimation("NorPortal_Shadow_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalShadowRenderer_->CreateAnimation("NorPortal_Shadow_Idle.png", "IDLE", 0, 14, 0.1f);
	}
	else
	{
		// 본체 렌더러 생성
		PortalEntityRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalEntityRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));

		PortalEntityRenderer_->CreateAnimation("BossPortal_Entity_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalEntityRenderer_->CreateAnimation("BossPortal_Entity_Idle.png", "IDLE", 0, 14, 0.1f);
		PortalEntityRenderer_->SetEndCallBack("OPEN", std::bind(&Portal::IdleAnimationEnd, this));

		// 충돌체 생성(본체기준)
		PortalCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Object));
		PortalCollision_->GetTransform()->SetLocalScaling(float4(80.f, 120.f));
		PortalCollision_->GetTransform()->SetLocalPosition(PortalEntityRenderer_->GetTransform()->GetLocalPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition());
		PortalCollision_->GetTransform()->SetLocalZOrder(-99.f);

		// 그림자 렌더러 생성
		PortalShadowRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalShadowRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
		PortalShadowRenderer_->GetTransform()->SetLocalZOrder(10.f);

		PortalShadowRenderer_->CreateAnimation("BossPortal_Shadow_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalShadowRenderer_->CreateAnimation("BossPortal_Shadow_Idle.png", "IDLE", 0, 14, 0.1f);
	}

	// 알파블렌딩변경
	PortalEntityRenderer_->SetRenderingPipeLine("TextureTrans");

	// 사운드 플레이어 생성
	PortalSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();

	// 열기 애니메이션부터 시작
	if (true == _Open)
	{
		PortalEntityRenderer_->SetChangeAnimation("OPEN");
		PortalShadowRenderer_->SetChangeAnimation("OPEN");

		// 열기 사운드 재생
		PortalSound_->PlayAlone("portalopen.wav", 0);
	}
	// 이미 소환되어있음
	else
	{
		PortalEntityRenderer_->SetChangeAnimation("IDLE");
		PortalShadowRenderer_->SetChangeAnimation("IDLE");
	}
}

void Portal::PortMoveableFlagOff(const float4& _MousePos)
{
	// 마우스 클릭지점의 타일을 검사하여 포탈이 있으면 해제 실패
	// 아니라면 해제
	TileIndex CheckTile;
	TileIndex MyTileIndex;

	// 마을레벨일때 마을맵에서 검사
	if (std::string::npos != GetLevel()->GetName().find("TownLevel"))
	{
		CheckTile = GlobalValue::TownMap->GetPosToTileIndex(_MousePos + GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition());
		MyTileIndex = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
		if (MyTileIndex == CheckTile)
		{
			return;
		}

		// Flag 해제 성공
		InteractionFlag_ = false;
	}
	// 필드레벨들일때 랜덤맵에서 검사
	else
	{
		CheckTile = GlobalValue::CatacombsMap->GetWallTileIndex(_MousePos + GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition());
		MyTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());
		if (MyTileIndex == CheckTile)
		{
			return;
		}

		// Flag 해제 성공
		InteractionFlag_ = false;
	}
}
