#include "PreCompile.h"
#include "MainPlayer_LeftWeaponSkillButton.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "UserGame.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

MainPlayer_LeftWeaponSkillButton::MainPlayer_LeftWeaponSkillButton() :
	IsActive_(false),
	ButtonState_(Button_State::Normal),
	CurSkillButton_(nullptr),
	CurSkillButtonCollision_(nullptr),
	SkillListPushCount_{ 0, }
{
}

MainPlayer_LeftWeaponSkillButton::~MainPlayer_LeftWeaponSkillButton()
{
}

void MainPlayer_LeftWeaponSkillButton::PlayerIsTownCheck()
{
	// �÷��̾ ������ �ִ��� üũ�Ͽ� ������ ��ġ�Ѵٸ� ���� ���õ� ��ų ��Ȱ��ȭ
	if (true == GlobalValue::CurPlayer->GetIsTown())
	{
		CurSkillButton_->SetChangeAnimation("Disabled");

		ButtonState_ = Button_State::Disabled;
	}
	
	if(false == GlobalValue::CurPlayer->GetIsTown() && ButtonState_ == Button_State::Disabled)
	{
		CurSkillButton_->SetChangeAnimation("Default");

		ButtonState_ = Button_State::Normal;
	}
}

void MainPlayer_LeftWeaponSkillButton::Start()
{
	// Button Image Cutting
	GameEngineTexture* AttackDefault = GameEngineTextureManager::GetInst().Find("Attack_Default.png");
	AttackDefault->Cut(1, 1);
	GameEngineTexture* AttackClick = GameEngineTextureManager::GetInst().Find("Attack_Click.png");
	AttackClick->Cut(1, 1);
	GameEngineTexture* AttackDisabled = GameEngineTextureManager::GetInst().Find("Attack_Disabled.png");
	AttackDisabled->Cut(1, 1);

	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// ���� ���õ� ���� ���� ��ų 
	CurSkillButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));
	CurSkillButton_->CreateAnimation("Attack_Default.png", "Default", 0, 0, 0.1f, false);
	CurSkillButton_->CreateAnimation("Attack_Click.png", "Click", 0, 0, 0.1f, false);
	CurSkillButton_->CreateAnimation("Attack_Disabled.png", "Disabled", 0, 0, 0.1f, false);
	CurSkillButton_->GetTransform()->SetLocalScaling(float4(48.f, 48.f));
	CurSkillButton_->GetTransform()->SetLocalPosition(float4(140.f - ScreenHarfSize.x, 24.f - ScreenHarfSize.y));
	CurSkillButton_->SetChangeAnimation("Default");

	// ���� ���õ� ���� ���� ��ų �浹ü
	CurSkillButtonCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI11_Collider));
	CurSkillButtonCollision_->GetTransform()->SetLocalScaling(float4(48.f, 48.f));
	CurSkillButtonCollision_->GetTransform()->SetLocalPosition(CurSkillButton_->GetTransform()->GetLocalPosition());
}

void MainPlayer_LeftWeaponSkillButton::Update(float _DeltaTime)
{
	PlayerIsTownCheck();

	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// ���� ���� Ȱ��ȭ ��ų��� Ȱ��ȭ/��Ȱ��ȭ
			if (false == IsActive_)
			{
				IsActive_ = true;
			}
			else
			{
				IsActive_ = false;
			}
			LWeaponActiveSkillListView(IsActive_);

			ButtonState_ = Button_State::Normal;
		}
	}

	CurSkillButtonCollision_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_LeftWeaponSkillButton::CurLWeaponSkillBtnCol, this, std::placeholders::_1));

	LWeaponSkillList_;
}

void MainPlayer_LeftWeaponSkillButton::UpdateWeaponSkillList(int _SkillID)
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// ���Ӱ� Ȱ��ȭ�� ���ʹ��� ��ų�� ��Ͽ� �߰��Ѵ�.
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();

	int SkillSize = static_cast<int>(PlayerInfo.SkillInfo.size());
	for (int i = 0; i < SkillSize; ++i)
	{
		if (PlayerInfo.SkillInfo[i].SkillCode == _SkillID)
		{
			// ��Ͽ� �ش� ��ų �߰�
			WeaponSkillBtn_List NewSkillButton = {};

			// ��ų ������
			NewSkillButton.SkillPage = PlayerInfo.SkillInfo[i].SkillPage;

			// ��ų Code
			NewSkillButton.SkillID = PlayerInfo.SkillInfo[i].SkillCode;

			// ��ϻ��� ��ȣ
			NewSkillButton.PushNo = SkillListPushCount_[NewSkillButton.SkillPage];

			// ������ ����
			NewSkillButton.SkillButton = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));

			// ��ų �̸� ����
			NewSkillButton.ButtonName = PlayerInfo.SkillInfo[i].SkillName;

			// ��ų�̸��� �̿��Ͽ� �ؽ��ĸ� ����

			// ����Ʈ
			std::string DefaultTex = NewSkillButton.ButtonName;
			DefaultTex += "_Default";
			DefaultTex += ".png";
			GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTex);
			if (nullptr != DefaultTexture)
			{
				DefaultTexture->Cut(1, 1);
				NewSkillButton.SkillButton->CreateAnimation(DefaultTex, "Default", 0, 0, 0.1f, false);
			}

			// Ŭ��
			std::string ClickTex = NewSkillButton.ButtonName;
			ClickTex += "_Click";
			ClickTex += ".png";
			GameEngineTexture* ClickTexture = GameEngineTextureManager::GetInst().Find(ClickTex);
			if (nullptr != ClickTexture)
			{
				ClickTexture->Cut(1, 1);
				NewSkillButton.SkillButton->CreateAnimation(ClickTex, "Click", 0, 0, 0.1f, false);
			}

			// ����-��Ȱ��
			std::string DisabledTex = NewSkillButton.ButtonName;
			DisabledTex += "_Disabled";
			DisabledTex += ".png";
			GameEngineTexture* DisabledTexture = GameEngineTextureManager::GetInst().Find(DisabledTex);
			if (nullptr != DisabledTexture)
			{
				DisabledTexture->Cut(1, 1);
				NewSkillButton.SkillButton->CreateAnimation(DisabledTex, "Disabled", 0, 0, 0.1f, false);

				// ��ġ ���
				float4 CalcPos = float4(140.f - ScreenHarfSize.x, 80.f - ScreenHarfSize.y);
				CalcPos.x += (48.f * NewSkillButton.PushNo);
				CalcPos.y += (48.f * NewSkillButton.SkillPage);

				// ��ġ�� ����
				NewSkillButton.SkillBtnPos = CalcPos;

				// ũ�� �� ��ġ ����
				NewSkillButton.SkillButton->GetTransform()->SetLocalScaling(float4(48.f, 48.f, 1.f));
				NewSkillButton.SkillButton->GetTransform()->SetLocalPosition(CalcPos);
				NewSkillButton.SkillButton->SetChangeAnimation("Default");
				NewSkillButton.SkillButton->Off();

				// ������Ͽ� �߰�
				LWeaponSkillList_.push_back(NewSkillButton);

				++SkillListPushCount_[NewSkillButton.SkillPage];
			}

			break;
		}
	}
}

void MainPlayer_LeftWeaponSkillButton::InitLWeaponSkillList()
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// �ʱ� Ȱ��ȭ�� ���ʹ��� ��ų����� �����Ѵ�.
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();

	int SkillSize = static_cast<int>(PlayerInfo.SkillInfo.size());
	for (int i = 0; i < SkillSize; ++i)
	{
		// ���� Ȱ��ȭ�Ǿ������� ���ʽ�ų�� ��밡���� ��ų
		if (true == PlayerInfo.SkillInfo[i].SkillActive && true == PlayerInfo.SkillInfo[i].LeftSkillUse)
		{
			int Row = PlayerInfo.SkillInfo[i].SkillRow;
			int Column = PlayerInfo.SkillInfo[i].SkillColumn;

			WeaponSkillBtn_List NewSkillButton = {};

			// ��ų ������
			NewSkillButton.SkillPage = PlayerInfo.SkillInfo[i].SkillPage;

			// ��ų Code
			NewSkillButton.SkillID = PlayerInfo.SkillInfo[i].SkillCode;

			// ��ϻ��� ��ȣ
			NewSkillButton.PushNo = SkillListPushCount_[NewSkillButton.SkillPage];

			// ������ ����
			NewSkillButton.SkillButton = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));

			// ��ų �̸� ����
			NewSkillButton.ButtonName = PlayerInfo.SkillInfo[i].SkillName;

			// ��ų�̸��� �̿��Ͽ� �ؽ��ĸ� ����

			// ����Ʈ
			std::string DefaultTex = NewSkillButton.ButtonName;
			DefaultTex += "_Default";
			DefaultTex += ".png";
			GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTex);
			if (nullptr != DefaultTexture)
			{
				DefaultTexture->Cut(1, 1);
				NewSkillButton.SkillButton->CreateAnimation(DefaultTex, "Default", 0, 0, 0.1f, false);
			}

			// Ŭ��
			std::string ClickTex = NewSkillButton.ButtonName;
			ClickTex += "_Click";
			ClickTex += ".png";
			GameEngineTexture* ClickTexture = GameEngineTextureManager::GetInst().Find(ClickTex);
			if (nullptr != ClickTexture)
			{
				ClickTexture->Cut(1, 1);
				NewSkillButton.SkillButton->CreateAnimation(ClickTex, "Click", 0, 0, 0.1f, false);
			}

			// ����-��Ȱ��
			std::string DisabledTex = NewSkillButton.ButtonName;
			DisabledTex += "_Disabled";
			DisabledTex += ".png";
			GameEngineTexture* DisabledTexture = GameEngineTextureManager::GetInst().Find(DisabledTex);
			if (nullptr != DisabledTexture)
			{
				DisabledTexture->Cut(1, 1);
				NewSkillButton.SkillButton->CreateAnimation(DisabledTex, "Disabled", 0, 0, 0.1f, false);

				// ��ġ ���
				float4 CalcPos = float4(140.f - ScreenHarfSize.x, 80.f - ScreenHarfSize.y);
				CalcPos.x += (48.f * NewSkillButton.PushNo);
				CalcPos.y += (48.f * NewSkillButton.SkillPage);

				// ��ġ�� ����
				NewSkillButton.SkillBtnPos = CalcPos;

				// ũ�� �� ��ġ ����
				NewSkillButton.SkillButton->GetTransform()->SetLocalScaling(float4(48.f, 48.f, 1.f));
				NewSkillButton.SkillButton->GetTransform()->SetLocalPosition(CalcPos);
				NewSkillButton.SkillButton->SetChangeAnimation("Default");
				NewSkillButton.SkillButton->Off();

				// ������Ͽ� �߰�
				LWeaponSkillList_.push_back(NewSkillButton);

				++SkillListPushCount_[NewSkillButton.SkillPage];
			}
		}
	}
}

void MainPlayer_LeftWeaponSkillButton::CurLWeaponSkillBtnCol(GameEngineCollision* _Other)
{
	if (ButtonState_ != Button_State::Disabled)
	{
		// ���� ���� ��ų��� Ȱ��ȭ
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

void MainPlayer_LeftWeaponSkillButton::LWeaponActiveSkillListView(bool _Flag)
{
	if (true == _Flag)
	{
		// ��ų��� On
		int Count = static_cast<int>(LWeaponSkillList_.size());
		for (int i = 0; i < Count; ++i)
		{
			LWeaponSkillList_[i].SkillButton->On();
		}
	}
	else
	{
		// ��ų��� Off
		int Count = static_cast<int>(LWeaponSkillList_.size());
		for (int i = 0; i < Count; ++i)
		{
			LWeaponSkillList_[i].SkillButton->Off();
		}
	}
}
