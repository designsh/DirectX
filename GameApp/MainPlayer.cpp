#include "PreCompile.h"
#include "MainPlayer.h"

#include "BottomStateBar.h"

#include <GameEngine/GameEngineImageRenderer.h>

MainPlayer::MainPlayer() :
	PrevDirect_(TargetDirect::None),
	CurDirect_(TargetDirect::None),
	PlayerInfomation_(nullptr),
	BottomStateBar_(nullptr),
	HD_Renderer_(nullptr),
	LA_Renderer_(nullptr),
	LG_Renderer_(nullptr),
	RA_Renderer_(nullptr),
	RH_Renderer_(nullptr),
	S1_Renderer_(nullptr),
	S2_Renderer_(nullptr),
	SH_Renderer_(nullptr),
	TR_Renderer_(nullptr)
{
}

MainPlayer::~MainPlayer()
{
}

void MainPlayer::ChangeAnimaton(const std::string& _AnimationName, TargetDirect _Direct)
{
	// 수신한 인자를 이용하여 애니메이션 명칭 편집
	TargetDirect ChangeDirect = _Direct;

	std::string EditName = _AnimationName;

	// 



}

void MainPlayer::Start()
{
	// 플레이어 애니메이션 관련 이미지 Cut
	AllAnimationCut();

	// 플레이어 애니메이션 생성 관련
	CreateAnimation();

	// 하단 상태바
	BottomStateBar_ = GetLevel()->CreateActor<BottomStateBar>();

	// 스킬창

	// 스탯창

	// 인벤토리창

}

void MainPlayer::Update(float _DeltaTime)
{
	// 카메라위치를 플레이어위치에 따라 갱신
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());


}

