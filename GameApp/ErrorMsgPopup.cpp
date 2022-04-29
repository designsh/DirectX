#include "PreCompile.h"
#include "ErrorMsgPopup.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"
#include "MouseObject.h"

ErrorMsgPopup::ErrorMsgPopup() :
	ErrorMsgText_(),
	ButtonState_(Button_State::Normal),
	ErrorMsgPanel_(nullptr),
	ErrorMsgCol_(nullptr),
	ErrorMsgButton_(nullptr),
	ErrorMsgBtnCollision_(nullptr)
{
}

ErrorMsgPopup::~ErrorMsgPopup()
{
}

void ErrorMsgPopup::Start()
{	
	// 에러 메세지 창 닫기 버튼 생성
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("ShortButton_Stay.png");
	ButtonDefault->Cut(1, 1);

	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("ShortButton_Click.png");
	ButtonClick->Cut(1, 1);

	// 에러 메세지 창
	ErrorMsgPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup));
	ErrorMsgPanel_->SetImage("ErrorMsgBox_Panel.png");
	ErrorMsgPanel_->TextSetting("diablo", ErrorMsgText_, 15, FW1_CENTER | FW1_VCENTER, float4::WHITE);

	// 마우스와 충돌중일때 마우스 동작 제한
	ErrorMsgCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Action_Col));
	ErrorMsgCol_->GetTransform()->SetLocalScaling(ErrorMsgPanel_->GetTransform()->GetLocalScaling());
	ErrorMsgCol_->GetTransform()->SetLocalPosition(ErrorMsgCol_->GetTransform()->GetLocalPosition());

	// 에러 확인 버튼(액터)
	ErrorMsgButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::Popup_Button));
	ErrorMsgButton_->CreateAnimation("ShortButton_Stay.png", "Default", 0, 0, 0.1f, false);
	ErrorMsgButton_->CreateAnimation("ShortButton_Click.png", "Click", 0, 0, 0.1f, false);
	ErrorMsgButton_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.0f));
	ErrorMsgButton_->GetTransform()->SetLocalPosition(float4(0.f, -60.f));
	ErrorMsgButton_->SetChangeAnimation("Default");

	// 게임시작 TextSetting
	ErrorMsgButton_->TextSetting("diablo", "OK", 15, FW1_VCENTER | FW1_CENTER, float4::BLACK);

	// 충돌체 생성
	ErrorMsgBtnCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::Popup_Collider));
	ErrorMsgBtnCollision_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.0f));
	ErrorMsgBtnCollision_->GetTransform()->SetLocalPosition(ErrorMsgButton_->GetTransform()->GetLocalPosition());

}

void ErrorMsgPopup::Update(float _DeltaTime)
{
	if (nullptr != ErrorMsgCol_)
	{
#ifdef _DEBUG
		GetLevel()->UIPushDebugRender(ErrorMsgCol_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG
	}

	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 해당 창 비활성
			ErrorMsgPopupDeactive();

			ButtonState_ = Button_State::Normal;
		}
	}

	// 버튼 충돌체크
	ErrorMsgBtnCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&ErrorMsgPopup::ErrorMsgDisabled, this, std::placeholders::_1));
}

void ErrorMsgPopup::ErrorMsgPopupActive(const std::string& _ErrorMsg)
{
	// ErrorMsg Setting
	ErrorMsgText_ = _ErrorMsg;

	// ErrorMsgText가 일정글자수를 넘어가면 줄바꿈 Flag 추가 - 보류
	ErrorMsgPanel_->SetPrintText(ErrorMsgText_);

	// 활성화
	On();
}

void ErrorMsgPopup::ErrorMsgPopupDeactive()
{
	// 해당 충돌 Flag를 해제시키고
	if (nullptr != GlobalValue::CurMouse && true == GlobalValue::CurMouse->GetUIPopupCollision())
	{
		GlobalValue::CurMouse->UIPopupCollisionOff();
	}

	// 해당 액터 사망처리
	Death();
}

void ErrorMsgPopup::ErrorMsgDisabled(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		ErrorMsgButton_->SetChangeAnimation("Click");

		ButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		ErrorMsgButton_->SetChangeAnimation("Default");
	}
}
