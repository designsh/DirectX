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
#include <GameEngine/GameEngineLevel.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

MainPlayer::MainPlayer() :
	IsTown_(true),
	//IsTown_(false),
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
	GameEndMenuView_(nullptr)
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
		// UI 충돌과 동시에 클릭일시 리턴처리(이동불가처리)



		// 이동인지 체크후 이동이라면 방향계산후 상태 변경
		MouseObject* MainMouse = GlobalValue::CurMouse;
		if (nullptr == MainMouse)
		{
			GameEngineDebug::MsgBoxError("현재 마우스 오브젝트를 찾지 못하였습니다!!!!");
			return;
		}

		float4 MousePos = MainMouse->GetTransform()->GetWorldPosition();

		// 현재 방향 전환 및 이동 Flag On
		if (true == MoveDirectCheck(MousePos))
		{
			// 이동 시작
			MoveStart();
		}
	}
}

