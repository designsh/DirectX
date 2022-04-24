#include "PreCompile.h"
#include "MainPlayer_SkillIcon.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

#include "BottomStateBar.h"
#include "MainPlayer_LeftWeaponSkillButton.h"
#include "MainPlayer_RightWeaponSkillButton.h"

#include "SkillView.h"

MainPlayer_SkillIcon::MainPlayer_SkillIcon() :
	PageNo_(SkillPageNo::NONE),
	SkillName_{},
	SkillCode_(-1),
	SkillActive_(false),
	SkillPageRow_(-1),
	SkillPageColumn_(-1),
	SkillPos_(float4::ZERO),
	CurSkillLevel_(0),
	IconRenderer_(nullptr),
	IconCollision_(nullptr),
	CurLevelRenderer_(nullptr),
	ButtonState_(Button_State::Normal)
{
}

MainPlayer_SkillIcon::~MainPlayer_SkillIcon()
{
}

void MainPlayer_SkillIcon::Start()
{
}

void MainPlayer_SkillIcon::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(IconCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	// ��ų������ Ŭ�� üũ
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// �ش� ��ų ������
			SkillLevelUp();

			ButtonState_ = Button_State::Normal;
		}
	}

	// �ش� ��ų�� Ȱ��ȭ �Ǿ������ʴٸ� �浹üũ ����
	if (true == SkillActive_ && nullptr != IconCollision_)
	{
		IconCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_SkillIcon::SkillIconClick, this, std::placeholders::_1));
	}
}

void MainPlayer_SkillIcon::SkillIconClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		IconRenderer_->SetChangeAnimation("Click");

		ButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		IconRenderer_->SetChangeAnimation("Default");
	}
}

void MainPlayer_SkillIcon::SkillLevelUp()
{
	// ���� �������϶�
	if (0 == CurSkillLevel_)
	{
		if (nullptr != GlobalValue::CurPlayer)
		{
			// �����ʽ�ų��Ͽ� �ش� ��ų��ư �߰�
			GlobalValue::CurPlayer->GetBottomStateBar()->GetRightWeaponSkillControl()->UpdateWeaponSkillList(SkillCode_);

			// ���ʽ�ų�� ��밡�ɿ��� �Ǵ��Ͽ� ��밡���ϴٸ� ���ʽ�ų��Ͽ� �ش� ��ų��ư �߰�
			if (true == MainPlayerInfomation::GetInst().PlayerLeftSkillUseCheck(SkillCode_))
			{
				GlobalValue::CurPlayer->GetBottomStateBar()->GetLeftWeaponSkillControl()->UpdateWeaponSkillList(SkillCode_);
			}
		}
	}

	// �ش� ��ų������
	CurSkillLevel_ += 1;

	// �÷��̾� ��ų������ ���� ����
	MainPlayerInfomation::GetInst().PlayerSkillLevelUp(SkillCode_);

	// ��ų ���緹�� �ؽ�Ʈ ����
	CurLevelRenderer_->SetPrintText(std::to_string(CurSkillLevel_));

	// �ο��� ��ų����Ʈ ����
	if (nullptr != GlobalValue::CurPlayer)
	{
		GlobalValue::CurPlayer->GetSkillView()->SkillPointDeduction();
	}
}

void MainPlayer_SkillIcon::CreateSkillIcon(SkillPageNo _PageNo, const std::string& _SkillName, int _SkillCode, bool _SkillActiveFlag, int _Row, int _Column, int _CurSkillLevel)
{
	// �⺻���� ����
	PageNo_ = _PageNo;
	SkillName_ = _SkillName;
	SkillCode_ = _SkillCode;
	SkillActive_ = _SkillActiveFlag;
	SkillPageRow_ = _Row;
	SkillPageColumn_ = _Column;
	CurSkillLevel_ = _CurSkillLevel;

	// Screen Harf Size Get
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// Create SkillIcon Renderer
	IconRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1));
	IconRenderer_->GetTransform()->SetLocalScaling(float4(48.f, 48.f, 1.f));

	// Ȱ��ȭ
	std::string DefaultTexName = SkillName_;
	DefaultTexName += "_Default";
	DefaultTexName += ".png";
	GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTexName);
	if (nullptr != DefaultTexture)
	{
		DefaultTexture->Cut(1, 1);
		IconRenderer_->CreateAnimation(DefaultTexName, "Default", 0, 0, 0.1f, false);
	}

	// Ŭ��
	std::string ClickTexName = SkillName_;
	ClickTexName += "_Click";
	ClickTexName += ".png";
	GameEngineTexture* ClickTexture = GameEngineTextureManager::GetInst().Find(ClickTexName);
	if (nullptr != ClickTexture)
	{
		ClickTexture->Cut(1, 1);
		IconRenderer_->CreateAnimation(ClickTexName, "Click", 0, 0, 0.1f, false);
	}

	// ��Ȱ��ȭ
	std::string InactiveTexName = SkillName_;
	InactiveTexName += "_Inactive";
	InactiveTexName += ".png";
	GameEngineTexture* InactiveTexture = GameEngineTextureManager::GetInst().Find(InactiveTexName);
	if (nullptr != InactiveTexture)
	{
		InactiveTexture->Cut(1, 1);
		IconRenderer_->CreateAnimation(InactiveTexName, "Inactive", 0, 0, 0.1f, false);
	}

	// Renderer Pos Calc
	float4 CalcPos = float4::ZERO;
	CalcPos.x = 40.f + (68.f * (SkillPageColumn_ - 1));
	CalcPos.y = 202.f - (68.f * (SkillPageRow_ - 1));
	IconRenderer_->GetTransform()->SetLocalPosition(CalcPos);

	// ��Ȱ�� ����(�⺻)
	IconRenderer_->SetChangeAnimation("Inactive");

	// Create SkillIcon Collsion
	IconCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI1_Collider));
	IconCollision_->GetTransform()->SetLocalScaling(IconRenderer_->GetTransform()->GetLocalScaling());
	IconCollision_->GetTransform()->SetLocalPosition(IconRenderer_->GetTransform()->GetLocalPosition());

	// Create Skill CurLevel Text Renderer
	CurLevelRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI1_Text));

	// Calc TextPos
	float4 TextCalcPos = float4::ZERO;
	TextCalcPos = IconRenderer_->GetTransform()->GetLocalPosition();
	TextCalcPos.x += 28.f;
	TextCalcPos.y -= 28.f;
	CurLevelRenderer_->GetTransform()->SetLocalPosition(TextCalcPos);
	CurLevelRenderer_->TextSetting("diablo", std::to_string(CurSkillLevel_), 15, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	Off();
}

void MainPlayer_SkillIcon::SetSkillIconActive()
{
	// �ش� ��ų������ Ȱ��ȭ
	SkillActive_ = true;
	IconRenderer_->SetChangeAnimation("Default");
}

void MainPlayer_SkillIcon::SetSkillIconInactvie()
{
	// �ش� ��ų������ ��Ȱ��ȭ
	SkillActive_ = false;
	IconRenderer_->SetChangeAnimation("Inactive");
}
