#include "PreCompile.h"
#include "StoreView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayer.h"
#include "MouseObject.h"

StoreView::StoreView() :
	StoreViewActive_(false),
	StoreViewPanel_(nullptr),
	StoreViewPanelCol_(nullptr),
	StoreGold_(nullptr),
	StoreMaxGold_(nullptr)
{
}

StoreView::~StoreView()
{
}

void StoreView::Start()
{
	// ImageCutting
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	ButtonDefault->Cut(1, 1);

	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	ButtonClick->Cut(1, 1);

	// Panel ����
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("Player_StorehouseView_Panel.png");
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();
	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();

	StoreViewPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	StoreViewPanel_->SetImage("Player_StorehouseView_Panel.png");
	StoreViewPanel_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x - WindowHarfSize.x, 24.f));

	// Player �̵����ѿ� �ǳ� �浹ü ����
	StoreViewPanelCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UIMoveabledCheckCol));
	StoreViewPanelCol_->SetName("Player_StoreView");
	StoreViewPanelCol_->GetTransform()->SetLocalScaling(StoreViewPanel_->GetTransform()->GetLocalScaling());
	StoreViewPanelCol_->GetTransform()->SetLocalPosition(StoreViewPanel_->GetTransform()->GetLocalPosition());

	// â�ݱ� ��ư����









	// �⺻ Off���·� ����
	Off();
}

void StoreView::Update(float _DeltaTime)
{
#pragma region �浹ü Renderer
	if (nullptr != StoreViewPanelCol_)
	{
#ifdef _DEBUG
		
		
		//GetLevel()->PushDebugRenderer(StoreViewPanelCol_->GetTransform(), CollisionType::Rect);
#endif
	}


#pragma endregion


}

void StoreView::PrivateStoreViewActive()
{
	// ���ο��� ó����

	if (false == StoreViewActive_)
	{
		// ��Ȱ��ȭ -> Ȱ��ȭ
		StoreViewActive_ = true;

		// Ȱ��ȭ�� �÷��̾��� �κ��丮â�� ���� Ȱ��ȭ�ȴ�.



	}
	else
	{
		// Ȱ��ȭ -> ��Ȱ��ȭ
		StoreViewActive_ = false;


		// ��Ȱ��ȭ�� �÷��̾��� �κ��丮â�� ���� ��Ȱ��ȭ �ȴ�.



	}
}

void StoreView::StoreViewOff()
{
	// �ܺο��� �ش� â��â�� ��Ȱ��ȭ�ҽ� ȣ��ȴ�.
	// ��, �κ��丮â���� Close��ư Ŭ���� ȣ��
	if (true == StoreViewActive_)
	{
		StoreViewActive_ = false;

		// �� �ڽ��� Off ���·� ��ȯ
		Off();
	}
}
