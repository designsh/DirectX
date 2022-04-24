#include "PreCompile.h"
#include "Portal.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "UserGame.h"

Portal::Portal() :
	PortalType_(PortalType::TOWN),
	Moveable_(false),
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
		GetLevel()->PushDebugRender(PortalCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

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
		if (false == Moveable_)
		{
			Moveable_ = true;
		}
	}
}

void Portal::PlayerCollisionCheck(GameEngineCollision* _Other)
{
	if (true == Moveable_)
	{
		// �÷��̾�� �浹üũ �浹������ ���� ü����
		// ��, �̵����� Flag Ȱ��ȭ �����϶��� ����
		UserGame::LevelChange("CatacombsLevel");
	}
}

void Portal::CreateLevelChangePortal(PortalType _PortalType, GameEngineLevel* _NextLevel)
{
	// ��������
	PortalType_ = _PortalType;
	NextLevel_ = _NextLevel;

	if (PortalType::TOWN == PortalType_)
	{
		// ��ü ������ ����
		PortalEntityRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalEntityRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));

		PortalEntityRenderer_->CreateAnimation("NorPortal_Entity_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalEntityRenderer_->CreateAnimation("NorPortal_Entity_Idle.png", "IDLE", 0, 14, 0.1f);

		PortalEntityRenderer_->SetChangeAnimation("IDLE");

		// �浹ü ����(��ü����)
		PortalCollision_ = CreateTransformComponent<GameEngineCollision>();
		PortalCollision_->GetTransform()->SetLocalScaling(float4(100.f, 150.f));
		PortalCollision_->GetTransform()->SetLocalZOrder(-10.f);

		// �׸��� ������ ����
		PortalShadowRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalShadowRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));

		PortalShadowRenderer_->CreateAnimation("NorPortal_Shadow_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalShadowRenderer_->CreateAnimation("NorPortal_Shadow_Idle.png", "IDLE", 0, 14, 0.1f);

		// ��ü�������� ȸ������ �׸���ó������
		float4 CalcPos = PortalEntityRenderer_->GetTransform()->GetLocalPosition();
		//CalcPos.ro

		PortalShadowRenderer_->SetChangeAnimation("IDLE");

		// ���ĺ�������
		PortalEntityRenderer_->SetRenderingPipeLine("TextureTrans");
	}
	else
	{

	}

	// FSM ����

}

void Portal::PortMoveableFlagOff()
{
	Moveable_ = false;
}
