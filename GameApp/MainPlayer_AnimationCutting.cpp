#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineTextureManager.h>
#include <GameEngine/GameEngineTexture.h>

void MainPlayer::AllAnimationCut()
{
	// 플레이어가 필요로하는 모든 애니메이션 컷팅 작업처리
	AnimationA1Cut();
	AnimationA2Cut();
	AnimationBLCut();
	AnimationDDCut();
	AnimationDTCut();
	AnimationGHCut();
	AnimationKKCut();
	AnimationNUCut();
	AnimationRNCut();
	AnimationS1Cut();
	AnimationSCCut();
	AnimationTNCut();
	AnimationTWCut();
	AnimationWLCut();
}

void MainPlayer::AnimationA1Cut()
{
}

void MainPlayer::AnimationA2Cut()
{
}

void MainPlayer::AnimationBLCut()
{
}

void MainPlayer::AnimationDDCut()
{
}

void MainPlayer::AnimationDTCut()
{
}

void MainPlayer::AnimationGHCut()
{
}

void MainPlayer::AnimationKKCut()
{
}

void MainPlayer::AnimationNUCut()
{
	// ========================= NU(대기모션) ======================== //
	// x : 8, y : 16
	// HD(머리)
	GameEngineTexture* LIT_NU_HD = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_HD.png");
	LIT_NU_HD->Cut(8, 16);
	//GameEngineTexture* HVY_NU_HD = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_HD.png");
	//HVY_NU_HD->Cut(8, 16);

	// LA(왼팔)
	GameEngineTexture* LIT_NU_LA = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_LA.png");
	LIT_NU_LA->Cut(8, 16);
	//GameEngineTexture* HVY_NU_LA = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_LA.png");
	//HVY_NU_LA->Cut(8, 16);

	// LG(다리)
	GameEngineTexture* LIT_NU_LG = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_LG.png");
	LIT_NU_LG->Cut(8, 16);
	//GameEngineTexture* HVY_NU_LG = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_LG.png");
	//HVY_NU_LG->Cut(8, 16);

	// RA(오른팔)
	GameEngineTexture* LIT_NU_RA = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_RA.png");
	LIT_NU_RA->Cut(8, 16);
	//GameEngineTexture* HVY_NU_RA = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_RA.png");
	//HVY_NU_RA->Cut(8, 16);

	// RH(무기)
	GameEngineTexture* LIT_NU_RH = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_RH.png");
	LIT_NU_RH->Cut(8, 16);
	//GameEngineTexture* HVY_NU_RH = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_RH.png");
	//HVY_NU_RH->Cut(8, 16);

	// S1(오른쪽어깨)
	GameEngineTexture* LIT_NU_S1 = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_S1.png");
	LIT_NU_S1->Cut(8, 16);
	//GameEngineTexture* HVY_NU_S1 = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_S1.png");
	//HVY_NU_S1->Cut(8, 16);

	// S2(왼쪽어깨)
	GameEngineTexture* LIT_NU_S2 = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_S2.png");
	LIT_NU_S2->Cut(8, 16);
	//GameEngineTexture* HVY_NU_S2 = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_S2.png");
	//HVY_NU_S2->Cut(8, 16);

	// SH(방패)
	//GameEngineTexture* HVY_NU_SH = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_SH.png");
	//HVY_NU_SH->Cut(8, 16);

	// TR(몸통)
	GameEngineTexture* LIT_NU_TR = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_TR.png");
	LIT_NU_TR->Cut(8, 16);
	//GameEngineTexture* HVY_NU_TR = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_TR.png");
	//HVY_NU_TR->Cut(8, 16);
}

void MainPlayer::AnimationRNCut()
{
}

void MainPlayer::AnimationS1Cut()
{
}

void MainPlayer::AnimationSCCut()
{
}

void MainPlayer::AnimationTNCut()
{
}

void MainPlayer::AnimationTWCut()
{
}

void MainPlayer::AnimationWLCut()
{
}
