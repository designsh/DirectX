#include "PreCompile.h"
#include "MainPlayer_RightWeaponSkillButton.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "UserGame.h"
#include "GlobalValue.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

#include "MainPlayer_WeaponSkillButton.h"

MainPlayer_RightWeaponSkillButton::MainPlayer_RightWeaponSkillButton() :
	IsActive_(false),
	ButtonState_(Button_State::Normal),
	CurSkillButton_(nullptr),
	CurSkillButtonCollision_(nullptr),
	CurSkillCode_(-1),
	SkillListPushCount_{ 0, }
{
}

MainPlayer_RightWeaponSkillButton::~MainPlayer_RightWeaponSkillButton()
{
}

void MainPlayer_RightWeaponSkillButton::PlayerIsTownCheck()
{
	// 플레이어가 마을에 있는지 체크하여 마을에 위치한다면 현재 선택된 스킬 비활성화
	if (true == GlobalValue::CurPlayer->GetIsTown())
	{
		CurSkillButton_->SetChangeAnimation("Disabled");

		ButtonState_ = Button_State::Disabled;
	}

	if (false == GlobalValue::CurPlayer->GetIsTown() && ButtonState_ == Button_State::Disabled)
	{
		CurSkillButton_->SetChangeAnimation("Default");

		ButtonState_ = Button_State::Normal;
	}
}

void MainPlayer_RightWeaponSkillButton::Start()
{
	// Button Image Cutting
	GameEngineTexture* AttackDefault = GameEngineTextureManager::GetInst().Find("Attack_Default.png");
	AttackDefault->Cut(1, 1);
	GameEngineTexture* AttackClick = GameEngineTextureManager::GetInst().Find("Attack_Click.png");
	AttackClick->Cut(1, 1);
	GameEngineTexture* AttackDisabled = GameEngineTextureManager::GetInst().Find("Attack_Disabled.png");
	AttackDisabled->Cut(1, 1);

	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// 현재 선택된 왼쪽 무기 스킬 
	CurSkillButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));
	CurSkillButton_->CreateAnimation("Attack_Default.png", "Default", 0, 0, 0.1f, false);
	CurSkillButton_->CreateAnimation("Attack_Click.png", "Click", 0, 0, 0.1f, false);
	CurSkillButton_->CreateAnimation("Attack_Disabled.png", "Disabled", 0, 0, 0.1f, false);
	CurSkillButton_->GetTransform()->SetLocalScaling(float4(50.f, 48.f));
	CurSkillButton_->GetTransform()->SetLocalPosition(float4(ScreenHarfSize.x - 140.f, 24.f - ScreenHarfSize.y));
	CurSkillButton_->SetChangeAnimation("Default");

	// 현재 선택된 왼쪽 무기 스킬 충돌체
	CurSkillButtonCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI11_Collider));
	CurSkillButtonCollision_->GetTransform()->SetLocalScaling(float4(48.f, 48.f));
	CurSkillButtonCollision_->GetTransform()->SetLocalPosition(CurSkillButton_->GetTransform()->GetLocalPosition());

	// 현재 스킬 코드 저장(기본공격)
	CurSkillCode_ = 0;
}

void MainPlayer_RightWeaponSkillButton::Update(float _DeltaTime)
{
	PlayerIsTownCheck();

	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 왼쪽 무기 활성화 스킬목록 활성화/비활성화
			if (false == IsActive_)
			{
				IsActive_ = true;
			}
			else
			{
				IsActive_ = false;
			}
			RWeaponActiveSkillListView(IsActive_);

			ButtonState_ = Button_State::Normal;
		}
	}

	CurSkillButtonCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_RightWeaponSkillButton::CurRWeaponSkillBtnCol, this, std::placeholders::_1));
}

void MainPlayer_RightWeaponSkillButton::UpdateWeaponSkillList(int _SkillID)
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// 새롭게 활성화된 왼쪽무기 스킬을 목록에 추가한다.
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();

	int SkillSize = static_cast<int>(PlayerInfo.SkillInfo.size());
	for (int i = 0; i < SkillSize; ++i)
	{
		if (PlayerInfo.SkillInfo[i].SkillCode == _SkillID)
		{
			// 필요 정보 Get
			int PageNo = PlayerInfo.SkillInfo[i].SkillPage;
			int SkillID = _SkillID;
			int PushNo = SkillListPushCount_[PageNo];

			// 위치 계산
			float4 CalcPos = float4(ScreenHarfSize.x - 140.f, 80.f - ScreenHarfSize.y);
			CalcPos.x -= (48.f * PushNo);
			CalcPos.y += (48.f * PageNo);

			// 스킬 버튼 생성
			MainPlayer_WeaponSkillButton* NewSkillBtnActor = GetLevel()->CreateActor<MainPlayer_WeaponSkillButton>();
			NewSkillBtnActor->SetWeaponDirType(DirectType::Right);
			NewSkillBtnActor->CreateSkillButton(PageNo, CalcPos, SkillID);

			RWeaponSkillList_.push_back(NewSkillBtnActor);

			++SkillListPushCount_[PageNo];

			break;
		}
	}
}

void MainPlayer_RightWeaponSkillButton::InitRWeaponSkillList()
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// 초기 활성화된 왼쪽무기 스킬목록을 생성한다.
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();

	int SkillSize = static_cast<int>(PlayerInfo.SkillInfo.size());
	for (int i = 0; i < SkillSize; ++i)
	{
		// 현재 활성화되어있는 스킬을 목록에 추가
		if (true == PlayerInfo.SkillInfo[i].SkillActive)
		{
			// 필요 정보 Get
			int PageNo = PlayerInfo.SkillInfo[i].SkillPage;
			int SkillID = PlayerInfo.SkillInfo[i].SkillCode;
			int PushNo = SkillListPushCount_[PageNo];

			// 위치 계산
			float4 CalcPos = float4(ScreenHarfSize.x - 140.f, 80.f - ScreenHarfSize.y);
			CalcPos.x -= (48.f * PushNo);
			CalcPos.y += (48.f * PageNo);

			// 스킬 버튼 생성
			MainPlayer_WeaponSkillButton* NewSkillBtnActor = GetLevel()->CreateActor<MainPlayer_WeaponSkillButton>();
			NewSkillBtnActor->SetWeaponDirType(DirectType::Right);
			NewSkillBtnActor->CreateSkillButton(PageNo, CalcPos, SkillID);

			RWeaponSkillList_.push_back(NewSkillBtnActor);

			++SkillListPushCount_[PageNo];
		}
	}

	// 전역 지정
	GlobalValue::CurRightSkill = this;
}

void MainPlayer_RightWeaponSkillButton::CurRWeaponSkillBtnCol(GameEngineCollision* _Other)
{
	if (ButtonState_ != Button_State::Disabled)
	{
		// 왼쪽 무기 스킬목록 활성화
		if (true == GameEngineInput::GetInst().Down("MouseLButton"))
		{
			CurSkillButton_->SetChangeAnimation("Click");

			ButtonState_ = Button_State::Click;
		}
		else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			CurSkillButton_->SetChangeAnimation("Default");
		}
	}
}

void MainPlayer_RightWeaponSkillButton::RWeaponActiveSkillListView(bool _Flag)
{
	if (true == _Flag)
	{
		// 스킬목록 On
		int Count = static_cast<int>(RWeaponSkillList_.size());
		for (int i = 0; i < Count; ++i)
		{
			RWeaponSkillList_[i]->On();
		}
	}
	else
	{
		// 스킬목록 Off
		int Count = static_cast<int>(RWeaponSkillList_.size());
		for (int i = 0; i < Count; ++i)
		{
			RWeaponSkillList_[i]->Off();
		}
	}
}

void MainPlayer_RightWeaponSkillButton::CurSkillChange(int _SkillID, const std::string& _TextureName)
{
	// 현재 스킬 코드와 같다면 리턴
	// 단, 목록은 비활성화시킨다.
	if (CurSkillCode_ == _SkillID)
	{
		// 스킬목록 Off
		int Count = static_cast<int>(RWeaponSkillList_.size());
		for (int i = 0; i < Count; ++i)
		{
			RWeaponSkillList_[i]->Off();
		}
		IsActive_ = false;

		return;
	}

	// 현재 선택된 스킬코드 저장
	CurSkillCode_ = _SkillID;

	// 텍스쳐 이름 편집
	std::string DefaultTexture = _TextureName;
	DefaultTexture += "_Default.png";

	std::string ClickTexture = _TextureName;
	ClickTexture += "_Click.png";

	std::string DisabledTexture = _TextureName;
	DisabledTexture += "_Disabled.png";

	// 아니라면 현재 선택된 스킬 변경
	CurSkillButton_->ChangeAnimationImage("Default", DefaultTexture);
	CurSkillButton_->ChangeAnimationImage("Click", ClickTexture);
	CurSkillButton_->ChangeAnimationImage("Disabled", DisabledTexture);
	CurSkillButton_->SetChangeAnimation("Default", true);

	// 스킬목록 Off
	int Count = static_cast<int>(RWeaponSkillList_.size());
	for (int i = 0; i < Count; ++i)
	{
		RWeaponSkillList_[i]->Off();
	}
	IsActive_ = false;
}
