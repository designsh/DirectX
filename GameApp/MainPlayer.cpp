#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"
#include "BottomStateBar.h"
#include "MouseObject.h"

#include <GameEngine/GameEngineImageRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

MainPlayer::MainPlayer() :
	IsTown_(true),
	IsRun_(false),
	IsInventory_(false),
	IsStateView_(false),
	IsSkillView_(false),
	IsRightSkillList_(false),
	IsLeftSkillList_(false),
	IsStorehouse_(false),
	IsMove_(false),
	IsDefaultZOrderChangeChk_(false),
	IsFrameZOrderChangeChk_(false),
	State_(),
	RenderSize_(float4(256.f, 256.f)),
	PrevMoveTargetPos_(float4::ZERO),
	CurMoveTargetPos_(float4::ZERO),
	PrevDirect_(TargetDirect::DIR_B),
	CurDirect_(TargetDirect::DIR_B),
	PrevState_(PlayerState::STAT_TN),
	CurState_(PlayerState::STAT_TN),
	BottomStateBar_(nullptr)
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

	// 스탯창

	// 인벤토리창

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

	// 스태미나 활성/비활성
	if (false == GameEngineInput::GetInst().IsKey("StaminaActive"))
	{
		GameEngineInput::GetInst().CreateKey("StaminaActive", 'R');
	}

	// TEST 용
	if (false == GameEngineInput::GetInst().IsKey("NextDirect"))
	{
		GameEngineInput::GetInst().CreateKey("NextDirect", '1');
	}

	if (false == GameEngineInput::GetInst().IsKey("PrevDirect"))
	{
		GameEngineInput::GetInst().CreateKey("PrevDirect", '2');
	}

	if (false == GameEngineInput::GetInst().IsKey("NextState"))
	{
		GameEngineInput::GetInst().CreateKey("NextState", '3');
	}

	if (false == GameEngineInput::GetInst().IsKey("PrevState"))
	{
		GameEngineInput::GetInst().CreateKey("PrevState", '4');
	}
}

void MainPlayer::Update(float _DeltaTime)
{
	// 카메라위치를 플레이어위치에 따라 갱신
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

	// 플레이어 관련 키체크
	PlayerUIActiveKeyCheck();

	// 상태별 행동패턴 처리
	State_.Update();

	// TEST
	if (true == GameEngineInput::GetInst().Down("NextDirect"))
	{

	}

	if (true == GameEngineInput::GetInst().Down("PrevDirect"))
	{

		int a = 0;
	}

	if (true == GameEngineInput::GetInst().Down("NextState"))
	{

		int a = 0;
	}

	if (true == GameEngineInput::GetInst().Down("PrevState"))
	{

		int a = 0;
	}
}

void MainPlayer::PlayerUIActiveKeyCheck()
{
	// 스킬창 열기
	if (true == GameEngineInput::GetInst().Down("SkillViewActive"))
	{
		// 이미 활성화 되어있다면 비활성화
		if (true == IsSkillView_)
		{
			IsSkillView_ = false;
		}
		else // 아니라면 활성화
		{
			IsSkillView_ = true;
		}
	}
	
	// 스탯창 열기
	if (true == GameEngineInput::GetInst().Down("StatViewActive"))
	{
		// 이미 활성화 되어있다면 비활성화
		if (true == IsStateView_)
		{
			IsStateView_ = false;
		}
		else // 아니라면 활성화
		{
			IsStateView_ = true;
		}
	}

	// 인벤토리 열기
	if (true == GameEngineInput::GetInst().Down("InventoryActive"))
	{
		// 이미 활성화 되어있다면 비활성화
		if (true == IsInventory_)
		{
			IsInventory_ = false;
		}
		else // 아니라면 활성화
		{
			IsInventory_ = true;
		}
	}

	// 스태미나 활성/비활성
	if (true == GameEngineInput::GetInst().Down("StaminaActive"))
	{
		// 이미 활성화 되어있다면 비활성화
		if (true == IsRun_)
		{
			IsRun_ = false;
		}
		else // 아니라면 활성화
		{
			IsRun_ = true;
		}
	}

	// 마우스 왼쪽버튼(추후 충돌시 호출로 변경예정)
	if (true == GameEngineInput::GetInst().Down("MouseLButton"))
	{
		// 이동인지 체크후 이동이라면 방향계산후 상태 변경
		MouseObject* MainMouse = GlobalValue::CurMouse;
		if (nullptr == MainMouse)
		{
			GameEngineDebug::MsgBoxError("현재 마우스 오브젝트를 찾지 못하였습니다!!!!");
			return;
		}

		float4 MousePos = MainMouse->GetTransform()->GetLocalPosition();

		// 현재 방향 전환 및 이동 Flag On
		if (true == MoveDirectCheck(MousePos))
		{
			// 이동 시작
			MoveStart();
		}
	}
}

