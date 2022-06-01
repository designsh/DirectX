#include "PreCompile.h"
#include "MainPlayer_CurExpProgressBar.h"

#include <GameEngine/GameEngineProgressBarRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

#include "SkillView.h"
#include "StatView.h"

MainPlayer_CurExpProgressBar::MainPlayer_CurExpProgressBar() :
	ExpRenderer_(nullptr),
	CurEXP_(0.f)
{
}

MainPlayer_CurExpProgressBar::~MainPlayer_CurExpProgressBar()
{
}

void MainPlayer_CurExpProgressBar::Start()
{
	float4 ScreenHarfSize = GameEngineWindow::GetInst().GetSize().halffloat4();

	CurEXP_ = 0.0f;

	ExpRenderer_ = CreateTransformComponent<GameEngineProgressBarRenderer>(static_cast<int>(UIRenderOrder::UI11));
	ExpRenderer_->SetImage("MainPlayer_CurEXP.png");
	ExpRenderer_->SetProgressBarDirect(static_cast<int>(ProgressBarDirect::RightToLeft));
	ExpRenderer_->GetTransform()->SetLocalPosition(float4(-85.f, 38.f - ScreenHarfSize.y));
	ExpRenderer_->SetPercent(CurEXP_);
}

void MainPlayer_CurExpProgressBar::Update(float _DeltaTime)
{
}

void MainPlayer_CurExpProgressBar::AddEXP(int _EXP)
{
	float EXP = static_cast<float>(_EXP);
	EXP *= 0.001f;
	CurEXP_ += EXP;

	// 스탯창의 현재 경험치 셋팅
	GlobalValue::CurPlayer->GetStatView()->CurEXPUpdate(CurEXP_);

	// 경험치 100%일때 플레이어는 레벨업하며, 아니면 경험치만 증가
	if (1.0f <= CurEXP_)
	{
		// 경험치 초기화
		CurEXP_ = 0.0f;
		GlobalValue::CurPlayer->GetStatView()->CurEXPUpdate(CurEXP_);

		// 현재 플레이어 레벨업
		GlobalValue::CurPlayer->SetLevelUP();

		// 스탯포인트 부여 및 상태창의 현재레벨 변경, 스탯 포인트업 버튼 활성화
		GlobalValue::CurPlayer->GetStatView()->LevelUpStatPointGrant();

		// 스킬포인트 부여 및 스킬창의 스킬아이콘 활성화
		GlobalValue::CurPlayer->GetSkillView()->LevelUpSkillPointGrant();
	}
	ExpRenderer_->SetPercent(CurEXP_);
}
