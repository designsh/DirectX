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

	// 스킬아이콘 클릭 체크
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 해당 스킬 레벨업
			SkillLevelUp();

			ButtonState_ = Button_State::Normal;
		}
	}

	// 해당 스킬이 활성화 되어있지않다면 충돌체크 안함
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
	// 최초 레벨업일때
	if (0 == CurSkillLevel_)
	{
		if (nullptr != GlobalValue::CurPlayer)
		{
			// 오른쪽스킬목록에 해당 스킬버튼 추가
			GlobalValue::CurPlayer->GetBottomStateBar()->GetRightWeaponSkillControl()->UpdateWeaponSkillList(SkillCode_);

			// 왼쪽스킬로 사용가능여부 판단하여 사용가능하다면 왼쪽스킬목록에 해당 스킬버튼 추가
			if (true == MainPlayerInfomation::GetInst().PlayerLeftSkillUseCheck(SkillCode_))
			{
				GlobalValue::CurPlayer->GetBottomStateBar()->GetLeftWeaponSkillControl()->UpdateWeaponSkillList(SkillCode_);
			}
		}
	}

	// 해당 스킬레벨업
	CurSkillLevel_ += 1;

	// 플레이어 스킬정보에 레벨 갱신
	MainPlayerInfomation::GetInst().PlayerSkillLevelUp(SkillCode_);

	// 스킬 현재레벨 텍스트 갱신
	CurLevelRenderer_->SetPrintText(std::to_string(CurSkillLevel_));

	// 부여된 스킬포인트 차감
	if (nullptr != GlobalValue::CurPlayer)
	{
		GlobalValue::CurPlayer->GetSkillView()->SkillPointDeduction();
	}
}

void MainPlayer_SkillIcon::CreateSkillIcon(SkillPageNo _PageNo, const std::string& _SkillName, int _SkillCode, bool _SkillActiveFlag, int _Row, int _Column, int _CurSkillLevel)
{
	// 기본정보 셋팅
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

	// 활성화
	std::string DefaultTexName = SkillName_;
	DefaultTexName += "_Default";
	DefaultTexName += ".png";
	GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTexName);
	if (nullptr != DefaultTexture)
	{
		DefaultTexture->Cut(1, 1);
		IconRenderer_->CreateAnimation(DefaultTexName, "Default", 0, 0, 0.1f, false);
	}

	// 클릭
	std::string ClickTexName = SkillName_;
	ClickTexName += "_Click";
	ClickTexName += ".png";
	GameEngineTexture* ClickTexture = GameEngineTextureManager::GetInst().Find(ClickTexName);
	if (nullptr != ClickTexture)
	{
		ClickTexture->Cut(1, 1);
		IconRenderer_->CreateAnimation(ClickTexName, "Click", 0, 0, 0.1f, false);
	}

	// 비활성화
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

	// 비활성 상태(기본)
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
	// 해당 스킬아이콘 활성화
	SkillActive_ = true;
	IconRenderer_->SetChangeAnimation("Default");
}

void MainPlayer_SkillIcon::SetSkillIconInactvie()
{
	// 해당 스킬아이콘 비활성화
	SkillActive_ = false;
	IconRenderer_->SetChangeAnimation("Inactive");
}
