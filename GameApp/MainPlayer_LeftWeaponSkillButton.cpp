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
	SkillListPushCount_(0)
{
}

MainPlayer_LeftWeaponSkillButton::~MainPlayer_LeftWeaponSkillButton()
{
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
}

void MainPlayer_LeftWeaponSkillButton::UpdateWeaponSkillList()
{
	// ���Ӱ� Ȱ��ȭ�� ���ʹ��� ��ų�� ��Ͽ� �߰��Ѵ�.


}

void MainPlayer_LeftWeaponSkillButton::InitLWeaponSkillList()
{
	// �ʱ� Ȱ��ȭ�� ���ʹ��� ��ų����� �����Ѵ�.
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();

	int SkillSize = static_cast<int>(PlayerInfo.SkillInfo.size());
	for (int i = 0; i < SkillSize; ++i)
	{
		// ���� Ȱ��ȭ�Ǿ��ִ� ��ų�� ��ų��Ͽ� �߰�
		if (true == PlayerInfo.SkillInfo[i].SkillActive)
		{
			int Row = PlayerInfo.SkillInfo[i].SkillRow;
			int Column = PlayerInfo.SkillInfo[i].SkillColumn;

			WeaponSkillBtn_List NewSkillButton = {};

			// ��ų ������
			NewSkillButton.SkillPage = PlayerInfo.SkillInfo[i].SkillPage;

			// ��ų �ο�
			NewSkillButton.SkillRow = PlayerInfo.SkillInfo[i].SkillRow;

			// ��ų �÷�
			NewSkillButton.SkillColumn = PlayerInfo.SkillInfo[i].SkillColumn;

			// ��ų Code
			NewSkillButton.SkillID = PlayerInfo.SkillInfo[i].SkillCode;

			// ��ϻ��� ��ȣ
			NewSkillButton.PushNo = SkillListPushCount_;

			// ������ ����
			GameEngineUIRenderer* NewSkillBtnRenderer = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));

			// ��ų �̸� ����
			NewSkillButton.ButtonName = PlayerInfo.SkillInfo[i].SkillName;

			// ��ų�̸��� �̿��Ͽ� �ؽ��ĸ� ����

			// ����Ʈ
			std::string DefaultTex = NewSkillButton.ButtonName;
			DefaultTex += "_Default";
			DefaultTex += ".png";
			GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTex);
			DefaultTexture->Cut(1, 1);
			NewSkillBtnRenderer->CreateAnimation(DefaultTex, "Default", 0, 0, 0.1f, false);

			// Ŭ��
			std::string ClickTex = NewSkillButton.ButtonName;
			ClickTex += "_Click";
			ClickTex += ".png";
			GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTex);
			DefaultTexture->Cut(1, 1);
			NewSkillBtnRenderer->CreateAnimation(DefaultTex, "Click", 0, 0, 0.1f, false);

			// ����-��Ȱ��
			std::string ClickTex = NewSkillButton.ButtonName;
			ClickTex += "_Disabled";
			ClickTex += ".png";
			GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTex);
			DefaultTexture->Cut(1, 1);
			NewSkillBtnRenderer->CreateAnimation(DefaultTex, "Disabled", 0, 0, 0.1f, false);

			// ��ġ ���
			int Row = NewSkillButton.SkillRow;
			int Column = NewSkillButton.SkillColumn;




			// ��ġ�� ����
			//NewSkillButton.SkillBtnPos = float4();


			// ũ�� �� ��ġ ����
			NewSkillBtnRenderer->GetTransform()->SetLocalScaling(float4(48.f, 48.f, 1.f));
			NewSkillBtnRenderer->GetTransform()->SetLocalPosition(float4());

			// ������Ͽ� �߰�
			LWeaponSkillList_.push_back(NewSkillButton);

			++SkillListPushCount_;
		}
	}
}

void MainPlayer_LeftWeaponSkillButton::CurLWeaponSkillBtnCol(GameEngineCollision* _Other)
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

void MainPlayer_LeftWeaponSkillButton::LWeaponActiveSkillListView(bool _Flag)
{
	if (true == _Flag)
	{
		// ��ų��� On

	}
	else
	{
		// ��ų��� Off

	}
}
