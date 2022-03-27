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

	// 현재 선택된 왼쪽 무기 스킬 
	CurSkillButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));
	CurSkillButton_->CreateAnimation("Attack_Default.png", "Default", 0, 0, 0.1f, false);
	CurSkillButton_->CreateAnimation("Attack_Click.png", "Click", 0, 0, 0.1f, false);
	CurSkillButton_->CreateAnimation("Attack_Disabled.png", "Disabled", 0, 0, 0.1f, false);
	CurSkillButton_->GetTransform()->SetLocalScaling(float4(48.f, 48.f));
	CurSkillButton_->GetTransform()->SetLocalPosition(float4(140.f - ScreenHarfSize.x, 24.f - ScreenHarfSize.y));
	CurSkillButton_->SetChangeAnimation("Default");

	// 현재 선택된 왼쪽 무기 스킬 충돌체
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
			// 왼쪽 무기 활성화 스킬목록 활성화/비활성화
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
	// 새롭게 활성화된 왼쪽무기 스킬을 목록에 추가한다.


}

void MainPlayer_LeftWeaponSkillButton::InitLWeaponSkillList()
{
	// 초기 활성화된 왼쪽무기 스킬목록을 생성한다.
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();

	int SkillSize = static_cast<int>(PlayerInfo.SkillInfo.size());
	for (int i = 0; i < SkillSize; ++i)
	{
		// 현재 활성화되어있는 스킬을 스킬목록에 추가
		if (true == PlayerInfo.SkillInfo[i].SkillActive)
		{
			int Row = PlayerInfo.SkillInfo[i].SkillRow;
			int Column = PlayerInfo.SkillInfo[i].SkillColumn;

			WeaponSkillBtn_List NewSkillButton = {};

			// 스킬 페이지
			NewSkillButton.SkillPage = PlayerInfo.SkillInfo[i].SkillPage;

			// 스킬 로우
			NewSkillButton.SkillRow = PlayerInfo.SkillInfo[i].SkillRow;

			// 스킬 컬럼
			NewSkillButton.SkillColumn = PlayerInfo.SkillInfo[i].SkillColumn;

			// 스킬 Code
			NewSkillButton.SkillID = PlayerInfo.SkillInfo[i].SkillCode;

			// 목록삽입 번호
			NewSkillButton.PushNo = SkillListPushCount_;

			// 렌더러 생성
			GameEngineUIRenderer* NewSkillBtnRenderer = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));

			// 스킬 이름 저장
			NewSkillButton.ButtonName = PlayerInfo.SkillInfo[i].SkillName;

			// 스킬이름을 이용하여 텍스쳐명 편집

			// 디폴트
			std::string DefaultTex = NewSkillButton.ButtonName;
			DefaultTex += "_Default";
			DefaultTex += ".png";
			GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTex);
			DefaultTexture->Cut(1, 1);
			NewSkillBtnRenderer->CreateAnimation(DefaultTex, "Default", 0, 0, 0.1f, false);

			// 클릭
			std::string ClickTex = NewSkillButton.ButtonName;
			ClickTex += "_Click";
			ClickTex += ".png";
			GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTex);
			DefaultTexture->Cut(1, 1);
			NewSkillBtnRenderer->CreateAnimation(DefaultTex, "Click", 0, 0, 0.1f, false);

			// 마을-비활성
			std::string ClickTex = NewSkillButton.ButtonName;
			ClickTex += "_Disabled";
			ClickTex += ".png";
			GameEngineTexture* DefaultTexture = GameEngineTextureManager::GetInst().Find(DefaultTex);
			DefaultTexture->Cut(1, 1);
			NewSkillBtnRenderer->CreateAnimation(DefaultTex, "Disabled", 0, 0, 0.1f, false);

			// 위치 계산
			int Row = NewSkillButton.SkillRow;
			int Column = NewSkillButton.SkillColumn;




			// 위치값 저장
			//NewSkillButton.SkillBtnPos = float4();


			// 크기 및 위치 지정
			NewSkillBtnRenderer->GetTransform()->SetLocalScaling(float4(48.f, 48.f, 1.f));
			NewSkillBtnRenderer->GetTransform()->SetLocalPosition(float4());

			// 관리목록에 추가
			LWeaponSkillList_.push_back(NewSkillButton);

			++SkillListPushCount_;
		}
	}
}

void MainPlayer_LeftWeaponSkillButton::CurLWeaponSkillBtnCol(GameEngineCollision* _Other)
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

void MainPlayer_LeftWeaponSkillButton::LWeaponActiveSkillListView(bool _Flag)
{
	if (true == _Flag)
	{
		// 스킬목록 On

	}
	else
	{
		// 스킬목록 Off

	}
}
