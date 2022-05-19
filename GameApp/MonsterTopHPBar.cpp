#include "PreCompile.h"
#include "MonsterTopHPBar.h"

#include <GameEngine/GameEngineProgressBarRenderer.h>
#include <GameEngine/GameEngineUIRenderer.h>

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

MonsterTopHPBar::MonsterTopHPBar() :
	HPBar_(nullptr),
	CurSelMonsterName_(nullptr),
	CurMonsterName_(),
	CurHP_(0.f),
	MapHP_(0.f),
	TextColor_(float4::WHITE)
{
}

MonsterTopHPBar::~MonsterTopHPBar()
{
}

void MonsterTopHPBar::Start()
{
	CurSelMonsterName_ = CreateTransformComponent<GameEngineUIRenderer>(static_cast<int>(UIRenderOrder::UI11));
	CurSelMonsterName_->SetImage("TopHPBar.png");
	CurSelMonsterName_->GetTransform()->SetLocalPosition(float4(0.f, 270.f));
	CurSelMonsterName_->SetResultColor(float4(0.f, 0.f, 0.f, 0.3f));
	CurSelMonsterName_->TextSetting("diablo", CurMonsterName_, 15.f, FW1_CENTER | FW1_VCENTER, float4::WHITE);

	HPBar_ = CreateTransformComponent<GameEngineProgressBarRenderer>(static_cast<int>(UIRenderOrder::UI12));
	HPBar_->SetImage("TopHPBar.png");
	HPBar_->SetResultColor(float4(1.f, 0.f, 0.f, 0.3f));
	HPBar_->SetProgressBarDirect(static_cast<int>(ProgressBarDirect::RightToLeft));
	HPBar_->GetTransform()->SetLocalPosition(CurSelMonsterName_->GetTransform()->GetLocalPosition());

	// 전역에 등록
	GlobalValue::TopHPBar = this;
	Off();
}

void MonsterTopHPBar::Update(float _DeltaTime)
{

}

void MonsterTopHPBar::SetCurMonster(const std::string& _MonsterName, int _MaxHP, int _HP, const float4& _TextColor)
{
	// 현재 화면에 표시되는 몬스터 이름과 해당 몬스터의 체력을 셋팅
	CurMonsterName_ = _MonsterName;
	CurHP_ = static_cast<float>(_HP);
	MapHP_ = static_cast<float>(_MaxHP);

	// 현재 선택된 몬스터명으로 화면에 표시
	CurSelMonsterName_->SetTextColor(_TextColor);
	CurSelMonsterName_->SetPrintText(CurMonsterName_);

	float Percent = CurHP_ / MapHP_;
	if (0.0f >= Percent)
	{
		Percent = 0.0f;
	}
	HPBar_->SetPercent(Percent);

	On();
}

void MonsterTopHPBar::CurMonsterTopHPBarOff()
{
	// 현재 정보 리셋
	CurMonsterName_ = "";
	CurHP_ = 0;
	MapHP_ = 0;

	CurSelMonsterName_->SetPrintText(CurMonsterName_);
	HPBar_->SetPercent(1.f);

	Off();

}
