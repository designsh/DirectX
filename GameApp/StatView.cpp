#include "PreCompile.h"
#include "StatView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_MiniMenuButton.h"
#include "MainPlayer_LevelUpActiveButton.h"

int StatView::StatPoint = 0;

StatView::StatView() :
	PanelRenderer_(nullptr),
	PanelCol_(nullptr),
	IDRenderer_(nullptr),
	JobClassRenderer_(nullptr),
	CurLevelRenderer_(nullptr),
	CurExpRenderer_(nullptr),
	StrengthRenderer_(nullptr),
	DexterityRenderer_(nullptr),
	VitalityRenderer_(nullptr),
	EnergyRenderer_(nullptr),
	DamageRenderer_(nullptr),
	AttackRatingRenderer_(nullptr),
	DefenseRenderer_(nullptr),
	StaminaRenderer_(nullptr),
	LifeRenderer_(nullptr),
	ManaRenderer_(nullptr),
	FireResistanceRenderer_(nullptr),
	ColdResistanceRenderer_(nullptr),
	LightningResistanceRenderer_(nullptr),
	PoisonResistanceRenderer_(nullptr),
	CloseButton_(nullptr),
	MainCollider_(nullptr),
	ButtonState_(Button_State::Normal),
	STRPointUpButton_(nullptr),
	STRPointUpButtonCollider_(nullptr),
	DEXPointUpButton_(nullptr),
	DEXPointUpButtonCollider_(nullptr),
	VITPointUpButton_(nullptr),
	VITPointUpButtonCollider_(nullptr),
	ENRPointUpButton_(nullptr),
	ENRPointUpButtonCollider_(nullptr),
	STRButtonState_(Button_State::Normal),
	DEXButtonState_(Button_State::Normal),
	VITButtonState_(Button_State::Normal),
	ENRButtonState_(Button_State::Normal)
{
}

StatView::~StatView()
{
}

void StatView::Start()
{
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	ButtonDefault->Cut(1, 1);

	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	ButtonClick->Cut(1, 1);

	// Player_StateView_Panel
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("Player_StateView_Panel.png");
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();

	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();

	// MainPlayer StateView Panel Setting
	PanelRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1));
	PanelRenderer_->SetImage("Player_StateView_Panel.png");
	PanelRenderer_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x - WindowHarfSize.x, 24.f));

	// ???????? ?????????????? ???? ?????? ????
	PanelCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UIMoveabledCheckCol));
	PanelCol_->SetName("Player_StatView");
	PanelCol_->GetTransform()->SetLocalScaling(PanelRenderer_->GetTransform()->GetLocalScaling());
	PanelCol_->GetTransform()->SetLocalPosition(PanelRenderer_->GetTransform()->GetLocalPosition());

	// MainPlayer Infomation String Setting
	// ?????? ID
	IDRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	IDRenderer_->GetTransform()->SetLocalPosition(float4(-220.f, 222.f));

	// ?????? ??????
	JobClassRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	JobClassRenderer_->GetTransform()->SetLocalPosition(float4(-70.f, 222.f));

	// ?????? ???? ????
	GameEngineUIRenderer* LevelName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	LevelName->GetTransform()->SetLocalPosition(float4(-288.f, 198.f));
	LevelName->TextSetting("diablo", "????", 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	CurLevelRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	CurLevelRenderer_->GetTransform()->SetLocalPosition(float4(-288.f, 184.f));

	// ?????? ??????
	GameEngineUIRenderer* ExpName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	ExpName->GetTransform()->SetLocalPosition(float4(-198.f, 198.f));
	ExpName->TextSetting("diablo", "??????", 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	CurExpRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	CurExpRenderer_->GetTransform()->SetLocalPosition(float4(-198.f, 184.f));

	// ?????? ??
	GameEngineUIRenderer* StrengthName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	StrengthName->GetTransform()->SetLocalPosition(float4(-278.f, 148.f));
	StrengthName->TextSetting("diablo", "??", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	StrengthRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	StrengthRenderer_->GetTransform()->SetLocalPosition(float4(-224.f, 148.f));

	// ?????? ????
	GameEngineUIRenderer* DexterityName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	DexterityName->GetTransform()->SetLocalPosition(float4(-278.f, 86.f));
	DexterityName->TextSetting("diablo", "????", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	DexterityRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	DexterityRenderer_->GetTransform()->SetLocalPosition(float4(-224.f, 86.f));

	// ?????? ??????
	GameEngineUIRenderer* VitalityName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	VitalityName->GetTransform()->SetLocalPosition(float4(-278.f, 0.f));
	VitalityName->TextSetting("diablo", "??????", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	VitalityRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	VitalityRenderer_->GetTransform()->SetLocalPosition(float4(-224.f, 0.f));

	// ?????? ??????
	GameEngineUIRenderer* EnergyName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	EnergyName->GetTransform()->SetLocalPosition(float4(-278.f, -62.f));
	EnergyName->TextSetting("diablo", "??????", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	EnergyRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	EnergyRenderer_->GetTransform()->SetLocalPosition(float4(-224.f, -62.f));

	// ?????? ??????????(????)-?????? ??????????(????)
	GameEngineUIRenderer* AttackName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	AttackName->GetTransform()->SetLocalPosition(float4(-110.f, 150.f));
	AttackName->TextSetting("diablo", "????", 9, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	GameEngineUIRenderer* DamageName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	DamageName->GetTransform()->SetLocalPosition(float4(-110.f, 142.f));
	DamageName->TextSetting("diablo", "??????", 9, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	DamageRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	DamageRenderer_->GetTransform()->SetLocalPosition(float4(-34.f, 148.f));
	
	// ?????? ????????
	GameEngineUIRenderer* RatingAttackName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	RatingAttackName->GetTransform()->SetLocalPosition(float4(-110.f, 90.f));
	RatingAttackName->TextSetting("diablo", "????", 9, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	GameEngineUIRenderer* RatingName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	RatingName->GetTransform()->SetLocalPosition(float4(-110.f, 82.f));
	RatingName->TextSetting("diablo", "????", 9, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	AttackRatingRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	AttackRatingRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, 86.f));

	// ?????? ????
	GameEngineUIRenderer* DefenseName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	DefenseName->GetTransform()->SetLocalPosition(float4(-110.f, 38.f));
	DefenseName->TextSetting("diablo", "????", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	DefenseRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	DefenseRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, 38.f));

	// ?????? ????????
	GameEngineUIRenderer* StaminaName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	StaminaName->GetTransform()->SetLocalPosition(float4(-126.f, -2.f));
	StaminaName->TextSetting("diablo", "????????", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	StaminaRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	StaminaRenderer_->GetTransform()->SetLocalPosition(float4(-70.f, 0.f));

	// ?????? ??????
	GameEngineUIRenderer* LifeName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	LifeName->GetTransform()->SetLocalPosition(float4(-126.f, -26.f));
	LifeName->TextSetting("diablo", "??????", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	LifeRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	LifeRenderer_->GetTransform()->SetLocalPosition(float4(-70.f, -24.f));

	// ?????? ????
	GameEngineUIRenderer* ManaName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	ManaName->GetTransform()->SetLocalPosition(float4(-126.f, -64.f));
	ManaName->TextSetting("diablo", "????", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	ManaRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	ManaRenderer_->GetTransform()->SetLocalPosition(float4(-70.f, -62.f));

	// ?????? ?????? ??????
	GameEngineUIRenderer* FireResistanceName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	FireResistanceName->GetTransform()->SetLocalPosition(float4(-98.f, -102.f));
	FireResistanceName->TextSetting("diablo", "?????? ??????", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	FireResistanceRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	FireResistanceRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, -102.f));

	// ?????? ???? ??????
	GameEngineUIRenderer* ColdResistanceName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	ColdResistanceName->GetTransform()->SetLocalPosition(float4(-98.f, -126.f));
	ColdResistanceName->TextSetting("diablo", "???? ??????", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	ColdResistanceRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	ColdResistanceRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, -126.f));

	// ?????? ???????? ??????
	GameEngineUIRenderer* LightningResistanceName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	LightningResistanceName->GetTransform()->SetLocalPosition(float4(-98.f, -150.f));
	LightningResistanceName->TextSetting("diablo", "???????? ??????", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	LightningResistanceRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	LightningResistanceRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, -150.f));

	// ?????? ?????? ??????
	GameEngineUIRenderer* PoisonResistanceName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	PoisonResistanceName->GetTransform()->SetLocalPosition(float4(-98.f, -174.f));
	PoisonResistanceName->TextSetting("diablo", "?????? ??????", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	PoisonResistanceRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));
	PoisonResistanceRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, -174.f));

	// ????????
	CloseButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
	CloseButton_->CreateAnimation("CloseButton_Default.png", "Default", 0, 0, 0.1f, false);
	CloseButton_->CreateAnimation("CloseButton_Click.png", "Click", 0, 0, 0.1f, false);
	CloseButton_->GetTransform()->SetLocalScaling(float4(32.f, 32.f, 1.f));
	CloseButton_->GetTransform()->SetLocalPosition(float4(-176.f, -166.f));
	CloseButton_->SetChangeAnimation("Default");

	MainCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	MainCollider_->GetTransform()->SetLocalScaling(float4(32.f, 32.f, 1.0f));
	MainCollider_->GetTransform()->SetLocalPosition(CloseButton_->GetTransform()->GetLocalPosition());

	// ???????? ?????? ???? ????(??,????,??????,??????)
	
	// Button Image Cutting
	GameEngineTexture* PointBtnDefault = GameEngineTextureManager::GetInst().Find("LevelUpButton_Default.png");
	ButtonDefault->Cut(1, 1);
	GameEngineTexture* PointBtnClick = GameEngineTextureManager::GetInst().Find("LevelUpButton_Click.png");
	ButtonClick->Cut(1, 1);
	GameEngineTexture* PointBtnDisabled = GameEngineTextureManager::GetInst().Find("LevelUpButton_Disabled.png");
	PointBtnDisabled->Cut(1, 1);

	// ??
	STRPointUpButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
	STRPointUpButton_->CreateAnimation("LevelUpButton_Default.png", "Default", 0, 0, 0.1f, false);
	STRPointUpButton_->CreateAnimation("LevelUpButton_Click.png", "Click", 0, 0, 0.1f, false);
	STRPointUpButton_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.f));
	STRPointUpButton_->GetTransform()->SetLocalPosition(float4(-178.f, 148.f));
	STRPointUpButton_->SetChangeAnimation("Default");
	STRPointUpButton_->Off();

	STRPointUpButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	STRPointUpButtonCollider_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.0f));
	STRPointUpButtonCollider_->GetTransform()->SetLocalPosition(STRPointUpButton_->GetTransform()->GetLocalPosition());
	STRPointUpButtonCollider_->Off();

	// ????
	DEXPointUpButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
	DEXPointUpButton_->CreateAnimation("LevelUpButton_Default.png", "Default", 0, 0, 0.1f, false);
	DEXPointUpButton_->CreateAnimation("LevelUpButton_Click.png", "Click", 0, 0, 0.1f, false);
	DEXPointUpButton_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.f));
	DEXPointUpButton_->GetTransform()->SetLocalPosition(float4(-178.f, 86.f));
	DEXPointUpButton_->SetChangeAnimation("Default");
	DEXPointUpButton_->Off();

	DEXPointUpButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	DEXPointUpButtonCollider_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.0f));
	DEXPointUpButtonCollider_->GetTransform()->SetLocalPosition(DEXPointUpButton_->GetTransform()->GetLocalPosition());
	DEXPointUpButtonCollider_->Off();

	// ??????
	VITPointUpButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
	VITPointUpButton_->CreateAnimation("LevelUpButton_Default.png", "Default", 0, 0, 0.1f, false);
	VITPointUpButton_->CreateAnimation("LevelUpButton_Click.png", "Click", 0, 0, 0.1f, false);
	VITPointUpButton_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.f));
	VITPointUpButton_->GetTransform()->SetLocalPosition(float4(-178.f, 0.f));
	VITPointUpButton_->SetChangeAnimation("Default");
	VITPointUpButton_->Off();

	VITPointUpButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	VITPointUpButtonCollider_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.0f));
	VITPointUpButtonCollider_->GetTransform()->SetLocalPosition(VITPointUpButton_->GetTransform()->GetLocalPosition());
	VITPointUpButtonCollider_->Off();

	// ??????
	ENRPointUpButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Button));
	ENRPointUpButton_->CreateAnimation("LevelUpButton_Default.png", "Default", 0, 0, 0.1f, false);
	ENRPointUpButton_->CreateAnimation("LevelUpButton_Click.png", "Click", 0, 0, 0.1f, false);
	ENRPointUpButton_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.f));
	ENRPointUpButton_->GetTransform()->SetLocalPosition(float4(-178.f, -62.f));
	ENRPointUpButton_->SetChangeAnimation("Default");
	ENRPointUpButton_->Off();

	ENRPointUpButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	ENRPointUpButtonCollider_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.0f));
	ENRPointUpButtonCollider_->GetTransform()->SetLocalPosition(ENRPointUpButton_->GetTransform()->GetLocalPosition());
	ENRPointUpButtonCollider_->Off();

	Off();
}

void StatView::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(PanelCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->UIPushDebugRender(MainCollider_->GetTransform(), CollisionType::Rect);

	if (true == STRPointUpButtonCollider_->IsUpdate())
	{
		GetLevel()->UIPushDebugRender(STRPointUpButtonCollider_->GetTransform(), CollisionType::Rect);
	}

	if (true == DEXPointUpButtonCollider_->IsUpdate())
	{
		GetLevel()->UIPushDebugRender(DEXPointUpButtonCollider_->GetTransform(), CollisionType::Rect);
	}

	if (true == VITPointUpButtonCollider_->IsUpdate())
	{
		GetLevel()->UIPushDebugRender(VITPointUpButtonCollider_->GetTransform(), CollisionType::Rect);
	}

	if (true == ENRPointUpButtonCollider_->IsUpdate())
	{
		GetLevel()->UIPushDebugRender(ENRPointUpButtonCollider_->GetTransform(), CollisionType::Rect);
	}
#endif // _DEBUG


	// ???????? ????????
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// MainPlayer Flag Off
			if (nullptr != GlobalValue::CurPlayer)
			{
				// ???????? ???????? ????
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

				// ?????? ????????
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->KeyInputViewProcess(0);
			}

			ButtonState_ = Button_State::Normal;
		}
	}

	// ?????????????? ????????
	// ??
	if (STRButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ?????? ?????? ???? ?? ???? ???? ????
			StatPointUP(StatPointType::STR);
			STRButtonState_ = Button_State::Normal;
			STRPointUpButton_->SetChangeAnimation("Default");
		}
	}

	// ????
	if (DEXButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ?????? ?????? ???? ?? ???? ???? ????
			StatPointUP(StatPointType::DEX);
			DEXButtonState_ = Button_State::Normal;
			DEXPointUpButton_->SetChangeAnimation("Default");
		}
	}

	// ??????
	if (VITButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ?????? ?????? ???? ?? ???? ???? ????
			StatPointUP(StatPointType::VIT);
			VITButtonState_ = Button_State::Normal;
			VITPointUpButton_->SetChangeAnimation("Default");
		}
	}

	// ??????
	if (ENRButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ?????? ?????? ???? ?? ???? ???? ????
			StatPointUP(StatPointType::ENR);
			ENRButtonState_ = Button_State::Normal;
			ENRPointUpButton_->SetChangeAnimation("Default");
		}
	}

	// ?????????????? ????????
	if (0 != StatPoint)
	{
		STRPointUpButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StatView::STRButtonClick, this, std::placeholders::_1));
		DEXPointUpButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StatView::DEXButtonClick, this, std::placeholders::_1));
		VITPointUpButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StatView::VITButtonClick, this, std::placeholders::_1));
		ENRPointUpButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StatView::ENRButtonClick, this, std::placeholders::_1));
	}

	// ???????? ???? ????
	MainCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StatView::CloseButtonClick, this, std::placeholders::_1));
}

void StatView::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// ???????? ???????? ???? ???? ????


}

void StatView::InitStatView()
{
	// ???????????? ?????? ???????? String Setting
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();

	// ?????? ID
	IDString_ = PlayerInfo.ID;
	IDRenderer_->TextSetting("diablo", IDString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ??????
	JobClassString_ = GameEngineString::WStringToStringReturn(PlayerInfo.JobName);
	JobClassRenderer_->TextSetting("diablo", JobClassString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ???? ????
	CurLevelString_ = std::to_string(PlayerInfo.Level);
	CurLevelRenderer_->TextSetting("diablo", CurLevelString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ??????
	CurExpString_ = std::to_string(PlayerInfo.Exp);
	CurExpRenderer_->TextSetting("diablo", CurExpString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ??
	StrengthString_ = std::to_string(PlayerInfo.Strength);
	StrengthRenderer_->TextSetting("diablo", StrengthString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ????
	DexterityString_ = std::to_string(PlayerInfo.Dexterity);
	DexterityRenderer_->TextSetting("diablo", DexterityString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ??????
	VitalityString_ = std::to_string(PlayerInfo.Vitality);
	VitalityRenderer_->TextSetting("diablo", VitalityString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ??????
	EnergyString_ = std::to_string(PlayerInfo.Energy);
	EnergyRenderer_->TextSetting("diablo", EnergyString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ??????????(????) - ?????? ??????????(????)
	MinDamageString_ = std::to_string(PlayerInfo.MinDamage);
	MaxDamageString_ = std::to_string(PlayerInfo.MaxDamage);
	std::string Damage = MinDamageString_;
	Damage += "-";
	Damage += MaxDamageString_;
	DamageRenderer_->TextSetting("diablo", Damage, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ????????
	AttackRatingString_ = std::to_string(PlayerInfo.AttackRating);
	AttackRatingRenderer_->TextSetting("diablo", AttackRatingString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ????
	DefenseString_ = std::to_string(PlayerInfo.Defense);
	DefenseRenderer_->TextSetting("diablo", DefenseString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ????????
	StaminaString_ = std::to_string(PlayerInfo.Stamina);
	StaminaRenderer_->TextSetting("diablo", StaminaString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ??????
	LifeString_ = std::to_string(PlayerInfo.Life);
	LifeRenderer_->TextSetting("diablo", LifeString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ????
	ManaString_ = std::to_string(PlayerInfo.Mana);
	ManaRenderer_->TextSetting("diablo", ManaString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ?????? ??????
	FireResistanceString_ = std::to_string(PlayerInfo.FireResistance);
	FireResistanceRenderer_->TextSetting("diablo", FireResistanceString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ???? ??????
	ColdResistanceString_ = std::to_string(PlayerInfo.ColdResistance);
	ColdResistanceRenderer_->TextSetting("diablo", ColdResistanceString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ???????? ??????
	LightningResistanceString_ = std::to_string(PlayerInfo.LightningResistance);
	LightningResistanceRenderer_->TextSetting("diablo", LightningResistanceString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// ?????? ?????? ??????
	PoisonResistanceString_ = std::to_string(PlayerInfo.PoisonResistance);
	PoisonResistanceRenderer_->TextSetting("diablo", PoisonResistanceString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);
}

void StatView::CloseButtonClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		CloseButton_->SetChangeAnimation("Click");

		ButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		CloseButton_->SetChangeAnimation("Default");
	}
}

void StatView::STRButtonClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		STRPointUpButton_->SetChangeAnimation("Click");

		STRButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		STRPointUpButton_->SetChangeAnimation("Default");
	}
}

void StatView::DEXButtonClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		DEXPointUpButton_->SetChangeAnimation("Click");

		DEXButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		DEXPointUpButton_->SetChangeAnimation("Default");
	}
}

void StatView::VITButtonClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		VITPointUpButton_->SetChangeAnimation("Click");

		VITButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		VITPointUpButton_->SetChangeAnimation("Default");
	}
}

void StatView::ENRButtonClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		ENRPointUpButton_->SetChangeAnimation("Click");

		ENRButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		ENRPointUpButton_->SetChangeAnimation("Default");
	}
}

void StatView::StatPointUP(StatPointType _Type)
{
	// ?????????? ???? ?? ????????
	StatPoint -= 1;

	switch (_Type)
	{
		case StatPointType::STR:
		{
			// ???????? ???? ????
			MainPlayerInfomation::GetInst().StrengthPointUP();
			
			// ?????? ?? ?????? ????
			int STR = std::stoi(StrengthString_);
			STR += 1;
			StrengthString_ = std::to_string(STR);
			StrengthRenderer_->SetPrintText(StrengthString_);

			break;
		}
		case StatPointType::DEX:
		{
			// ???????? ???? ????
			MainPlayerInfomation::GetInst().DexterityPointUP();

			// ?????? ???? ?????? ????
			int DEX = std::stoi(DexterityString_);
			DEX += 1;
			DexterityString_ = std::to_string(DEX);
			DexterityRenderer_->SetPrintText(DexterityString_);

			break;
		}
		case StatPointType::VIT:
		{
			// ???????? ???? ????
			MainPlayerInfomation::GetInst().VitalityPointUP();

			// ?????? ?????? ?????? ????
			int VIT = std::stoi(VitalityString_);
			VIT += 1;
			VitalityString_ = std::to_string(VIT);
			VitalityRenderer_->SetPrintText(VitalityString_);

			break;
		}
		case StatPointType::ENR:
		{
			// ???????? ???? ????
			MainPlayerInfomation::GetInst().EnergyPointUP();

			// ?????? ?????? ?????? ????
			int ENR = std::stoi(EnergyString_);
			ENR += 1;
			EnergyString_ = std::to_string(ENR);
			EnergyRenderer_->SetPrintText(EnergyString_);

			break;
		}
	}

	// ?????????? ???? ?????? ?????????? ??????????
	if (0 == StatPoint)
	{
		STRPointUpButton_->Off();
		STRPointUpButtonCollider_->Off();
		DEXPointUpButton_->Off();
		DEXPointUpButtonCollider_->Off();
		VITPointUpButton_->Off();
		VITPointUpButtonCollider_->Off();
		ENRPointUpButton_->Off();
		ENRPointUpButtonCollider_->Off();

		// ?????????? ?????????????? ????????
		GlobalValue::CurPlayer->GetBottomStateBar()->GetStatPointControl()->LevelUpPointExhaust();
	}
}

void StatView::CurEXPUpdate(float _EXP)
{
	// ???? ?????? ????
	float CurExp = _EXP;
	CurExp *= 1000.f;
	int ConvertEXP = static_cast<int>(CurExp);
	CurExpString_ = std::to_string(ConvertEXP);
	CurExpRenderer_->SetPrintText(CurExpString_);
}

void StatView::LevelUpStatPointGrant()
{
	// 5?????? ????
	StatPoint += 5;

	// ?????? ???????? ????
	CurLevelRenderer_->SetPrintText(std::to_string(GlobalValue::CurPlayer->GetCurrentLevel()));

	// ???? ?????? ???? ??????
	STRPointUpButton_->On();
	STRPointUpButtonCollider_->On();
	DEXPointUpButton_->On();
	DEXPointUpButtonCollider_->On();
	VITPointUpButton_->On();
	VITPointUpButtonCollider_->On();
	ENRPointUpButton_->On();
	ENRPointUpButtonCollider_->On();

	// ?????????? ?????????????? ??????
	GlobalValue::CurPlayer->GetBottomStateBar()->GetStatPointControl()->LevelUpPointButtonActive();
}
