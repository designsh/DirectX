#include "PreCompile.h"
#include "NPC_TopMenuBar.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "WeaponNPC.h"
#include "ChandleryNPC.h"
#include "NPC_BuySellView.h"

NPC_TopMenuBar::NPC_TopMenuBar() :
	TopMenuPanel_(nullptr),
	ConversationMenuRenderer_(nullptr),
	ConversationMenuCol_(nullptr),
	BuySellMenuRenderer_(nullptr),
	ButSellMenuCol_(nullptr),
	CloseMenuRenderer_(nullptr),
	CloseMenuCol_(nullptr),
	NPCClassType_(NPCClassType::MAX),
	NPCType_(NPCType::Normal),
	BuySellView_(nullptr),
	ConversationMenuBtnState_(Button_State::Normal),
	BuySellMenuBtnState_(Button_State::Normal),
	CloseMenuBtnState_(Button_State::Normal)
{
}

NPC_TopMenuBar::~NPC_TopMenuBar()
{
}

void NPC_TopMenuBar::Start()
{
}

void NPC_TopMenuBar::Update(float _DeltaTime)
{
#pragma region 버튼충돌체크
	if (nullptr != ConversationMenuCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(ConversationMenuCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		ConversationMenuCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_TopMenuBar::SelectConversationMenu, this, std::placeholders::_1));
	}

	if (nullptr != ButSellMenuCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(ButSellMenuCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		ButSellMenuCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_TopMenuBar::SelectBuySellMenu, this, std::placeholders::_1));
	}

	if (nullptr != CloseMenuCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(CloseMenuCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		CloseMenuCol_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_TopMenuBar::SelectCloseMenu, this, std::placeholders::_1));
	}
#pragma endregion
}

void NPC_TopMenuBar::SelectConversationMenu(GameEngineCollision* _Other)
{
	// 대화선택
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		switch (NPCClassType_)
		{
			case NPCClassType::Akara:
			{
				GlobalValue::ChandleryNPC->SelectConversationMenu();
				break;
			}
			case NPCClassType::Charsi:
			{
				GlobalValue::WeaponNPC->SelectConversationMenu();
				break;
			}
		}
	}

	if (ConversationMenuBtnState_ == Button_State::Normal)
	{
		ConversationMenuRenderer_->SetTextColor(float4(0.f, 0.f, 1.f, 1.f));
		BuySellMenuRenderer_->SetTextColor(float4::WHITE);
		CloseMenuRenderer_->SetTextColor(float4::WHITE);
		ConversationMenuBtnState_ = Button_State::MouseOn;
		BuySellMenuBtnState_ = Button_State::Normal;
		CloseMenuBtnState_ = Button_State::Normal;
	}
}

void NPC_TopMenuBar::SelectBuySellMenu(GameEngineCollision* _Other)
{
	// 판매창 선택
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// 판매창 Active
		BuySellView_->PublicNPCBuySellViewActive();
	}

	if (BuySellMenuBtnState_ == Button_State::Normal)
	{
		ConversationMenuRenderer_->SetTextColor(float4::WHITE);
		BuySellMenuRenderer_->SetTextColor(float4(0.f, 0.f, 1.f, 1.f));
		CloseMenuRenderer_->SetTextColor(float4::WHITE);
		ConversationMenuBtnState_ = Button_State::Normal;
		BuySellMenuBtnState_ = Button_State::MouseOn;
		CloseMenuBtnState_ = Button_State::Normal;
	}
}

void NPC_TopMenuBar::SelectCloseMenu(GameEngineCollision* _Other)
{
	// 상호작용취소 선택
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		Off();

		// 해당 NPC 대기상태로 전환
		switch (NPCClassType_)
		{
			case NPCClassType::Akara:
			{
				GlobalValue::ChandleryNPC->InteractionEnd();
				break;
			}
			case NPCClassType::Charsi:
			{
				GlobalValue::WeaponNPC->InteractionEnd();
				break;
			}
		}
	}

	if (CloseMenuBtnState_ == Button_State::Normal)
	{
		ConversationMenuRenderer_->SetTextColor(float4::WHITE);
		BuySellMenuRenderer_->SetTextColor(float4::WHITE);
		CloseMenuRenderer_->SetTextColor(float4(0.f, 0.f, 1.f, 1.f));
		ConversationMenuBtnState_ = Button_State::Normal;
		BuySellMenuBtnState_ = Button_State::Normal;
		CloseMenuBtnState_ = Button_State::MouseOn;
	}
}

void NPC_TopMenuBar::CreateNPCTopMenu(NPCClassType _NPCClassType, NPCType _NPCType)
{
	// 기본정보 저장
	NPCClassType_ = _NPCClassType;
	NPCType_ = _NPCType;

	// NPC 클래스 타입에 따른 상단메뉴바 판넬 생성 및 메뉴목록 생성
	switch (NPCClassType_)
	{
		case NPCClassType::Akara:
		{
			// 메뉴바 판넬
			TopMenuPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0));
			TopMenuPanel_->SetImage("TopMenu_Type2_Panel.png");
			TopMenuPanel_->TextSetting("HMKMRHD", "아카라", 12.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f), float4(0.f, -30.f));
			TopMenuPanel_->SetAlpha(0.5f);

			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("TopMenu_Type2_Panel.png");
			float4 TextureSizeHalf = Texture->GetTextureSize();
			TopMenuPanel_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y + 6.f));

			// 메뉴선택텍스트(버튼처럼사용)

			// 대화
			ConversationMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			ConversationMenuRenderer_->SetAlpha(0.f);
			ConversationMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y + 18.f));
			ConversationMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			ConversationMenuRenderer_->TextSetting("HMKMRHD", "대화", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			ConversationMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));

			ConversationMenuCol_->GetTransform()->SetLocalPosition(ConversationMenuRenderer_->GetTransform()->GetLocalPosition());
			ConversationMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			ConversationMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

			// 판매창
			BuySellMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			BuySellMenuRenderer_->SetAlpha(0.f);
			BuySellMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y));
			BuySellMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			BuySellMenuRenderer_->TextSetting("HMKMRHD", "거래", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			ButSellMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));
			ButSellMenuCol_->GetTransform()->SetLocalPosition(BuySellMenuRenderer_->GetTransform()->GetLocalPosition());
			ButSellMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			ButSellMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

			// 취소
			CloseMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			CloseMenuRenderer_->SetAlpha(0.f);
			CloseMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y - 18.f));
			CloseMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			CloseMenuRenderer_->TextSetting("HMKMRHD", "취소", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			CloseMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));
			CloseMenuCol_->GetTransform()->SetLocalPosition(CloseMenuRenderer_->GetTransform()->GetLocalPosition());
			CloseMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			CloseMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

#pragma region 판매창생성
			BuySellView_ = GetLevel()->CreateActor<NPC_BuySellView>();
			BuySellView_->CreateBuySellView(NPCType_, NPCClassType_);
			BuySellView_->Off();
#pragma endregion

			break;
		}
		case NPCClassType::Charsi:
		{
			// 메뉴바 판넬
			TopMenuPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0));
			TopMenuPanel_->SetImage("TopMenu_Type1_Panel.png");
			TopMenuPanel_->TextSetting("HMKMRHD", "찰시", 12.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f), float4(0.f, -30.f));
			TopMenuPanel_->SetAlpha(0.5f);
			
			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("TopMenu_Type1_Panel.png");
			float4 TextureSizeHalf = Texture->GetTextureSize();
			TopMenuPanel_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y + 6.f));

			// 메뉴선택텍스트(버튼처럼사용)

			// 대화
			ConversationMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			ConversationMenuRenderer_->SetAlpha(0.f);
			ConversationMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y + 18.f));
			ConversationMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			ConversationMenuRenderer_->TextSetting("HMKMRHD", "대화", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			ConversationMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));

			ConversationMenuCol_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y + 18.f));
			ConversationMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			ConversationMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

			// 판매창
			BuySellMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			BuySellMenuRenderer_->SetAlpha(0.f);
			BuySellMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y));
			BuySellMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			BuySellMenuRenderer_->TextSetting("HMKMRHD", "거래/수리", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			ButSellMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));
			ButSellMenuCol_->GetTransform()->SetLocalPosition(BuySellMenuRenderer_->GetTransform()->GetLocalPosition());
			ButSellMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			ButSellMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

			// 취소
			CloseMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			CloseMenuRenderer_->SetAlpha(0.f);
			CloseMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y - 18.f));
			CloseMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			CloseMenuRenderer_->TextSetting("HMKMRHD", "취소", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			CloseMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));
			CloseMenuCol_->GetTransform()->SetLocalPosition(CloseMenuRenderer_->GetTransform()->GetLocalPosition());
			CloseMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			CloseMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

			#pragma region 판매창생성
			BuySellView_ = GetLevel()->CreateActor<NPC_BuySellView>();
			BuySellView_->CreateBuySellView(NPCType_, NPCClassType_);
			BuySellView_->Off();
			#pragma endregion

			break;
		}
	}
}

void NPC_TopMenuBar::NPCTopMenuActive()
{
	// 해당 메뉴 On
	On();

	// 상단메뉴액터의 위치를 타입별 NPC의 현재위치로 셋팅
	switch (NPCClassType_)
	{
		case NPCClassType::Akara:
		{
			float4 AkaraPos = GlobalValue::ChandleryNPC->GetTransform()->GetLocalPosition();
			GetTransform()->SetWorldPosition(AkaraPos - GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition());
			break;
		}
		case NPCClassType::Charsi:
		{
			float4 CharsiPos = GlobalValue::WeaponNPC->GetTransform()->GetLocalPosition();
			GetTransform()->SetWorldPosition(CharsiPos - GetLevel()->GetMainCameraActor()->GetTransform()->GetLocalPosition());
			break;
		}
	}

	MenuButtonStateReset();
}

void NPC_TopMenuBar::MenuButtonStateReset()
{
	// 버튼 충돌상태 초기화
	ConversationMenuRenderer_->SetTextColor(float4::WHITE);
	BuySellMenuRenderer_->SetTextColor(float4::WHITE);
	CloseMenuRenderer_->SetTextColor(float4::WHITE);
	ConversationMenuBtnState_ = Button_State::Normal;
	BuySellMenuBtnState_ = Button_State::Normal;
	CloseMenuBtnState_ = Button_State::Normal;
}
