#include "PreCompile.h"
#include "SkillView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayer_SkillIcon.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_MiniMenuButton.h"

SkillPageNo SkillView::CurSkillPage = SkillPageNo::CurseSpell;

SkillPageNo SkillView::GetCurSkillPage()
{
	return CurSkillPage;
}

void SkillView::SetCurSkillPage(SkillPageNo _SkillPageNo)
{
	CurSkillPage = _SkillPageNo;
}

SkillView::SkillView() :
	PanelRenderer_(nullptr),
	SkillPagePanel_{nullptr, },
	SkillPageCollider_{ nullptr, },
	CloseButton_(nullptr),
	CloseButtonCollider_(nullptr),
	CloseButtonState_(Button_State::Normal)
{
}

SkillView::~SkillView()
{
}

void SkillView::Start()
{
	// Screen Harf Size
	float4 ScreenHarfSzie = GameEngineWindow::GetInst().GetSize().halffloat4();

	// Create Panel Renderer
	GameEngineTexture* PanelTexture = GameEngineTextureManager::GetInst().Find("Player_SkillView_Panel.png");
	float4 ImageHarfSize = PanelTexture->GetTextureSize().halffloat4();

	PanelRenderer_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0));
	PanelRenderer_->SetImage("Player_SkillView_Panel.png");
	PanelRenderer_->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x, 24.f));

	// Button Image Cutting
	GameEngineTexture* ButtonDefault = GameEngineTextureManager::GetInst().Find("CloseButton_Default.png");
	ButtonDefault->Cut(1, 1);
	GameEngineTexture* ButtonClick = GameEngineTextureManager::GetInst().Find("CloseButton_Click.png");
	ButtonClick->Cut(1, 1);

	// Create Button Renderer
	CloseButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Button));
	CloseButton_->CreateAnimation("CloseButton_Default.png", "Default", 0, 0, 0.1f, false);
	CloseButton_->CreateAnimation("CloseButton_Click.png", "Click", 0, 0, 0.1f, false);
	CloseButton_->GetTransform()->SetLocalScaling(float4(32.f, 32.f, 1.f));
	CloseButton_->GetTransform()->SetLocalPosition(float4(31.f, -161.f));
	CloseButton_->SetChangeAnimation("Default");

	// Create Button Collision
	CloseButtonCollider_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
	CloseButtonCollider_->GetTransform()->SetLocalScaling(float4(32.f, 32.f, 1.0f));
	CloseButtonCollider_->GetTransform()->SetLocalPosition(CloseButton_->GetTransform()->GetLocalPosition());

	// ============================================ Skill Page ============================================ //
	
	for (int i = 0; i < static_cast<int>(SkillPageNo::MAX); ++i)
	{
		// Create Skill Page Panel Renderer
		std::string SkillPageName = "SkillPage";
		SkillPageName += std::to_string(i + 1);
		SkillPageName += ".png";

		SkillPagePanel_[i] = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Tab));
		SkillPagePanel_[i]->SetImage(SkillPageName);
		SkillPagePanel_[i]->GetTransform()->SetLocalPosition(float4(ImageHarfSize.x, 24.f));
		SkillPagePanel_[i]->Off();

		// Create Skill Page Panel Collider
		SkillPageCollider_[i] = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI0_Collider));
		SkillPageCollider_[i]->GetTransform()->SetLocalScaling(float4(75.f, 95.f, 1.0f));

		float4 CalcColliderPos = float4(272.5f, 80.f);
		CalcColliderPos.y -= ((i * 95.f) + (i * 13));
		SkillPageCollider_[i]->GetTransform()->SetLocalPosition(CalcColliderPos);
	}

	// ���� ���õ� ������ �ǳ� �������� On����
	SkillPagePanel_[static_cast<int>(CurSkillPage)]->On();

	Off();
}

void SkillView::Update(float _DeltaTime)
{
	// ��ųâ �����ư üũ
	if (CloseButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// MainPlayer Flag Off
			if (nullptr != GlobalValue::CurPlayer)
			{
				// �̴ϸ޴� �����ڸ� ����
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

				// ����â ��Ȱ��ȭ
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->KeyInputViewProcess(2);
			}

			CloseButtonState_ = Button_State::Normal;
		}
	}

	// â���� ��ư �浹üũ
	CloseButtonCollider_->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::CloseButtonClick, this, std::placeholders::_1));

	// ��ų������ ��ȯ ��ư �浹üũ
	SkillPageCollider_[0]->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::SkillPage1ChangeClick, this, std::placeholders::_1));
	SkillPageCollider_[1]->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::SkillPage2ChangeClick, this, std::placeholders::_1));
	SkillPageCollider_[2]->Collision(CollisionType::AABBBox3D, CollisionType::Sphere3D, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::SkillPage3ChangeClick, this, std::placeholders::_1));

	//// Ȯ�ο�
	//for (int i = 0; i < 3; ++i)
	//{
	//	GetLevel()->PushDebugRender(SkillPageCollider_[i]->GetTransform(), CollisionType::Rect);
	//}
}

void SkillView::InitSkillView()
{
	// �����÷��̾� ������ �̿��Ͽ� String Setting
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();
	
	// ��ų�������� ��ų��� ����(�⺻��ų ����)

	// �ش� �����÷��̾ �������ִ� ��ų������ŭ �ݺ�
	int AllSkillCount = static_cast<int>(PlayerInfo.SkillInfo.size());
	for (int i = 0; i < AllSkillCount; ++i)
	{
		// �ش� ��ų�� ������ No Get
		if (0 == PlayerInfo.SkillInfo[i].SkillPage)
		{
			// �⺻��ų���� ������ ���������ʴ´�.
			continue;
		}

		// ��ų������ ������ �ʿ����� Get
		SkillPageNo PageNo = static_cast<SkillPageNo>(PlayerInfo.SkillInfo[i].SkillPage - 1);	// ��ų�� 1�����������ͽ����̹Ƿ� ��������ȣ�� -1�Ͽ� 0������ �����ǵ��� ����
		std::string SkillName = PlayerInfo.SkillInfo[i].SkillName;
		int SkillCode = PlayerInfo.SkillInfo[i].SkillCode;
		bool SkillActive = PlayerInfo.SkillInfo[i].SkillActive;
		int SkillRow = PlayerInfo.SkillInfo[i].SkillRow;
		int SkillColumn = PlayerInfo.SkillInfo[i].SkillColumn;
		int SkillLevel = PlayerInfo.SkillInfo[i].CurSkillLevel;

		// �ű� ��ų ������ ����
		MainPlayer_SkillIcon* NewSkillIcon = GetLevel()->CreateActor<MainPlayer_SkillIcon>();
		NewSkillIcon->CreateSkillIcon(PageNo, SkillName, SkillCode, SkillActive, SkillRow, SkillColumn, SkillLevel);
		SkillPageToIcon[static_cast<int>(PageNo)].push_back(NewSkillIcon);
	}

	// ���� ���õ� �������� ��ų������ ��ϸ� On����
	int PageIconCnt = static_cast<int>(SkillPageToIcon[static_cast<int>(CurSkillPage)].size());
	for (int i = 0; i < PageIconCnt; ++i)
	{
		SkillPageToIcon[static_cast<int>(CurSkillPage)][i]->On();
	}
}

void SkillView::CloseButtonClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		CloseButton_->SetChangeAnimation("Click");

		CloseButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		CloseButton_->SetChangeAnimation("Default");
	}
}

void SkillView::SkillPage1ChangeClick(GameEngineCollision* _Other)
{
	// Page1 ����(CurseSpell(���ֽ���))
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		SkillPageTabChange(SkillPageNo::CurseSpell);
	}
}

void SkillView::SkillPage2ChangeClick(GameEngineCollision* _Other)
{
	// Page2 ����(PoisonandBoneSpells(������&������))
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		SkillPageTabChange(SkillPageNo::PoisonandBoneSpells);
	}
}

void SkillView::SkillPage3ChangeClick(GameEngineCollision* _Other)
{
	// Page3 ����(SummonSpell(��ȯ����))
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		SkillPageTabChange(SkillPageNo::SummonSpell);
	}
}

void SkillView::SkillPageTabChange(SkillPageNo _SkillPageNo)
{
	// ���� ���õ� ��ų�������� ���� ���õ� ��ų�������� ���ٸ� ����
	if (CurSkillPage == _SkillPageNo)
	{
		return;
	}

	// �ƴ϶�� CurSkillPage�� �ǳڰ� �����ܸ���� ��� Off��Ű��,
	// ���� ���õ� �������� ����
	SkillPagePanel_[static_cast<int>(CurSkillPage)]->Off();

	// �ش� ��ų������ ��� ��� On
	int CurSkillIconCnt = static_cast<int>(SkillPageToIcon[static_cast<int>(CurSkillPage)].size());
	for (int i = 0; i < CurSkillIconCnt; ++i)
	{
		SkillPageToIcon[static_cast<int>(CurSkillPage)][i]->Off();
	}
	CurSkillPage = _SkillPageNo;

	// ���� ���õ� ������ ���� �������� ��� On���·� ��ȯ

	// ��ų������ �ǳ� On
	SkillPagePanel_[static_cast<int>(CurSkillPage)]->On();

	// �ش� ��ų������ ��� ��� On
	int ChangeSkillIconCnt = static_cast<int>(SkillPageToIcon[static_cast<int>(CurSkillPage)].size());
	for (int i = 0; i < ChangeSkillIconCnt; ++i)
	{
		SkillPageToIcon[static_cast<int>(CurSkillPage)][i]->On();
	}

	// ��ųâ �����ư �̵�(2���������϶��� ��ġ�� �ٸ�)
	if (SkillPageNo::PoisonandBoneSpells == CurSkillPage)
	{
		CloseButton_->GetTransform()->SetLocalPosition(float4(187.f, -161.f));
		CloseButtonCollider_->GetTransform()->SetLocalPosition(CloseButton_->GetTransform()->GetLocalPosition());
	}
	else
	{
		CloseButton_->GetTransform()->SetLocalPosition(float4(31.f, -161.f));
		CloseButtonCollider_->GetTransform()->SetLocalPosition(CloseButton_->GetTransform()->GetLocalPosition());
	}
}
