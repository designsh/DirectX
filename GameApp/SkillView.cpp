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

	// 플레이어 이동불가처리를 위한 충돌체 생성
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

	// 현재 선택된 페이지 판넬 렌더러만 On상태
	SkillPagePanel_[static_cast<int>(CurSkillPage)]->On();

	// 스킬창 관련 텍스트
	SkillPointTitle_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	SkillPointTitle_->GetTransform()->SetLocalPosition(float4(ScreenHarfSzie.x - 122.f, 194.f));
	SkillPointTitle_->TextSetting("diablo", "POINT", 14, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	CurSkillPoint_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	CurSkillPoint_->GetTransform()->SetLocalPosition(float4(ScreenHarfSzie.x - 122.f, 166.f));
	CurSkillPoint_->TextSetting("diablo", std::to_string(SkillPoint), 14, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	Page3Name_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	Page3Name_->GetTransform()->SetLocalPosition(float4(ScreenHarfSzie.x - 124.f, 80.f));
	Page3Name_->TextSetting("diablo", "소환 스펠", 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	Page2Name_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	Page2Name_->GetTransform()->SetLocalPosition(float4(ScreenHarfSzie.x - 124.f, -30.f));
	Page2Name_->TextSetting("diablo", "포이즌&본스펠", 11, FW1_VCENTER | FW1_CENTER, float4::WHITE);

	Page1Name_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI0_Text));
	Page1Name_->GetTransform()->SetLocalPosition(float4(ScreenHarfSzie.x - 124.f, -136.f));
	Page1Name_->TextSetting("diablo", "저주 스펠", 12, FW1_VCENTER | FW1_CENTER, float4::WHITE);

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

	// 스킬창 종료버튼 체크
	if (CloseButtonState_ == Button_State::Click)
	{
		if (true == GameEngineInput::GetInst().Up("MouseLButton"))
		{
			// MainPlayer Flag Off
			if (nullptr != GlobalValue::CurPlayer)
			{
				// 미니메뉴 원래자리 복귀
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->AllMoveMiniMenu(true);

				// 스킬창 비활성화
				GlobalValue::CurPlayer->GetBottomStateBar()->GetMiniMenuControl()->KeyInputViewProcess(2);
			}

			CloseButtonState_ = Button_State::Normal;
		}
	}

	// 창종료 버튼 충돌체크
	CloseButtonCollider_->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::CloseButtonClick, this, std::placeholders::_1));

	// 스킬페이지 전환 버튼 충돌체크
	SkillPageCollider_[0]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::SkillPage1ChangeClick, this, std::placeholders::_1));
	SkillPageCollider_[1]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::SkillPage2ChangeClick, this, std::placeholders::_1));
	SkillPageCollider_[2]->Collision(CollisionType::Rect, CollisionType::CirCle, static_cast<int>(UIRenderOrder::Mouse), std::bind(&SkillView::SkillPage3ChangeClick, this, std::placeholders::_1));
}

void SkillView::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
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
	else if (std::string::npos != _NextLevel->GetName().find("EndingLevel"))
	{
		return;
	}

	// 스킬창이 들고있는 모든 액터 넘김
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
	// 메인플레이어 정보를 이용하여 String Setting
	MainPlayerInfo PlayerInfo = MainPlayerInfomation::GetInst().GetMainPlayerInfoValue();
	
	// 스킬페이지별 스킬목록 생성(기본스킬 제외)

	// 해당 메인플레이어가 가지고있는 스킬정보만큼 반복
	int AllSkillCount = static_cast<int>(PlayerInfo.SkillInfo.size());
	for (int i = 0; i < AllSkillCount; ++i)
	{
		// 해당 스킬의 페이지 No Get
		if (0 == PlayerInfo.SkillInfo[i].SkillPage)
		{
			// 기본스킬들은 아이콘 생성하지않는다.
			continue;
		}

		// 스킬아이콘 생성에 필요정보 Get
		SkillPageNo PageNo = static_cast<SkillPageNo>(PlayerInfo.SkillInfo[i].SkillPage - 1);	// 스킬이 1번페이지부터시작이므로 페이지번호를 -1하여 0번부터 설정되도록 설정
		std::string SkillName = PlayerInfo.SkillInfo[i].SkillName;
		int SkillCode = PlayerInfo.SkillInfo[i].SkillCode;
		bool SkillActive = PlayerInfo.SkillInfo[i].SkillActive;
		int SkillRow = PlayerInfo.SkillInfo[i].SkillRow;
		int SkillColumn = PlayerInfo.SkillInfo[i].SkillColumn;
		int SkillLevel = PlayerInfo.SkillInfo[i].CurSkillLevel;

		// 신규 스킬 아이콘 생성
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
	// Page1 선택(CurseSpell(저주스펠))
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		SkillPageTabChange(SkillPageNo::CurseSpell);
	}
}

void SkillView::SkillPage2ChangeClick(GameEngineCollision* _Other)
{
	// Page2 선택(PoisonandBoneSpells(포이즌&본스펠))
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		SkillPageTabChange(SkillPageNo::PoisonandBoneSpells);
	}
}

void SkillView::SkillPage3ChangeClick(GameEngineCollision* _Other)
{
	// Page3 선택(SummonSpell(소환스펠))
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		SkillPageTabChange(SkillPageNo::SummonSpell);
	}
}

void SkillView::SkillPageTabChange(SkillPageNo _SkillPageNo)
{
	// 현재 선택된 스킬페이지와 현재 선택된 스킬페이지가 같다면 리턴
	if (CurSkillPage == _SkillPageNo)
	{
		return;
	}

	// 아니라면 CurSkillPage의 판넬과 아이콘목록을 모두 Off시키고,
	// 현재 선택된 페이지를 변경
	SkillPagePanel_[static_cast<int>(CurSkillPage)]->Off();

	// 해당 스킬아이콘 목록 모두 On
	int CurSkillIconCnt = static_cast<int>(SkillPageToIcon[static_cast<int>(CurSkillPage)].size());
	for (int i = 0; i < CurSkillIconCnt; ++i)
	{
		SkillPageToIcon[static_cast<int>(CurSkillPage)][i]->Off();
	}
	CurSkillPage = _SkillPageNo;

	// 현재 선택된 페이지 관련 렌더러를 모두 On상태로 전환

	// 스킬페이지 판넬 On
	SkillPagePanel_[static_cast<int>(CurSkillPage)]->On();

	// 해당 스킬아이콘 목록 모두 On
	int ChangeSkillIconCnt = static_cast<int>(SkillPageToIcon[static_cast<int>(CurSkillPage)].size());
	for (int i = 0; i < ChangeSkillIconCnt; ++i)
	{
		SkillPageToIcon[static_cast<int>(CurSkillPage)][i]->On();
	}

	// 스킬창 종료버튼 이동(2번페이지일때만 위치가 다름)
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
	// 3포인트 부여
	SkillPoint += 3;

	// 스킬창 포인트 텍스트 셋팅
	CurSkillPoint_->SetPrintText(std::to_string(SkillPoint));

	// 외부에서 호출하며, 플레이어 레벨업시 스킬포인트가 부여되며 스킬아이콘 레벨업을 위해
	// 스킬아이콘이 모두 활성화 상태가 된다.
	for (int i = 0; i < static_cast<int>(SkillPageNo::MAX); ++i)
	{
		int SkillIconListCnt = static_cast<int>(SkillPageToIcon[i].size());
		for (int j = 0; j < SkillIconListCnt; ++j)
		{
			SkillPageToIcon[i][j]->SetSkillIconActive();
		}
	}

	// 하단상태바의 스킬포인트 활성화포인트 활성화
	GlobalValue::CurPlayer->GetBottomStateBar()->GetSkillPointControl()->LevelUpPointButtonActive();
}

void SkillView::SkillPointDeduction()
{
	if (0 != SkillPoint)
	{
		SkillPoint -= 1;
	}

	CurSkillPoint_->SetPrintText(std::to_string(SkillPoint));

	// 외부에서 호출하며, 부여된 스킬포인트가 모두 소진하여
	// 스킬아이콘이 모두 비활성화 상태가 된다.
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

		// 하단상태바의 스킬포인트 활성화포인트 비활성화
		GlobalValue::CurPlayer->GetBottomStateBar()->GetSkillPointControl()->LevelUpPointExhaust();
	}
}
