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

	// Panel 생성
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("Player_StorehouseView_Panel.png");
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();
	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();

	StoreViewPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	StoreViewPanel_->SetImage("Player_StorehouseView_Panel.png");
	StoreViewPanel_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x - WindowHarfSize.x, 24.f));

	// Player 이동제한용 판넬 충돌체 생성
	StoreViewPanelCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UIMoveabledCheckCol));
	StoreViewPanelCol_->SetName("Player_StoreView");
	StoreViewPanelCol_->GetTransform()->SetLocalScaling(StoreViewPanel_->GetTransform()->GetLocalScaling());
	StoreViewPanelCol_->GetTransform()->SetLocalPosition(StoreViewPanel_->GetTransform()->GetLocalPosition());

	// 창닫기 버튼관련









	// 기본 Off상태로 생성
	Off();
}

void StoreView::Update(float _DeltaTime)
{
#pragma region 충돌체 Renderer
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
	// 내부에서 처리용

	if (false == StoreViewActive_)
	{
		// 비활성화 -> 활성화
		StoreViewActive_ = true;

		// 활성화시 플레이어의 인벤토리창이 같이 활성화된다.



	}
	else
	{
		// 활성화 -> 비활성화
		StoreViewActive_ = false;


		// 비활성화시 플레이어의 인벤토리창이 같이 비활성화 된다.



	}
}

void StoreView::StoreViewOff()
{
	// 외부에서 해당 창고창을 비활성화할시 호출된다.
	// 즉, 인벤토리창에서 Close버튼 클릭시 호출
	if (true == StoreViewActive_)
	{
		StoreViewActive_ = false;

		// 나 자신을 Off 상태로 전환
		Off();
	}
}
