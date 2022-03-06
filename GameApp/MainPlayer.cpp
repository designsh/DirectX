#include "PreCompile.h"
#include "MainPlayer.h"

#include "MainPlayerInfomation.h"
#include "BottomStateBar.h"

#include <GameEngine/GameEngineImageRenderer.h>

MainPlayer::MainPlayer() :
	PrevDirect_(TargetDirect::None),
	CurDirect_(TargetDirect::None),
	PrevState_(PlayerState::STAT_TN),
	CurState_(PlayerState::STAT_TN),
	StateName_(),
	BottomStateBar_(nullptr),
	PlayerSize_(float4::ZERO)
{
}

MainPlayer::~MainPlayer()
{
	if (!StateName_.empty())
	{
		StateName_.clear();
	}
}

void MainPlayer::Start()
{
	// 플레이어 상태명을 생성
	CreateStateName();

	// 플레이어 애니메이션 관련 이미지 Cut
	AllAnimationCut();

	// 플레이어 애니메이션 생성 관련
	CreateAnimation();

	// 하단 상태바
	BottomStateBar_ = GetLevel()->CreateActor<BottomStateBar>();

	// 스킬창

	// 스탯창

	// 인벤토리창

	// TEST(원래는 캐릭터생성화면에서 해당 함수 호출됨)
	MainPlayerInfomation::GetInst().CreateMainPlayerInfo("aaaa", JobType::Necromancer);

	if (false == GameEngineInput::GetInst().IsKey("NextAnimation"))
	{
		GameEngineInput::GetInst().CreateKey("NextAnimation", '1');
	}
}

void MainPlayer::Update(float _DeltaTime)
{
	// TEST
	if (true == GameEngineInput::GetInst().Down("NextAnimation"))
	{
		ChangePlayerAnimation(PlayerState::STAT_TN, static_cast<TargetDirect>(Test));
		++Test;
		if (Test >= static_cast<int>(TargetDirect::DIR_MAX))
		{
			Test = 0;
		}
	}

	// 카메라위치를 플레이어위치에 따라 갱신
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
}

