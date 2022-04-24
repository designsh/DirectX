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
	// 활성화되어있다면 Down 이미지가 디폴트 : 클릭시 DownClick -> UpDefault
	// 비활성화되어있다면 Up 이미지가 디폴트 : 클릭시 UpClick -> DownDefault
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
			// 미니메뉴 활성/비활성
			MiniMenuEnabledOrDisabled();

			ButtonState_ = Button_State::Normal;
		}
	}

	MiniMenuActiveButtonCollision_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&MainPlayer_MiniMenu::MiniMenuButtonClick, this, std::placeholders::_1));
}

void MainPlayer_MiniMenu::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 타이틀 화면 or 로딩화면 or 캐릭터생성화면 or 캐릭터선택화면 or 엔딩화면 이동시 액터이동없음
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

	// MiniMenu 바로가기버튼 목록 생성
	int MenuCount = static_cast<int>(ShortcutsType::MAX);
	for (int i = 0; i < MenuCount; ++i)
	{
		MainPlayer_MiniMenuButton* NewButton = GetLevel()->CreateActor<MainPlayer_MiniMenuButton>();
		MiniMenuList_.push_back(NewButton);
	}

	// PLAYER STATE VIEW(상태창)
	MiniMenuList_[0]->CreateShortcutsButton(this, "StatView_Button", float4(-32.f, 58.f - ScreenHarfSize.y), ShortcutsType::STATVIEW);

	// PLAYER INVENTORY VIEW(인벤토리창)
	MiniMenuList_[1]->CreateShortcutsButton(this, "Inventory_Button", float4(-11.f, 58.f - ScreenHarfSize.y), ShortcutsType::INVENTORY);

	// PLAYER SKILL VIEW(스킬창)
	MiniMenuList_[2]->CreateShortcutsButton(this, "SkillView_Button", float4(11.f, 58.f - ScreenHarfSize.y), ShortcutsType::SKILLVIEW);

	// PLAYER GAMEENDMENU VIEW(게임종료 메뉴 - 화면전체창)
	MiniMenuList_[3]->CreateShortcutsButton(this, "Menu_Button", float4(32.f, 58.f - ScreenHarfSize.y), ShortcutsType::GAMEENDMENU);
}

MainPlayer_MiniMenuButton* MainPlayer_MiniMenu::GetMenuButton(int _Index)
{
	return MiniMenuList_[_Index];
}

void MainPlayer_MiniMenu::MiniMenuEnabledOrDisabled()
{
	// 상태에 따라 메뉴목록 활성/비활성
	// 활성화되어있다면 Down 이미지가 디폴트 : 클릭시 DownClick -> UpDefault
	// 비활성화되어있다면 Up 이미지가 디폴트 : 클릭시 UpClick -> DownDefault
	if (false == MiniMenuActive_)
	{
		// 미니메뉴버튼목록 판넬 비활성화
		MiniMenuListPanel_->Off();

		// 미니메뉴버튼 목록 비활성화
		int MenuCnt = static_cast<int>(MiniMenuList_.size());
		for (int i = 0; i < MenuCnt; ++i)
		{
			MiniMenuList_[i]->Off();
		}
	}
	else
	{
		// 미니메뉴버튼목록 판넬 활성화
		MiniMenuListPanel_->On();

		// 미니메뉴버튼 목록 활성화
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
	// 활성화되어있다면 Down 이미지가 디폴트 : 클릭시 DownClick -> UpDefault
	// 비활성화되어있다면 Up 이미지가 디폴트 : 클릭시 UpClick -> DownDefault
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
	// 제자리 복귀 Flag On 이라면
	if (true == _BasicPosMove)
	{
		MiniMenuListPanel_->GetTransform()->SetLocalPosition(MiniMenuListPanelBasicPos_);

		// 미니메뉴목록 무브
		int MenuCnt = static_cast<int>(MiniMenuList_.size());
		for (int i = 0; i < MenuCnt; ++i)
		{
			MiniMenuList_[i]->GetTransform()->SetLocalPosition(float4::ZERO);
		}
	}
	else // 아니라면
	{
		// 판넬 무브
		float4 PanelMovePos = MiniMenuListPanel_->GetTransform()->GetLocalPosition();
		PanelMovePos.x += _MovePos.x;
		MiniMenuListPanel_->GetTransform()->SetLocalPosition(PanelMovePos);

		// 미니메뉴목록 무브
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
	// 외부에서 접근
	// 활성화되어있다면 Down 이미지가 디폴트 : 클릭시 DownClick -> UpDefault
	// 비활성화되어있다면 Up 이미지가 디폴트 : 클릭시 UpClick -> DownDefault
	// 1. 스킬창 활성화/비활성화시 호출
	// 2. 상태창 활성화/비활성화시 호출
	// 3. 인벤토리창 활성화/비활성화시 호출
	// 4. 창고창 활성화/비활성화시 호출
	// 5. 판매창 활성화/비활성화시 호출
	MiniMenuActive_ = _Flag;
	if (false == MiniMenuActive_)
	{
		// 미니메뉴버튼목록 판넬 비활성화
		MiniMenuListPanel_->Off();

		// 미니메뉴버튼 목록 비활성화
		int MenuCnt = static_cast<int>(MiniMenuList_.size());
		for (int i = 0; i < MenuCnt; ++i)
		{
			MiniMenuList_[i]->Off();
		}

		// 활성화/비활성화 버튼 이미지 전환
		MiniMenuActiveButton_->SetChangeAnimation("EnabledDefault");
	}
	else
	{
		// 미니메뉴버튼 목록 활성화
		MiniMenuListPanel_->On();

		// 미니메뉴버튼 목록 활성화
		int MenuCnt = static_cast<int>(MiniMenuList_.size());
		for (int i = 0; i < MenuCnt; ++i)
		{
			MiniMenuList_[i]->On();
		}

		// 활성화/비활성화 버튼 이미지 전환
		MiniMenuActiveButton_->SetChangeAnimation("DisabledDefault");
	}
}

void MainPlayer_MiniMenu::KeyInputViewProcess(int _Index)
{
	// 키입력에 의한 플레이어 UI 창 활성화/비활성화처리
	MiniMenuList_[_Index]->ShortcutsProcess();
}
