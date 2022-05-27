#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngineBase/GameEngineSoundPlayer.h>

#pragma region ��������
void MainPlayer::PlayerSpeechIcant()
{
	SpeechSound_->PlayAlone("Nec_Icant.wav", 0);
}

#pragma endregion

#pragma region �����۰���
void MainPlayer::ItemEquipOnSound(const std::string& _ItemName)
{
	// ���������ۺ� ���� ���

	// �︧
	if (std::string::npos != _ItemName.find("bhm"))
	{
		ItemSound_->PlayAlone("helm.wav", 0);
	}

	// ũ����Ż �ҵ�(����)
	if (std::string::npos != _ItemName.find("crs"))
	{
		ItemSound_->PlayAlone("sword.wav", 0);
	}

	// �ϵ�(����)
	if (std::string::npos != _ItemName.find("wnd"))
	{
		ItemSound_->PlayAlone("wand.wav", 0);
	}

	// ����
	if (std::string::npos != _ItemName.find("bsh"))
	{
		ItemSound_->PlayAlone("metalshield.wav", 0);
	}

	// ����
	if (std::string::npos != _ItemName.find("chn"))
	{
		ItemSound_->PlayAlone("chainarmor.wav", 0);
	}

	// ��Ʈ
	if (std::string::npos != _ItemName.find("tbl"))
	{
		ItemSound_->PlayAlone("belt.wav", 0);
	}

	// �尩
	if (std::string::npos != _ItemName.find("tgl"))
	{
		ItemSound_->PlayAlone("glovesmetal.wav", 0);
	}

	// ����
	if (std::string::npos != _ItemName.find("hbt"))
	{
		ItemSound_->PlayAlone("bootsmetal.wav", 0);
	}

	// ����
	if (std::string::npos != _ItemName.find("vpl"))
	{
		ItemSound_->PlayAlone("potion.wav", 0);
	}

	// ��ũ��
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
