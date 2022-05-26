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
	// ������ ���� ���� ���� ����
	CurLevel_ = GetLevel();
}

Portal::~Portal()
{
}

void Portal::Start()
{
	// Image Cutting

	// �Ϲ���Ż(�Ķ���)
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


	// ������Ż(������)
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

		// ���콺�� �ش� ��Ż�� Ŭ���� ���¿��� 
		PortalCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Mouse), std::bind(&Portal::MouseLButtonClick, this, std::placeholders::_1));

		// �÷��̾�� �浹�� ����ü����
		PortalCollision_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Player), std::bind(&Portal::PlayerCollisionCheck, this, std::placeholders::_1));
	}
}

void Portal::MouseLButtonClick(GameEngineCollision* _Other)
{
	// ���콺�� Ŭ�� �ϸ� �÷��̾���� �浹üũ Ȱ��ȭ
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
			// �÷��̾�� �浹üũ �浹������ ���� ü����
			// ��, �̵����� Flag Ȱ��ȭ �����϶��� ����
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
	// ��������
	PortalType_ = _PortalType;
	NextLevel_ = _NextLevel;

	if (PortalType::TOWN == PortalType_)
	{
		// ��ü ������ ����
		PortalEntityRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalEntityRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
		PortalEntityRenderer_->GetTransform()->SetLocalZOrder(9.f);

		PortalEntityRenderer_->CreateAnimation("NorPortal_Entity_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalEntityRenderer_->CreateAnimation("NorPortal_Entity_Idle.png", "IDLE", 0, 14, 0.1f);
		PortalEntityRenderer_->SetEndCallBack("OPEN", std::bind(&Portal::IdleAnimationEnd, this));

		// �浹ü ����(��ü����)
		PortalCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Object));
		PortalCollision_->GetTransform()->SetLocalScaling(float4(80.f, 120.f));
		PortalCollision_->GetTransform()->SetLocalPosition(PortalEntityRenderer_->GetTransform()->GetLocalPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition());
		PortalCollision_->GetTransform()->SetLocalZOrder(-10.f);

		// �׸��� ������ ����
		PortalShadowRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalShadowRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
		PortalShadowRenderer_->GetTransform()->SetLocalZOrder(10.f);

		PortalShadowRenderer_->CreateAnimation("NorPortal_Shadow_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalShadowRenderer_->CreateAnimation("NorPortal_Shadow_Idle.png", "IDLE", 0, 14, 0.1f);
	}
	else
	{
		// ��ü ������ ����
		PortalEntityRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalEntityRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));

		PortalEntityRenderer_->CreateAnimation("BossPortal_Entity_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalEntityRenderer_->CreateAnimation("BossPortal_Entity_Idle.png", "IDLE", 0, 14, 0.1f);
		PortalEntityRenderer_->SetEndCallBack("OPEN", std::bind(&Portal::IdleAnimationEnd, this));

		// �浹ü ����(��ü����)
		PortalCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Object));
		PortalCollision_->GetTransform()->SetLocalScaling(float4(80.f, 120.f));
		PortalCollision_->GetTransform()->SetLocalPosition(PortalEntityRenderer_->GetTransform()->GetLocalPosition() - GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition());
		PortalCollision_->GetTransform()->SetLocalZOrder(-99.f);

		// �׸��� ������ ����
		PortalShadowRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalShadowRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));
		PortalShadowRenderer_->GetTransform()->SetLocalZOrder(10.f);

		PortalShadowRenderer_->CreateAnimation("BossPortal_Shadow_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalShadowRenderer_->CreateAnimation("BossPortal_Shadow_Idle.png", "IDLE", 0, 14, 0.1f);
	}

	// ���ĺ�������
	PortalEntityRenderer_->SetRenderingPipeLine("TextureTrans");

	// ���� �÷��̾� ����
	PortalSound_ = GameEngineSoundManager::GetInst().CreateSoundPlayer();

	// ���� �ִϸ��̼Ǻ��� ����
	if (true == _Open)
	{
		PortalEntityRenderer_->SetChangeAnimation("OPEN");
		PortalShadowRenderer_->SetChangeAnimation("OPEN");

		// ���� ���� ���
		PortalSound_->PlayAlone("portalopen.wav", 0);
	}
	// �̹� ��ȯ�Ǿ�����
	else
	{
		PortalEntityRenderer_->SetChangeAnimation("IDLE");
		PortalShadowRenderer_->SetChangeAnimation("IDLE");
	}
}

void Portal::PortMoveableFlagOff(const float4& _MousePos)
{
	// ���콺 Ŭ�������� Ÿ���� �˻��Ͽ� ��Ż�� ������ ���� ����
	// �ƴ϶�� ����
	TileIndex CheckTile;
	TileIndex MyTileIndex;

	// ���������϶� �����ʿ��� �˻�
	if (std::string::npos != GetLevel()->GetName().find("TownLevel"))
	{
		CheckTile = GlobalValue::TownMap->GetPosToTileIndex(_MousePos + GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition());
		MyTileIndex = GlobalValue::TownMap->GetPosToTileIndex(GetTransform()->GetWorldPosition());
		if (MyTileIndex == CheckTile)
		{
			return;
		}

		// Flag ���� ����
		InteractionFlag_ = false;
	}
	// �ʵ巹�����϶� �����ʿ��� �˻�
	else
	{
		CheckTile = GlobalValue::CatacombsMap->GetWallTileIndex(_MousePos + GetLevel()->GetMainCameraActor()->GetTransform()->GetWorldPosition());
		MyTileIndex = GlobalValue::CatacombsMap->GetWallTileIndex(GetTransform()->GetWorldPosition());
		if (MyTileIndex == CheckTile)
		{
			return;
		}

		// Flag ���� ����
		InteractionFlag_ = false;
	}
}
