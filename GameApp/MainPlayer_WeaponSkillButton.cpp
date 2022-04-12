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
	// ��ư ���� üũ
	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ���� ��ų�� ���� ���õ� ��ų ��ȯ
			SelectCurWeapon(DirectType_, SkillID_, ButtonName_);

			// ��ư ���� ��ȯ
			ButtonState_ = Button_State::Normal;
		}
	}

	// �浹üũ
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
		// ���� ���� ��ų��� Ȱ��ȭ
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

	// ��ų ��ư ������ ����
	int KillCount = static_cast<int>(PlayerInfo.SkillInfo.size());
	for (int i = 0; i < KillCount; ++i)
	{
		// �ش� ��ġ�ϴ� ��ų Ž��
		if (PlayerInfo.SkillInfo[i].SkillCode == _SkillID)
		{
			// ���� Write

			// ��ų ������
			SkillPage_ = PlayerInfo.SkillInfo[i].SkillPage;

			// ��ų Code
			SkillID_ = PlayerInfo.SkillInfo[i].SkillCode;

			// ��ϻ��� ��ȣ
			PushNo_ = _PushNo;

			// ������ ����
			SkillButtonRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));

			// ��ų �̸� ����
			ButtonName_ = PlayerInfo.SkillInfo[i].SkillName;

			// ��ų�̸��� �̿��Ͽ� �ؽ��ĸ� ����

			// ����Ʈ
			std::string DefaultTex = ButtonName_;
			DefaultTex += "_Default";
			DefaultTex += ".png";
			GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTex);
			if (nullptr != DefaultTexture)
			{
				DefaultTexture->Cut(1, 1);
				SkillButtonRenderer_->CreateAnimation(DefaultTex, "Default", 0, 0, 0.1f, false);
			}

			// Ŭ��
			std::string ClickTex = ButtonName_;
			ClickTex += "_Click";
			ClickTex += ".png";
			GameEngineTexture* ClickTexture = GameEngineTextureManager::GetInst().Find(ClickTex);
			if (nullptr != ClickTexture)
			{
				ClickTexture->Cut(1, 1);
				SkillButtonRenderer_->CreateAnimation(ClickTex, "Click", 0, 0, 0.1f, false);
			}

			// ����-��Ȱ��
			std::string DisabledTex = ButtonName_;
			DisabledTex += "_Disabled";
			DisabledTex += ".png";
			GameEngineTexture* DisabledTexture = GameEngineTextureManager::GetInst().Find(DisabledTex);
			if (nullptr != DisabledTexture)
			{
				DisabledTexture->Cut(1, 1);
				SkillButtonRenderer_->CreateAnimation(DisabledTex, "Disabled", 0, 0, 0.1f, false);

				// ��ġ�� ����
				SkillBtnPos_ = _Pos;

				// ũ�� �� ��ġ ����
				SkillButtonRenderer_->GetTransform()->SetLocalScaling(float4(48.f, 48.f, 1.f));
				SkillButtonRenderer_->GetTransform()->SetLocalPosition(SkillBtnPos_);
				SkillButtonRenderer_->SetChangeAnimation("Default");
				//SkillButtonRenderer_->Off();

				// �浹ü ����
				SkillButtonCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI11_Collider));
				SkillButtonCollision_->GetTransform()->SetLocalScaling(float4(46.f, 46.f));
				SkillButtonCollision_->GetTransform()->SetLocalPosition(SkillButtonRenderer_->GetTransform()->GetLocalPosition());

				// �⺻ Off ����
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
		// ���ʹ��� ���� ��ų ����
		if (nullptr != GlobalValue::CurLeftSkill)
		{
			GlobalValue::CurLeftSkill->CurSkillChange(_SkillID, _TextureName);
		}
	}
	else
	{
		// �����ʹ��� ���� ��ų ����
		if (nullptr != GlobalValue::CurRightSkill)
		{
			GlobalValue::CurRightSkill->CurSkillChange(_SkillID, _TextureName);
		}
	}
}

