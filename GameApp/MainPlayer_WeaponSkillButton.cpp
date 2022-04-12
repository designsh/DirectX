#include "PreCompile.h"
#include "MainPlayer_WeaponSkillButton.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

#include "MainPlayer_LeftWeaponSkillButton.h"
#include "MainPlayer_RightWeaponSkillButton.h"

MainPlayer_WeaponSkillButton::MainPlayer_WeaponSkillButton() :
	DirectType_(DirectType::None),
	SkillPage_(-1),
	SkillID_(-1),
	PushNo_(0),
	ButtonName_(),
	SkillBtnPos_(float4::ZERO),
	ButtonState_(Button_State::Normal),
	SkillButtonRenderer_(nullptr),
	SkillButtonCollision_(nullptr)
{
}

MainPlayer_WeaponSkillButton::~MainPlayer_WeaponSkillButton()
{
}

void MainPlayer_WeaponSkillButton::Start()
{
}

void MainPlayer_WeaponSkillButton::Update(float _DeltaTime)
{
	// 버튼 상태 체크
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// 현재 스킬로 현재 선택된 스킬 전환
			SelectCurWeapon(DirectType_, SkillID_, ButtonName_);

			// 버튼 상태 전환
			ButtonState_ = Button_State::Normal;
		}
	}

	// 충돌체크
	if (nullptr != SkillButtonCollision_)
	{
		//GetLevel()->PushDebugRender(SkillButtonCollision_->GetTransform(), CollisionType::Rect);
		SkillButtonCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_WeaponSkillButton::SelectCurrentSkill, this, std::placeholders::_1));
	}
}

void MainPlayer_WeaponSkillButton::SelectCurrentSkill(GameEngineCollision* _Other)
{
	if (ButtonState_ != Button_State::Disabled)
	{
		// 왼쪽 무기 스킬목록 활성화
		if (true == GameEngineInput::GetInst().Down("MouseLButton"))
		{
			SkillButtonRenderer_->SetChangeAnimation("Click");

			ButtonState_ = Button_State::Click;
		}
		else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			SkillButtonRenderer_->SetChangeAnimation("Default");
		}
	}
}

void MainPlayer_WeaponSkillButton::CreateSkillButton(int _PushNo, const float4& _Pos, int _SkillID)
{
	// ScreenSize
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// MainPlayer Infomation Get
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();

	// 스킬 버튼 렌더러 생성
	int KillCount = static_cast<int>(PlayerInfo.SkillInfo.size());
	for (int i = 0; i < KillCount; ++i)
	{
		// 해당 일치하는 스킬 탐색
		if (PlayerInfo.SkillInfo[i].SkillCode == _SkillID)
		{
			// 정보 Write

			// 스킬 페이지
			SkillPage_ = PlayerInfo.SkillInfo[i].SkillPage;

			// 스킬 Code
			SkillID_ = PlayerInfo.SkillInfo[i].SkillCode;

			// 목록삽입 번호
			PushNo_ = _PushNo;

			// 렌더러 생성
			SkillButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));

			// 스킬 이름 저장
			ButtonName_ = PlayerInfo.SkillInfo[i].SkillName;

			// 스킬이름을 이용하여 텍스쳐명 편집

			// 디폴트
			std::string DefaultTex = ButtonName_;
			DefaultTex += "_Default";
			DefaultTex += ".png";
			GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTex);
			if (nullptr != DefaultTexture)
			{
				DefaultTexture->Cut(1, 1);
				SkillButtonRenderer_->CreateAnimation(DefaultTex, "Default", 0, 0, 0.1f, false);
			}

			// 클릭
			std::string ClickTex = ButtonName_;
			ClickTex += "_Click";
			ClickTex += ".png";
			GameEngineTexture* ClickTexture = GameEngineTextureManager::GetInst().Find(ClickTex);
			if (nullptr != ClickTexture)
			{
				ClickTexture->Cut(1, 1);
				SkillButtonRenderer_->CreateAnimation(ClickTex, "Click", 0, 0, 0.1f, false);
			}

			// 마을-비활성
			std::string DisabledTex = ButtonName_;
			DisabledTex += "_Disabled";
			DisabledTex += ".png";
			GameEngineTexture* DisabledTexture = GameEngineTextureManager::GetInst().Find(DisabledTex);
			if (nullptr != DisabledTexture)
			{
				DisabledTexture->Cut(1, 1);
				SkillButtonRenderer_->CreateAnimation(DisabledTex, "Disabled", 0, 0, 0.1f, false);

				// 위치값 저장
				SkillBtnPos_ = _Pos;

				// 크기 및 위치 지정
				SkillButtonRenderer_->GetTransform()->SetLocalScaling(float4(48.f, 48.f, 1.f));
				SkillButtonRenderer_->GetTransform()->SetLocalPosition(SkillBtnPos_);
				SkillButtonRenderer_->SetChangeAnimation("Default");
				//SkillButtonRenderer_->Off();

				// 충돌체 생성
				SkillButtonCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI11_Collider));
				SkillButtonCollision_->GetTransform()->SetLocalScaling(float4(46.f, 46.f));
				SkillButtonCollision_->GetTransform()->SetLocalPosition(SkillButtonRenderer_->GetTransform()->GetLocalPosition());

				// 기본 Off 상태
				Off();
			}
			break;
		}
	}
}

void MainPlayer_WeaponSkillButton::SetWeaponDirType(DirectType _DirType)
{
	DirectType_ = _DirType;
}

void MainPlayer_WeaponSkillButton::SelectCurWeapon(DirectType _DirType, int _SkillID, const std::string& _TextureName)
{
	if (DirectType::Left == _DirType)
	{
		// 왼쪽무기 현재 스킬 변경
		if (nullptr != GlobalValue::CurLeftSkill)
		{
			GlobalValue::CurLeftSkill->CurSkillChange(_SkillID, _TextureName);
		}
	}
	else
	{
		// 오른쪽무기 현재 스킬 변경
		if (nullptr != GlobalValue::CurRightSkill)
		{
			GlobalValue::CurRightSkill->CurSkillChange(_SkillID, _TextureName);
		}
	}
}

