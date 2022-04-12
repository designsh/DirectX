#include "PreCompile.h"
#include "NPC_BuySellView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"

#include "WeaponNPC.h"
#include "NPC_TopMenuBar.h"

NPC_BuySellView::NPC_BuySellView() :
	ViewPanel_(nullptr),
	BuyButtonRenderer_(nullptr),
	BuyButtonCollider_(nullptr),
	SellButtonRenderer_(nullptr),
	SellButtonCollider_(nullptr),
	RepairButtonRenderer_(nullptr),
	RepairButtonCollider_(nullptr),
	AllRepairButtonRenderer_(nullptr),
	AllRepairButtonCollider_(nullptr),
	NPCClassType_(NPCClassType::Akara),
	BuySellViewType_(NPCType::PotionShop)
{
}

NPC_BuySellView::~NPC_BuySellView()
{
}

void NPC_BuySellView::Start()
{
}

void NPC_BuySellView::Update(float _DeltaTime)
{
	// �� ��ư �浹üũ
	if (nullptr != BuyButtonCollider_)	// ���Ź�ư
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(BuyButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		BuyButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::BuyButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != SellButtonCollider_)	// �ǸŹ�ư
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(SellButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		SellButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::SellButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != RepairButtonCollider_)	// ������ư
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(RepairButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		RepairButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::RepairButtonClick, this, std::placeholders::_1));
	}

	if (nullptr != AllRepairButtonCollider_)	// ���μ�����ư
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(AllRepairButtonCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		AllRepairButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&NPC_BuySellView::AllRepairButtonClick, this, std::placeholders::_1));
	}
}

void NPC_BuySellView::BuyButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// ���콺 Ŀ�� �̹��� ����

	}
}

void NPC_BuySellView::SellButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// ���콺 Ŀ�� �̹��� ����

	}
}

void NPC_BuySellView::RepairButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// ���콺 Ŀ�� �̹��� ����

	}
}

void NPC_BuySellView::AllRepairButtonClick(GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// ���� �÷��̾ ����ִ� ��� ������ �� �������� �����ϴ� ��� ������ ����

	}
}

void NPC_BuySellView::CreateBuySellView(NPCType _BuySellViewType, NPCClassType _NPCClassType)
{
	// ��������
	BuySellViewType_ = _BuySellViewType;
	NPCClassType_ = _NPCClassType;

	// ������ũ�� Get
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();

	// NPCŸ�Կ� ���� �Ǹ�â ����

	// �Ǹ�â �ǳ�
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("BuySell_Panel.png");
	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();
	ViewPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	ViewPanel_->SetImage("BuySell_Panel.png");
	ViewPanel_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x - WindowHarfSize.x, 24.f));

	// �Ǹ�âŸ�Ժ� ��ư �� �ǻ���
	switch (BuySellViewType_)
	{
		case NPCType::PotionShop:
		{
			// �� 1ĭ(��Ÿ)

			// ��ư(����/�Ǹ�, null, null)

			break;
		}
		case NPCType::WeaponShop:
		{
			// �� 2ĭ(����, ����)


			// ��ư(����/�Ǹ�, ����, ���μ���)

			break;
		}
	}
}

void NPC_BuySellView::NPCBuySellViewActive()
{
	//On();

	// �Ǹ�â Ȱ��ȭ�� �÷��̾��� �κ��丮â�� Ȱ��ȭ�Ǹ�,
	

	// �÷��̾��� �ϴܻ��¹��� �̴ϸ޴��� ��Ȱ��ȭ ��Ų��.




	// �ش� NPC�� ��ܸ޴� Off




}

void NPC_BuySellView::NPCBuySellViewInactive()
{
	//Off();

	// �Ǹ�â ��Ȱ��ȭ�� �÷��̾��� �κ��丮â�� ��Ȱ��ȭ�Ǹ�,
	

	// �÷��̾��� �ϴܻ��¹��� �̴ϸ޴��� Ȱ��ȭ ��Ų��.





	// �ش� NPC�� ��ܸ޴� On




}
