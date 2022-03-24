#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineTextureManager.h>
#include <GameEngine/GameEngineTexture.h>
#include <GameEngine/GameEngineTransform.h>

void MainPlayer::CreateAnimation()
{
	for (int i = 0; i < static_cast<int>(RendererPartType::PART_MAX); ++i)
	{
		PlayerRendererPart RenderPart = {};

		// LIT / HVY 렌더러 추가
		for (int j = 0; j < 2; ++j)
		{
			RenderPart.Renderer_[j] = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		}

		// 초기 LIT 상태이므로 HVY상태 렌더러 모두 Off
		RenderPart.Renderer_[1]->Off();

		RenderPart.PartType_ = static_cast<RendererPartType>(i);

		// 초기 방패 렌더러 Off
		if (i == static_cast<int>(RendererPartType::PART_SH))
		{
			RenderPart.Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->Off();
		}

		PartRenderer_.push_back(RenderPart);
	}

	CreateA1Animation();
	CreateA2Animation();
	CreateBLAnimation();
	CreateDDAnimation();
	CreateDTAnimation();
	CreateGHAnimation();
	CreateKKAnimation();
	CreateNUAnimation();
	CreateRNAnimation();
	CreateS1Animation();
	CreateSCAnimation();
	CreateTNAnimation();
	CreateTWAnimation();
	CreateWLAnimation();
}

void MainPlayer::CreateA1Animation()
{
	// =========================== x : 19, y : 16 ============================ //
	
	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_HD.png", "LIT_Attack1_HD_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_HD.png", "LIT_Attack1_HD_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_HD.png", "LIT_Attack1_HD_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_HD.png", "LIT_Attack1_HD_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_HD.png", "LIT_Attack1_HD_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_HD.png", "LIT_Attack1_HD_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_HD.png", "LIT_Attack1_HD_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_HD.png", "LIT_Attack1_HD_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LA.png", "LIT_Attack1_LA_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LA.png", "LIT_Attack1_LA_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LA.png", "LIT_Attack1_LA_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LA.png", "LIT_Attack1_LA_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LA.png", "LIT_Attack1_LA_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LA.png", "LIT_Attack1_LA_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LA.png", "LIT_Attack1_LA_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LA.png", "LIT_Attack1_LA_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LG.png", "LIT_Attack1_LG_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LG.png", "LIT_Attack1_LG_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LG.png", "LIT_Attack1_LG_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LG.png", "LIT_Attack1_LG_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LG.png", "LIT_Attack1_LG_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LG.png", "LIT_Attack1_LG_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LG.png", "LIT_Attack1_LG_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_LG.png", "LIT_Attack1_LG_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RA.png", "LIT_Attack1_RA_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RA.png", "LIT_Attack1_RA_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RA.png", "LIT_Attack1_RA_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RA.png", "LIT_Attack1_RA_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RA.png", "LIT_Attack1_RA_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RA.png", "LIT_Attack1_RA_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RA.png", "LIT_Attack1_RA_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RA.png", "LIT_Attack1_RA_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RH.png", "LIT_Attack1_RH_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RH.png", "LIT_Attack1_RH_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RH.png", "LIT_Attack1_RH_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RH.png", "LIT_Attack1_RH_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RH.png", "LIT_Attack1_RH_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RH.png", "LIT_Attack1_RH_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RH.png", "LIT_Attack1_RH_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_RH.png", "LIT_Attack1_RH_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S1.png", "LIT_Attack1_S1_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S1.png", "LIT_Attack1_S1_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S1.png", "LIT_Attack1_S1_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S1.png", "LIT_Attack1_S1_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S1.png", "LIT_Attack1_S1_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S1.png", "LIT_Attack1_S1_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S1.png", "LIT_Attack1_S1_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S1.png", "LIT_Attack1_S1_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S2.png", "LIT_Attack1_S2_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S2.png", "LIT_Attack1_S2_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S2.png", "LIT_Attack1_S2_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S2.png", "LIT_Attack1_S2_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S2.png", "LIT_Attack1_S2_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S2.png", "LIT_Attack1_S2_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S2.png", "LIT_Attack1_S2_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_S2.png", "LIT_Attack1_S2_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_TR.png", "LIT_Attack1_TR_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_TR.png", "LIT_Attack1_TR_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_TR.png", "LIT_Attack1_TR_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_TR.png", "LIT_Attack1_TR_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_TR.png", "LIT_Attack1_TR_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_TR.png", "LIT_Attack1_TR_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_TR.png", "LIT_Attack1_TR_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack1_TR.png", "LIT_Attack1_TR_R", 133, 151, 0.1f);

	// =============================== HVY =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_HD.png", "HVY_Attack1_HD_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_HD.png", "HVY_Attack1_HD_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_HD.png", "HVY_Attack1_HD_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_HD.png", "HVY_Attack1_HD_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_HD.png", "HVY_Attack1_HD_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_HD.png", "HVY_Attack1_HD_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_HD.png", "HVY_Attack1_HD_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_HD.png", "HVY_Attack1_HD_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LA.png", "HVY_Attack1_LA_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LA.png", "HVY_Attack1_LA_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LA.png", "HVY_Attack1_LA_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LA.png", "HVY_Attack1_LA_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LA.png", "HVY_Attack1_LA_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LA.png", "HVY_Attack1_LA_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LA.png", "HVY_Attack1_LA_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LA.png", "HVY_Attack1_LA_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LG.png", "HVY_Attack1_LG_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LG.png", "HVY_Attack1_LG_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LG.png", "HVY_Attack1_LG_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LG.png", "HVY_Attack1_LG_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LG.png", "HVY_Attack1_LG_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LG.png", "HVY_Attack1_LG_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LG.png", "HVY_Attack1_LG_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_LG.png", "HVY_Attack1_LG_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RA.png", "HVY_Attack1_RA_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RA.png", "HVY_Attack1_RA_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RA.png", "HVY_Attack1_RA_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RA.png", "HVY_Attack1_RA_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RA.png", "HVY_Attack1_RA_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RA.png", "HVY_Attack1_RA_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RA.png", "HVY_Attack1_RA_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RA.png", "HVY_Attack1_RA_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RH.png", "HVY_Attack1_RH_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RH.png", "HVY_Attack1_RH_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RH.png", "HVY_Attack1_RH_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RH.png", "HVY_Attack1_RH_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RH.png", "HVY_Attack1_RH_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RH.png", "HVY_Attack1_RH_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RH.png", "HVY_Attack1_RH_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_RH.png", "HVY_Attack1_RH_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S1.png", "HVY_Attack1_S1_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S1.png", "HVY_Attack1_S1_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S1.png", "HVY_Attack1_S1_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S1.png", "HVY_Attack1_S1_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S1.png", "HVY_Attack1_S1_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S1.png", "HVY_Attack1_S1_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S1.png", "HVY_Attack1_S1_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S1.png", "HVY_Attack1_S1_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S2.png", "HVY_Attack1_S2_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S2.png", "HVY_Attack1_S2_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S2.png", "HVY_Attack1_S2_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S2.png", "HVY_Attack1_S2_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S2.png", "HVY_Attack1_S2_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S2.png", "HVY_Attack1_S2_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S2.png", "HVY_Attack1_S2_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_S2.png", "HVY_Attack1_S2_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_TR.png", "HVY_Attack1_TR_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_TR.png", "HVY_Attack1_TR_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_TR.png", "HVY_Attack1_TR_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_TR.png", "HVY_Attack1_TR_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_TR.png", "HVY_Attack1_TR_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_TR.png", "HVY_Attack1_TR_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_TR.png", "HVY_Attack1_TR_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_TR.png", "HVY_Attack1_TR_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_SH.png", "HVY_Attack1_SH_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_SH.png", "HVY_Attack1_SH_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_SH.png", "HVY_Attack1_SH_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_SH.png", "HVY_Attack1_SH_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_SH.png", "HVY_Attack1_SH_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_SH.png", "HVY_Attack1_SH_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_SH.png", "HVY_Attack1_SH_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack1_SH.png", "HVY_Attack1_SH_R", 133, 151, 0.1f);
}

void MainPlayer::CreateA2Animation()
{
	// =========================== x : 19, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_HD.png", "LIT_Attack2_HD_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_HD.png", "LIT_Attack2_HD_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_HD.png", "LIT_Attack2_HD_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_HD.png", "LIT_Attack2_HD_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_HD.png", "LIT_Attack2_HD_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_HD.png", "LIT_Attack2_HD_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_HD.png", "LIT_Attack2_HD_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_HD.png", "LIT_Attack2_HD_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LA.png", "LIT_Attack2_LA_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LA.png", "LIT_Attack2_LA_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LA.png", "LIT_Attack2_LA_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LA.png", "LIT_Attack2_LA_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LA.png", "LIT_Attack2_LA_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LA.png", "LIT_Attack2_LA_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LA.png", "LIT_Attack2_LA_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LA.png", "LIT_Attack2_LA_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LG.png", "LIT_Attack2_LG_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LG.png", "LIT_Attack2_LG_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LG.png", "LIT_Attack2_LG_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LG.png", "LIT_Attack2_LG_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LG.png", "LIT_Attack2_LG_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LG.png", "LIT_Attack2_LG_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LG.png", "LIT_Attack2_LG_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_LG.png", "LIT_Attack2_LG_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RA.png", "LIT_Attack2_RA_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RA.png", "LIT_Attack2_RA_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RA.png", "LIT_Attack2_RA_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RA.png", "LIT_Attack2_RA_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RA.png", "LIT_Attack2_RA_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RA.png", "LIT_Attack2_RA_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RA.png", "LIT_Attack2_RA_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RA.png", "LIT_Attack2_RA_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RH.png", "LIT_Attack2_RH_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RH.png", "LIT_Attack2_RH_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RH.png", "LIT_Attack2_RH_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RH.png", "LIT_Attack2_RH_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RH.png", "LIT_Attack2_RH_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RH.png", "LIT_Attack2_RH_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RH.png", "LIT_Attack2_RH_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_RH.png", "LIT_Attack2_RH_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S1.png", "LIT_Attack2_S1_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S1.png", "LIT_Attack2_S1_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S1.png", "LIT_Attack2_S1_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S1.png", "LIT_Attack2_S1_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S1.png", "LIT_Attack2_S1_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S1.png", "LIT_Attack2_S1_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S1.png", "LIT_Attack2_S1_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S1.png", "LIT_Attack2_S1_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S2.png", "LIT_Attack2_S2_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S2.png", "LIT_Attack2_S2_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S2.png", "LIT_Attack2_S2_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S2.png", "LIT_Attack2_S2_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S2.png", "LIT_Attack2_S2_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S2.png", "LIT_Attack2_S2_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S2.png", "LIT_Attack2_S2_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_S2.png", "LIT_Attack2_S2_R", 133, 151, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_TR.png", "LIT_Attack2_TR_LB", 0, 18, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_TR.png", "LIT_Attack2_TR_LT", 19, 37, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_TR.png", "LIT_Attack2_TR_RT", 38, 56, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_TR.png", "LIT_Attack2_TR_RB", 57, 75, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_TR.png", "LIT_Attack2_TR_B", 76, 94, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_TR.png", "LIT_Attack2_TR_L", 95, 113, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_TR.png", "LIT_Attack2_TR_T", 114, 132, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Attack2_TR.png", "LIT_Attack2_TR_R", 133, 151, 0.1f);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_HD.png", "HVY_Attack2_HD_LB", 0, 18, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_HD.png", "HVY_Attack2_HD_LT", 19, 37, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_HD.png", "HVY_Attack2_HD_RT", 38, 56, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_HD.png", "HVY_Attack2_HD_RB", 57, 75, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_HD.png", "HVY_Attack2_HD_B", 76, 94, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_HD.png", "HVY_Attack2_HD_L", 95, 113, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_HD.png", "HVY_Attack2_HD_T", 114, 132, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_HD.png", "HVY_Attack2_HD_R", 133, 151, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LA.png", "HVY_Attack2_LA_LB", 0, 18, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LA.png", "HVY_Attack2_LA_LT", 19, 37, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LA.png", "HVY_Attack2_LA_RT", 38, 56, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LA.png", "HVY_Attack2_LA_RB", 57, 75, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LA.png", "HVY_Attack2_LA_B", 76, 94, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LA.png", "HVY_Attack2_LA_L", 95, 113, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LA.png", "HVY_Attack2_LA_T", 114, 132, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LA.png", "HVY_Attack2_LA_R", 133, 151, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LG.png", "HVY_Attack2_LG_LB", 0, 18, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LG.png", "HVY_Attack2_LG_LT", 19, 37, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LG.png", "HVY_Attack2_LG_RT", 38, 56, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LG.png", "HVY_Attack2_LG_RB", 57, 75, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LG.png", "HVY_Attack2_LG_B", 76, 94, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LG.png", "HVY_Attack2_LG_L", 95, 113, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LG.png", "HVY_Attack2_LG_T", 114, 132, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_LG.png", "HVY_Attack2_LG_R", 133, 151, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RA.png", "HVY_Attack2_RA_LB", 0, 18, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RA.png", "HVY_Attack2_RA_LT", 19, 37, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RA.png", "HVY_Attack2_RA_RT", 38, 56, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RA.png", "HVY_Attack2_RA_RB", 57, 75, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RA.png", "HVY_Attack2_RA_B", 76, 94, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RA.png", "HVY_Attack2_RA_L", 95, 113, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RA.png", "HVY_Attack2_RA_T", 114, 132, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RA.png", "HVY_Attack2_RA_R", 133, 151, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RH.png", "HVY_Attack2_RH_LB", 0, 18, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RH.png", "HVY_Attack2_RH_LT", 19, 37, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RH.png", "HVY_Attack2_RH_RT", 38, 56, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RH.png", "HVY_Attack2_RH_RB", 57, 75, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RH.png", "HVY_Attack2_RH_B", 76, 94, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RH.png", "HVY_Attack2_RH_L", 95, 113, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RH.png", "HVY_Attack2_RH_T", 114, 132, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_RH.png", "HVY_Attack2_RH_R", 133, 151, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S1.png", "HVY_Attack2_S1_LB", 0, 18, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S1.png", "HVY_Attack2_S1_LT", 19, 37, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S1.png", "HVY_Attack2_S1_RT", 38, 56, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S1.png", "HVY_Attack2_S1_RB", 57, 75, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S1.png", "HVY_Attack2_S1_B", 76, 94, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S1.png", "HVY_Attack2_S1_L", 95, 113, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S1.png", "HVY_Attack2_S1_T", 114, 132, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S1.png", "HVY_Attack2_S1_R", 133, 151, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S2.png", "HVY_Attack2_S2_LB", 0, 18, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S2.png", "HVY_Attack2_S2_LT", 19, 37, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S2.png", "HVY_Attack2_S2_RT", 38, 56, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S2.png", "HVY_Attack2_S2_RB", 57, 75, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S2.png", "HVY_Attack2_S2_B", 76, 94, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S2.png", "HVY_Attack2_S2_L", 95, 113, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S2.png", "HVY_Attack2_S2_T", 114, 132, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_S2.png", "HVY_Attack2_S2_R", 133, 151, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_TR.png", "HVY_Attack2_TR_LB", 0, 18, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_TR.png", "HVY_Attack2_TR_LT", 19, 37, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_TR.png", "HVY_Attack2_TR_RT", 38, 56, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_TR.png", "HVY_Attack2_TR_RB", 57, 75, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_TR.png", "HVY_Attack2_TR_B", 76, 94, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_TR.png", "HVY_Attack2_TR_L", 95, 113, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_TR.png", "HVY_Attack2_TR_T", 114, 132, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Attack2_TR.png", "HVY_Attack2_TR_R", 133, 151, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation(""HVY_Attack2_SH.png", HVY_Attack2_SH_LB", 0, 18, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation(""HVY_Attack2_SH.png", HVY_Attack2_SH_LT", 19, 37, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation(""HVY_Attack2_SH.png", HVY_Attack2_SH_RT", 38, 56, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation(""HVY_Attack2_SH.png", HVY_Attack2_SH_RB", 57, 75, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation(""HVY_Attack2_SH.png", HVY_Attack2_SH_B", 76, 94, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation(""HVY_Attack2_SH.png", HVY_Attack2_SH_L", 95, 113, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation(""HVY_Attack2_SH.png", HVY_Attack2_SH_T", 114, 132, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation(""HVY_Attack2_SH.png", HVY_Attack2_SH_R", 133, 151, 0.1f);
}

void MainPlayer::CreateBLAnimation()
{
	// =========================== x :  6, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_HD.png", "LIT_Block_HD_LB", 0, 5, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_HD.png", "LIT_Block_HD_LT", 6, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_HD.png", "LIT_Block_HD_RT", 12, 17, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_HD.png", "LIT_Block_HD_RB", 18, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_HD.png", "LIT_Block_HD_B", 24, 29, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_HD.png", "LIT_Block_HD_L", 30, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_HD.png", "LIT_Block_HD_T", 36, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_HD.png", "LIT_Block_HD_R", 42, 47, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LA.png", "LIT_Block_LA_LB", 0, 5, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LA.png", "LIT_Block_LA_LT", 6, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LA.png", "LIT_Block_LA_RT", 12, 17, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LA.png", "LIT_Block_LA_RB", 18, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LA.png", "LIT_Block_LA_B", 24, 29, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LA.png", "LIT_Block_LA_L", 30, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LA.png", "LIT_Block_LA_T", 36, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LA.png", "LIT_Block_LA_R", 42, 47, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LG.png", "LIT_Block_LG_LB", 0, 5, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LG.png", "LIT_Block_LG_LT", 6, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LG.png", "LIT_Block_LG_RT", 12, 17, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LG.png", "LIT_Block_LG_RB", 18, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LG.png", "LIT_Block_LG_B", 24, 29, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LG.png", "LIT_Block_LG_L", 30, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LG.png", "LIT_Block_LG_T", 36, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_LG.png", "LIT_Block_LG_R", 42, 47, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RA.png", "LIT_Block_RA_LB", 0, 5, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RA.png", "LIT_Block_RA_LT", 6, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RA.png", "LIT_Block_RA_RT", 12, 17, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RA.png", "LIT_Block_RA_RB", 18, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RA.png", "LIT_Block_RA_B", 24, 29, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RA.png", "LIT_Block_RA_L", 30, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RA.png", "LIT_Block_RA_T", 36, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RA.png", "LIT_Block_RA_R", 42, 47, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RH.png", "LIT_Block_RH_LB", 0, 5, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RH.png", "LIT_Block_RH_LT", 6, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RH.png", "LIT_Block_RH_RT", 12, 17, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RH.png", "LIT_Block_RH_RB", 18, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RH.png", "LIT_Block_RH_B", 24, 29, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RH.png", "LIT_Block_RH_L", 30, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RH.png", "LIT_Block_RH_T", 36, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_RH.png", "LIT_Block_RH_R", 42, 47, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S1.png", "LIT_Block_S1_LB", 0, 5, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S1.png", "LIT_Block_S1_LT", 6, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S1.png", "LIT_Block_S1_RT", 12, 17, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S1.png", "LIT_Block_S1_RB", 18, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S1.png", "LIT_Block_S1_B", 24, 29, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S1.png", "LIT_Block_S1_L", 30, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S1.png", "LIT_Block_S1_T", 36, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S1.png", "LIT_Block_S1_R", 42, 47, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S2.png", "LIT_Block_S2_LB", 0, 5, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S2.png", "LIT_Block_S2_LT", 6, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S2.png", "LIT_Block_S2_RT", 12, 17, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S2.png", "LIT_Block_S2_RB", 18, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S2.png", "LIT_Block_S2_B", 24, 29, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S2.png", "LIT_Block_S2_L", 30, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S2.png", "LIT_Block_S2_T", 36, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_S2.png", "LIT_Block_S2_R", 42, 47, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_TR.png", "LIT_Block_TR_LB", 0, 5, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_TR.png", "LIT_Block_TR_LT", 6, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_TR.png", "LIT_Block_TR_RT", 12, 17, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_TR.png", "LIT_Block_TR_RB", 18, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_TR.png", "LIT_Block_TR_B", 24, 29, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_TR.png", "LIT_Block_TR_L", 30, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_TR.png", "LIT_Block_TR_T", 36, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Block_TR.png", "LIT_Block_TR_R", 42, 47, 0.1f);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_HD.png", "HVY_Block_HD_LB", 0, 5, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_HD.png", "HVY_Block_HD_LT", 6, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_HD.png", "HVY_Block_HD_RT", 12, 17, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_HD.png", "HVY_Block_HD_RB", 18, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_HD.png", "HVY_Block_HD_B", 24, 29, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_HD.png", "HVY_Block_HD_L", 30, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_HD.png", "HVY_Block_HD_T", 36, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_HD.png", "HVY_Block_HD_R", 42, 47, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LA.png", "HVY_Block_LA_LB", 0, 5, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LA.png", "HVY_Block_LA_LT", 6, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LA.png", "HVY_Block_LA_RT", 12, 17, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LA.png", "HVY_Block_LA_RB", 18, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LA.png", "HVY_Block_LA_B", 24, 29, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LA.png", "HVY_Block_LA_L", 30, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LA.png", "HVY_Block_LA_T", 36, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LA.png", "HVY_Block_LA_R", 42, 47, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LG.png", "HVY_Block_LG_LB", 0, 5, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LG.png", "HVY_Block_LG_LT", 6, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LG.png", "HVY_Block_LG_RT", 12, 17, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LG.png", "HVY_Block_LG_RB", 18, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LG.png", "HVY_Block_LG_B", 24, 29, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LG.png", "HVY_Block_LG_L", 30, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LG.png", "HVY_Block_LG_T", 36, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_LG.png", "HVY_Block_LG_R", 42, 47, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RA.png", "HVY_Block_RA_LB", 0, 5, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RA.png", "HVY_Block_RA_LT", 6, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RA.png", "HVY_Block_RA_RT", 12, 17, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RA.png", "HVY_Block_RA_RB", 18, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RA.png", "HVY_Block_RA_B", 24, 29, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RA.png", "HVY_Block_RA_L", 30, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RA.png", "HVY_Block_RA_T", 36, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RA.png", "HVY_Block_RA_R", 42, 47, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RH.png", "HVY_Block_RH_LB", 0, 5, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RH.png", "HVY_Block_RH_LT", 6, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RH.png", "HVY_Block_RH_RT", 12, 17, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RH.png", "HVY_Block_RH_RB", 18, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RH.png", "HVY_Block_RH_B", 24, 29, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RH.png", "HVY_Block_RH_L", 30, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RH.png", "HVY_Block_RH_T", 36, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_RH.png", "HVY_Block_RH_R", 42, 47, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S1.png", "HVY_Block_S1_LB", 0, 5, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S1.png", "HVY_Block_S1_LT", 6, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S1.png", "HVY_Block_S1_RT", 12, 17, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S1.png", "HVY_Block_S1_RB", 18, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S1.png", "HVY_Block_S1_B", 24, 29, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S1.png", "HVY_Block_S1_L", 30, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S1.png", "HVY_Block_S1_T", 36, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S1.png", "HVY_Block_S1_R", 42, 47, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S2.png", "HVY_Block_S2_LB", 0, 5, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S2.png", "HVY_Block_S2_LT", 6, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S2.png", "HVY_Block_S2_RT", 12, 17, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S2.png", "HVY_Block_S2_RB", 18, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S2.png", "HVY_Block_S2_B", 24, 29, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S2.png", "HVY_Block_S2_L", 30, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S2.png", "HVY_Block_S2_T", 36, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_S2.png", "HVY_Block_S2_R", 42, 47, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_TR.png", "HVY_Block_TR_LB", 0, 5, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_TR.png", "HVY_Block_TR_LT", 6, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_TR.png", "HVY_Block_TR_RT", 12, 17, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_TR.png", "HVY_Block_TR_RB", 18, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_TR.png", "HVY_Block_TR_B", 24, 29, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_TR.png", "HVY_Block_TR_L", 30, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_TR.png", "HVY_Block_TR_T", 36, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_TR.png", "HVY_Block_TR_R", 42, 47, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_SH.png", "HVY_Block_SH_LB", 0, 5, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_SH.png", "HVY_Block_SH_LT", 6, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_SH.png", "HVY_Block_SH_RT", 12, 17, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_SH.png", "HVY_Block_SH_RB", 18, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_SH.png", "HVY_Block_SH_B", 24, 29, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_SH.png", "HVY_Block_SH_L", 30, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_SH.png", "HVY_Block_SH_T", 36, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Block_SH.png", "HVY_Block_SH_R", 42, 47, 0.1f);
}

void MainPlayer::CreateDDAnimation()
{
	// =========================== x :  1, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Dead_TR.png", "LIT_Dead_TR_LB", 0, 0, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Dead_TR.png", "LIT_Dead_TR_LT", 1, 1, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Dead_TR.png", "LIT_Dead_TR_RT", 2, 2, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Dead_TR.png", "LIT_Dead_TR_RB", 3, 3, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Dead_TR.png", "LIT_Dead_TR_B", 4, 4, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Dead_TR.png", "LIT_Dead_TR_L", 5, 5, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Dead_TR.png", "LIT_Dead_TR_T", 6, 6, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Dead_TR.png", "LIT_Dead_TR_R", 7, 7, 0.1f, false);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Dead_TR.png", "HVY_Dead_TR_LB", 0, 0, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Dead_TR.png", "HVY_Dead_TR_LT", 1, 1, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Dead_TR.png", "HVY_Dead_TR_RT", 2, 2, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Dead_TR.png", "HVY_Dead_TR_RB", 3, 3, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Dead_TR.png", "HVY_Dead_TR_B", 4, 4, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Dead_TR.png", "HVY_Dead_TR_L", 5, 5, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Dead_TR.png", "HVY_Dead_TR_T", 6, 6, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Dead_TR.png", "HVY_Dead_TR_R", 7, 7, 0.1f);
}

void MainPlayer::CreateDTAnimation()
{
	// =========================== x : 27, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Death_TR.png", "LIT_Death_TR_LB", 0, 26, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Death_TR.png", "LIT_Death_TR_LT", 27, 53, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Death_TR.png", "LIT_Death_TR_RT", 54, 80, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Death_TR.png", "LIT_Death_TR_RB", 81, 107, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Death_TR.png", "LIT_Death_TR_B", 108, 134, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Death_TR.png", "LIT_Death_TR_L", 135, 161, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Death_TR.png", "LIT_Death_TR_T", 162, 188, 0.1f, false);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Death_TR.png", "LIT_Death_TR_R", 189, 215, 0.1f, false);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Death_TR.png", "HVY_Death_TR_LB", 0, 26, 0.1f, false);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Death_TR.png", "HVY_Death_TR_LT", 27, 53, 0.1f, false);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Death_TR.png", "HVY_Death_TR_RT", 54, 80, 0.1f, false);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Death_TR.png", "HVY_Death_TR_RB", 81, 107, 0.1f, false);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Death_TR.png", "HVY_Death_TR_B", 108, 134, 0.1f, false);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Death_TR.png", "HVY_Death_TR_L", 135, 161, 0.1f, false);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Death_TR.png", "HVY_Death_TR_T", 162, 188, 0.1f, false);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Death_TR.png", "HVY_Death_TR_R", 189, 215, 0.1f, false);
}

void MainPlayer::CreateGHAnimation()
{
	// =========================== x :  7, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_HD.png", "LIT_Gethit_HD_LB", 0, 6, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_HD.png", "LIT_Gethit_HD_LT", 7, 13, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_HD.png", "LIT_Gethit_HD_RT", 14, 20, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_HD.png", "LIT_Gethit_HD_RB", 21, 27, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_HD.png", "LIT_Gethit_HD_B", 28, 34, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_HD.png", "LIT_Gethit_HD_L", 35, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_HD.png", "LIT_Gethit_HD_T", 42, 48, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_HD.png", "LIT_Gethit_HD_R", 49, 55, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LA.png", "LIT_Gethit_LA_LB", 0, 6, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LA.png", "LIT_Gethit_LA_LT", 7, 13, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LA.png", "LIT_Gethit_LA_RT", 14, 20, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LA.png", "LIT_Gethit_LA_RB", 21, 27, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LA.png", "LIT_Gethit_LA_B", 28, 34, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LA.png", "LIT_Gethit_LA_L", 35, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LA.png", "LIT_Gethit_LA_T", 42, 48, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LA.png", "LIT_Gethit_LA_R", 49, 55, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LG.png", "LIT_Gethit_LG_LB", 0, 6, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LG.png", "LIT_Gethit_LG_LT", 7, 13, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LG.png", "LIT_Gethit_LG_RT", 14, 20, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LG.png", "LIT_Gethit_LG_RB", 21, 27, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LG.png", "LIT_Gethit_LG_B", 28, 34, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LG.png", "LIT_Gethit_LG_L", 35, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LG.png", "LIT_Gethit_LG_T", 42, 48, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_LG.png", "LIT_Gethit_LG_R", 49, 55, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RA.png", "LIT_Gethit_RA_LB", 0, 6, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RA.png", "LIT_Gethit_RA_LT", 7, 13, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RA.png", "LIT_Gethit_RA_RT", 14, 20, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RA.png", "LIT_Gethit_RA_RB", 21, 27, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RA.png", "LIT_Gethit_RA_B", 28, 34, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RA.png", "LIT_Gethit_RA_L", 35, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RA.png", "LIT_Gethit_RA_T", 42, 48, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RA.png", "LIT_Gethit_RA_R", 49, 55, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RH.png", "LIT_Gethit_RH_LB", 0, 6, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RH.png", "LIT_Gethit_RH_LT", 7, 13, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RH.png", "LIT_Gethit_RH_RT", 14, 20, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RH.png", "LIT_Gethit_RH_RB", 21, 27, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RH.png", "LIT_Gethit_RH_B", 28, 34, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RH.png", "LIT_Gethit_RH_L", 35, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RH.png", "LIT_Gethit_RH_T", 42, 48, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_RH.png", "LIT_Gethit_RH_R", 49, 55, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S1.png", "LIT_Gethit_S1_LB", 0, 6, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S1.png", "LIT_Gethit_S1_LT", 7, 13, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S1.png", "LIT_Gethit_S1_RT", 14, 20, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S1.png", "LIT_Gethit_S1_RB", 21, 27, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S1.png", "LIT_Gethit_S1_B", 28, 34, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S1.png", "LIT_Gethit_S1_L", 35, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S1.png", "LIT_Gethit_S1_T", 42, 48, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S1.png", "LIT_Gethit_S1_R", 49, 55, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S2.png", "LIT_Gethit_S2_LB", 0, 6, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S2.png", "LIT_Gethit_S2_LT", 7, 13, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S2.png", "LIT_Gethit_S2_RT", 14, 20, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S2.png", "LIT_Gethit_S2_RB", 21, 27, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S2.png", "LIT_Gethit_S2_B", 28, 34, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S2.png", "LIT_Gethit_S2_L", 35, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S2.png", "LIT_Gethit_S2_T", 42, 48, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_S2.png", "LIT_Gethit_S2_R", 49, 55, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_TR.png", "LIT_Gethit_TR_LB", 0, 6, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_TR.png", "LIT_Gethit_TR_LT", 7, 13, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_TR.png", "LIT_Gethit_TR_RT", 14, 20, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_TR.png", "LIT_Gethit_TR_RB", 21, 27, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_TR.png", "LIT_Gethit_TR_B", 28, 34, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_TR.png", "LIT_Gethit_TR_L", 35, 41, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_TR.png", "LIT_Gethit_TR_T", 42, 48, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Gethit_TR.png", "LIT_Gethit_TR_R", 49, 55, 0.1f);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_HD.png", "HVY_Gethit_HD_LB", 0, 6, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_HD.png", "HVY_Gethit_HD_LT", 7, 13, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_HD.png", "HVY_Gethit_HD_RT", 14, 20, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_HD.png", "HVY_Gethit_HD_RB", 21, 27, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_HD.png", "HVY_Gethit_HD_B", 28, 34, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_HD.png", "HVY_Gethit_HD_L", 35, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_HD.png", "HVY_Gethit_HD_T", 42, 48, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_HD.png", "HVY_Gethit_HD_R", 49, 55, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LA.png", "HVY_Gethit_LA_LB", 0, 6, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LA.png", "HVY_Gethit_LA_LT", 7, 13, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LA.png", "HVY_Gethit_LA_RT", 14, 20, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LA.png", "HVY_Gethit_LA_RB", 21, 27, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LA.png", "HVY_Gethit_LA_B", 28, 34, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LA.png", "HVY_Gethit_LA_L", 35, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LA.png", "HVY_Gethit_LA_T", 42, 48, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LA.png", "HVY_Gethit_LA_R", 49, 55, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LG.png", "HVY_Gethit_LG_LB", 0, 6, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LG.png", "HVY_Gethit_LG_LT", 7, 13, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LG.png", "HVY_Gethit_LG_RT", 14, 20, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LG.png", "HVY_Gethit_LG_RB", 21, 27, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LG.png", "HVY_Gethit_LG_B", 28, 34, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LG.png", "HVY_Gethit_LG_L", 35, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LG.png", "HVY_Gethit_LG_T", 42, 48, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_LG.png", "HVY_Gethit_LG_R", 49, 55, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RA.png", "HVY_Gethit_RA_LB", 0, 6, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RA.png", "HVY_Gethit_RA_LT", 7, 13, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RA.png", "HVY_Gethit_RA_RT", 14, 20, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RA.png", "HVY_Gethit_RA_RB", 21, 27, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RA.png", "HVY_Gethit_RA_B", 28, 34, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RA.png", "HVY_Gethit_RA_L", 35, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RA.png", "HVY_Gethit_RA_T", 42, 48, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RA.png", "HVY_Gethit_RA_R", 49, 55, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RH.png", "HVY_Gethit_RH_LB", 0, 6, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RH.png", "HVY_Gethit_RH_LT", 7, 13, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RH.png", "HVY_Gethit_RH_RT", 14, 20, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RH.png", "HVY_Gethit_RH_RB", 21, 27, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RH.png", "HVY_Gethit_RH_B", 28, 34, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RH.png", "HVY_Gethit_RH_L", 35, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RH.png", "HVY_Gethit_RH_T", 42, 48, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_RH.png", "HVY_Gethit_RH_R", 49, 55, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S1.png", "HVY_Gethit_S1_LB", 0, 6, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S1.png", "HVY_Gethit_S1_LT", 7, 13, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S1.png", "HVY_Gethit_S1_RT", 14, 20, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S1.png", "HVY_Gethit_S1_RB", 21, 27, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S1.png", "HVY_Gethit_S1_B", 28, 34, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S1.png", "HVY_Gethit_S1_L", 35, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S1.png", "HVY_Gethit_S1_T", 42, 48, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S1.png", "HVY_Gethit_S1_R", 49, 55, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S2.png", "HVY_Gethit_S2_LB", 0, 6, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S2.png", "HVY_Gethit_S2_LT", 7, 13, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S2.png", "HVY_Gethit_S2_RT", 14, 20, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S2.png", "HVY_Gethit_S2_RB", 21, 27, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S2.png", "HVY_Gethit_S2_B", 28, 34, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S2.png", "HVY_Gethit_S2_L", 35, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S2.png", "HVY_Gethit_S2_T", 42, 48, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_S2.png", "HVY_Gethit_S2_R", 49, 55, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_TR.png", "HVY_Gethit_TR_LB", 0, 6, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_TR.png", "HVY_Gethit_TR_LT", 7, 13, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_TR.png", "HVY_Gethit_TR_RT", 14, 20, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_TR.png", "HVY_Gethit_TR_RB", 21, 27, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_TR.png", "HVY_Gethit_TR_B", 28, 34, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_TR.png", "HVY_Gethit_TR_L", 35, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_TR.png", "HVY_Gethit_TR_T", 42, 48, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_TR.png", "HVY_Gethit_TR_R", 49, 55, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_SH.png", "HVY_Gethit_SH_LB", 0, 6, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_SH.png", "HVY_Gethit_SH_LT", 7, 13, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_SH.png", "HVY_Gethit_SH_RT", 14, 20, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_SH.png", "HVY_Gethit_SH_RB", 21, 27, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_SH.png", "HVY_Gethit_SH_B", 28, 34, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_SH.png", "HVY_Gethit_SH_L", 35, 41, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_SH.png", "HVY_Gethit_SH_T", 42, 48, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Gethit_SH.png", "HVY_Gethit_SH_R", 49, 55, 0.1f);
}

void MainPlayer::CreateKKAnimation()
{
	// =========================== x : 12, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_HD.png", "LIT_Kick_HD_LB", 0, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_HD.png", "LIT_Kick_HD_LT", 12, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_HD.png", "LIT_Kick_HD_RT", 24, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_HD.png", "LIT_Kick_HD_RB", 36, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_HD.png", "LIT_Kick_HD_B", 48, 59, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_HD.png", "LIT_Kick_HD_L", 60, 71, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_HD.png", "LIT_Kick_HD_T", 72, 83, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_HD.png", "LIT_Kick_HD_R", 84, 95, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LA.png", "LIT_Kick_LA_LB", 0, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LA.png", "LIT_Kick_LA_LT", 12, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LA.png", "LIT_Kick_LA_RT", 24, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LA.png", "LIT_Kick_LA_RB", 36, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LA.png", "LIT_Kick_LA_B", 48, 59, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LA.png", "LIT_Kick_LA_L", 60, 71, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LA.png", "LIT_Kick_LA_T", 72, 83, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LA.png", "LIT_Kick_LA_R", 84, 95, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LG.png", "LIT_Kick_LG_LB", 0, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LG.png", "LIT_Kick_LG_LT", 12, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LG.png", "LIT_Kick_LG_RT", 24, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LG.png", "LIT_Kick_LG_RB", 36, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LG.png", "LIT_Kick_LG_B", 48, 59, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LG.png", "LIT_Kick_LG_L", 60, 71, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LG.png", "LIT_Kick_LG_T", 72, 83, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_LG.png", "LIT_Kick_LG_R", 84, 95, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RA.png", "LIT_Kick_RA_LB", 0, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RA.png", "LIT_Kick_RA_LT", 12, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RA.png", "LIT_Kick_RA_RT", 24, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RA.png", "LIT_Kick_RA_RB", 36, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RA.png", "LIT_Kick_RA_B", 48, 59, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RA.png", "LIT_Kick_RA_L", 60, 71, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RA.png", "LIT_Kick_RA_T", 72, 83, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RA.png", "LIT_Kick_RA_R", 84, 95, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RH.png", "LIT_Kick_RH_LB", 0, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RH.png", "LIT_Kick_RH_LT", 12, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RH.png", "LIT_Kick_RH_RT", 24, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RH.png", "LIT_Kick_RH_RB", 36, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RH.png", "LIT_Kick_RH_B", 48, 59, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RH.png", "LIT_Kick_RH_L", 60, 71, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RH.png", "LIT_Kick_RH_T", 72, 83, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_RH.png", "LIT_Kick_RH_R", 84, 95, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S1.png", "LIT_Kick_S1_LB", 0, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S1.png", "LIT_Kick_S1_LT", 12, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S1.png", "LIT_Kick_S1_RT", 24, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S1.png", "LIT_Kick_S1_RB", 36, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S1.png", "LIT_Kick_S1_B", 48, 59, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S1.png", "LIT_Kick_S1_L", 60, 71, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S1.png", "LIT_Kick_S1_T", 72, 83, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S1.png", "LIT_Kick_S1_R", 84, 95, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S2.png", "LIT_Kick_S2_LB", 0, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S2.png", "LIT_Kick_S2_LT", 12, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S2.png", "LIT_Kick_S2_RT", 24, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S2.png", "LIT_Kick_S2_RB", 36, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S2.png", "LIT_Kick_S2_B", 48, 59, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S2.png", "LIT_Kick_S2_L", 60, 71, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S2.png", "LIT_Kick_S2_T", 72, 83, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_S2.png", "LIT_Kick_S2_R", 84, 95, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_TR.png", "LIT_Kick_TR_LB", 0, 11, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_TR.png", "LIT_Kick_TR_LT", 12, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_TR.png", "LIT_Kick_TR_RT", 24, 35, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_TR.png", "LIT_Kick_TR_RB", 36, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_TR.png", "LIT_Kick_TR_B", 48, 59, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_TR.png", "LIT_Kick_TR_L", 60, 71, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_TR.png", "LIT_Kick_TR_T", 72, 83, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Kick_TR.png", "LIT_Kick_TR_R", 84, 95, 0.1f);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_HD.png", "HVY_Kick_HD_LB", 0, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_HD.png", "HVY_Kick_HD_LT", 12, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_HD.png", "HVY_Kick_HD_RT", 24, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_HD.png", "HVY_Kick_HD_RB", 36, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_HD.png", "HVY_Kick_HD_B", 48, 59, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_HD.png", "HVY_Kick_HD_L", 60, 71, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_HD.png", "HVY_Kick_HD_T", 72, 83, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_HD.png", "HVY_Kick_HD_R", 84, 95, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LA.png", "HVY_Kick_LA_LB", 0, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LA.png", "HVY_Kick_LA_LT", 12, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LA.png", "HVY_Kick_LA_RT", 24, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LA.png", "HVY_Kick_LA_RB", 36, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LA.png", "HVY_Kick_LA_B", 48, 59, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LA.png", "HVY_Kick_LA_L", 60, 71, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LA.png", "HVY_Kick_LA_T", 72, 83, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LA.png", "HVY_Kick_LA_R", 84, 95, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LG.png", "HVY_Kick_LG_LB", 0, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LG.png", "HVY_Kick_LG_LT", 12, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LG.png", "HVY_Kick_LG_RT", 24, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LG.png", "HVY_Kick_LG_RB", 36, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LG.png", "HVY_Kick_LG_B", 48, 59, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LG.png", "HVY_Kick_LG_L", 60, 71, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LG.png", "HVY_Kick_LG_T", 72, 83, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_LG.png", "HVY_Kick_LG_R", 84, 95, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RA.png", "HVY_Kick_RA_LB", 0, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RA.png", "HVY_Kick_RA_LT", 12, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RA.png", "HVY_Kick_RA_RT", 24, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RA.png", "HVY_Kick_RA_RB", 36, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RA.png", "HVY_Kick_RA_B", 48, 59, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RA.png", "HVY_Kick_RA_L", 60, 71, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RA.png", "HVY_Kick_RA_T", 72, 83, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RA.png", "HVY_Kick_RA_R", 84, 95, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RH.png", "HVY_Kick_RH_LB", 0, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RH.png", "HVY_Kick_RH_LT", 12, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RH.png", "HVY_Kick_RH_RT", 24, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RH.png", "HVY_Kick_RH_RB", 36, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RH.png", "HVY_Kick_RH_B", 48, 59, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RH.png", "HVY_Kick_RH_L", 60, 71, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RH.png", "HVY_Kick_RH_T", 72, 83, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_RH.png", "HVY_Kick_RH_R", 84, 95, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S1.png", "HVY_Kick_S1_LB", 0, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S1.png", "HVY_Kick_S1_LT", 12, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S1.png", "HVY_Kick_S1_RT", 24, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S1.png", "HVY_Kick_S1_RB", 36, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S1.png", "HVY_Kick_S1_B", 48, 59, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S1.png", "HVY_Kick_S1_L", 60, 71, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S1.png", "HVY_Kick_S1_T", 72, 83, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S1.png", "HVY_Kick_S1_R", 84, 95, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S2.png", "HVY_Kick_S2_LB", 0, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S2.png", "HVY_Kick_S2_LT", 12, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S2.png", "HVY_Kick_S2_RT", 24, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S2.png", "HVY_Kick_S2_RB", 36, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S2.png", "HVY_Kick_S2_B", 48, 59, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S2.png", "HVY_Kick_S2_L", 60, 71, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S2.png", "HVY_Kick_S2_T", 72, 83, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_S2.png", "HVY_Kick_S2_R", 84, 95, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_TR.png", "HVY_Kick_TR_LB", 0, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_TR.png", "HVY_Kick_TR_LT", 12, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_TR.png", "HVY_Kick_TR_RT", 24, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_TR.png", "HVY_Kick_TR_RB", 36, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_TR.png", "HVY_Kick_TR_B", 48, 59, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_TR.png", "HVY_Kick_TR_L", 60, 71, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_TR.png", "HVY_Kick_TR_T", 72, 83, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_TR.png", "HVY_Kick_TR_R", 84, 95, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_SH.png", "HVY_Kick_SH_LB", 0, 11, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_SH.png", "HVY_Kick_SH_LT", 12, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_SH.png", "HVY_Kick_SH_RT", 24, 35, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_SH.png", "HVY_Kick_SH_RB", 36, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_SH.png", "HVY_Kick_SH_B", 48, 59, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_SH.png", "HVY_Kick_SH_L", 60, 71, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_SH.png", "HVY_Kick_SH_T", 72, 83, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Kick_SH.png", "HVY_Kick_SH_R", 84, 95, 0.1f);
}

void MainPlayer::CreateNUAnimation()
{
	// =========================== x :  8, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_HD.png", "LIT_Natural_Field_HD_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_HD.png", "LIT_Natural_Field_HD_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_HD.png", "LIT_Natural_Field_HD_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_HD.png", "LIT_Natural_Field_HD_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_HD.png", "LIT_Natural_Field_HD_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_HD.png", "LIT_Natural_Field_HD_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_HD.png", "LIT_Natural_Field_HD_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_HD.png", "LIT_Natural_Field_HD_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LA.png", "LIT_Natural_Field_LA_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LA.png", "LIT_Natural_Field_LA_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LA.png", "LIT_Natural_Field_LA_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LA.png", "LIT_Natural_Field_LA_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LA.png", "LIT_Natural_Field_LA_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LA.png", "LIT_Natural_Field_LA_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LA.png", "LIT_Natural_Field_LA_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LA.png", "LIT_Natural_Field_LA_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LG.png", "LIT_Natural_Field_LG_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LG.png", "LIT_Natural_Field_LG_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LG.png", "LIT_Natural_Field_LG_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LG.png", "LIT_Natural_Field_LG_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LG.png", "LIT_Natural_Field_LG_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LG.png", "LIT_Natural_Field_LG_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LG.png", "LIT_Natural_Field_LG_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_LG.png", "LIT_Natural_Field_LG_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RA.png", "LIT_Natural_Field_RA_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RA.png", "LIT_Natural_Field_RA_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RA.png", "LIT_Natural_Field_RA_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RA.png", "LIT_Natural_Field_RA_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RA.png", "LIT_Natural_Field_RA_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RA.png", "LIT_Natural_Field_RA_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RA.png", "LIT_Natural_Field_RA_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RA.png", "LIT_Natural_Field_RA_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RH.png", "LIT_Natural_Field_RH_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RH.png", "LIT_Natural_Field_RH_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RH.png", "LIT_Natural_Field_RH_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RH.png", "LIT_Natural_Field_RH_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RH.png", "LIT_Natural_Field_RH_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RH.png", "LIT_Natural_Field_RH_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RH.png", "LIT_Natural_Field_RH_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_RH.png", "LIT_Natural_Field_RH_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S1.png", "LIT_Natural_Field_S1_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S1.png", "LIT_Natural_Field_S1_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S1.png", "LIT_Natural_Field_S1_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S1.png", "LIT_Natural_Field_S1_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S1.png", "LIT_Natural_Field_S1_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S1.png", "LIT_Natural_Field_S1_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S1.png", "LIT_Natural_Field_S1_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S1.png", "LIT_Natural_Field_S1_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S2.png", "LIT_Natural_Field_S2_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S2.png", "LIT_Natural_Field_S2_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S2.png", "LIT_Natural_Field_S2_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S2.png", "LIT_Natural_Field_S2_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S2.png", "LIT_Natural_Field_S2_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S2.png", "LIT_Natural_Field_S2_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S2.png", "LIT_Natural_Field_S2_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_S2.png", "LIT_Natural_Field_S2_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_TR.png", "LIT_Natural_Field_TR_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_TR.png", "LIT_Natural_Field_TR_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_TR.png", "LIT_Natural_Field_TR_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_TR.png", "LIT_Natural_Field_TR_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_TR.png", "LIT_Natural_Field_TR_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_TR.png", "LIT_Natural_Field_TR_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_TR.png", "LIT_Natural_Field_TR_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Field_TR.png", "LIT_Natural_Field_TR_R", 56, 63, 0.1f);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_HD.png", "HVY_Natural_Field_HD_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_HD.png", "HVY_Natural_Field_HD_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_HD.png", "HVY_Natural_Field_HD_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_HD.png", "HVY_Natural_Field_HD_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_HD.png", "HVY_Natural_Field_HD_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_HD.png", "HVY_Natural_Field_HD_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_HD.png", "HVY_Natural_Field_HD_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_HD.png", "HVY_Natural_Field_HD_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LA.png", "HVY_Natural_Field_LA_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LA.png", "HVY_Natural_Field_LA_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LA.png", "HVY_Natural_Field_LA_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LA.png", "HVY_Natural_Field_LA_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LA.png", "HVY_Natural_Field_LA_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LA.png", "HVY_Natural_Field_LA_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LA.png", "HVY_Natural_Field_LA_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LA.png", "HVY_Natural_Field_LA_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LG.png", "HVY_Natural_Field_LG_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LG.png", "HVY_Natural_Field_LG_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LG.png", "HVY_Natural_Field_LG_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LG.png", "HVY_Natural_Field_LG_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LG.png", "HVY_Natural_Field_LG_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LG.png", "HVY_Natural_Field_LG_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LG.png", "HVY_Natural_Field_LG_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_LG.png", "HVY_Natural_Field_LG_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RA.png", "HVY_Natural_Field_RA_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RA.png", "HVY_Natural_Field_RA_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RA.png", "HVY_Natural_Field_RA_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RA.png", "HVY_Natural_Field_RA_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RA.png", "HVY_Natural_Field_RA_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RA.png", "HVY_Natural_Field_RA_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RA.png", "HVY_Natural_Field_RA_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RA.png", "HVY_Natural_Field_RA_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RH.png", "HVY_Natural_Field_RH_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RH.png", "HVY_Natural_Field_RH_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RH.png", "HVY_Natural_Field_RH_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RH.png", "HVY_Natural_Field_RH_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RH.png", "HVY_Natural_Field_RH_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RH.png", "HVY_Natural_Field_RH_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RH.png", "HVY_Natural_Field_RH_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_RH.png", "HVY_Natural_Field_RH_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S1.png", "HVY_Natural_Field_S1_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S1.png", "HVY_Natural_Field_S1_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S1.png", "HVY_Natural_Field_S1_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S1.png", "HVY_Natural_Field_S1_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S1.png", "HVY_Natural_Field_S1_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S1.png", "HVY_Natural_Field_S1_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S1.png", "HVY_Natural_Field_S1_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S1.png", "HVY_Natural_Field_S1_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S2.png", "HVY_Natural_Field_S2_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S2.png", "HVY_Natural_Field_S2_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S2.png", "HVY_Natural_Field_S2_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S2.png", "HVY_Natural_Field_S2_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S2.png", "HVY_Natural_Field_S2_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S2.png", "HVY_Natural_Field_S2_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S2.png", "HVY_Natural_Field_S2_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_S2.png", "HVY_Natural_Field_S2_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_TR.png", "HVY_Natural_Field_TR_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_TR.png", "HVY_Natural_Field_TR_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_TR.png", "HVY_Natural_Field_TR_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_TR.png", "HVY_Natural_Field_TR_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_TR.png", "HVY_Natural_Field_TR_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_TR.png", "HVY_Natural_Field_TR_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_TR.png", "HVY_Natural_Field_TR_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_TR.png", "HVY_Natural_Field_TR_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_SH.png", "HVY_Natural_Field_SH_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_SH.png", "HVY_Natural_Field_SH_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_SH.png", "HVY_Natural_Field_SH_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_SH.png", "HVY_Natural_Field_SH_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_SH.png", "HVY_Natural_Field_SH_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_SH.png", "HVY_Natural_Field_SH_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_SH.png", "HVY_Natural_Field_SH_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Field_SH.png", "HVY_Natural_Field_SH_R", 56, 63, 0.1f);
}

void MainPlayer::CreateRNAnimation()
{
	// =========================== x :  8, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_HD.png", "LIT_Run_HD_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_HD.png", "LIT_Run_HD_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_HD.png", "LIT_Run_HD_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_HD.png", "LIT_Run_HD_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_HD.png", "LIT_Run_HD_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_HD.png", "LIT_Run_HD_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_HD.png", "LIT_Run_HD_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_HD.png", "LIT_Run_HD_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LA.png", "LIT_Run_LA_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LA.png", "LIT_Run_LA_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LA.png", "LIT_Run_LA_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LA.png", "LIT_Run_LA_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LA.png", "LIT_Run_LA_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LA.png", "LIT_Run_LA_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LA.png", "LIT_Run_LA_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LA.png", "LIT_Run_LA_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LG.png", "LIT_Run_LG_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LG.png", "LIT_Run_LG_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LG.png", "LIT_Run_LG_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LG.png", "LIT_Run_LG_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LG.png", "LIT_Run_LG_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LG.png", "LIT_Run_LG_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LG.png", "LIT_Run_LG_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_LG.png", "LIT_Run_LG_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RA.png", "LIT_Run_RA_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RA.png", "LIT_Run_RA_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RA.png", "LIT_Run_RA_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RA.png", "LIT_Run_RA_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RA.png", "LIT_Run_RA_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RA.png", "LIT_Run_RA_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RA.png", "LIT_Run_RA_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RA.png", "LIT_Run_RA_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RH.png", "LIT_Run_RH_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RH.png", "LIT_Run_RH_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RH.png", "LIT_Run_RH_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RH.png", "LIT_Run_RH_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RH.png", "LIT_Run_RH_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RH.png", "LIT_Run_RH_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RH.png", "LIT_Run_RH_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_RH.png", "LIT_Run_RH_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S1.png", "LIT_Run_S1_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S1.png", "LIT_Run_S1_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S1.png", "LIT_Run_S1_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S1.png", "LIT_Run_S1_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S1.png", "LIT_Run_S1_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S1.png", "LIT_Run_S1_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S1.png", "LIT_Run_S1_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S1.png", "LIT_Run_S1_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S2.png", "LIT_Run_S2_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S2.png", "LIT_Run_S2_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S2.png", "LIT_Run_S2_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S2.png", "LIT_Run_S2_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S2.png", "LIT_Run_S2_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S2.png", "LIT_Run_S2_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S2.png", "LIT_Run_S2_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_S2.png", "LIT_Run_S2_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_TR.png", "LIT_Run_TR_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_TR.png", "LIT_Run_TR_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_TR.png", "LIT_Run_TR_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_TR.png", "LIT_Run_TR_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_TR.png", "LIT_Run_TR_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_TR.png", "LIT_Run_TR_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_TR.png", "LIT_Run_TR_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Run_TR.png", "LIT_Run_TR_R", 56, 63, 0.1f);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_HD.png", "HVY_Run_HD_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_HD.png", "HVY_Run_HD_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_HD.png", "HVY_Run_HD_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_HD.png", "HVY_Run_HD_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_HD.png", "HVY_Run_HD_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_HD.png", "HVY_Run_HD_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_HD.png", "HVY_Run_HD_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_HD.png", "HVY_Run_HD_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LA.png", "HVY_Run_LA_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LA.png", "HVY_Run_LA_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LA.png", "HVY_Run_LA_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LA.png", "HVY_Run_LA_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LA.png", "HVY_Run_LA_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LA.png", "HVY_Run_LA_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LA.png", "HVY_Run_LA_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LA.png", "HVY_Run_LA_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LG.png", "HVY_Run_LG_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LG.png", "HVY_Run_LG_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LG.png", "HVY_Run_LG_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LG.png", "HVY_Run_LG_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LG.png", "HVY_Run_LG_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LG.png", "HVY_Run_LG_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LG.png", "HVY_Run_LG_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_LG.png", "HVY_Run_LG_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RA.png", "HVY_Run_RA_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RA.png", "HVY_Run_RA_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RA.png", "HVY_Run_RA_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RA.png", "HVY_Run_RA_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RA.png", "HVY_Run_RA_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RA.png", "HVY_Run_RA_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RA.png", "HVY_Run_RA_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RA.png", "HVY_Run_RA_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RH.png", "HVY_Run_RH_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RH.png", "HVY_Run_RH_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RH.png", "HVY_Run_RH_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RH.png", "HVY_Run_RH_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RH.png", "HVY_Run_RH_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RH.png", "HVY_Run_RH_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RH.png", "HVY_Run_RH_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_RH.png", "HVY_Run_RH_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S1.png", "HVY_Run_S1_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S1.png", "HVY_Run_S1_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S1.png", "HVY_Run_S1_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S1.png", "HVY_Run_S1_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S1.png", "HVY_Run_S1_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S1.png", "HVY_Run_S1_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S1.png", "HVY_Run_S1_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S1.png", "HVY_Run_S1_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S2.png", "HVY_Run_S2_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S2.png", "HVY_Run_S2_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S2.png", "HVY_Run_S2_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S2.png", "HVY_Run_S2_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S2.png", "HVY_Run_S2_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S2.png", "HVY_Run_S2_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S2.png", "HVY_Run_S2_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_S2.png", "HVY_Run_S2_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_TR.png", "HVY_Run_TR_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_TR.png", "HVY_Run_TR_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_TR.png", "HVY_Run_TR_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_TR.png", "HVY_Run_TR_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_TR.png", "HVY_Run_TR_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_TR.png", "HVY_Run_TR_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_TR.png", "HVY_Run_TR_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_TR.png", "HVY_Run_TR_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_SH.png", "HVY_Run_SH_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_SH.png", "HVY_Run_SH_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_SH.png", "HVY_Run_SH_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_SH.png", "HVY_Run_SH_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_SH.png", "HVY_Run_SH_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_SH.png", "HVY_Run_SH_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_SH.png", "HVY_Run_SH_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Run_SH.png", "HVY_Run_SH_R", 56, 63, 0.1f);
}

void MainPlayer::CreateS1Animation()
{
	// =========================== x : 16, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_HD.png", "LIT_Special_Attack_HD_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_HD.png", "LIT_Special_Attack_HD_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_HD.png", "LIT_Special_Attack_HD_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_HD.png", "LIT_Special_Attack_HD_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_HD.png", "LIT_Special_Attack_HD_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_HD.png", "LIT_Special_Attack_HD_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_HD.png", "LIT_Special_Attack_HD_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_HD.png", "LIT_Special_Attack_HD_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LA.png", "LIT_Special_Attack_LA_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LA.png", "LIT_Special_Attack_LA_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LA.png", "LIT_Special_Attack_LA_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LA.png", "LIT_Special_Attack_LA_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LA.png", "LIT_Special_Attack_LA_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LA.png", "LIT_Special_Attack_LA_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LA.png", "LIT_Special_Attack_LA_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LA.png", "LIT_Special_Attack_LA_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LG.png", "LIT_Special_Attack_LG_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LG.png", "LIT_Special_Attack_LG_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LG.png", "LIT_Special_Attack_LG_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LG.png", "LIT_Special_Attack_LG_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LG.png", "LIT_Special_Attack_LG_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LG.png", "LIT_Special_Attack_LG_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LG.png", "LIT_Special_Attack_LG_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_LG.png", "LIT_Special_Attack_LG_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RA.png", "LIT_Special_Attack_RA_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RA.png", "LIT_Special_Attack_RA_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RA.png", "LIT_Special_Attack_RA_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RA.png", "LIT_Special_Attack_RA_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RA.png", "LIT_Special_Attack_RA_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RA.png", "LIT_Special_Attack_RA_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RA.png", "LIT_Special_Attack_RA_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RA.png", "LIT_Special_Attack_RA_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RH.png", "LIT_Special_Attack_RH_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RH.png", "LIT_Special_Attack_RH_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RH.png", "LIT_Special_Attack_RH_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RH.png", "LIT_Special_Attack_RH_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RH.png", "LIT_Special_Attack_RH_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RH.png", "LIT_Special_Attack_RH_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RH.png", "LIT_Special_Attack_RH_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_RH.png", "LIT_Special_Attack_RH_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S1.png", "LIT_Special_Attack_S1_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S1.png", "LIT_Special_Attack_S1_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S1.png", "LIT_Special_Attack_S1_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S1.png", "LIT_Special_Attack_S1_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S1.png", "LIT_Special_Attack_S1_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S1.png", "LIT_Special_Attack_S1_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S1.png", "LIT_Special_Attack_S1_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S1.png", "LIT_Special_Attack_S1_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S2.png", "LIT_Special_Attack_S2_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S2.png", "LIT_Special_Attack_S2_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S2.png", "LIT_Special_Attack_S2_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S2.png", "LIT_Special_Attack_S2_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S2.png", "LIT_Special_Attack_S2_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S2.png", "LIT_Special_Attack_S2_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S2.png", "LIT_Special_Attack_S2_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_S2.png", "LIT_Special_Attack_S2_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_TR.png", "LIT_Special_Attack_TR_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_TR.png", "LIT_Special_Attack_TR_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_TR.png", "LIT_Special_Attack_TR_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_TR.png", "LIT_Special_Attack_TR_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_TR.png", "LIT_Special_Attack_TR_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_TR.png", "LIT_Special_Attack_TR_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_TR.png", "LIT_Special_Attack_TR_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Attack_TR.png", "LIT_Special_Attack_TR_R", 112, 127, 0.1f);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_HD.png", "HVY_Special_Attack_HD_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_HD.png", "HVY_Special_Attack_HD_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_HD.png", "HVY_Special_Attack_HD_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_HD.png", "HVY_Special_Attack_HD_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_HD.png", "HVY_Special_Attack_HD_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_HD.png", "HVY_Special_Attack_HD_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_HD.png", "HVY_Special_Attack_HD_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_HD.png", "HVY_Special_Attack_HD_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LA.png", "HVY_Special_Attack_LA_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LA.png", "HVY_Special_Attack_LA_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LA.png", "HVY_Special_Attack_LA_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LA.png", "HVY_Special_Attack_LA_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LA.png", "HVY_Special_Attack_LA_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LA.png", "HVY_Special_Attack_LA_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LA.png", "HVY_Special_Attack_LA_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LA.png", "HVY_Special_Attack_LA_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LG.png", "HVY_Special_Attack_LG_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LG.png", "HVY_Special_Attack_LG_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LG.png", "HVY_Special_Attack_LG_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LG.png", "HVY_Special_Attack_LG_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LG.png", "HVY_Special_Attack_LG_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LG.png", "HVY_Special_Attack_LG_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LG.png", "HVY_Special_Attack_LG_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_LG.png", "HVY_Special_Attack_LG_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RA.png", "HVY_Special_Attack_RA_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RA.png", "HVY_Special_Attack_RA_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RA.png", "HVY_Special_Attack_RA_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RA.png", "HVY_Special_Attack_RA_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RA.png", "HVY_Special_Attack_RA_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RA.png", "HVY_Special_Attack_RA_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RA.png", "HVY_Special_Attack_RA_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RA.png", "HVY_Special_Attack_RA_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RH.png", "HVY_Special_Attack_RH_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RH.png", "HVY_Special_Attack_RH_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RH.png", "HVY_Special_Attack_RH_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RH.png", "HVY_Special_Attack_RH_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RH.png", "HVY_Special_Attack_RH_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RH.png", "HVY_Special_Attack_RH_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RH.png", "HVY_Special_Attack_RH_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_RH.png", "HVY_Special_Attack_RH_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S1.png", "HVY_Special_Attack_S1_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S1.png", "HVY_Special_Attack_S1_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S1.png", "HVY_Special_Attack_S1_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S1.png", "HVY_Special_Attack_S1_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S1.png", "HVY_Special_Attack_S1_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S1.png", "HVY_Special_Attack_S1_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S1.png", "HVY_Special_Attack_S1_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S1.png", "HVY_Special_Attack_S1_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S2.png", "HVY_Special_Attack_S2_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S2.png", "HVY_Special_Attack_S2_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S2.png", "HVY_Special_Attack_S2_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S2.png", "HVY_Special_Attack_S2_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S2.png", "HVY_Special_Attack_S2_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S2.png", "HVY_Special_Attack_S2_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S2.png", "HVY_Special_Attack_S2_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_S2.png", "HVY_Special_Attack_S2_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_TR.png", "HVY_Special_Attack_TR_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_TR.png", "HVY_Special_Attack_TR_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_TR.png", "HVY_Special_Attack_TR_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_TR.png", "HVY_Special_Attack_TR_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_TR.png", "HVY_Special_Attack_TR_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_TR.png", "HVY_Special_Attack_TR_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_TR.png", "HVY_Special_Attack_TR_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_TR.png", "HVY_Special_Attack_TR_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_SH.png", "HVY_Special_Attack_SH_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_SH.png", "HVY_Special_Attack_SH_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_SH.png", "HVY_Special_Attack_SH_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_SH.png", "HVY_Special_Attack_SH_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_SH.png", "HVY_Special_Attack_SH_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_SH.png", "HVY_Special_Attack_SH_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_SH.png", "HVY_Special_Attack_SH_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Attack_SH.png", "HVY_Special_Attack_SH_R", 112, 127, 0.1f);
}

void MainPlayer::CreateSCAnimation()
{
	// =========================== x : 16, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_HD.png", "LIT_Special_Cast_HD_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_HD.png", "LIT_Special_Cast_HD_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_HD.png", "LIT_Special_Cast_HD_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_HD.png", "LIT_Special_Cast_HD_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_HD.png", "LIT_Special_Cast_HD_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_HD.png", "LIT_Special_Cast_HD_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_HD.png", "LIT_Special_Cast_HD_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_HD.png", "LIT_Special_Cast_HD_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LA.png", "LIT_Special_Cast_LA_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LA.png", "LIT_Special_Cast_LA_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LA.png", "LIT_Special_Cast_LA_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LA.png", "LIT_Special_Cast_LA_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LA.png", "LIT_Special_Cast_LA_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LA.png", "LIT_Special_Cast_LA_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LA.png", "LIT_Special_Cast_LA_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LA.png", "LIT_Special_Cast_LA_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LG.png", "LIT_Special_Cast_LG_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LG.png", "LIT_Special_Cast_LG_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LG.png", "LIT_Special_Cast_LG_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LG.png", "LIT_Special_Cast_LG_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LG.png", "LIT_Special_Cast_LG_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LG.png", "LIT_Special_Cast_LG_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LG.png", "LIT_Special_Cast_LG_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_LG.png", "LIT_Special_Cast_LG_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RA.png", "LIT_Special_Cast_RA_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RA.png", "LIT_Special_Cast_RA_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RA.png", "LIT_Special_Cast_RA_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RA.png", "LIT_Special_Cast_RA_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RA.png", "LIT_Special_Cast_RA_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RA.png", "LIT_Special_Cast_RA_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RA.png", "LIT_Special_Cast_RA_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RA.png", "LIT_Special_Cast_RA_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RH.png", "LIT_Special_Cast_RH_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RH.png", "LIT_Special_Cast_RH_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RH.png", "LIT_Special_Cast_RH_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RH.png", "LIT_Special_Cast_RH_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RH.png", "LIT_Special_Cast_RH_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RH.png", "LIT_Special_Cast_RH_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RH.png", "LIT_Special_Cast_RH_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_RH.png", "LIT_Special_Cast_RH_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S1.png", "LIT_Special_Cast_S1_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S1.png", "LIT_Special_Cast_S1_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S1.png", "LIT_Special_Cast_S1_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S1.png", "LIT_Special_Cast_S1_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S1.png", "LIT_Special_Cast_S1_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S1.png", "LIT_Special_Cast_S1_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S1.png", "LIT_Special_Cast_S1_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S1.png", "LIT_Special_Cast_S1_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S2.png", "LIT_Special_Cast_S2_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S2.png", "LIT_Special_Cast_S2_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S2.png", "LIT_Special_Cast_S2_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S2.png", "LIT_Special_Cast_S2_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S2.png", "LIT_Special_Cast_S2_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S2.png", "LIT_Special_Cast_S2_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S2.png", "LIT_Special_Cast_S2_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_S2.png", "LIT_Special_Cast_S2_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_TR.png", "LIT_Special_Cast_TR_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_TR.png", "LIT_Special_Cast_TR_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_TR.png", "LIT_Special_Cast_TR_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_TR.png", "LIT_Special_Cast_TR_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_TR.png", "LIT_Special_Cast_TR_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_TR.png", "LIT_Special_Cast_TR_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_TR.png", "LIT_Special_Cast_TR_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Special_Cast_TR.png", "LIT_Special_Cast_TR_R", 112, 127, 0.1f);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_HD.png", "HVY_Special_Cast_HD_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_HD.png", "HVY_Special_Cast_HD_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_HD.png", "HVY_Special_Cast_HD_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_HD.png", "HVY_Special_Cast_HD_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_HD.png", "HVY_Special_Cast_HD_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_HD.png", "HVY_Special_Cast_HD_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_HD.png", "HVY_Special_Cast_HD_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_HD.png", "HVY_Special_Cast_HD_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LA.png", "HVY_Special_Cast_LA_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LA.png", "HVY_Special_Cast_LA_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LA.png", "HVY_Special_Cast_LA_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LA.png", "HVY_Special_Cast_LA_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LA.png", "HVY_Special_Cast_LA_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LA.png", "HVY_Special_Cast_LA_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LA.png", "HVY_Special_Cast_LA_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LA.png", "HVY_Special_Cast_LA_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LG.png", "HVY_Special_Cast_LG_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LG.png", "HVY_Special_Cast_LG_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LG.png", "HVY_Special_Cast_LG_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LG.png", "HVY_Special_Cast_LG_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LG.png", "HVY_Special_Cast_LG_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LG.png", "HVY_Special_Cast_LG_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LG.png", "HVY_Special_Cast_LG_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_LG.png", "HVY_Special_Cast_LG_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RA.png", "HVY_Special_Cast_RA_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RA.png", "HVY_Special_Cast_RA_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RA.png", "HVY_Special_Cast_RA_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RA.png", "HVY_Special_Cast_RA_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RA.png", "HVY_Special_Cast_RA_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RA.png", "HVY_Special_Cast_RA_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RA.png", "HVY_Special_Cast_RA_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RA.png", "HVY_Special_Cast_RA_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RH.png", "HVY_Special_Cast_RH_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RH.png", "HVY_Special_Cast_RH_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RH.png", "HVY_Special_Cast_RH_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RH.png", "HVY_Special_Cast_RH_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RH.png", "HVY_Special_Cast_RH_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RH.png", "HVY_Special_Cast_RH_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RH.png", "HVY_Special_Cast_RH_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_RH.png", "HVY_Special_Cast_RH_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S1.png", "HVY_Special_Cast_S1_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S1.png", "HVY_Special_Cast_S1_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S1.png", "HVY_Special_Cast_S1_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S1.png", "HVY_Special_Cast_S1_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S1.png", "HVY_Special_Cast_S1_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S1.png", "HVY_Special_Cast_S1_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S1.png", "HVY_Special_Cast_S1_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S1.png", "HVY_Special_Cast_S1_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S2.png", "HVY_Special_Cast_S2_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S2.png", "HVY_Special_Cast_S2_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S2.png", "HVY_Special_Cast_S2_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S2.png", "HVY_Special_Cast_S2_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S2.png", "HVY_Special_Cast_S2_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S2.png", "HVY_Special_Cast_S2_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S2.png", "HVY_Special_Cast_S2_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_S2.png", "HVY_Special_Cast_S2_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_TR.png", "HVY_Special_Cast_TR_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_TR.png", "HVY_Special_Cast_TR_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_TR.png", "HVY_Special_Cast_TR_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_TR.png", "HVY_Special_Cast_TR_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_TR.png", "HVY_Special_Cast_TR_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_TR.png", "HVY_Special_Cast_TR_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_TR.png", "HVY_Special_Cast_TR_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_TR.png", "HVY_Special_Cast_TR_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_SH.png", "HVY_Special_Cast_SH_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_SH.png", "HVY_Special_Cast_SH_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_SH.png", "HVY_Special_Cast_SH_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_SH.png", "HVY_Special_Cast_SH_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_SH.png", "HVY_Special_Cast_SH_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_SH.png", "HVY_Special_Cast_SH_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_SH.png", "HVY_Special_Cast_SH_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Special_Cast_SH.png", "HVY_Special_Cast_SH_R", 112, 127, 0.1f);
}

void MainPlayer::CreateTNAnimation()
{
	// =========================== x : 16, y : 16 ============================ //
	
	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_HD.png", "LIT_Natural_Town_HD_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_HD.png", "LIT_Natural_Town_HD_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_HD.png", "LIT_Natural_Town_HD_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_HD.png", "LIT_Natural_Town_HD_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_HD.png", "LIT_Natural_Town_HD_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_HD.png", "LIT_Natural_Town_HD_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_HD.png", "LIT_Natural_Town_HD_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_HD.png", "LIT_Natural_Town_HD_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LA.png", "LIT_Natural_Town_LA_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LA.png", "LIT_Natural_Town_LA_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LA.png", "LIT_Natural_Town_LA_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LA.png", "LIT_Natural_Town_LA_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LA.png", "LIT_Natural_Town_LA_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LA.png", "LIT_Natural_Town_LA_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LA.png", "LIT_Natural_Town_LA_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LA.png", "LIT_Natural_Town_LA_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LG.png", "LIT_Natural_Town_LG_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LG.png", "LIT_Natural_Town_LG_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LG.png", "LIT_Natural_Town_LG_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LG.png", "LIT_Natural_Town_LG_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LG.png", "LIT_Natural_Town_LG_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LG.png", "LIT_Natural_Town_LG_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LG.png", "LIT_Natural_Town_LG_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_LG.png", "LIT_Natural_Town_LG_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RA.png", "LIT_Natural_Town_RA_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RA.png", "LIT_Natural_Town_RA_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RA.png", "LIT_Natural_Town_RA_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RA.png", "LIT_Natural_Town_RA_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RA.png", "LIT_Natural_Town_RA_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RA.png", "LIT_Natural_Town_RA_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RA.png", "LIT_Natural_Town_RA_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RA.png", "LIT_Natural_Town_RA_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RH.png", "LIT_Natural_Town_RH_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RH.png", "LIT_Natural_Town_RH_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RH.png", "LIT_Natural_Town_RH_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RH.png", "LIT_Natural_Town_RH_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RH.png", "LIT_Natural_Town_RH_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RH.png", "LIT_Natural_Town_RH_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RH.png", "LIT_Natural_Town_RH_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_RH.png", "LIT_Natural_Town_RH_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S1.png", "LIT_Natural_Town_S1_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S1.png", "LIT_Natural_Town_S1_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S1.png", "LIT_Natural_Town_S1_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S1.png", "LIT_Natural_Town_S1_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S1.png", "LIT_Natural_Town_S1_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S1.png", "LIT_Natural_Town_S1_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S1.png", "LIT_Natural_Town_S1_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S1.png", "LIT_Natural_Town_S1_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S2.png", "LIT_Natural_Town_S2_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S2.png", "LIT_Natural_Town_S2_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S2.png", "LIT_Natural_Town_S2_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S2.png", "LIT_Natural_Town_S2_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S2.png", "LIT_Natural_Town_S2_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S2.png", "LIT_Natural_Town_S2_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S2.png", "LIT_Natural_Town_S2_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_S2.png", "LIT_Natural_Town_S2_R", 112, 127, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_TR.png", "LIT_Natural_Town_TR_LB", 0, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_TR.png", "LIT_Natural_Town_TR_LT", 16, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_TR.png", "LIT_Natural_Town_TR_RT", 32, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_TR.png", "LIT_Natural_Town_TR_RB", 48, 63, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_TR.png", "LIT_Natural_Town_TR_B", 64, 79, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_TR.png", "LIT_Natural_Town_TR_L", 80, 95, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_TR.png", "LIT_Natural_Town_TR_T", 96, 111, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Natural_Town_TR.png", "LIT_Natural_Town_TR_R", 112, 127, 0.1f);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_HD.png", "HVY_Natural_Town_HD_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_HD.png", "HVY_Natural_Town_HD_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_HD.png", "HVY_Natural_Town_HD_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_HD.png", "HVY_Natural_Town_HD_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_HD.png", "HVY_Natural_Town_HD_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_HD.png", "HVY_Natural_Town_HD_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_HD.png", "HVY_Natural_Town_HD_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_HD.png", "HVY_Natural_Town_HD_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LA.png", "HVY_Natural_Town_LA_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LA.png", "HVY_Natural_Town_LA_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LA.png", "HVY_Natural_Town_LA_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LA.png", "HVY_Natural_Town_LA_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LA.png", "HVY_Natural_Town_LA_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LA.png", "HVY_Natural_Town_LA_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LA.png", "HVY_Natural_Town_LA_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LA.png", "HVY_Natural_Town_LA_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LG.png", "HVY_Natural_Town_LG_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LG.png", "HVY_Natural_Town_LG_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LG.png", "HVY_Natural_Town_LG_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LG.png", "HVY_Natural_Town_LG_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LG.png", "HVY_Natural_Town_LG_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LG.png", "HVY_Natural_Town_LG_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LG.png", "HVY_Natural_Town_LG_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_LG.png", "HVY_Natural_Town_LG_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RA.png", "HVY_Natural_Town_RA_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RA.png", "HVY_Natural_Town_RA_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RA.png", "HVY_Natural_Town_RA_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RA.png", "HVY_Natural_Town_RA_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RA.png", "HVY_Natural_Town_RA_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RA.png", "HVY_Natural_Town_RA_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RA.png", "HVY_Natural_Town_RA_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RA.png", "HVY_Natural_Town_RA_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RH.png", "HVY_Natural_Town_RH_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RH.png", "HVY_Natural_Town_RH_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RH.png", "HVY_Natural_Town_RH_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RH.png", "HVY_Natural_Town_RH_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RH.png", "HVY_Natural_Town_RH_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RH.png", "HVY_Natural_Town_RH_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RH.png", "HVY_Natural_Town_RH_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_RH.png", "HVY_Natural_Town_RH_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S1.png", "HVY_Natural_Town_S1_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S1.png", "HVY_Natural_Town_S1_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S1.png", "HVY_Natural_Town_S1_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S1.png", "HVY_Natural_Town_S1_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S1.png", "HVY_Natural_Town_S1_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S1.png", "HVY_Natural_Town_S1_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S1.png", "HVY_Natural_Town_S1_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S1.png", "HVY_Natural_Town_S1_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S2.png", "HVY_Natural_Town_S2_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S2.png", "HVY_Natural_Town_S2_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S2.png", "HVY_Natural_Town_S2_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S2.png", "HVY_Natural_Town_S2_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S2.png", "HVY_Natural_Town_S2_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S2.png", "HVY_Natural_Town_S2_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S2.png", "HVY_Natural_Town_S2_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_S2.png", "HVY_Natural_Town_S2_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_TR.png", "HVY_Natural_Town_TR_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_TR.png", "HVY_Natural_Town_TR_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_TR.png", "HVY_Natural_Town_TR_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_TR.png", "HVY_Natural_Town_TR_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_TR.png", "HVY_Natural_Town_TR_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_TR.png", "HVY_Natural_Town_TR_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_TR.png", "HVY_Natural_Town_TR_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_TR.png", "HVY_Natural_Town_TR_R", 112, 127, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_SH.png", "HVY_Natural_Town_SH_LB", 0, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_SH.png", "HVY_Natural_Town_SH_LT", 16, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_SH.png", "HVY_Natural_Town_SH_RT", 32, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_SH.png", "HVY_Natural_Town_SH_RB", 48, 63, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_SH.png", "HVY_Natural_Town_SH_B", 64, 79, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_SH.png", "HVY_Natural_Town_SH_L", 80, 95, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_SH.png", "HVY_Natural_Town_SH_T", 96, 111, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Natural_Town_SH.png", "HVY_Natural_Town_SH_R", 112, 127, 0.1f);
}

void MainPlayer::CreateTWAnimation()
{
	// =========================== x :  8, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_HD.png", "LIT_Walk_Town_HD_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_HD.png", "LIT_Walk_Town_HD_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_HD.png", "LIT_Walk_Town_HD_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_HD.png", "LIT_Walk_Town_HD_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_HD.png", "LIT_Walk_Town_HD_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_HD.png", "LIT_Walk_Town_HD_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_HD.png", "LIT_Walk_Town_HD_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_HD.png", "LIT_Walk_Town_HD_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LA.png", "LIT_Walk_Town_LA_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LA.png", "LIT_Walk_Town_LA_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LA.png", "LIT_Walk_Town_LA_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LA.png", "LIT_Walk_Town_LA_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LA.png", "LIT_Walk_Town_LA_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LA.png", "LIT_Walk_Town_LA_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LA.png", "LIT_Walk_Town_LA_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LA.png", "LIT_Walk_Town_LA_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LG.png", "LIT_Walk_Town_LG_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LG.png", "LIT_Walk_Town_LG_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LG.png", "LIT_Walk_Town_LG_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LG.png", "LIT_Walk_Town_LG_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LG.png", "LIT_Walk_Town_LG_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LG.png", "LIT_Walk_Town_LG_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LG.png", "LIT_Walk_Town_LG_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_LG.png", "LIT_Walk_Town_LG_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RA.png", "LIT_Walk_Town_RA_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RA.png", "LIT_Walk_Town_RA_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RA.png", "LIT_Walk_Town_RA_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RA.png", "LIT_Walk_Town_RA_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RA.png", "LIT_Walk_Town_RA_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RA.png", "LIT_Walk_Town_RA_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RA.png", "LIT_Walk_Town_RA_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RA.png", "LIT_Walk_Town_RA_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RH.png", "LIT_Walk_Town_RH_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RH.png", "LIT_Walk_Town_RH_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RH.png", "LIT_Walk_Town_RH_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RH.png", "LIT_Walk_Town_RH_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RH.png", "LIT_Walk_Town_RH_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RH.png", "LIT_Walk_Town_RH_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RH.png", "LIT_Walk_Town_RH_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_RH.png", "LIT_Walk_Town_RH_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S1.png", "LIT_Walk_Town_S1_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S1.png", "LIT_Walk_Town_S1_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S1.png", "LIT_Walk_Town_S1_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S1.png", "LIT_Walk_Town_S1_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S1.png", "LIT_Walk_Town_S1_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S1.png", "LIT_Walk_Town_S1_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S1.png", "LIT_Walk_Town_S1_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S1.png", "LIT_Walk_Town_S1_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S2.png", "LIT_Walk_Town_S2_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S2.png", "LIT_Walk_Town_S2_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S2.png", "LIT_Walk_Town_S2_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S2.png", "LIT_Walk_Town_S2_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S2.png", "LIT_Walk_Town_S2_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S2.png", "LIT_Walk_Town_S2_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S2.png", "LIT_Walk_Town_S2_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_S2.png", "LIT_Walk_Town_S2_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_TR.png", "LIT_Walk_Town_TR_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_TR.png", "LIT_Walk_Town_TR_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_TR.png", "LIT_Walk_Town_TR_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_TR.png", "LIT_Walk_Town_TR_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_TR.png", "LIT_Walk_Town_TR_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_TR.png", "LIT_Walk_Town_TR_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_TR.png", "LIT_Walk_Town_TR_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Town_TR.png", "LIT_Walk_Town_TR_R", 56, 63, 0.1f);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_HD.png", "HVY_Walk_Town_HD_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_HD.png", "HVY_Walk_Town_HD_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_HD.png", "HVY_Walk_Town_HD_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_HD.png", "HVY_Walk_Town_HD_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_HD.png", "HVY_Walk_Town_HD_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_HD.png", "HVY_Walk_Town_HD_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_HD.png", "HVY_Walk_Town_HD_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_HD.png", "HVY_Walk_Town_HD_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LA.png", "HVY_Walk_Town_LA_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LA.png", "HVY_Walk_Town_LA_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LA.png", "HVY_Walk_Town_LA_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LA.png", "HVY_Walk_Town_LA_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LA.png", "HVY_Walk_Town_LA_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LA.png", "HVY_Walk_Town_LA_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LA.png", "HVY_Walk_Town_LA_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LA.png", "HVY_Walk_Town_LA_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LG.png", "HVY_Walk_Town_LG_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LG.png", "HVY_Walk_Town_LG_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LG.png", "HVY_Walk_Town_LG_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LG.png", "HVY_Walk_Town_LG_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LG.png", "HVY_Walk_Town_LG_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LG.png", "HVY_Walk_Town_LG_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LG.png", "HVY_Walk_Town_LG_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_LG.png", "HVY_Walk_Town_LG_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RA.png", "HVY_Walk_Town_RA_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RA.png", "HVY_Walk_Town_RA_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RA.png", "HVY_Walk_Town_RA_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RA.png", "HVY_Walk_Town_RA_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RA.png", "HVY_Walk_Town_RA_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RA.png", "HVY_Walk_Town_RA_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RA.png", "HVY_Walk_Town_RA_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RA.png", "HVY_Walk_Town_RA_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RH.png", "HVY_Walk_Town_RH_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RH.png", "HVY_Walk_Town_RH_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RH.png", "HVY_Walk_Town_RH_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RH.png", "HVY_Walk_Town_RH_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RH.png", "HVY_Walk_Town_RH_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RH.png", "HVY_Walk_Town_RH_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RH.png", "HVY_Walk_Town_RH_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_RH.png", "HVY_Walk_Town_RH_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S1.png", "HVY_Walk_Town_S1_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S1.png", "HVY_Walk_Town_S1_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S1.png", "HVY_Walk_Town_S1_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S1.png", "HVY_Walk_Town_S1_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S1.png", "HVY_Walk_Town_S1_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S1.png", "HVY_Walk_Town_S1_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S1.png", "HVY_Walk_Town_S1_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S1.png", "HVY_Walk_Town_S1_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S2.png", "HVY_Walk_Town_S2_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S2.png", "HVY_Walk_Town_S2_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S2.png", "HVY_Walk_Town_S2_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S2.png", "HVY_Walk_Town_S2_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S2.png", "HVY_Walk_Town_S2_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S2.png", "HVY_Walk_Town_S2_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S2.png", "HVY_Walk_Town_S2_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_S2.png", "HVY_Walk_Town_S2_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_TR.png", "HVY_Walk_Town_TR_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_TR.png", "HVY_Walk_Town_TR_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_TR.png", "HVY_Walk_Town_TR_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_TR.png", "HVY_Walk_Town_TR_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_TR.png", "HVY_Walk_Town_TR_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_TR.png", "HVY_Walk_Town_TR_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_TR.png", "HVY_Walk_Town_TR_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_TR.png", "HVY_Walk_Town_TR_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_SH.png", "HVY_Walk_Town_SH_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_SH.png", "HVY_Walk_Town_SH_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_SH.png", "HVY_Walk_Town_SH_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_SH.png", "HVY_Walk_Town_SH_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_SH.png", "HVY_Walk_Town_SH_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_SH.png", "HVY_Walk_Town_SH_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_SH.png", "HVY_Walk_Town_SH_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Town_SH.png", "HVY_Walk_Town_SH_R", 56, 63, 0.1f);
}

void MainPlayer::CreateWLAnimation()
{
	// =========================== x :  8, y : 16 ============================ //

	// =============================== LIT =============================== //
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_HD.png", "LIT_Walk_Field_HD_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_HD.png", "LIT_Walk_Field_HD_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_HD.png", "LIT_Walk_Field_HD_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_HD.png", "LIT_Walk_Field_HD_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_HD.png", "LIT_Walk_Field_HD_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_HD.png", "LIT_Walk_Field_HD_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_HD.png", "LIT_Walk_Field_HD_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_HD.png", "LIT_Walk_Field_HD_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LA.png", "LIT_Walk_Field_LA_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LA.png", "LIT_Walk_Field_LA_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LA.png", "LIT_Walk_Field_LA_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LA.png", "LIT_Walk_Field_LA_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LA.png", "LIT_Walk_Field_LA_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LA.png", "LIT_Walk_Field_LA_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LA.png", "LIT_Walk_Field_LA_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LA.png", "LIT_Walk_Field_LA_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LG.png", "LIT_Walk_Field_LG_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LG.png", "LIT_Walk_Field_LG_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LG.png", "LIT_Walk_Field_LG_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LG.png", "LIT_Walk_Field_LG_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LG.png", "LIT_Walk_Field_LG_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LG.png", "LIT_Walk_Field_LG_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LG.png", "LIT_Walk_Field_LG_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_LG.png", "LIT_Walk_Field_LG_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RA.png", "LIT_Walk_Field_RA_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RA.png", "LIT_Walk_Field_RA_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RA.png", "LIT_Walk_Field_RA_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RA.png", "LIT_Walk_Field_RA_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RA.png", "LIT_Walk_Field_RA_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RA.png", "LIT_Walk_Field_RA_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RA.png", "LIT_Walk_Field_RA_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RA.png", "LIT_Walk_Field_RA_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RH.png", "LIT_Walk_Field_RH_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RH.png", "LIT_Walk_Field_RH_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RH.png", "LIT_Walk_Field_RH_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RH.png", "LIT_Walk_Field_RH_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RH.png", "LIT_Walk_Field_RH_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RH.png", "LIT_Walk_Field_RH_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RH.png", "LIT_Walk_Field_RH_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_RH.png", "LIT_Walk_Field_RH_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S1.png", "LIT_Walk_Field_S1_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S1.png", "LIT_Walk_Field_S1_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S1.png", "LIT_Walk_Field_S1_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S1.png", "LIT_Walk_Field_S1_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S1.png", "LIT_Walk_Field_S1_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S1.png", "LIT_Walk_Field_S1_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S1.png", "LIT_Walk_Field_S1_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S1.png", "LIT_Walk_Field_S1_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S2.png", "LIT_Walk_Field_S2_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S2.png", "LIT_Walk_Field_S2_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S2.png", "LIT_Walk_Field_S2_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S2.png", "LIT_Walk_Field_S2_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S2.png", "LIT_Walk_Field_S2_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S2.png", "LIT_Walk_Field_S2_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S2.png", "LIT_Walk_Field_S2_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_S2.png", "LIT_Walk_Field_S2_R", 56, 63, 0.1f);

	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_TR.png", "LIT_Walk_Field_TR_LB", 0, 7, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_TR.png", "LIT_Walk_Field_TR_LT", 8, 15, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_TR.png", "LIT_Walk_Field_TR_RT", 16, 23, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_TR.png", "LIT_Walk_Field_TR_RB", 24, 31, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_TR.png", "LIT_Walk_Field_TR_B", 32, 39, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_TR.png", "LIT_Walk_Field_TR_L", 40, 47, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_TR.png", "LIT_Walk_Field_TR_T", 48, 55, 0.1f);
	PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->CreateAnimation("LIT_Walk_Field_TR.png", "LIT_Walk_Field_TR_R", 56, 63, 0.1f);

	// =============================== HVY =============================== //
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_HD.png", "HVY_Walk_Field_HD_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_HD.png", "HVY_Walk_Field_HD_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_HD.png", "HVY_Walk_Field_HD_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_HD.png", "HVY_Walk_Field_HD_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_HD.png", "HVY_Walk_Field_HD_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_HD.png", "HVY_Walk_Field_HD_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_HD.png", "HVY_Walk_Field_HD_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_HD)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_HD.png", "HVY_Walk_Field_HD_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LA.png", "HVY_Walk_Field_LA_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LA.png", "HVY_Walk_Field_LA_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LA.png", "HVY_Walk_Field_LA_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LA.png", "HVY_Walk_Field_LA_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LA.png", "HVY_Walk_Field_LA_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LA.png", "HVY_Walk_Field_LA_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LA.png", "HVY_Walk_Field_LA_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LA.png", "HVY_Walk_Field_LA_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LG.png", "HVY_Walk_Field_LG_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LG.png", "HVY_Walk_Field_LG_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LG.png", "HVY_Walk_Field_LG_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LG.png", "HVY_Walk_Field_LG_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LG.png", "HVY_Walk_Field_LG_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LG.png", "HVY_Walk_Field_LG_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LG.png", "HVY_Walk_Field_LG_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_LG)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_LG.png", "HVY_Walk_Field_LG_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RA.png", "HVY_Walk_Field_RA_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RA.png", "HVY_Walk_Field_RA_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RA.png", "HVY_Walk_Field_RA_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RA.png", "HVY_Walk_Field_RA_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RA.png", "HVY_Walk_Field_RA_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RA.png", "HVY_Walk_Field_RA_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RA.png", "HVY_Walk_Field_RA_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RA)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RA.png", "HVY_Walk_Field_RA_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RH.png", "HVY_Walk_Field_RH_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RH.png", "HVY_Walk_Field_RH_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RH.png", "HVY_Walk_Field_RH_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RH.png", "HVY_Walk_Field_RH_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RH.png", "HVY_Walk_Field_RH_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RH.png", "HVY_Walk_Field_RH_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RH.png", "HVY_Walk_Field_RH_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_RH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_RH.png", "HVY_Walk_Field_RH_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S1.png", "HVY_Walk_Field_S1_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S1.png", "HVY_Walk_Field_S1_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S1.png", "HVY_Walk_Field_S1_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S1.png", "HVY_Walk_Field_S1_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S1.png", "HVY_Walk_Field_S1_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S1.png", "HVY_Walk_Field_S1_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S1.png", "HVY_Walk_Field_S1_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S1)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S1.png", "HVY_Walk_Field_S1_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S2.png", "HVY_Walk_Field_S2_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S2.png", "HVY_Walk_Field_S2_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S2.png", "HVY_Walk_Field_S2_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S2.png", "HVY_Walk_Field_S2_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S2.png", "HVY_Walk_Field_S2_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S2.png", "HVY_Walk_Field_S2_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S2.png", "HVY_Walk_Field_S2_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_S2)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_S2.png", "HVY_Walk_Field_S2_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_TR.png", "HVY_Walk_Field_TR_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_TR.png", "HVY_Walk_Field_TR_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_TR.png", "HVY_Walk_Field_TR_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_TR.png", "HVY_Walk_Field_TR_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_TR.png", "HVY_Walk_Field_TR_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_TR.png", "HVY_Walk_Field_TR_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_TR.png", "HVY_Walk_Field_TR_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_TR.png", "HVY_Walk_Field_TR_R", 56, 63, 0.1f);

	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_SH.png", "HVY_Walk_Field_SH_LB", 0, 7, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_SH.png", "HVY_Walk_Field_SH_LT", 8, 15, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_SH.png", "HVY_Walk_Field_SH_RT", 16, 23, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_SH.png", "HVY_Walk_Field_SH_RB", 24, 31, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_SH.png", "HVY_Walk_Field_SH_B", 32, 39, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_SH.png", "HVY_Walk_Field_SH_L", 40, 47, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_SH.png", "HVY_Walk_Field_SH_T", 48, 55, 0.1f);
	//PartRenderer_[static_cast<int>(RendererPartType::PART_SH)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->CreateAnimation("HVY_Walk_Field_SH.png", "HVY_Walk_Field_SH_R", 56, 63, 0.1f);
}
