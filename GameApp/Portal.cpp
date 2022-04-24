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
		GetLevel()->PushDebugRender(PortalCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

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
		// 플레이어와 충돌체크 충돌성공시 레벨 체인지
		// 단, 이동가능 Flag 활성화 상태일때만 가능
		UserGame::LevelChange("CatacombsLevel");
	}
}

void Portal::CreateLevelChangePortal(PortalType _PortalType, GameEngineLevel* _NextLevel)
{
	// 정보저장
	PortalType_ = _PortalType;
	NextLevel_ = _NextLevel;

	if (PortalType::TOWN == PortalType_)
	{
		// 본체 렌더러 생성
		PortalEntityRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalEntityRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));

		PortalEntityRenderer_->CreateAnimation("NorPortal_Entity_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalEntityRenderer_->CreateAnimation("NorPortal_Entity_Idle.png", "IDLE", 0, 14, 0.1f);

		PortalEntityRenderer_->SetChangeAnimation("IDLE");

		// 충돌체 생성(본체기준)
		PortalCollision_ = CreateTransformComponent<GameEngineCollision>();
		PortalCollision_->GetTransform()->SetLocalScaling(float4(100.f, 150.f));
		PortalCollision_->GetTransform()->SetLocalZOrder(-10.f);

		// 그림자 렌더러 생성
		PortalShadowRenderer_ = CreateTransformComponent<GameEngineImageRenderer>();
		PortalShadowRenderer_->GetTransform()->SetLocalScaling(float4(256.f, 256.f));

		PortalShadowRenderer_->CreateAnimation("NorPortal_Shadow_Open.png", "OPEN", 0, 14, 0.1f, false);
		PortalShadowRenderer_->CreateAnimation("NorPortal_Shadow_Idle.png", "IDLE", 0, 14, 0.1f);

		// 본체렌더러를 회전시켜 그림자처럼구현
		float4 CalcPos = PortalEntityRenderer_->GetTransform()->GetLocalPosition();
		//CalcPos.ro

		PortalShadowRenderer_->SetChangeAnimation("IDLE");

		// 알파블렌딩변경
		PortalEntityRenderer_->SetRenderingPipeLine("TextureTrans");
	}
	else
	{

	}

	// FSM 생성

}

void Portal::PortMoveableFlagOff()
{
	Moveable_ = false;
}
