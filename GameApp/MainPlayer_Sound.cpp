#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngineBase/GameEngineSoundPlayer.h>

#pragma region 음성관련
void MainPlayer::PlayerSpeechIcant()
{
	SpeechSound_->PlayAlone("Nec_Icant.wav", 0);
}

#pragma endregion

#pragma region 아이템관련
void MainPlayer::ItemEquipOnSound(const std::string& _ItemName)
{
	// 장착아이템별 사운드 재생

	// 헬름
	if (std::string::npos != _ItemName.find("bhm"))
	{
		ItemSound_->PlayAlone("helm.wav", 0);
	}

	// 크리스탈 소드(무기)
	if (std::string::npos != _ItemName.find("crs"))
	{
		ItemSound_->PlayAlone("sword.wav", 0);
	}

	// 완드(무기)
	if (std::string::npos != _ItemName.find("wnd"))
	{
		ItemSound_->PlayAlone("wand.wav", 0);
	}

	// 방패
	if (std::string::npos != _ItemName.find("bsh"))
	{
		ItemSound_->PlayAlone("metalshield.wav", 0);
	}

	// 갑옷
	if (std::string::npos != _ItemName.find("chn"))
	{
		ItemSound_->PlayAlone("chainarmor.wav", 0);
	}

	// 벨트
	if (std::string::npos != _ItemName.find("tbl"))
	{
		ItemSound_->PlayAlone("belt.wav", 0);
	}

	// 장갑
	if (std::string::npos != _ItemName.find("tgl"))
	{
		ItemSound_->PlayAlone("glovesmetal.wav", 0);
	}

	// 부츠
	if (std::string::npos != _ItemName.find("hbt"))
	{
		ItemSound_->PlayAlone("bootsmetal.wav", 0);
	}

	// 포션
	if (std::string::npos != _ItemName.find("vpl"))
	{
		ItemSound_->PlayAlone("potion.wav", 0);
	}

	// 스크롤
	if (std::string::npos != _ItemName.find("bsc"))
	{
		ItemSound_->PlayAlone("scroll.wav", 0);
	}
	if (std::string::npos != _ItemName.find("chm"))
	{
		ItemSound_->PlayAlone("scroll.wav", 0);
	}
}

void MainPlayer::ItemEquipOffSound()
{
	ItemSound_->PlayAlone("ItemPickup.wav", 0);
}

void MainPlayer::PortionDrink()
{
	ItemSound_->PlayAlone("Potiondrink.wav", 0);
}

#pragma endregion
