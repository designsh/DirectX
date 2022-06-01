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

	// ����â�� ���� ����ġ ����
	GlobalValue::CurPlayer->GetStatView()->CurEXPUpdate(CurEXP_);

	// ����ġ 100%�϶� �÷��̾�� �������ϸ�, �ƴϸ� ����ġ�� ����
	if (1.0f <= CurEXP_)
	{
		// ����ġ �ʱ�ȭ
		CurEXP_ = 0.0f;
		GlobalValue::CurPlayer->GetStatView()->CurEXPUpdate(CurEXP_);

		// ���� �÷��̾� ������
		GlobalValue::CurPlayer->SetLevelUP();

		// ��������Ʈ �ο� �� ����â�� ���緹�� ����, ���� ����Ʈ�� ��ư Ȱ��ȭ
		GlobalValue::CurPlayer->GetStatView()->LevelUpStatPointGrant();

		// ��ų����Ʈ �ο� �� ��ųâ�� ��ų������ Ȱ��ȭ
		GlobalValue::CurPlayer->GetSkillView()->LevelUpSkillPointGrant();
	}
	ExpRenderer_->SetPercent(CurEXP_);
}
