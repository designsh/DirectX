#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"
#include "MouseObject.h"

#include "BottomStateBar.h"
#include "MainPlayer_MiniMenu.h"
#include "MainPlayer_Stamina.h"
#include "MainPlayer_CurExpProgressBar.h"
#include "StatView.h"
#include "SkillView.h"
#include "InventoryView.h"
#include "GameEndMenuView.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineLevel.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "Portal.h"

MainPlayer::MainPlayer() :
	IsTown_(true),
	IsRun_(false),
	IsInventoryView_(false),
	IsStateView_(false),
	IsSkillView_(false),
	IsRightSkillList_(false),
	IsLeftSkillList_(false),
	IsStorehouse_(false),
	IsGameEndMenu_(false),
	IsMove_(false),
	IsDefaultZOrderChangeChk_(false),
	IsFrameZOrderChangeChk_(false),
	CurHP_(100),
	CurMP_(100),
	PrevEXP_(0),
	CurEXP_(0),
	PrevLevel_(1),
	CurLevel_(1),
	State_(),
	BodyCollider_(nullptr),
	RenderSize_(float4(256.f, 256.f)),
	PrevMoveTargetPos_(float4::ZERO),
	CurMoveTargetPos_(float4::ZERO),
	PrevDirect_(TargetDirect::DIR_B),
	CurDirect_(TargetDirect::DIR_B),
	PrevState_(PlayerState::STAT_TN),
	CurState_(PlayerState::STAT_TN),
	BottomStateBar_(nullptr),
	StatView_(nullptr),
	SkillView_(nullptr),
	InventoryView_(nullptr),
	GameEndMenuView_(nullptr),
	MoveSpeed_(200.f),
	MoveTargetDir_(float4::ZERO),
	MoveTargetIndex_(TileIndex())
{
	IsItemEquipState_.clear();
	for (int i = 0; i < static_cast<int>(RendererPartType::PART_MAX); ++i)
	{
		IsItemEquipState_.insert(std::map<RendererPartType, bool>::value_type(static_cast<RendererPartType>(i), false));
	}
}

MainPlayer::~MainPlayer()
{
	if (!PartRenderer_.empty())
	{
		PartRenderer_.clear();
	}

	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		DirectRenderOrder_[i].clear();
	}
}

void MainPlayer::Start()
{
	// 플레이어 초기화
	MainPlayerinitialization();

	// 하단 상태바
	BottomStateBar_ = GetLevel()->CreateActor<BottomStateBar>();

	// 스킬창
	SkillView_ = GetLevel()->CreateActor<SkillView>();

	// 스탯창
	StatView_ = GetLevel()->CreateActor<StatView>();

	// 인벤토리창
	InventoryView_ = GetLevel()->CreateActor<InventoryView>();

	// 게임종료메뉴 창
	GameEndMenuView_ = GetLevel()->CreateActor<GameEndMenuView>();

	// ================================== 키생성 ================================== //
	// 스킬창 열기
	if (false == GameEngineInput::GetInst().IsKey("SkillViewActive"))
	{
		GameEngineInput::GetInst().CreateKey("SkillViewActive", 'T');
	}

	// 스탯창 열기
	if (false == GameEngineInput::GetInst().IsKey("StatViewActive"))
	{
		GameEngineInput::GetInst().CreateKey("StatViewActive", 'A');
	}

	// 인벤토리 열기
	if (false == GameEngineInput::GetInst().IsKey("InventoryActive"))
	{
		GameEngineInput::GetInst().CreateKey("InventoryActive", 'I');
	}

	// 게임종료메뉴 열기
	if (false == GameEngineInput::GetInst().IsKey("GameEndMenuActive"))
	{
		GameEngineInput::GetInst().CreateKey("GameEndMenuActive", VK_ESCAPE);
	}

	// 스태미나 활성/비활성
	if (false == GameEngineInput::GetInst().IsKey("StaminaActive"))
	{
		GameEngineInput::GetInst().CreateKey("StaminaActive", 'R');
	}

	// ============================================ 테스트용 ============================================ //
	if (false == GameEngineInput::GetInst().IsKey("TESTLEVELUP"))
	{
		GameEngineInput::GetInst().CreateKey("TESTLEVELUP", 'P');
	}
}

void MainPlayer::Update(float _DeltaTime)
{
	// 플레이어 관련 키체크
	PlayerUIActiveKeyCheck();

	// 상태별 행동패턴 처리
	State_.Update();

	if (true == GameEngineInput::GetInst().Down("TESTLEVELUP"))
	{
		// 테스트 경험치 증가
		int TextEXP = 10;
		BottomStateBar_->GetEXPProgressBarControl()->AddEXP(TextEXP);
	}

#pragma region 플레이어충돌체
	if (nullptr != BodyCollider_)
	{
#ifdef _DEBUG
		GetLevel()->PushDebugRender(BodyCollider_->GetTransform(), CollisionType::Rect);
#endif // _DEBUG

		BodyCollider_->Collision(CollisionType::Rect, CollisionType::Rect, static_cast<int>(UIRenderOrder::Object), std::bind(&MainPlayer::PlayerBodyCollision, this, std::placeholders::_1));
	}
#pragma endregion

	// 카메라는 플레이어를 따라 다닌다.
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
}

void MainPlayer::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
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

	// 하단상태바
	if (nullptr != BottomStateBar_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, BottomStateBar_);
	}

	// 상태창
	if (nullptr != StatView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, StatView_);
	}

	// 스킬창
	if (nullptr != SkillView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, SkillView_);
	}

	// 인벤토리창
	if (nullptr != InventoryView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, InventoryView_);
	}

	// 게임종료메뉴
	if (nullptr != GameEndMenuView_)
	{
		GetLevel()->SetLevelActorMove(_NextLevel, GameEndMenuView_);
	}

	// 메인플레이어
	GetLevel()->SetLevelActorMove(_NextLevel, this);
	_NextLevel->GetMainCameraActor()->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4(0.0f, 0.0f, -100.0f));
}

void MainPlayer::TownMapObjectCheck(const float4& _MousePos)
{
	// 마을맵에 존재하는 모든 오브젝트 상호작용 활성화해제 체크

	// 포탈
	if (nullptr != GlobalValue::Portal)
	{
		// 활성화되어있다면 해제
		if (true == GlobalValue::Portal->GetPortalInteractionFlag())
		{
			// 단, 마우스가 클릭한지점이 포탈이 존재하는 타일이 아닌경우에만 해제
			GlobalValue::Portal->PortMoveableFlagOff(_MousePos);
		}
	}

	// 창고는 제외
}

void MainPlayer::RandomMapObjectCheck(const float4& _MousePos)
{
	// 필드맵에 존재하는 모든 오브젝트 상호작용 활성화해제 체크

	// 아이템상자

	// HP우물

	// MP우물

	// 스태미나우물

	// 포탈
	if (nullptr != GlobalValue::Portal)
	{
		// 활성화되어있다면 해제
		if (true == GlobalValue::Portal->GetPortalInteractionFlag())
		{
			// 단, 마우스가 클릭한지점이 포탈이 존재하는 타일이 아닌경우에만 해제
			GlobalValue::Portal->PortMoveableFlagOff(_MousePos);
		}
	}
}

void MainPlayer::PlayerUIActiveKeyCheck()
{
	// 스킬창 열기
	if (true == GameEngineInput::GetInst().Down("SkillViewActive"))
	{
		BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(2);
	}
	
	// 스탯창 열기
	if (true == GameEngineInput::GetInst().Down("StatViewActive"))
	{
		BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(0);
	}

	// 인벤토리 열기
	if (true == GameEngineInput::GetInst().Down("InventoryActive"))
	{
		BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(1);
	}

	// 게임종료메뉴 열기(임시보류)
	if (true == GameEngineInput::GetInst().Down("GameEndMenuActive"))
	{
		BottomStateBar_->GetMiniMenuControl()->KeyInputViewProcess(3);
	}

	// 스태미나 활성/비활성
	if (true == GameEngineInput::GetInst().Down("StaminaActive"))
	{
		// 이미 활성화 되어있다면 비활성화
		if (true == IsRun_)
		{
			IsRun_ = false;

			// 하단상태바의 스태미나 활성/비활성버튼 셋팅
			BottomStateBar_->GetStaminaControl()->SetStaminaActive(IsRun_);

			// 플레이어가 이동중이라면 상태전환
			if (true == IsMove_)
			{
				// 마을인지 아닌지 판단
				if (true == IsTown_)
				{
					ChangeFSMState("Walk_Town");
				}
				else
				{
					ChangeFSMState("Walk_Field");
				}
			}
		}
		else // 아니라면 활성화
		{
			IsRun_ = true;

			// 하단상태바의 스태미나 활성/비활성버튼 셋팅
			BottomStateBar_->GetStaminaControl()->SetStaminaActive(IsRun_);

			// 플레이어가 이동중이라면 상태전환
			if (true == IsMove_)
			{
				ChangeFSMState("Run");
			}
		}
	}

	// 마우스 왼쪽버튼(추후 충돌시 호출로 변경예정)
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
#pragma region 게임화면을 벗어나면 이동불가 판단
		if (GameEngineWindow::GetInst().IsWindowRangeOut(GameEngineInput::GetInst().GetMousePos()))
		{
			return;
		}
#pragma endregion

#pragma region 마우스가 이미 UI와 충돌중이라면 이동불가 판단

#pragma region 플레이어 UI
		// 하단상태바와 충돌중이라면 클릭지점 이동불가
		if (true == GlobalValue::CurMouse->GetBottomStateBarCollision())
		{
			return;
		}

		// 스킬트리창 or 인벤토리창과 충돌중이라면 클릭지점 이동불가
		// 단, 클릭지점이 화면의 왼쪽지점이라면 이동가능판단
		if (true == GlobalValue::CurMouse->GetScreenRightUIViewCollision())
		{
			return;
		}

		// 스탯창 or NPC의 판매창 충돌중이라면 클릭지점 이동불가
		// 단, 클릭지점이 화면의 오른쪽지점이라면 이동가능판단
		if (true == GlobalValue::CurMouse->GetScreenLeftUIViewCollision())
		{
			return;
		}

		// 왼쪽스킬목록리스트와 충돌중이라면 이동불가
		if (true == GlobalValue::CurMouse->GetLWeaponSkillListCollision())
		{
			return;
		}

		// 오른쪽스킬목록리스트와 충돌중이라면 이동불가
		if (true == GlobalValue::CurMouse->GetRWeaponSkillListCollision())
		{
			return;
		}
#pragma endregion

#pragma region NPC UI
		if (true == IsTown_) // 마을레벨에만 NPC 존재
		{
			// 상단메뉴바
			if (true == GlobalValue::CurMouse->GetTopMenuBarCollision())
			{
				return;
			}

			// 판매창
			if (true == GlobalValue::CurMouse->GetBuySellViewCollision())
			{
				return;
			}
		}
#pragma endregion

#pragma endregion

		// 이동인지 체크후 이동이라면 방향계산후 상태 변경
		MouseObject* MainMouse = GlobalValue::CurMouse;
		if (nullptr == MainMouse)
		{
			GameEngineDebug::MsgBoxError("현재 마우스 오브젝트를 찾지 못하였습니다!!!!");
			return;
		}

		float4 MousePos = MainMouse->GetTransform()->GetWorldPosition();

#pragma region 오브젝트활성화여부체크
		if (true == IsTown_)
		{
			TownMapObjectCheck(MousePos);
		}
		else
		{
			RandomMapObjectCheck(MousePos);
		}
#pragma endregion

		// 이미 이동중이였다면 현재 경로를 삭제하고 Flag해제 후 플레이어 대기상태 돌입
		if (true == IsMove_)
		{
			MovePath_.clear();
			IsMove_ = false;

			if (true == IsTown_)
			{
				ChangeFSMState("Natural_Town");
			}
			else
			{
				ChangeFSMState("Natural_Field");
			}
		}

		// 현재 방향 전환 및 이동 Flag On
		if (true == MoveDirectCheck(MousePos))
		{
			// 이동 시작
			MoveStart(MousePos);
		}
	}
}

