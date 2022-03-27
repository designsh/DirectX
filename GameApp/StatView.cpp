#include "PreCompile.h"
#include "StatView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

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
	ButtonState_(Button_State::Normal)
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
	MainCollider_->GetTransform()->SetLocalScaling(float4(96.f, 32.f, 1.0f));
	MainCollider_->GetTransform()->SetLocalPosition(CloseButton_->GetTransform()->GetLocalPosition());

	Off();
}

void StatView::Update(float _DeltaTime)
{
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// MainPlayer Flag Off
			if (nullptr != GlobalValue::CurPlayer)
			{
				GlobalValue::CurPlayer->StateViewEnabled(false);
			}

			ButtonState_ = Button_State::Normal;
		}
	}

	MainCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&StatView::CloseButtonClick, this, std::placeholders::_1));
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
