#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineTextureManager.h>
#include <GameEngine/GameEngineTexture.h>

void MainPlayer::AllAnimationCut()
{
	// ÇÃ·¹ÀÌ¾î°¡ ÇÊ¿ä·ÎÇÏ´Â ¸ðµç ¾Ö´Ï¸ÞÀÌ¼Ç ÄÆÆÃ ÀÛ¾÷Ã³¸®
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
	// ===================================== x : 19, y : 16 ===================================== //

	// HD(¸Ó¸®)
	GameEngineTexture* LIT_A1_HD = GameEngineTextureManager::GetInst().Find("LIT_Attack1_HD.png");
	LIT_A1_HD->Cut(19, 16);
	GameEngineTexture* HVY_A1_HD = GameEngineTextureManager::GetInst().Find("HVY_Attack1_HD.png");
	HVY_A1_HD->Cut(19, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_A1_LA = GameEngineTextureManager::GetInst().Find("LIT_Attack1_LA.png");
	LIT_A1_LA->Cut(19, 16);
	GameEngineTexture* HVY_A1_LA = GameEngineTextureManager::GetInst().Find("HVY_Attack1_LA.png");
	HVY_A1_LA->Cut(19, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_A1_LG = GameEngineTextureManager::GetInst().Find("LIT_Attack1_LG.png");
	LIT_A1_LG->Cut(19, 16);
	GameEngineTexture* HVY_A1_LG = GameEngineTextureManager::GetInst().Find("HVY_Attack1_LG.png");
	HVY_A1_LG->Cut(19, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_A1_RA = GameEngineTextureManager::GetInst().Find("LIT_Attack1_RA.png");
	LIT_A1_RA->Cut(19, 16);
	GameEngineTexture* HVY_A1_RA = GameEngineTextureManager::GetInst().Find("HVY_Attack1_RA.png");
	HVY_A1_RA->Cut(19, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_A1_RH = GameEngineTextureManager::GetInst().Find("LIT_Attack1_RH.png");
	LIT_A1_RH->Cut(19, 16);
	GameEngineTexture* HVY_A1_RH = GameEngineTextureManager::GetInst().Find("HVY_Attack1_RH.png");
	HVY_A1_RH->Cut(19, 16);

	// S1(¿À¸¥¾î±ú)
	GameEngineTexture* LIT_A1_S1 = GameEngineTextureManager::GetInst().Find("LIT_Attack1_S1.png");
	LIT_A1_S1->Cut(19, 16);
	GameEngineTexture* HVY_A1_S1 = GameEngineTextureManager::GetInst().Find("HVY_Attack1_S1.png");
	HVY_A1_S1->Cut(19, 16);

	// S2(¿Þ¾î±ú)
	GameEngineTexture* LIT_A1_S2 = GameEngineTextureManager::GetInst().Find("LIT_Attack1_S2.png");
	LIT_A1_S2->Cut(19, 16);
	GameEngineTexture* HVY_A1_S2 = GameEngineTextureManager::GetInst().Find("HVY_Attack1_S2.png");
	HVY_A1_S2->Cut(19, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_A1_TR = GameEngineTextureManager::GetInst().Find("LIT_Attack1_TR.png");
	LIT_A1_TR->Cut(19, 16);
	GameEngineTexture* HVY_A1_TR = GameEngineTextureManager::GetInst().Find("HVY_Attack1_TR.png");
	HVY_A1_TR->Cut(19, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	GameEngineTexture* HVY_A1_SH = GameEngineTextureManager::GetInst().Find("HVY_Attack1_SH.png");
	HVY_A1_SH->Cut(19, 16);
}

void MainPlayer::AnimationA2Cut()
{
	// ===================================== x : 19, y : 16 ===================================== //

	// HD(¸Ó¸®)
	GameEngineTexture* LIT_A2_HD = GameEngineTextureManager::GetInst().Find("LIT_Attack2_HD.png");
	LIT_A2_HD->Cut(19, 16);
	//GameEngineTexture* HVY_A2_HD = GameEngineTextureManager::GetInst().Find("HVY_Attack2_HD.png");
	//HVY_A2_HD->Cut(19, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_A2_LA = GameEngineTextureManager::GetInst().Find("LIT_Attack2_LA.png");
	LIT_A2_LA->Cut(19, 16);
	//GameEngineTexture* HVY_A2_LA = GameEngineTextureManager::GetInst().Find("HVY_Attack2_LA.png");
	//HVY_A2_LA->Cut(19, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_A2_LG = GameEngineTextureManager::GetInst().Find("LIT_Attack2_LG.png");
	LIT_A2_LG->Cut(19, 16);
	//GameEngineTexture* HVY_A2_LG = GameEngineTextureManager::GetInst().Find("HVY_Attack2_LG.png");
	//HVY_A2_LG->Cut(19, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_A2_RA = GameEngineTextureManager::GetInst().Find("LIT_Attack2_RA.png");
	LIT_A2_RA->Cut(19, 16);
	//GameEngineTexture* HVY_A2_RA = GameEngineTextureManager::GetInst().Find("HVY_Attack2_RA.png");
	//HVY_A2_RA->Cut(19, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_A2_RH = GameEngineTextureManager::GetInst().Find("LIT_Attack2_RH.png");
	LIT_A2_RH->Cut(19, 16);
	//GameEngineTexture* HVY_A2_RH = GameEngineTextureManager::GetInst().Find("HVY_Attack2_RH.png");
	//HVY_A2_RH->Cut(19, 16);

	// S1(¿À¸¥¾î±ú)
	GameEngineTexture* LIT_A2_S1 = GameEngineTextureManager::GetInst().Find("LIT_Attack2_S1.png");
	LIT_A2_S1->Cut(19, 16);
	//GameEngineTexture* HVY_A2_S1 = GameEngineTextureManager::GetInst().Find("HVY_Attack2_S1.png");
	//HVY_A2_S1->Cut(19, 16);

	// S2(¿Þ¾î±ú)
	GameEngineTexture* LIT_A2_S2 = GameEngineTextureManager::GetInst().Find("LIT_Attack2_S2.png");
	LIT_A2_S2->Cut(19, 16);
	//GameEngineTexture* HVY_A2_S2 = GameEngineTextureManager::GetInst().Find("HVY_Attack2_S2.png");
	//HVY_A2_S2->Cut(19, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_A2_TR = GameEngineTextureManager::GetInst().Find("LIT_Attack2_TR.png");
	LIT_A2_TR->Cut(19, 16);
	//GameEngineTexture* HVY_A2_TR = GameEngineTextureManager::GetInst().Find("HVY_Attack2_TR.png");
	//HVY_A2_TR->Cut(19, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	//GameEngineTexture* HVY_A2_SH = GameEngineTextureManager::GetInst().Find("HVY_Attack2_SH.png");
	//HVY_A2_SH->Cut(19, 16);
}

void MainPlayer::AnimationBLCut()
{
	// ===================================== x : 6, y : 16 ===================================== //

	// HD(¸Ó¸®)
	GameEngineTexture* LIT_BL_HD = GameEngineTextureManager::GetInst().Find("LIT_Block_HD.png");
	LIT_BL_HD->Cut(6, 16);
	//GameEngineTexture* HVY_BL_HD = GameEngineTextureManager::GetInst().Find("HVY_Block_HD.png");
	//HVY_BL_HD->Cut(6, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_BL_LA = GameEngineTextureManager::GetInst().Find("LIT_Block_LA.png");
	LIT_BL_LA->Cut(6, 16);
	//GameEngineTexture* HVY_BL_LA = GameEngineTextureManager::GetInst().Find("HVY_Block_LA.png");
	//HVY_BL_LA->Cut(6, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_BL_LG = GameEngineTextureManager::GetInst().Find("LIT_Block_LG.png");
	LIT_BL_LG->Cut(6, 16);
	//GameEngineTexture* HVY_BL_LG = GameEngineTextureManager::GetInst().Find("HVY_Block_LG.png");
	//HVY_BL_LG->Cut(6, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_BL_RA = GameEngineTextureManager::GetInst().Find("LIT_Block_RA.png");
	LIT_BL_RA->Cut(6, 16);
	//GameEngineTexture* HVY_BL_RA = GameEngineTextureManager::GetInst().Find("HVY_Block_RA.png");
	//HVY_BL_RA->Cut(6, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_BL_RH = GameEngineTextureManager::GetInst().Find("LIT_Block_RH.png");
	LIT_BL_RH->Cut(6, 16);
	//GameEngineTexture* HVY_BL_RH = GameEngineTextureManager::GetInst().Find("HVY_Block_RH.png");
	//HVY_BL_RH->Cut(6, 16);

	// S1(¿À¸¥¾î±ú)
	GameEngineTexture* LIT_BL_S1 = GameEngineTextureManager::GetInst().Find("LIT_Block_S1.png");
	LIT_BL_S1->Cut(6, 16);
	//GameEngineTexture* HVY_BL_S1 = GameEngineTextureManager::GetInst().Find("HVY_Block_S1.png");
	//HVY_BL_S1->Cut(6, 16);

	// S2(¿Þ¾î±ú)
	GameEngineTexture* LIT_BL_S2 = GameEngineTextureManager::GetInst().Find("LIT_Block_S2.png");
	LIT_BL_S2->Cut(6, 16);
	//GameEngineTexture* HVY_BL_S2 = GameEngineTextureManager::GetInst().Find("HVY_Block_S2.png");
	//HVY_BL_S2->Cut(6, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_BL_TR = GameEngineTextureManager::GetInst().Find("LIT_Block_TR.png");
	LIT_BL_TR->Cut(6, 16);
	//GameEngineTexture* HVY_BL_TR = GameEngineTextureManager::GetInst().Find("HVY_Block_TR.png");
	//HVY_BL_TR->Cut(6, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	//GameEngineTexture* HVY_BL_SH = GameEngineTextureManager::GetInst().Find("HVY_Block_SH.png");
	//HVY_BL_SH->Cut(6, 16);
}

void MainPlayer::AnimationDDCut()
{
	// ===================================== x : 1, y : 16 ===================================== //

	// TR(¸öÅë)
	GameEngineTexture* LIT_DD_TR = GameEngineTextureManager::GetInst().Find("LIT_Dead_TR.png");
	LIT_DD_TR->Cut(1, 16);
	//GameEngineTexture* HVY_DD_TR = GameEngineTextureManager::GetInst().Find("HVY_Dead_TR.png");
	//HVY_DD_TR->Cut(1, 16);
}

void MainPlayer::AnimationDTCut()
{
	// ===================================== x : 27, y : 16 ===================================== //

	// TR(¸öÅë)
	GameEngineTexture* LIT_DT_TR = GameEngineTextureManager::GetInst().Find("LIT_Death_TR.png");
	LIT_DT_TR->Cut(27, 16);
	//GameEngineTexture* HVY_DT_TR = GameEngineTextureManager::GetInst().Find("HVY_Death_TR.png");
	//HVY_DT_TR->Cut(27, 16);
}

void MainPlayer::AnimationGHCut()
{
	// ===================================== x : 7, y : 16 ===================================== //

	// HD(¸Ó¸®)
	GameEngineTexture* LIT_GH_HD = GameEngineTextureManager::GetInst().Find("LIT_Gethit_HD.png");
	LIT_GH_HD->Cut(7, 16);
	//GameEngineTexture* HVY_GH_HD = GameEngineTextureManager::GetInst().Find("HVY_Gethit_HD.png");
	//HVY_GH_HD->Cut(7, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_GH_LA = GameEngineTextureManager::GetInst().Find("LIT_Gethit_LA.png");
	LIT_GH_LA->Cut(7, 16);
	//GameEngineTexture* HVY_GH_LA = GameEngineTextureManager::GetInst().Find("HVY_Gethit_LA.png");
	//HVY_GH_LA->Cut(7, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_GH_LG = GameEngineTextureManager::GetInst().Find("LIT_Gethit_LG.png");
	LIT_GH_LG->Cut(7, 16);
	//GameEngineTexture* HVY_GH_LG = GameEngineTextureManager::GetInst().Find("HVY_Gethit_LG.png");
	//HVY_GH_LG->Cut(7, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_GH_RA = GameEngineTextureManager::GetInst().Find("LIT_Gethit_RA.png");
	LIT_GH_RA->Cut(7, 16);
	//GameEngineTexture* HVY_GH_RA = GameEngineTextureManager::GetInst().Find("HVY_Gethit_RA.png");
	//HVY_GH_RA->Cut(7, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_GH_RH = GameEngineTextureManager::GetInst().Find("LIT_Gethit_RH.png");
	LIT_GH_RH->Cut(7, 16);
	//GameEngineTexture* HVY_GH_RH = GameEngineTextureManager::GetInst().Find("HVY_Gethit_RH.png");
	//HVY_GH_RH->Cut(7, 16);

	// S1(¿À¸¥¾î±ú)
	GameEngineTexture* LIT_GH_S1 = GameEngineTextureManager::GetInst().Find("LIT_Gethit_S1.png");
	LIT_GH_S1->Cut(7, 16);
	//GameEngineTexture* HVY_GH_S1 = GameEngineTextureManager::GetInst().Find("HVY_Gethit_S1.png");
	//HVY_GH_S1->Cut(7, 16);

	// S2(¿Þ¾î±ú)
	GameEngineTexture* LIT_GH_S2 = GameEngineTextureManager::GetInst().Find("LIT_Gethit_S2.png");
	LIT_GH_S2->Cut(7, 16);
	//GameEngineTexture* HVY_GH_S2 = GameEngineTextureManager::GetInst().Find("HVY_Gethit_S2.png");
	//HVY_GH_S2->Cut(7, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_GH_TR = GameEngineTextureManager::GetInst().Find("LIT_Gethit_TR.png");
	LIT_GH_TR->Cut(7, 16);
	//GameEngineTexture* HVY_GH_TR = GameEngineTextureManager::GetInst().Find("HVY_Gethit_TR.png");
	//HVY_GH_TR->Cut(7, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	//GameEngineTexture* HVY_GH_SH = GameEngineTextureManager::GetInst().Find("HVY_Gethit_SH.png");
	//HVY_GH_SH->Cut(7, 16);
}

void MainPlayer::AnimationKKCut()
{
	// ===================================== x : 12, y : 16 ===================================== //

	// HD(¸Ó¸®)
	GameEngineTexture* LIT_KK_HD = GameEngineTextureManager::GetInst().Find("LIT_Kick_HD.png");
	LIT_KK_HD->Cut(12, 16);
	//GameEngineTexture* HVY_KK_HD = GameEngineTextureManager::GetInst().Find("HVY_Kick_HD.png");
	//HVY_KK_HD->Cut(12, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_KK_LA = GameEngineTextureManager::GetInst().Find("LIT_Kick_LA.png");
	LIT_KK_LA->Cut(12, 16);
	//GameEngineTexture* HVY_KK_LA = GameEngineTextureManager::GetInst().Find("HVY_Kick_LA.png");
	//HVY_KK_LA->Cut(12, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_KK_LG = GameEngineTextureManager::GetInst().Find("LIT_Kick_LG.png");
	LIT_KK_LG->Cut(12, 16);
	//GameEngineTexture* HVY_KK_LG = GameEngineTextureManager::GetInst().Find("HVY_Kick_LG.png");
	//HVY_KK_LG->Cut(12, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_KK_RA = GameEngineTextureManager::GetInst().Find("LIT_Kick_RA.png");
	LIT_KK_RA->Cut(12, 16);
	//GameEngineTexture* HVY_KK_RA = GameEngineTextureManager::GetInst().Find("HVY_Kick_RA.png");
	//HVY_KK_RA->Cut(12, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_KK_RH = GameEngineTextureManager::GetInst().Find("LIT_Kick_RH.png");
	LIT_KK_RH->Cut(12, 16);
	//GameEngineTexture* HVY_KK_RH = GameEngineTextureManager::GetInst().Find("HVY_Kick_RH.png");
	//HVY_KK_RH->Cut(12, 16);

	// S1(¿À¸¥¾î±ú)
	GameEngineTexture* LIT_KK_S1 = GameEngineTextureManager::GetInst().Find("LIT_Kick_S1.png");
	LIT_KK_S1->Cut(12, 16);
	//GameEngineTexture* HVY_KK_S1 = GameEngineTextureManager::GetInst().Find("HVY_Kick_S1.png");
	//HVY_KK_S1->Cut(12, 16);

	// S2(¿Þ¾î±ú)
	GameEngineTexture* LIT_KK_S2 = GameEngineTextureManager::GetInst().Find("LIT_Kick_S2.png");
	LIT_KK_S2->Cut(12, 16);
	//GameEngineTexture* HVY_KK_S2 = GameEngineTextureManager::GetInst().Find("HVY_Kick_S2.png");
	//HVY_KK_S2->Cut(12, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_KK_TR = GameEngineTextureManager::GetInst().Find("LIT_Kick_TR.png");
	LIT_KK_TR->Cut(12, 16);
	//GameEngineTexture* HVY_KK_TR = GameEngineTextureManager::GetInst().Find("HVY_Kick_TR.png");
	//HVY_KK_TR->Cut(12, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	//GameEngineTexture* HVY_KK_SH = GameEngineTextureManager::GetInst().Find("HVY_Kick_SH.png");
	//HVY_KK_SH->Cut(12, 16);
}

void MainPlayer::AnimationNUCut()
{
	// ===================================== x : 8, y : 16 ===================================== //
	
	// HD(¸Ó¸®)
	GameEngineTexture* LIT_NU_HD = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_HD.png");
	LIT_NU_HD->Cut(8, 16);
	//GameEngineTexture* HVY_NU_HD = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_HD.png");
	//HVY_NU_HD->Cut(8, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_NU_LA = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_LA.png");
	LIT_NU_LA->Cut(8, 16);
	//GameEngineTexture* HVY_NU_LA = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_LA.png");
	//HVY_NU_LA->Cut(8, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_NU_LG = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_LG.png");
	LIT_NU_LG->Cut(8, 16);
	//GameEngineTexture* HVY_NU_LG = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_LG.png");
	//HVY_NU_LG->Cut(8, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_NU_RA = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_RA.png");
	LIT_NU_RA->Cut(8, 16);
	//GameEngineTexture* HVY_NU_RA = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_RA.png");
	//HVY_NU_RA->Cut(8, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_NU_RH = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_RH.png");
	LIT_NU_RH->Cut(8, 16);
	//GameEngineTexture* HVY_NU_RH = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_RH.png");
	//HVY_NU_RH->Cut(8, 16);

	// S1(¿À¸¥ÂÊ¾î±ú)
	GameEngineTexture* LIT_NU_S1 = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_S1.png");
	LIT_NU_S1->Cut(8, 16);
	//GameEngineTexture* HVY_NU_S1 = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_S1.png");
	//HVY_NU_S1->Cut(8, 16);

	// S2(¿ÞÂÊ¾î±ú)
	GameEngineTexture* LIT_NU_S2 = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_S2.png");
	LIT_NU_S2->Cut(8, 16);
	//GameEngineTexture* HVY_NU_S2 = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_S2.png");
	//HVY_NU_S2->Cut(8, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_NU_TR = GameEngineTextureManager::GetInst().Find("LIT_Natural_Field_TR.png");
	LIT_NU_TR->Cut(8, 16);
	//GameEngineTexture* HVY_NU_TR = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_TR.png");
	//HVY_NU_TR->Cut(8, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	//GameEngineTexture* HVY_NU_SH = GameEngineTextureManager::GetInst().Find("HVY_Natural_Field_SH.png");
	//HVY_NU_SH->Cut(8, 16);
}

void MainPlayer::AnimationRNCut()
{
	// ===================================== x : 8, y : 16 ===================================== //

	// HD(¸Ó¸®)
	GameEngineTexture* LIT_RN_HD = GameEngineTextureManager::GetInst().Find("LIT_Run_HD.png");
	LIT_RN_HD->Cut(8, 16);
	//GameEngineTexture* HVY_RN_HD = GameEngineTextureManager::GetInst().Find("HVY_Run_HD.png");
	//HVY_RN_HD->Cut(8, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_RN_LA = GameEngineTextureManager::GetInst().Find("LIT_Run_LA.png");
	LIT_RN_LA->Cut(8, 16);
	//GameEngineTexture* HVY_RN_LA = GameEngineTextureManager::GetInst().Find("HVY_Run_LA.png");
	//HVY_RN_LA->Cut(8, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_RN_LG = GameEngineTextureManager::GetInst().Find("LIT_Run_LG.png");
	LIT_RN_LG->Cut(8, 16);
	//GameEngineTexture* HVY_RN_LG = GameEngineTextureManager::GetInst().Find("HVY_Run_LG.png");
	//HVY_RN_LG->Cut(8, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_RN_RA = GameEngineTextureManager::GetInst().Find("LIT_Run_RA.png");
	LIT_RN_RA->Cut(8, 16);
	//GameEngineTexture* HVY_RN_RA = GameEngineTextureManager::GetInst().Find("HVY_Run_RA.png");
	//HVY_RN_RA->Cut(8, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_RN_RH = GameEngineTextureManager::GetInst().Find("LIT_Run_RH.png");
	LIT_RN_RH->Cut(8, 16);
	//GameEngineTexture* HVY_RN_RH = GameEngineTextureManager::GetInst().Find("HVY_Run_RH.png");
	//HVY_RN_RH->Cut(8, 16);

	// S1(¿À¸¥¾î±ú)
	GameEngineTexture* LIT_RN_S1 = GameEngineTextureManager::GetInst().Find("LIT_Run_S1.png");
	LIT_RN_S1->Cut(8, 16);
	//GameEngineTexture* HVY_RN_S1 = GameEngineTextureManager::GetInst().Find("HVY_Run_S1.png");
	//HVY_RN_S1->Cut(8, 16);

	// S2(¿Þ¾î±ú)
	GameEngineTexture* LIT_RN_S2 = GameEngineTextureManager::GetInst().Find("LIT_Run_S2.png");
	LIT_RN_S2->Cut(8, 16);
	//GameEngineTexture* HVY_RN_S2 = GameEngineTextureManager::GetInst().Find("HVY_Run_S2.png");
	//HVY_RN_S2->Cut(8, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_RN_TR = GameEngineTextureManager::GetInst().Find("LIT_Run_TR.png");
	LIT_RN_TR->Cut(8, 16);
	//GameEngineTexture* HVY_RN_TR = GameEngineTextureManager::GetInst().Find("HVY_Run_TR.png");
	//HVY_RN_TR->Cut(8, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	//GameEngineTexture* HVY_RN_SH = GameEngineTextureManager::GetInst().Find("HVY_Run_SH.png");
	//HVY_RN_SH->Cut(8, 16);
}

void MainPlayer::AnimationS1Cut()
{
	// ===================================== x : 16, y : 16 ===================================== //

	// HD(¸Ó¸®)
	GameEngineTexture* LIT_S1_HD = GameEngineTextureManager::GetInst().Find("LIT_Special_Attack_HD.png");
	LIT_S1_HD->Cut(16, 16);
	//GameEngineTexture* HVY_S1_HD = GameEngineTextureManager::GetInst().Find("HVY_Special_Attack_HD.png");
	//HVY_S1_HD->Cut(16, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_S1_LA = GameEngineTextureManager::GetInst().Find("LIT_Special_Attack_LA.png");
	LIT_S1_LA->Cut(16, 16);
	//GameEngineTexture* HVY_S1_LA = GameEngineTextureManager::GetInst().Find("HVY_Special_Attack_LA.png");
	//HVY_S1_LA->Cut(16, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_S1_LG = GameEngineTextureManager::GetInst().Find("LIT_Special_Attack_LG.png");
	LIT_S1_LG->Cut(16, 16);
	//GameEngineTexture* HVY_S1_LG = GameEngineTextureManager::GetInst().Find("HVY_Special_Attack_LG.png");
	//HVY_S1_LG->Cut(16, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_S1_RA = GameEngineTextureManager::GetInst().Find("LIT_Special_Attack_RA.png");
	LIT_S1_RA->Cut(16, 16);
	//GameEngineTexture* HVY_S1_RA = GameEngineTextureManager::GetInst().Find("HVY_Special_Attack_RA.png");
	//HVY_S1_RA->Cut(16, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_S1_RH = GameEngineTextureManager::GetInst().Find("LIT_Special_Attack_RH.png");
	LIT_S1_RH->Cut(16, 16);
	//GameEngineTexture* HVY_S1_RH = GameEngineTextureManager::GetInst().Find("HVY_Special_Attack_RH.png");
	//HVY_S1_RH->Cut(16, 16);

	// S1(¿À¸¥¾î±ú)
	GameEngineTexture* LIT_S1_S1 = GameEngineTextureManager::GetInst().Find("LIT_Special_Attack_S1.png");
	LIT_S1_S1->Cut(16, 16);
	//GameEngineTexture* HVY_S1_S1 = GameEngineTextureManager::GetInst().Find("HVY_Special_Attack_S1.png");
	//HVY_S1_S1->Cut(16, 16);

	// S2(¿Þ¾î±ú)
	GameEngineTexture* LIT_S1_S2 = GameEngineTextureManager::GetInst().Find("LIT_Special_Attack_S2.png");
	LIT_S1_S2->Cut(16, 16);
	//GameEngineTexture* HVY_S1_S2 = GameEngineTextureManager::GetInst().Find("HVY_Special_Attack_S2.png");
	//HVY_S1_S2->Cut(16, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_S1_TR = GameEngineTextureManager::GetInst().Find("LIT_Special_Attack_TR.png");
	LIT_S1_TR->Cut(16, 16);
	//GameEngineTexture* HVY_S1_TR = GameEngineTextureManager::GetInst().Find("HVY_Special_Attack_TR.png");
	//HVY_S1_TR->Cut(16, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	//GameEngineTexture* HVY_S1_SH = GameEngineTextureManager::GetInst().Find("HVY_Special_Attack_SH.png");
	//HVY_S1_SH->Cut(16, 16);
}

void MainPlayer::AnimationSCCut()
{
	// ===================================== x : 16, y : 16 ===================================== //

	// HD(¸Ó¸®)
	GameEngineTexture* LIT_SC_HD = GameEngineTextureManager::GetInst().Find("LIT_Special_Cast_HD.png");
	LIT_SC_HD->Cut(16, 16);
	//GameEngineTexture* HVY_SC_HD = GameEngineTextureManager::GetInst().Find("HVY_Special_Cast_HD.png");
	//HVY_SC_HD->Cut(16, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_SC_LA = GameEngineTextureManager::GetInst().Find("LIT_Special_Cast_LA.png");
	LIT_SC_LA->Cut(16, 16);
	//GameEngineTexture* HVY_SC_LA = GameEngineTextureManager::GetInst().Find("HVY_Special_Cast_LA.png");
	//HVY_SC_LA->Cut(16, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_SC_LG = GameEngineTextureManager::GetInst().Find("LIT_Special_Cast_LG.png");
	LIT_SC_LG->Cut(16, 16);
	//GameEngineTexture* HVY_SC_LG = GameEngineTextureManager::GetInst().Find("HVY_Special_Cast_LG.png");
	//HVY_SC_LG->Cut(16, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_SC_RA = GameEngineTextureManager::GetInst().Find("LIT_Special_Cast_RA.png");
	LIT_SC_RA->Cut(16, 16);
	//GameEngineTexture* HVY_SC_RA = GameEngineTextureManager::GetInst().Find("HVY_Special_Cast_RA.png");
	//HVY_SC_RA->Cut(16, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_SC_RH = GameEngineTextureManager::GetInst().Find("LIT_Special_Cast_RH.png");
	LIT_SC_RH->Cut(16, 16);
	//GameEngineTexture* HVY_SC_RH = GameEngineTextureManager::GetInst().Find("HVY_Special_Cast_RH.png");
	//HVY_SC_RH->Cut(16, 16);

	// S1(¿À¸¥¾î±ú)
	GameEngineTexture* LIT_SC_S1 = GameEngineTextureManager::GetInst().Find("LIT_Special_Cast_S1.png");
	LIT_SC_S1->Cut(16, 16);
	//GameEngineTexture* HVY_SC_S1 = GameEngineTextureManager::GetInst().Find("HVY_Special_Cast_S1.png");
	//HVY_SC_S1->Cut(16, 16);

	// S2(¿Þ¾î±ú)
	GameEngineTexture* LIT_SC_S2 = GameEngineTextureManager::GetInst().Find("LIT_Special_Cast_S2.png");
	LIT_SC_S2->Cut(16, 16);
	//GameEngineTexture* HVY_SC_S2 = GameEngineTextureManager::GetInst().Find("HVY_Special_Cast_S2.png");
	//HVY_SC_S2->Cut(16, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_SC_TR = GameEngineTextureManager::GetInst().Find("LIT_Special_Cast_TR.png");
	LIT_SC_TR->Cut(16, 16);
	//GameEngineTexture* HVY_SC_TR = GameEngineTextureManager::GetInst().Find("HVY_Special_Cast_TR.png");
	//HVY_SC_TR->Cut(16, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	//GameEngineTexture* HVY_SC_SH = GameEngineTextureManager::GetInst().Find("HVY_Special_Cast_SH.png");
	//HVY_SC_SH->Cut(16, 16);
}

void MainPlayer::AnimationTNCut()
{
	// ===================================== x : 16, y : 16 ===================================== //

	// HD(¸Ó¸®)
	GameEngineTexture* LIT_TN_HD = GameEngineTextureManager::GetInst().Find("LIT_Natural_Town_HD.png");
	LIT_TN_HD->Cut(16, 16);
	//GameEngineTexture* HVY_TN_HD = GameEngineTextureManager::GetInst().Find("HVY_Natural_Town_HD.png");
	//HVY_TN_HD->Cut(16, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_TN_LA = GameEngineTextureManager::GetInst().Find("LIT_Natural_Town_LA.png");
	LIT_TN_LA->Cut(16, 16);
	//GameEngineTexture* HVY_TN_LA = GameEngineTextureManager::GetInst().Find("HVY_Natural_Town_LA.png");
	//HVY_TN_LA->Cut(16, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_TN_LG = GameEngineTextureManager::GetInst().Find("LIT_Natural_Town_LG.png");
	LIT_TN_LG->Cut(16, 16);
	//GameEngineTexture* HVY_TN_LG = GameEngineTextureManager::GetInst().Find("HVY_Natural_Town_LG.png");
	//HVY_TN_LG->Cut(16, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_TN_RA = GameEngineTextureManager::GetInst().Find("LIT_Natural_Town_RA.png");
	LIT_TN_RA->Cut(16, 16);
	//GameEngineTexture* HVY_TN_RA = GameEngineTextureManager::GetInst().Find("HVY_Natural_Town_RA.png");
	//HVY_TN_RA->Cut(16, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_TN_RH = GameEngineTextureManager::GetInst().Find("LIT_Natural_Town_RH.png");
	LIT_TN_RH->Cut(16, 16);
	//GameEngineTexture* HVY_TN_RH = GameEngineTextureManager::GetInst().Find("HVY_Natural_Town_RH.png");
	//HVY_TN_RH->Cut(16, 16);

	// S1(¿À¸¥¾î±ú)
	GameEngineTexture* LIT_TN_S1 = GameEngineTextureManager::GetInst().Find("LIT_Natural_Town_S1.png");
	LIT_TN_S1->Cut(16, 16);
	//GameEngineTexture* HVY_TN_S1 = GameEngineTextureManager::GetInst().Find("HVY_Natural_Town_S1.png");
	//HVY_TN_S1->Cut(16, 16);

	// S2(¿Þ¾î±ú)
	GameEngineTexture* LIT_TN_S2 = GameEngineTextureManager::GetInst().Find("LIT_Natural_Town_S2.png");
	LIT_TN_S2->Cut(16, 16);
	//GameEngineTexture* HVY_TN_S2 = GameEngineTextureManager::GetInst().Find("HVY_Natural_Town_S2.png");
	//HVY_TN_S2->Cut(16, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_TN_TR = GameEngineTextureManager::GetInst().Find("LIT_Natural_Town_TR.png");
	LIT_TN_TR->Cut(16, 16);
	//GameEngineTexture* HVY_TN_TR = GameEngineTextureManager::GetInst().Find("HVY_Natural_Town_TR.png");
	//HVY_TN_TR->Cut(16, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	//GameEngineTexture* HVY_TN_SH = GameEngineTextureManager::GetInst().Find("HVY_Natural_Town_SH.png");
	//HVY_TN_SH->Cut(16, 16);
}

void MainPlayer::AnimationTWCut()
{
	// ===================================== x : 8, y : 16 ===================================== //

	// HD(¸Ó¸®)
	GameEngineTexture* LIT_TW_HD = GameEngineTextureManager::GetInst().Find("LIT_Walk_Town_HD.png");
	LIT_TW_HD->Cut(8, 16);
	//GameEngineTexture* HVY_TW_HD = GameEngineTextureManager::GetInst().Find("HVY_Walk_Town_HD.png");
	//HVY_TW_HD->Cut(8, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_TW_LA = GameEngineTextureManager::GetInst().Find("LIT_Walk_Town_LA.png");
	LIT_TW_LA->Cut(8, 16);
	//GameEngineTexture* HVY_TW_LA = GameEngineTextureManager::GetInst().Find("HVY_Walk_Town_LA.png");
	//HVY_TW_LA->Cut(8, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_TW_LG = GameEngineTextureManager::GetInst().Find("LIT_Walk_Town_LG.png");
	LIT_TW_LG->Cut(8, 16);
	//GameEngineTexture* HVY_TW_LG = GameEngineTextureManager::GetInst().Find("HVY_Walk_Town_LG.png");
	//HVY_TW_LG->Cut(8, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_TW_RA = GameEngineTextureManager::GetInst().Find("LIT_Walk_Town_RA.png");
	LIT_TW_RA->Cut(8, 16);
	//GameEngineTexture* HVY_TW_RA = GameEngineTextureManager::GetInst().Find("HVY_Walk_Town_RA.png");
	//HVY_TW_RA->Cut(8, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_TW_RH = GameEngineTextureManager::GetInst().Find("LIT_Walk_Town_RH.png");
	LIT_TW_RH->Cut(8, 16);
	//GameEngineTexture* HVY_TW_RH = GameEngineTextureManager::GetInst().Find("HVY_Walk_Town_RH.png");
	//HVY_TW_RH->Cut(8, 16);

	// S1(¿À¸¥¾î±ú)
	GameEngineTexture* LIT_TW_S1 = GameEngineTextureManager::GetInst().Find("LIT_Walk_Town_S1.png");
	LIT_TW_S1->Cut(8, 16);
	//GameEngineTexture* HVY_TW_S1 = GameEngineTextureManager::GetInst().Find("HVY_Walk_Town_S1.png");
	//HVY_TW_S1->Cut(8, 16);

	// S2(¿Þ¾î±ú)
	GameEngineTexture* LIT_TW_S2 = GameEngineTextureManager::GetInst().Find("LIT_Walk_Town_S2.png");
	LIT_TW_S2->Cut(8, 16);
	//GameEngineTexture* HVY_TW_S2 = GameEngineTextureManager::GetInst().Find("HVY_Walk_Town_S2.png");
	//HVY_TW_S2->Cut(8, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_TW_TR = GameEngineTextureManager::GetInst().Find("LIT_Walk_Town_TR.png");
	LIT_TW_TR->Cut(8, 16);
	//GameEngineTexture* HVY_TW_TR = GameEngineTextureManager::GetInst().Find("HVY_Walk_Town_TR.png");
	//HVY_TW_TR->Cut(8, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	//GameEngineTexture* HVY_TW_SH = GameEngineTextureManager::GetInst().Find("HVY_Walk_Town_SH.png");
	//HVY_TW_SH->Cut(8, 16);
}

void MainPlayer::AnimationWLCut()
{
	// ===================================== x : 8, y : 16 ===================================== //

	// HD(¸Ó¸®)
	GameEngineTexture* LIT_WL_HD = GameEngineTextureManager::GetInst().Find("LIT_Walk_Field_HD.png");
	LIT_WL_HD->Cut(8, 16);
	//GameEngineTexture* HVY_WL_HD = GameEngineTextureManager::GetInst().Find("HVY_Walk_Field_HD.png");
	//HVY_WL_HD->Cut(8, 16);

	// LA(¿ÞÆÈ)
	GameEngineTexture* LIT_WL_LA = GameEngineTextureManager::GetInst().Find("LIT_Walk_Field_LA.png");
	LIT_WL_LA->Cut(8, 16);
	//GameEngineTexture* HVY_WL_LA = GameEngineTextureManager::GetInst().Find("HVY_Walk_Field_LA.png");
	//HVY_WL_LA->Cut(8, 16);

	// LG(´Ù¸®)
	GameEngineTexture* LIT_WL_LG = GameEngineTextureManager::GetInst().Find("LIT_Walk_Field_LG.png");
	LIT_WL_LG->Cut(8, 16);
	//GameEngineTexture* HVY_WL_LG = GameEngineTextureManager::GetInst().Find("HVY_Walk_Field_LG.png");
	//HVY_WL_LG->Cut(8, 16);

	// RA(¿À¸¥ÆÈ)
	GameEngineTexture* LIT_WL_RA = GameEngineTextureManager::GetInst().Find("LIT_Walk_Field_RA.png");
	LIT_WL_RA->Cut(8, 16);
	//GameEngineTexture* HVY_WL_RA = GameEngineTextureManager::GetInst().Find("HVY_Walk_Field_RA.png");
	//HVY_WL_RA->Cut(8, 16);

	// RH(¹«±â)
	GameEngineTexture* LIT_WL_RH = GameEngineTextureManager::GetInst().Find("LIT_Walk_Field_RH.png");
	LIT_WL_RH->Cut(8, 16);
	//GameEngineTexture* HVY_WL_RH = GameEngineTextureManager::GetInst().Find("HVY_Walk_Field_RH.png");
	//HVY_WL_RH->Cut(8, 16);

	// S1(¿À¸¥¾î±ú)
	GameEngineTexture* LIT_WL_S1 = GameEngineTextureManager::GetInst().Find("LIT_Walk_Field_S1.png");
	LIT_WL_S1->Cut(8, 16);
	//GameEngineTexture* HVY_WL_S1 = GameEngineTextureManager::GetInst().Find("HVY_Walk_Field_S1.png");
	//HVY_WL_S1->Cut(8, 16);

	// S2(¿Þ¾î±ú)
	GameEngineTexture* LIT_WL_S2 = GameEngineTextureManager::GetInst().Find("LIT_Walk_Field_S2.png");
	LIT_WL_S2->Cut(8, 16);
	//GameEngineTexture* HVY_WL_S2 = GameEngineTextureManager::GetInst().Find("HVY_Walk_Field_S2.png");
	//HVY_WL_S2->Cut(8, 16);

	// TR(¸öÅë)
	GameEngineTexture* LIT_WL_TR = GameEngineTextureManager::GetInst().Find("LIT_Walk_Field_TR.png");
	LIT_WL_TR->Cut(8, 16);
	//GameEngineTexture* HVY_WL_TR = GameEngineTextureManager::GetInst().Find("HVY_Walk_Field_TR.png");
	//HVY_WL_TR->Cut(8, 16);

	// SH(¹æÆÐ) - LIT_ ÀÏ¶§ ¹æÆÐ¾øÀ½
	//GameEngineTexture* HVY_WL_SH = GameEngineTextureManager::GetInst().Find("HVY_Walk_Field_SH.png");
	//HVY_WL_SH->Cut(8, 16);
}
