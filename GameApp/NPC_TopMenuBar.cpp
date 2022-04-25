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
#pragma region ��ư�浹üũ
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
	// ��ȭ����
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
	// �Ǹ�â ����
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// �Ǹ�â Active
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
	// ��ȣ�ۿ���� ����
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		Off();

		// �ش� NPC �����·� ��ȯ
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
	// �⺻���� ����
	NPCClassType_ = _NPCClassType;
	NPCType_ = _NPCType;

	// NPC Ŭ���� Ÿ�Կ� ���� ��ܸ޴��� �ǳ� ���� �� �޴���� ����
	switch (NPCClassType_)
	{
		case NPCClassType::Akara:
		{
			// �޴��� �ǳ�
			TopMenuPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0));
			TopMenuPanel_->SetImage("TopMenu_Type2_Panel.png");
			TopMenuPanel_->TextSetting("HMKMRHD", "��ī��", 12.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f), float4(0.f, -30.f));
			TopMenuPanel_->SetAlpha(0.5f);

			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("TopMenu_Type2_Panel.png");
			float4 TextureSizeHalf = Texture->GetTextureSize();
			TopMenuPanel_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y + 6.f));

			// �޴������ؽ�Ʈ(��ưó�����)

			// ��ȭ
			ConversationMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			ConversationMenuRenderer_->SetAlpha(0.f);
			ConversationMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y + 18.f));
			ConversationMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			ConversationMenuRenderer_->TextSetting("HMKMRHD", "��ȭ", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			ConversationMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));

			ConversationMenuCol_->GetTransform()->SetLocalPosition(ConversationMenuRenderer_->GetTransform()->GetLocalPosition());
			ConversationMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			ConversationMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

			// �Ǹ�â
			BuySellMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			BuySellMenuRenderer_->SetAlpha(0.f);
			BuySellMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y));
			BuySellMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			BuySellMenuRenderer_->TextSetting("HMKMRHD", "�ŷ�", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			ButSellMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));
			ButSellMenuCol_->GetTransform()->SetLocalPosition(BuySellMenuRenderer_->GetTransform()->GetLocalPosition());
			ButSellMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			ButSellMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

			// ���
			CloseMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			CloseMenuRenderer_->SetAlpha(0.f);
			CloseMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y - 18.f));
			CloseMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			CloseMenuRenderer_->TextSetting("HMKMRHD", "���", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			CloseMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));
			CloseMenuCol_->GetTransform()->SetLocalPosition(CloseMenuRenderer_->GetTransform()->GetLocalPosition());
			CloseMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			CloseMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

#pragma region �Ǹ�â����
			BuySellView_ = GetLevel()->CreateActor<NPC_BuySellView>();
			BuySellView_->CreateBuySellView(NPCType_, NPCClassType_);
			BuySellView_->Off();
#pragma endregion

			break;
		}
		case NPCClassType::Charsi:
		{
			// �޴��� �ǳ�
			TopMenuPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0));
			TopMenuPanel_->SetImage("TopMenu_Type1_Panel.png");
			TopMenuPanel_->TextSetting("HMKMRHD", "����", 12.f, FW1_CENTER | FW1_VCENTER, float4(0.8f, 0.8f, 0.4f), float4(0.f, -30.f));
			TopMenuPanel_->SetAlpha(0.5f);
			
			GameEngineTexture* Texture = GameEngineTextureManager::GetInst().Find("TopMenu_Type1_Panel.png");
			float4 TextureSizeHalf = Texture->GetTextureSize();
			TopMenuPanel_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y + 6.f));

			// �޴������ؽ�Ʈ(��ưó�����)

			// ��ȭ
			ConversationMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			ConversationMenuRenderer_->SetAlpha(0.f);
			ConversationMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y + 18.f));
			ConversationMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			ConversationMenuRenderer_->TextSetting("HMKMRHD", "��ȭ", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			ConversationMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));

			ConversationMenuCol_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y + 18.f));
			ConversationMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			ConversationMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

			// �Ǹ�â
			BuySellMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			BuySellMenuRenderer_->SetAlpha(0.f);
			BuySellMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y));
			BuySellMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			BuySellMenuRenderer_->TextSetting("HMKMRHD", "�ŷ�/����", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			ButSellMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));
			ButSellMenuCol_->GetTransform()->SetLocalPosition(BuySellMenuRenderer_->GetTransform()->GetLocalPosition());
			ButSellMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			ButSellMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

			// ���
			CloseMenuRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::NPCUI0_Text));
			CloseMenuRenderer_->SetAlpha(0.f);
			CloseMenuRenderer_->GetTransform()->SetLocalPosition(float4(0.f, TextureSizeHalf.y - 18.f));
			CloseMenuRenderer_->GetTransform()->SetLocalScaling(float4(78.f, 20.f));
			CloseMenuRenderer_->TextSetting("HMKMRHD", "���", 12.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

			CloseMenuCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::NPCUI0_TextCol));
			CloseMenuCol_->GetTransform()->SetLocalPosition(CloseMenuRenderer_->GetTransform()->GetLocalPosition());
			CloseMenuCol_->GetTransform()->SetLocalZOrder(-1.f);
			CloseMenuCol_->GetTransform()->SetLocalScaling(float4(70.f, 16.f));

			#pragma region �Ǹ�â����
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
	// �ش� �޴� On
	On();

	// ��ܸ޴������� ��ġ�� Ÿ�Ժ� NPC�� ������ġ�� ����
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
	// ��ư �浹���� �ʱ�ȭ
	ConversationMenuRenderer_->SetTextColor(float4::WHITE);
	BuySellMenuRenderer_->SetTextColor(float4::WHITE);
	CloseMenuRenderer_->SetTextColor(float4::WHITE);
	ConversationMenuBtnState_ = Button_State::Normal;
	BuySellMenuBtnState_ = Button_State::Normal;
	CloseMenuBtnState_ = Button_State::Normal;
}
