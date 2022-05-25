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
#include "MainPlayer_LevelUpActiveButton.h"

SkillPageNo SkillView::CurSkillPage = SkillPageNo::CurseSpell;
int SkillView::SkillPoint = 0;

SkillView::SkillView() :
	PanelRenderer_(nullptr),
	PanelCol_(nullptr),
	SkillPagePanel_{nullptr, },
	SkillPageCollider_{ nullptr, },
	CloseButton_(nullptr),
	CloseButtonCollider_(nullptr),
	CloseButtonState_(Button_State::Normal),
	SkillPointTitle_(nullptr),
	CurSkillPoint_(nullptr),
	Page1Name_(nullptr),
	Page2Name_(nullptr),
	Page3Name_(nullptr)
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

	// �÷��̾� �̵��Ұ�ó���� ���� �浹ü ����
	PanelCol_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UIMoveabledCheckCol));
	PanelCol_->SetName("Player_SkillView");
	PanelCol_->GetTransform()->SetLocalScaling(PanelRenderer_->GetTransform()->GetLocalScaling());
	PanelCol_->GetTransform()->SetLocalPosition(PanelRenderer_->GetTransform()->GetLocalPosition());

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

		float4 CalcColliderPos = float4(272.5f, -136.f);
		CalcColliderPos.y += ((i * 95.f) + (i * 13));
		SkillPageCollider_[i]->GetTransform()->SetLocalPosition(CalcColliderPos);
	}

	// ���� ���õ� ������ �ǳ� �������� On����
	SkillPagePanel_[static_cast<int>(CurSkillPage)]->On();

	// ��ųâ ���� �ؽ�Ʈ
	SkillPointTitle_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	SkillPointTitle_->GetTransform()->SetLocalPosition(float4(ScreenHarfSzie.x - 122.f, 194.f));
	SkillPointTitle_->TextSetting("diablo", "POINT", 14, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	CurSkillPoint_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	CurSkillPoint_->GetTransform()->SetLocalPosition(float4(ScreenHarfSzie.x - 122.f, 166.f));
	CurSkillPoint_->TextSetting("diablo", std::to_string(SkillPoint), 14, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	Page3Name_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	Page3Name_->GetTransform()->SetLocalPosition(float4(ScreenHarfSzie.x - 124.f, 80.f));
	Page3Name_->TextSetting("diablo", "��ȯ ����", 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	Page2Name_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	Page2Name_->GetTransform()->SetLocalPosition(float4(ScreenHarfSzie.x - 124.f, -30.f));
	Page2Name_->TextSetting("diablo", "������&������", 11, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	Page1Name_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	Page1Name_->GetTransform()->SetLocalPosition(float4(ScreenHarfSzie.x - 124.f, -136.f));
	Page1Name_->TextSetting("diablo", "���� ����", 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	Off();
}

void SkillView::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(PanelCol_->GetTransform(), CollisionType::Rect);
	GetLevel()->UIPushDebugRender(CloseButtonCollider_->GetTransform(), CollisionType::Rect);
	GetLevel()->UIPushDebugRender(SkillPageCollider_[0]->GetTransform(), CollisionType::Rect);
	GetLevel()->UIPushDebugRender(SkillPageCollider_[1]->GetTransform(), CollisionType::Rect);
	GetLevel()->UIPushDebugRender(SkillPageCollider_[2]->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

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

				// ��ųâ ��Ȱ��ȭ
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->KeyInputViewProcess(2);
			}

			CloseButtonState_ = Button_State::Normal;
		}
	}

	// â���� ��ư �浹üũ
	CloseButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::CloseButtonClick, this, std::placeholders::_1));

	// ��ų������ ��ȯ ��ư �浹üũ
	SkillPageCollider_[0]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::SkillPage1ChangeClick, this, std::placeholders::_1));
	SkillPageCollider_[1]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::SkillPage2ChangeClick, this, std::placeholders::_1));
	SkillPageCollider_[2]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::SkillPage3ChangeClick, this, std::placeholders::_1));
}

void SkillView::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// Ÿ��Ʋ ȭ�� or �ε�ȭ�� or ĳ���ͻ���ȭ�� or ĳ���ͼ���ȭ�� or ����ȭ�� �̵��� �����̵�����
	if (std::string::npos != _NextLevel->GetName().find("TitleLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("CreateCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("SelectCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("LoadingLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("MapEditorLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("EndingLevel"))
	{
		return;
	}

	// ��ųâ�� ����ִ� ��� ���� �ѱ�
	for (int i = 0; i < static_cast<int>(SkillPageNo::MAX); ++i)
	{
		int PageToIconCnt = static_cast<int>(SkillPageToIcon[i].size());
		for (int j = 0; j < PageToIconCnt; ++j)
		{
			GetLevel()->SetLevelActorMove(_NextLevel, SkillPageToIcon[i][j]);
		}
	}
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
		NewSkillIcon->Off();
		SkillPageToIcon[static_cast<int>(PageNo)].push_back(NewSkillIcon);
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

void SkillView::SkillIconEnabled(bool _Flag)
{
	if (true == _Flag)
	{
		int PageIconCnt = static_cast<int>(SkillPageToIcon[static_cast<int>(CurSkillPage)].size());
		for (int i = 0; i < PageIconCnt; ++i)
		{
			SkillPageToIcon[static_cast<int>(CurSkillPage)][i]->On();
		}
	}
	else
	{
		int PageIconCnt = static_cast<int>(SkillPageToIcon[static_cast<int>(CurSkillPage)].size());
		for (int i = 0; i < PageIconCnt; ++i)
		{
			SkillPageToIcon[static_cast<int>(CurSkillPage)][i]->Off();
		}
	}
}

void SkillView::LevelUpSkillPointGrant()
{
	// 3����Ʈ �ο�
	SkillPoint += 3;

	// ��ųâ ����Ʈ �ؽ�Ʈ ����
	CurSkillPoint_->SetPrintText(std::to_string(SkillPoint));

	// �ܺο��� ȣ���ϸ�, �÷��̾� �������� ��ų����Ʈ�� �ο��Ǹ� ��ų������ �������� ����
	// ��ų�������� ��� Ȱ��ȭ ���°� �ȴ�.
	for (int i = 0; i < static_cast<int>(SkillPageNo::MAX); ++i)
	{
		int SkillIconListCnt = static_cast<int>(SkillPageToIcon[i].size());
		for (int j = 0; j < SkillIconListCnt; ++j)
		{
			SkillPageToIcon[i][j]->SetSkillIconActive();
		}
	}

	// �ϴܻ��¹��� ��ų����Ʈ Ȱ��ȭ����Ʈ Ȱ��ȭ
	GlobalValue::CurPlayer->GetBottomStateBar()->GetSkillPointControl()->LevelUpPointButtonActive();
}

void SkillView::SkillPointDeduction()
{
	if (0 != SkillPoint)
	{
		SkillPoint -= 1;
	}

	CurSkillPoint_->SetPrintText(std::to_string(SkillPoint));

	// �ܺο��� ȣ���ϸ�, �ο��� ��ų����Ʈ�� ��� �����Ͽ�
	// ��ų�������� ��� ��Ȱ��ȭ ���°� �ȴ�.
	if (0 == SkillPoint)
	{
		for (int i = 0; i < static_cast<int>(SkillPageNo::MAX); ++i)
		{
			int SkillIconListCnt = static_cast<int>(SkillPageToIcon[i].size());
			for (int j = 0; j < SkillIconListCnt; ++j)
			{
				SkillPageToIcon[i][j]->SetSkillIconInactvie();
			}
		}

		// �ϴܻ��¹��� ��ų����Ʈ Ȱ��ȭ����Ʈ ��Ȱ��ȭ
		GlobalValue::CurPlayer->GetBottomStateBar()->GetSkillPointControl()->LevelUpPointExhaust();
	}
}
