#include "PreCompile.h"
#include "MainPlayer.h"

#include "BottomStateBar.h"

#include <GameEngine/GameEngineImageRenderer.h>

MainPlayer::MainPlayer() :
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

void MainPlayer::ChangeAnimaton(const std::string& _Name)
{
	// 수신한 인자를 이용하여 애니메이션 명칭 편집




}

void MainPlayer::Start()
{
	// 플레이어 애니메이션 관련 이미지 Cut
	AllAnimationCut();

	// 플레이어 애니메이션 생성 관련
	CreateAnimation();

	// ======================================== 플레이어 부위별 렌더러 ======================================== //
	float4 PlayerSize = float4(500.f, 500.f, 1.f);

	HD_Renderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	HD_Renderer_->SetImage("LIT_Natural_Field_HD.png");
	HD_Renderer_->CreateAnimation("LIT_NU_HD_LB", 0, 7, 0.1f);
	HD_Renderer_->CreateAnimation("LIT_NU_HD_LT", 8, 15, 0.1f);
	HD_Renderer_->CreateAnimation("LIT_NU_HD_RT", 16, 23, 0.1f);
	HD_Renderer_->CreateAnimation("LIT_NU_HD_RB", 24, 31, 0.1f);
	HD_Renderer_->CreateAnimation("LIT_NU_HD_B", 32, 39, 0.1f);
	HD_Renderer_->CreateAnimation("LIT_NU_HD_L", 40, 47, 0.1f);
	HD_Renderer_->CreateAnimation("LIT_NU_HD_T", 48, 55, 0.1f);
	HD_Renderer_->CreateAnimation("LIT_NU_HD_R", 56, 73, 0.1f);
	HD_Renderer_->SetChangeAnimation("LIT_NU_HD_B");
	HD_Renderer_->GetTransform()->SetLocalScaling(PlayerSize);

	LA_Renderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	LA_Renderer_->SetImage("LIT_Natural_Field_LA.png");
	LA_Renderer_->CreateAnimation("LIT_NU_LA_LB", 0, 7, 0.1f);
	LA_Renderer_->CreateAnimation("LIT_NU_LA_LT", 8, 15, 0.1f);
	LA_Renderer_->CreateAnimation("LIT_NU_LA_RT", 16, 23, 0.1f);
	LA_Renderer_->CreateAnimation("LIT_NU_LA_RB", 24, 31, 0.1f);
	LA_Renderer_->CreateAnimation("LIT_NU_LA_B", 32, 39, 0.1f);
	LA_Renderer_->CreateAnimation("LIT_NU_LA_L", 40, 47, 0.1f);
	LA_Renderer_->CreateAnimation("LIT_NU_LA_T", 48, 55, 0.1f);
	LA_Renderer_->CreateAnimation("LIT_NU_LA_R", 56, 73, 0.1f);
	LA_Renderer_->SetChangeAnimation("LIT_NU_LA_B");
	LA_Renderer_->GetTransform()->SetLocalScaling(PlayerSize);

	LG_Renderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	LG_Renderer_->SetImage("LIT_Natural_Field_LG.png");
	LG_Renderer_->CreateAnimation("LIT_NU_LG_LB", 0, 7, 0.1f);
	LG_Renderer_->CreateAnimation("LIT_NU_LG_LT", 8, 15, 0.1f);
	LG_Renderer_->CreateAnimation("LIT_NU_LG_RT", 16, 23, 0.1f);
	LG_Renderer_->CreateAnimation("LIT_NU_LG_RB", 24, 31, 0.1f);
	LG_Renderer_->CreateAnimation("LIT_NU_LG_B", 32, 39, 0.1f);
	LG_Renderer_->CreateAnimation("LIT_NU_LG_L", 40, 47, 0.1f);
	LG_Renderer_->CreateAnimation("LIT_NU_LG_T", 48, 55, 0.1f);
	LG_Renderer_->CreateAnimation("LIT_NU_LG_R", 56, 73, 0.1f);
	LG_Renderer_->SetChangeAnimation("LIT_NU_LG_B");
	LG_Renderer_->GetTransform()->SetLocalScaling(PlayerSize);

	RA_Renderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	RA_Renderer_->SetImage("LIT_Natural_Field_RA.png");
	RA_Renderer_->CreateAnimation("LIT_NU_RA_LB", 0, 7, 0.1f);
	RA_Renderer_->CreateAnimation("LIT_NU_RA_LT", 8, 15, 0.1f);
	RA_Renderer_->CreateAnimation("LIT_NU_RA_RT", 16, 23, 0.1f);
	RA_Renderer_->CreateAnimation("LIT_NU_RA_RB", 24, 31, 0.1f);
	RA_Renderer_->CreateAnimation("LIT_NU_RA_B", 32, 39, 0.1f);
	RA_Renderer_->CreateAnimation("LIT_NU_RA_L", 40, 47, 0.1f);
	RA_Renderer_->CreateAnimation("LIT_NU_RA_T", 48, 55, 0.1f);
	RA_Renderer_->CreateAnimation("LIT_NU_RA_R", 56, 73, 0.1f);
	RA_Renderer_->SetChangeAnimation("LIT_NU_RA_B");
	RA_Renderer_->GetTransform()->SetLocalScaling(PlayerSize);

	RH_Renderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	RH_Renderer_->SetImage("LIT_Natural_Field_RH.png");
	RH_Renderer_->CreateAnimation("LIT_NU_RH_LB", 0, 7, 0.1f);
	RH_Renderer_->CreateAnimation("LIT_NU_RH_LT", 8, 15, 0.1f);
	RH_Renderer_->CreateAnimation("LIT_NU_RH_RT", 16, 23, 0.1f);
	RH_Renderer_->CreateAnimation("LIT_NU_RH_RB", 24, 31, 0.1f);
	RH_Renderer_->CreateAnimation("LIT_NU_RH_B", 32, 39, 0.1f);
	RH_Renderer_->CreateAnimation("LIT_NU_RH_L", 40, 47, 0.1f);
	RH_Renderer_->CreateAnimation("LIT_NU_RH_T", 48, 55, 0.1f);
	RH_Renderer_->CreateAnimation("LIT_NU_RH_R", 56, 73, 0.1f);
	RH_Renderer_->SetChangeAnimation("LIT_NU_RH_B");
	RH_Renderer_->GetTransform()->SetLocalScaling(PlayerSize);

	S1_Renderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	S1_Renderer_->SetImage("LIT_Natural_Field_S1.png");
	S1_Renderer_->CreateAnimation("LIT_NU_S1_LB", 0, 7, 0.1f);
	S1_Renderer_->CreateAnimation("LIT_NU_S1_LT", 8, 15, 0.1f);
	S1_Renderer_->CreateAnimation("LIT_NU_S1_RT", 16, 23, 0.1f);
	S1_Renderer_->CreateAnimation("LIT_NU_S1_RB", 24, 31, 0.1f);
	S1_Renderer_->CreateAnimation("LIT_NU_S1_B", 32, 39, 0.1f);
	S1_Renderer_->CreateAnimation("LIT_NU_S1_L", 40, 47, 0.1f);
	S1_Renderer_->CreateAnimation("LIT_NU_S1_T", 48, 55, 0.1f);
	S1_Renderer_->CreateAnimation("LIT_NU_S1_R", 56, 73, 0.1f);
	S1_Renderer_->SetChangeAnimation("LIT_NU_S1_B");
	S1_Renderer_->GetTransform()->SetLocalScaling(PlayerSize);

	S2_Renderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	S2_Renderer_->SetImage("LIT_Natural_Field_S2.png");
	S2_Renderer_->CreateAnimation("LIT_NU_S2_LB", 0, 7, 0.1f);
	S2_Renderer_->CreateAnimation("LIT_NU_S2_LT", 8, 15, 0.1f);
	S2_Renderer_->CreateAnimation("LIT_NU_S2_RT", 16, 23, 0.1f);
	S2_Renderer_->CreateAnimation("LIT_NU_S2_RB", 24, 31, 0.1f);
	S2_Renderer_->CreateAnimation("LIT_NU_S2_B", 32, 39, 0.1f);
	S2_Renderer_->CreateAnimation("LIT_NU_S2_L", 40, 47, 0.1f);
	S2_Renderer_->CreateAnimation("LIT_NU_S2_T", 48, 55, 0.1f);
	S2_Renderer_->CreateAnimation("LIT_NU_S2_R", 56, 73, 0.1f);
	S2_Renderer_->SetChangeAnimation("LIT_NU_S2_B");
	S2_Renderer_->GetTransform()->SetLocalScaling(PlayerSize);

	//SH_Renderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform()); // LIT상태일때 방패없음

	TR_Renderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	TR_Renderer_->SetImage("LIT_Natural_Field_TR.png");
	TR_Renderer_->CreateAnimation("LIT_NU_TR_LB", 0, 7, 0.1f);
	TR_Renderer_->CreateAnimation("LIT_NU_TR_LT", 8, 15, 0.1f);
	TR_Renderer_->CreateAnimation("LIT_NU_TR_RT", 16, 23, 0.1f);
	TR_Renderer_->CreateAnimation("LIT_NU_TR_RB", 24, 31, 0.1f);
	TR_Renderer_->CreateAnimation("LIT_NU_TR_B", 32, 39, 0.1f);
	TR_Renderer_->CreateAnimation("LIT_NU_TR_L", 40, 47, 0.1f);
	TR_Renderer_->CreateAnimation("LIT_NU_TR_T", 48, 55, 0.1f);
	TR_Renderer_->CreateAnimation("LIT_NU_TR_R", 56, 73, 0.1f);
	TR_Renderer_->SetChangeAnimation("LIT_NU_TR_B");
	TR_Renderer_->GetTransform()->SetLocalScaling(PlayerSize);
	
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

