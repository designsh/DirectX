#include "PreCompile.h"
#include "TakeInOutGoldPopup.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

TakeInOutGoldPopup::TakeInOutGoldPopup() :
	PopupType_(TakeInOutType::NONE),
	HaveGold_(0),
	Panel_(nullptr)
{
}

TakeInOutGoldPopup::~TakeInOutGoldPopup()
{
}

void TakeInOutGoldPopup::Start()
{
	// ImageCutting

	// 종료버튼
	GameEngineTexture* CloseButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	CloseButtonDefault->Cut(1, 1);
	GameEngineTexture* CloseButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	CloseButtonClick->Cut(1, 1);

	// 승인버튼
	GameEngineTexture* ApprovedButtonDefault = GameEngineTextureManager::GetInst().Find("ApprovedButton_Default.png");
	ApprovedButtonDefault->Cut(1, 1);
	GameEngineTexture* ApprovedButtonClick = GameEngineTextureManager::GetInst().Find("ApprovedButton_Click.png");
	ApprovedButtonClick->Cut(1, 1);
}

void TakeInOutGoldPopup::Update(float _DeltaTime)
{
}

void TakeInOutGoldPopup::CreateTakePopup(TakeInOutType _PopupType, const float4& _InitPos)
{
	// 판넬 생성
	Panel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::ErrorPopup));
	Panel_->SetImage("ErrorMsgBox_Panel.png");
	Panel_->TextSetting("diablo", std::to_string(HaveGold_), 15, FW1_CENTER | FW1_VCENTER, float4::WHITE);


	// 숫자증가 버튼생성


	// 숫자감소 버튼생성


	// 승인 버튼생성



	// 종료 버튼생성


	// 기본 Off상태
	Off();
}
