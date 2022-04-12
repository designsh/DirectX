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
	PanelRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	PanelRenderer_->SetImage("Player_StateView_Panel.png");
	PanelRenderer_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x - WindowHarfSize.x, 24.f));

	// MainPlayer Infomation String Setting

	// 상태창 ID
	IDRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	IDRenderer_->GetTransform()->SetLocalPosition(float4(-220.f, 222.f));

	// 상태창 직업명
	JobClassRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	JobClassRenderer_->GetTransform()->SetLocalPosition(float4(-70.f, 222.f));

	// 상태창 현재 레벨
	GameEngineUIRenderer* LevelName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	LevelName->GetTransform()->SetLocalPosition(float4(-288.f, 198.f));
	LevelName->TextSetting("diablo", "레벨", 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	CurLevelRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	CurLevelRenderer_->GetTransform()->SetLocalPosition(float4(-288.f, 184.f));

	// 상태창 경험치
	GameEngineUIRenderer* ExpName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	ExpName->GetTransform()->SetLocalPosition(float4(-198.f, 198.f));
	ExpName->TextSetting("diablo", "경험치", 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	CurExpRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	CurExpRenderer_->GetTransform()->SetLocalPosition(float4(-198.f, 184.f));

	// 상태창 힘
	GameEngineUIRenderer* StrengthName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	StrengthName->GetTransform()->SetLocalPosition(float4(-278.f, 148.f));
	StrengthName->TextSetting("diablo", "힘", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	StrengthRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	StrengthRenderer_->GetTransform()->SetLocalPosition(float4(-224.f, 148.f));

	// 상태창 민첩
	GameEngineUIRenderer* DexterityName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	DexterityName->GetTransform()->SetLocalPosition(float4(-278.f, 86.f));
	DexterityName->TextSetting("diablo", "민첩", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	DexterityRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	DexterityRenderer_->GetTransform()->SetLocalPosition(float4(-224.f, 86.f));

	// 상태창 생명력
	GameEngineUIRenderer* VitalityName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	VitalityName->GetTransform()->SetLocalPosition(float4(-278.f, 0.f));
	VitalityName->TextSetting("diablo", "생명력", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	VitalityRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	VitalityRenderer_->GetTransform()->SetLocalPosition(float4(-224.f, 0.f));

	// 상태창 에너지
	GameEngineUIRenderer* EnergyName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	EnergyName->GetTransform()->SetLocalPosition(float4(-278.f, -62.f));
	EnergyName->TextSetting("diablo", "에너지", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	EnergyRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	EnergyRenderer_->GetTransform()->SetLocalPosition(float4(-224.f, -62.f));

	// 상태창 공격데미지(최소)-상태창 공격데미지(최대)
	GameEngineUIRenderer* AttackName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	AttackName->GetTransform()->SetLocalPosition(float4(-110.f, 150.f));
	AttackName->TextSetting("diablo", "공격", 9, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	GameEngineUIRenderer* DamageName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	DamageName->GetTransform()->SetLocalPosition(float4(-110.f, 142.f));
	DamageName->TextSetting("diablo", "데미지", 9, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	DamageRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	DamageRenderer_->GetTransform()->SetLocalPosition(float4(-34.f, 148.f));
	
	// 상태창 공격등급
	GameEngineUIRenderer* RatingAttackName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	RatingAttackName->GetTransform()->SetLocalPosition(float4(-110.f, 90.f));
	RatingAttackName->TextSetting("diablo", "공격", 9, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	GameEngineUIRenderer* RatingName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	RatingName->GetTransform()->SetLocalPosition(float4(-110.f, 82.f));
	RatingName->TextSetting("diablo", "등급", 9, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	AttackRatingRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	AttackRatingRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, 86.f));

	// 상태창 방어
	GameEngineUIRenderer* DefenseName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	DefenseName->GetTransform()->SetLocalPosition(float4(-110.f, 38.f));
	DefenseName->TextSetting("diablo", "방어", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	DefenseRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	DefenseRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, 38.f));

	// 상태창 스태미나
	GameEngineUIRenderer* StaminaName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	StaminaName->GetTransform()->SetLocalPosition(float4(-126.f, -2.f));
	StaminaName->TextSetting("diablo", "스태미나", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	StaminaRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	StaminaRenderer_->GetTransform()->SetLocalPosition(float4(-70.f, 0.f));

	// 상태창 라이프
	GameEngineUIRenderer* LifeName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	LifeName->GetTransform()->SetLocalPosition(float4(-126.f, -26.f));
	LifeName->TextSetting("diablo", "라이프", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	LifeRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	LifeRenderer_->GetTransform()->SetLocalPosition(float4(-70.f, -24.f));

	// 상태창 마나
	GameEngineUIRenderer* ManaName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	ManaName->GetTransform()->SetLocalPosition(float4(-126.f, -64.f));
	ManaName->TextSetting("diablo", "마나", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	ManaRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	ManaRenderer_->GetTransform()->SetLocalPosition(float4(-70.f, -62.f));

	// 상태창 파이어 저항력
	GameEngineUIRenderer* FireResistanceName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	FireResistanceName->GetTransform()->SetLocalPosition(float4(-98.f, -102.f));
	FireResistanceName->TextSetting("diablo", "파이어 저항력", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	FireResistanceRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	FireResistanceRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, -102.f));

	// 상태창 콜드 저항력
	GameEngineUIRenderer* ColdResistanceName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	ColdResistanceName->GetTransform()->SetLocalPosition(float4(-98.f, -126.f));
	ColdResistanceName->TextSetting("diablo", "콜드 저항력", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	ColdResistanceRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	ColdResistanceRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, -126.f));

	// 상태창 라이트닝 저항력
	GameEngineUIRenderer* LightningResistanceName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	LightningResistanceName->GetTransform()->SetLocalPosition(float4(-98.f, -150.f));
	LightningResistanceName->TextSetting("diablo", "라이트닝 저항력", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	LightningResistanceRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	LightningResistanceRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, -150.f));

	// 상태창 포이즌 저항력
	GameEngineUIRenderer* PoisonResistanceName = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	PoisonResistanceName->GetTransform()->SetLocalPosition(float4(-98.f, -174.f));
	PoisonResistanceName->TextSetting("diablo", "포이즌 저항력", 10, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	PoisonResistanceRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	PoisonResistanceRenderer_->GetTransform()->SetLocalPosition(float4(-30.f, -174.f));

	// 종료버튼
	CloseButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	CloseButton_->CreateAnimation("CloseButton_Default.png", "Default", 0, 0, 0.1f, false);
	CloseButton_->CreateAnimation("CloseButton_Click.png", "Click", 0, 0, 0.1f, false);
	CloseButton_->GetTransform()->SetLocalScaling(float4(32.f, 32.f, 1.f));
	CloseButton_->GetTransform()->SetLocalPosition(float4(-176.f, -166.f));
	CloseButton_->SetChangeAnimation("Default");

	MainCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	MainCollider_->GetTransform()->SetLocalScaling(float4(32.f, 32.f, 1.0f));
	MainCollider_->GetTransform()->SetLocalPosition(CloseButton_->GetTransform()->GetLocalPosition());

	// 레벨업시 활성화 되는 버튼(힘,민첩,생명력,에너지)
	
	// Button Image Cutting
	GameEngineTexture* PointBtnDefault = GameEngineTextureManager::GetInst().Find("LevelUpButton_Default.png");
	ButtonDefault->Cut(1, 1);
	GameEngineTexture* PointBtnClick = GameEngineTextureManager::GetInst().Find("LevelUpButton_Click.png");
	ButtonClick->Cut(1, 1);
	GameEngineTexture* PointBtnDisabled = GameEngineTextureManager::GetInst().Find("LevelUpButton_Disabled.png");
	PointBtnDisabled->Cut(1, 1);

	// 힘
	STRPointUpButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	STRPointUpButton_->CreateAnimation("LevelUpButton_Default.png", "Default", 0, 0, 0.1f, false);
	STRPointUpButton_->CreateAnimation("LevelUpButton_Click.png", "Click", 0, 0, 0.1f, false);
	STRPointUpButton_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.f));
	STRPointUpButton_->GetTransform()->SetLocalPosition(float4(-178.f, 148.f));
	STRPointUpButton_->SetChangeAnimation("Default");
	STRPointUpButton_->Off();

	STRPointUpButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	STRPointUpButtonCollider_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.0f));
	STRPointUpButtonCollider_->GetTransform()->SetLocalPosition(STRPointUpButton_->GetTransform()->GetLocalPosition());
	STRPointUpButtonCollider_->Off();

	// 민첩
	DEXPointUpButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	DEXPointUpButton_->CreateAnimation("LevelUpButton_Default.png", "Default", 0, 0, 0.1f, false);
	DEXPointUpButton_->CreateAnimation("LevelUpButton_Click.png", "Click", 0, 0, 0.1f, false);
	DEXPointUpButton_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.f));
	DEXPointUpButton_->GetTransform()->SetLocalPosition(float4(-178.f, 86.f));
	DEXPointUpButton_->SetChangeAnimation("Default");
	DEXPointUpButton_->Off();

	DEXPointUpButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	DEXPointUpButtonCollider_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.0f));
	DEXPointUpButtonCollider_->GetTransform()->SetLocalPosition(DEXPointUpButton_->GetTransform()->GetLocalPosition());
	DEXPointUpButtonCollider_->Off();

	// 생명력
	VITPointUpButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	VITPointUpButton_->CreateAnimation("LevelUpButton_Default.png", "Default", 0, 0, 0.1f, false);
	VITPointUpButton_->CreateAnimation("LevelUpButton_Click.png", "Click", 0, 0, 0.1f, false);
	VITPointUpButton_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.f));
	VITPointUpButton_->GetTransform()->SetLocalPosition(float4(-178.f, 0.f));
	VITPointUpButton_->SetChangeAnimation("Default");
	VITPointUpButton_->Off();

	VITPointUpButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	VITPointUpButtonCollider_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.0f));
	VITPointUpButtonCollider_->GetTransform()->SetLocalPosition(VITPointUpButton_->GetTransform()->GetLocalPosition());
	VITPointUpButtonCollider_->Off();

	// 에너지
	ENRPointUpButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	ENRPointUpButton_->CreateAnimation("LevelUpButton_Default.png", "Default", 0, 0, 0.1f, false);
	ENRPointUpButton_->CreateAnimation("LevelUpButton_Click.png", "Click", 0, 0, 0.1f, false);
	ENRPointUpButton_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.f));
	ENRPointUpButton_->GetTransform()->SetLocalPosition(float4(-178.f, -62.f));
	ENRPointUpButton_->SetChangeAnimation("Default");
	ENRPointUpButton_->Off();

	ENRPointUpButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	ENRPointUpButtonCollider_->GetTransform()->SetLocalScaling(float4(30.f, 30.f, 1.0f));
	ENRPointUpButtonCollider_->GetTransform()->SetLocalPosition(ENRPointUpButton_->GetTransform()->GetLocalPosition());
	ENRPointUpButtonCollider_->Off();

	Off();
}

void StatView::Update(float _DeltaTime)
{
	// 종료버튼 클릭체크
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// MainPlayer Flag Off
			if (nullptr != GlobalValue::CurPlayer)
			{
				// 미니메뉴 원래자리 복귀
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

				// 스탯창 비활성화
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->KeyInputViewProcess(0);
			}

			ButtonState_ = Button_State::Normal;
		}
	}

	// 포인트증가버튼 클릭체크
	// 힘
	if (STRButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 상태별 포인트 증가 및 관련 스탯 증가
			StatPointUP(StatPointType::STR);
			STRButtonState_ = Button_State::Normal;
			STRPointUpButton_->SetChangeAnimation("Default");
		}
	}

	// 민첩
	if (DEXButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 상태별 포인트 증가 및 관련 스탯 증가
			StatPointUP(StatPointType::DEX);
			DEXButtonState_ = Button_State::Normal;
			DEXPointUpButton_->SetChangeAnimation("Default");
		}
	}

	// 생명력
	if (VITButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 상태별 포인트 증가 및 관련 스탯 증가
			StatPointUP(StatPointType::VIT);
			VITButtonState_ = Button_State::Normal;
			VITPointUpButton_->SetChangeAnimation("Default");
		}
	}

	// 에너지
	if (ENRButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 상태별 포인트 증가 및 관련 스탯 증가
			StatPointUP(StatPointType::ENR);
			ENRButtonState_ = Button_State::Normal;
			ENRPointUpButton_->SetChangeAnimation("Default");
		}
	}

	// 포인트증가버튼 충돌체크
	if (0 != StatPoint)
	{
		STRPointUpButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StatView::STRButtonClick, this, std::placeholders::_1));
		DEXPointUpButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StatView::DEXButtonClick, this, std::placeholders::_1));
		VITPointUpButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StatView::VITButtonClick, this, std::placeholders::_1));
		ENRPointUpButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StatView::ENRButtonClick, this, std::placeholders::_1));
	}

	// 종료버튼 충돌 체크
	MainCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StatView::CloseButtonClick, this, std::placeholders::_1));
}

void StatView::InitStatView()
{
	// 메인플레이어 정보를 이용하여 String Setting
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();

	// 상태창 ID
	IDString_ = PlayerInfo.ID;
	IDRenderer_->TextSetting("diablo", IDString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 직업명
	JobClassString_ = GameEngineString::WStringToStringReturn(PlayerInfo.JobName);
	JobClassRenderer_->TextSetting("diablo", JobClassString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 현재 레벨
	CurLevelString_ = std::to_string(PlayerInfo.Level);
	CurLevelRenderer_->TextSetting("diablo", CurLevelString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 경험치
	CurExpString_ = std::to_string(PlayerInfo.Exp);
	CurExpRenderer_->TextSetting("diablo", CurExpString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 힘
	StrengthString_ = std::to_string(PlayerInfo.Strength);
	StrengthRenderer_->TextSetting("diablo", StrengthString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 민첩
	DexterityString_ = std::to_string(PlayerInfo.Dexterity);
	DexterityRenderer_->TextSetting("diablo", DexterityString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 생명력
	VitalityString_ = std::to_string(PlayerInfo.Vitality);
	VitalityRenderer_->TextSetting("diablo", VitalityString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 에너지
	EnergyString_ = std::to_string(PlayerInfo.Energy);
	EnergyRenderer_->TextSetting("diablo", EnergyString_, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 공격데미지(최소) - 상태창 공격데미지(최대)
	MinDamageString_ = std::to_string(PlayerInfo.MinDamage);
	MaxDamageString_ = std::to_string(PlayerInfo.MaxDamage);
	std::string Damage = MinDamageString_;
	Damage += "-";
	Damage += MaxDamageString_;
	DamageRenderer_->TextSetting("diablo", Damage, 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 공격등급
	AttackRatingString_ = std::to_string(PlayerInfo.AttackRating);
	AttackRatingRenderer_->TextSetting("diablo", AttackRatingString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 방어
	DefenseString_ = std::to_string(PlayerInfo.Defense);
	DefenseRenderer_->TextSetting("diablo", DefenseString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 스태미나
	StaminaString_ = std::to_string(PlayerInfo.Stamina);
	StaminaRenderer_->TextSetting("diablo", StaminaString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 라이프
	LifeString_ = std::to_string(PlayerInfo.Life);
	LifeRenderer_->TextSetting("diablo", LifeString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 마나
	ManaString_ = std::to_string(PlayerInfo.Mana);
	ManaRenderer_->TextSetting("diablo", ManaString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 파이어 저항력
	FireResistanceString_ = std::to_string(PlayerInfo.FireResistance);
	FireResistanceRenderer_->TextSetting("diablo", FireResistanceString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 콜드 저항력
	ColdResistanceString_ = std::to_string(PlayerInfo.ColdResistance);
	ColdResistanceRenderer_->TextSetting("diablo", ColdResistanceString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 라이트닝 저항력
	LightningResistanceString_ = std::to_string(PlayerInfo.LightningResistance);
	LightningResistanceRenderer_->TextSetting("diablo", LightningResistanceString_, 13, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	// 상태창 포이즌 저항력
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
	// 스탯포인트 감소 후 스탯증가
	StatPoint -= 1;

	switch (_Type)
	{
		case StatPointType::STR:
		{
			// 플레이어 정보 갱신
			MainPlayerInfomation::GetInst().StrengthPointUP();
			
			// 상태창 힘 텍스트 갱신
			int STR = std::stoi(StrengthString_);
			STR += 1;
			StrengthString_ = std::to_string(STR);
			StrengthRenderer_->SetPrintText(StrengthString_);

			break;
		}
		case StatPointType::DEX:
		{
			// 플레이어 정보 갱신
			MainPlayerInfomation::GetInst().DexterityPointUP();

			// 상태창 민첩 텍스트 갱신
			int DEX = std::stoi(DexterityString_);
			DEX += 1;
			DexterityString_ = std::to_string(DEX);
			DexterityRenderer_->SetPrintText(DexterityString_);

			break;
		}
		case StatPointType::VIT:
		{
			// 플레이어 정보 갱신
			MainPlayerInfomation::GetInst().VitalityPointUP();

			// 상태창 생명력 텍스트 갱신
			int VIT = std::stoi(VitalityString_);
			VIT += 1;
			VitalityString_ = std::to_string(VIT);
			VitalityRenderer_->SetPrintText(VitalityString_);

			break;
		}
		case StatPointType::ENR:
		{
			// 플레이어 정보 갱신
			MainPlayerInfomation::GetInst().EnergyPointUP();

			// 상태창 에너지 텍스트 갱신
			int ENR = std::stoi(EnergyString_);
			ENR += 1;
			EnergyString_ = std::to_string(ENR);
			EnergyRenderer_->SetPrintText(EnergyString_);

			break;
		}
	}

	// 스탯포인트 모두 소멸시 포인트버튼 비활성처리
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

		// 하단상태바 스탯포인트버튼 비활성화
		GlobalValue::CurPlayer->GetBottomStateBar()->GetStatPointControl()->LevelUpPointExhaust();
	}
}

void StatView::CurEXPUpdate(float _EXP)
{
	// 현재 경험치 갱신
	float CurExp = _EXP;
	CurExp *= 100.f;
	int ConvertEXP = static_cast<int>(CurExp);
	CurExpString_ = std::to_string(ConvertEXP);
	CurExpRenderer_->SetPrintText(CurExpString_);
}

void StatView::LevelUpStatPointGrant()
{
	// 5포인트 부여
	StatPoint += 5;

	// 스탯창 현재레벨 갱신
	CurLevelRenderer_->SetPrintText(std::to_string(GlobalValue::CurPlayer->GetCurrentLevel()));

	// 스탯 레벨업 버튼 활성화
	STRPointUpButton_->On();
	STRPointUpButtonCollider_->On();
	DEXPointUpButton_->On();
	DEXPointUpButtonCollider_->On();
	VITPointUpButton_->On();
	VITPointUpButtonCollider_->On();
	ENRPointUpButton_->On();
	ENRPointUpButtonCollider_->On();

	// 하단상태바 스탯포인트버튼 활성화
	GlobalValue::CurPlayer->GetBottomStateBar()->GetStatPointControl()->LevelUpPointButtonActive();
}
