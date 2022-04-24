#include "PreCompile.h"
#include "MainPlayer_MiniMenu.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"
#include "MainPlayer_MiniMenuButton.h"

#include "GlobalValue.h"

bool MainPlayer_MiniMenu::MiniMenuActive_ = true;

bool MainPlayer_MiniMenu::MiniMenuActive()
{
	return MiniMenuActive_;
}

MainPlayer_MiniMenu::MainPlayer_MiniMenu() :
	MiniMenuListPanelBasicPos_(float4::ZERO),
	ButtonState_(Button_State::Normal),
	MiniMenuActiveButton_(nullptr),
	MiniMenuActiveButtonCollision_(nullptr),
	MiniMenuListPanel_(nullptr)
{
}

MainPlayer_MiniMenu::~MainPlayer_MiniMenu()
{
}

void MainPlayer_MiniMenu::Start()
{
	// Window Screen Harf Size Get
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// MiniMenu ActiveButton Image Cutting
	GameEngineTexture* DownClick = GameEngineTextureManager::GetInst().Find("MiniMenu_DownButton_Click.png");
	DownClick->Cut(1, 1);
	GameEngineTexture* DownDefault = GameEngineTextureManager::GetInst().Find("MiniMenu_DownButton_Default.png");
	DownDefault->Cut(1, 1);
	GameEngineTexture* UpClick = GameEngineTextureManager::GetInst().Find("MiniMenu_UpButton_Click.png");
	UpClick->Cut(1, 1);
	GameEngineTexture* UpDefault = GameEngineTextureManager::GetInst().Find("MiniMenu_UpButton_Default.png");
	UpDefault->Cut(1, 1);

	// MiniMenu ActiveButton Renderer
	// Ȱ��ȭ�Ǿ��ִٸ� Down �̹����� ����Ʈ : Ŭ���� DownClick -> UpDefault
	// ��Ȱ��ȭ�Ǿ��ִٸ� Up �̹����� ����Ʈ : Ŭ���� UpClick -> DownDefault
	MiniMenuActiveButton_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));
	MiniMenuActiveButton_->CreateAnimation("MiniMenu_UpButton_Click.png", "EnabledClick", 0, 0, 0.1f, false);
	MiniMenuActiveButton_->CreateAnimation("MiniMenu_UpButton_Default.png", "EnabledDefault", 0, 0, 0.1f, false);
	MiniMenuActiveButton_->CreateAnimation("MiniMenu_DownButton_Click.png", "DisabledClick", 0, 0, 0.1f, false);
	MiniMenuActiveButton_->CreateAnimation("MiniMenu_DownButton_Default.png", "DisabledDefault", 0, 0, 0.1f, false);
	MiniMenuActiveButton_->GetTransform()->SetLocalScaling(float4(14.f, 24.f, 1.0f));
	MiniMenuActiveButton_->GetTransform()->SetLocalPosition(float4(-2.f, 27.f - ScreenHarfSize.y));
	MiniMenuActiveButton_->SetChangeAnimation("DisabledDefault");

	// MiniMenu ActiveButton Collision
	MiniMenuActiveButtonCollision_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(UIRenderOrder::UI11_Collider));
	MiniMenuActiveButtonCollision_->GetTransform()->SetLocalScaling(MiniMenuActiveButton_->GetTransform()->GetLocalScaling());
	MiniMenuActiveButtonCollision_->GetTransform()->SetLocalPosition(MiniMenuActiveButton_->GetTransform()->GetLocalPosition());

	// MiniMenu ButtonList Panel
	MiniMenuListPanel_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));
	MiniMenuListPanel_->SetImage("Player_MiniMenuPanel_UI.png");
	MiniMenuListPanel_->GetTransform()->SetLocalPosition(float4(0.f, 58.f - ScreenHarfSize.y));

	MiniMenuListPanelBasicPos_ = MiniMenuListPanel_->GetTransform()->GetLocalPosition();

	// Create MiniMenu List
	CreateMiniMenuList();
}

void MainPlayer_MiniMenu::Update(float _DeltaTime)
{
#ifdef _DEBUG
	GetLevel()->UIPushDebugRender(MiniMenuActiveButtonCollision_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

	if (ButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// �̴ϸ޴� Ȱ��/��Ȱ��
			MiniMenuEnabledOrDisabled();

			ButtonState_ = Button_State::Normal;
		}
	}

	MiniMenuActiveButtonCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_MiniMenu::MiniMenuButtonClick, this, std::placeholders::_1));
}

void MainPlayer_MiniMenu::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
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

	if (false == MiniMenuList_.empty())
	{
		int MenuListCnt = static_cast<int>(MiniMenuList_.size());
		for (int i = 0; i < MenuListCnt; ++i)
		{
			GetLevel()->SetLevelActorMove(_NextLevel, MiniMenuList_[i]);
		}
	}
}

void MainPlayer_MiniMenu::CreateMiniMenuList()
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	// MiniMenu �ٷΰ����ư ��� ����
	int MenuCount = static_cast<int>(ShortcutsType::MAX);
	for (int i = 0; i < MenuCount; ++i)
	{
		MainPlayer_MiniMenuButton* NewButton = GetLevel()->CreateActor<MainPlayer_MiniMenuButton>();
		MiniMenuList_.push_back(NewButton);
	}

	// PLAYER STATE VIEW(����â)
	MiniMenuList_[0]->CreateShortcutsButton(this, "StatView_Button", float4(-32.f, 58.f - ScreenHarfSize.y), ShortcutsType::STATVIEW);

	// PLAYER INVENTORY VIEW(�κ��丮â)
	MiniMenuList_[1]->CreateShortcutsButton(this, "Inventory_Button", float4(-11.f, 58.f - ScreenHarfSize.y), ShortcutsType::INVENTORY);

	// PLAYER SKILL VIEW(��ųâ)
	MiniMenuList_[2]->CreateShortcutsButton(this, "SkillView_Button", float4(11.f, 58.f - ScreenHarfSize.y), ShortcutsType::SKILLVIEW);

	// PLAYER GAMEENDMENU VIEW(�������� �޴� - ȭ����üâ)
	MiniMenuList_[3]->CreateShortcutsButton(this, "Menu_Button", float4(32.f, 58.f - ScreenHarfSize.y), ShortcutsType::GAMEENDMENU);
}

MainPlayer_MiniMenuButton* MainPlayer_MiniMenu::GetMenuButton(int _Index)
{
	return MiniMenuList_[_Index];
}

void MainPlayer_MiniMenu::MiniMenuEnabledOrDisabled()
{
	// ���¿� ���� �޴���� Ȱ��/��Ȱ��
	// Ȱ��ȭ�Ǿ��ִٸ� Down �̹����� ����Ʈ : Ŭ���� DownClick -> UpDefault
	// ��Ȱ��ȭ�Ǿ��ִٸ� Up �̹����� ����Ʈ : Ŭ���� UpClick -> DownDefault
	if (false == MiniMenuActive_)
	{
		// �̴ϸ޴���ư��� �ǳ� ��Ȱ��ȭ
		MiniMenuListPanel_->Off();

		// �̴ϸ޴���ư ��� ��Ȱ��ȭ
		int MenuCnt = static_cast<int>(MiniMenuList_.size());
		for (int i = 0; i < MenuCnt; ++i)
		{
			MiniMenuList_[i]->Off();
		}
	}
	else
	{
		// �̴ϸ޴���ư��� �ǳ� Ȱ��ȭ
		MiniMenuListPanel_->On();

		// �̴ϸ޴���ư ��� Ȱ��ȭ
		int MenuCnt = static_cast<int>(MiniMenuList_.size());
		for (int i = 0; i < MenuCnt; ++i)
		{
			MiniMenuList_[i]->On();
		}
	}
}

void MainPlayer_MiniMenu::MiniMenuButtonClick(GameEngineCollision* _Other)
{
	// Mouse LButton Flag Check
	// Ȱ��ȭ�Ǿ��ִٸ� Down �̹����� ����Ʈ : Ŭ���� DownClick -> UpDefault
	// ��Ȱ��ȭ�Ǿ��ִٸ� Up �̹����� ����Ʈ : Ŭ���� UpClick -> DownDefault
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		if (true == MiniMenuActive_)
		{
			MiniMenuActiveButton_->SetChangeAnimation("DisabledClick");
			MiniMenuActive_ = false;
		}
		else
		{
			MiniMenuActiveButton_->SetChangeAnimation("EnabledClick");
			MiniMenuActive_ = true;
		}

		ButtonState_ = Button_State::Click;
	}
	else if (true == GameEngineInput::GetInst().Up("MouseLButton"))
	{
		if (true == MiniMenuActive_)
		{
			MiniMenuActiveButton_->SetChangeAnimation("DisabledDefault");
		}
		else
		{
			MiniMenuActiveButton_->SetChangeAnimation("EnabledDefault");
		}
	}
}

void MainPlayer_MiniMenu::AllMoveMiniMenu(bool _BasicPosMove, const float4& _MovePos)
{
	// ���ڸ� ���� Flag On �̶��
	if (true == _BasicPosMove)
	{
		MiniMenuListPanel_->GetTransform()->SetLocalPosition(MiniMenuListPanelBasicPos_);

		// �̴ϸ޴���� ����
		int MenuCnt = static_cast<int>(MiniMenuList_.size());
		for (int i = 0; i < MenuCnt; ++i)
		{
			MiniMenuList_[i]->GetTransform()->SetLocalPosition(float4::ZERO);
		}
	}
	else // �ƴ϶��
	{
		// �ǳ� ����
		float4 PanelMovePos = MiniMenuListPanel_->GetTransform()->GetLocalPosition();
		PanelMovePos.x += _MovePos.x;
		MiniMenuListPanel_->GetTransform()->SetLocalPosition(PanelMovePos);

		// �̴ϸ޴���� ����
		int MenuCnt = static_cast<int>(MiniMenuList_.size());
		for (int i = 0; i < MenuCnt; ++i)
		{
			float4 CalcMovePos = MiniMenuList_[i]->GetTransform()->GetLocalPosition();
			CalcMovePos.x += _MovePos.x;

			MiniMenuList_[i]->GetTransform()->SetLocalPosition(CalcMovePos);
		}
	}
}

void MainPlayer_MiniMenu::SetMiniMenuActiveFlag(bool _Flag)
{
	// �ܺο��� ����
	// Ȱ��ȭ�Ǿ��ִٸ� Down �̹����� ����Ʈ : Ŭ���� DownClick -> UpDefault
	// ��Ȱ��ȭ�Ǿ��ִٸ� Up �̹����� ����Ʈ : Ŭ���� UpClick -> DownDefault
	// 1. ��ųâ Ȱ��ȭ/��Ȱ��ȭ�� ȣ��
	// 2. ����â Ȱ��ȭ/��Ȱ��ȭ�� ȣ��
	// 3. �κ��丮â Ȱ��ȭ/��Ȱ��ȭ�� ȣ��
	// 4. â��â Ȱ��ȭ/��Ȱ��ȭ�� ȣ��
	// 5. �Ǹ�â Ȱ��ȭ/��Ȱ��ȭ�� ȣ��
	MiniMenuActive_ = _Flag;
	if (false == MiniMenuActive_)
	{
		// �̴ϸ޴���ư��� �ǳ� ��Ȱ��ȭ
		MiniMenuListPanel_->Off();

		// �̴ϸ޴���ư ��� ��Ȱ��ȭ
		int MenuCnt = static_cast<int>(MiniMenuList_.size());
		for (int i = 0; i < MenuCnt; ++i)
		{
			MiniMenuList_[i]->Off();
		}

		// Ȱ��ȭ/��Ȱ��ȭ ��ư �̹��� ��ȯ
		MiniMenuActiveButton_->SetChangeAnimation("EnabledDefault");
	}
	else
	{
		// �̴ϸ޴���ư ��� Ȱ��ȭ
		MiniMenuListPanel_->On();

		// �̴ϸ޴���ư ��� Ȱ��ȭ
		int MenuCnt = static_cast<int>(MiniMenuList_.size());
		for (int i = 0; i < MenuCnt; ++i)
		{
			MiniMenuList_[i]->On();
		}

		// Ȱ��ȭ/��Ȱ��ȭ ��ư �̹��� ��ȯ
		MiniMenuActiveButton_->SetChangeAnimation("DisabledDefault");
	}
}

void MainPlayer_MiniMenu::KeyInputViewProcess(int _Index)
{
	// Ű�Է¿� ���� �÷��̾� UI â Ȱ��ȭ/��Ȱ��ȭó��
	MiniMenuList_[_Index]->ShortcutsProcess();
}
