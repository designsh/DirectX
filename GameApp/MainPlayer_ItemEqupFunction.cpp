#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

ItemEquipState MainPlayer::CheckItemEquip(RendererPartType _PlayerPart)
{
	// Flag On ���¸� �������� �������ΰ��̴�.
	std::map<RendererPartType, bool>::iterator FindIter = IsItemEquipState_.find(_PlayerPart);
	if (true == (*FindIter).second)
	{
		return ItemEquipState::TP_HVY;
	}

	return ItemEquipState::TP_LIT;
}

void MainPlayer::ItemPutOn(ItemEquipPart _ItemPart)
{
	// ������ �������� ���� �� ������ ���� Flag On
	switch (_ItemPart)
	{
		case ItemEquipPart::Inv_Helm:	// HD Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator HD = IsItemEquipState_.find(RendererPartType::PART_HD);
			(*HD).second = true;
			break;
		}
		case ItemEquipPart::Inv_Armor:	// S1, S2, TR Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator S1 = IsItemEquipState_.find(RendererPartType::PART_S1);
			(*S1).second = true;

			std::map<RendererPartType, bool>::iterator S2 = IsItemEquipState_.find(RendererPartType::PART_S2);
			(*S2).second = true;

			std::map<RendererPartType, bool>::iterator TR = IsItemEquipState_.find(RendererPartType::PART_TR);
			(*TR).second = true;
			break;
		}
		case ItemEquipPart::Inv_Gloves:	// LA, RA Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator LA = IsItemEquipState_.find(RendererPartType::PART_LA);
			(*LA).second = true;

			std::map<RendererPartType, bool>::iterator RA = IsItemEquipState_.find(RendererPartType::PART_RA);
			(*RA).second = true;
			break;
		}
		case ItemEquipPart::Inv_Boots:	// LG Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator LG = IsItemEquipState_.find(RendererPartType::PART_LG);
			(*LG).second = true;
			break;
		}
		case ItemEquipPart::Inv_Weapon:	// RH Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator RH = IsItemEquipState_.find(RendererPartType::PART_RH);
			(*RH).second = true;
			break;
		}
		case ItemEquipPart::Inv_Shield:	// SH Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator SH = IsItemEquipState_.find(RendererPartType::PART_SH);
			(*SH).second = true;
			break;
		}
	}

	//
	ChangeAnimation(State_.GetCurStateName());

	// ������ ������ ������ ������Ʈ �� ZOrder������Ʈ
	ChangeCheckProcess();
	StateAndDirectChangeZOrder();
}

void MainPlayer::ItemPutOff(ItemEquipPart _ItemPart)
{
	// ������ �������� ���� �� ������ ���� Flag Off
	switch (_ItemPart)
	{
		case ItemEquipPart::Inv_Helm:	// HD ��Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator HD = IsItemEquipState_.find(RendererPartType::PART_HD);
			(*HD).second = false;
			break;
		}
		case ItemEquipPart::Inv_Armor:	// S1, S2, TR ��Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator S1 = IsItemEquipState_.find(RendererPartType::PART_S1);
			(*S1).second = false;

			std::map<RendererPartType, bool>::iterator S2 = IsItemEquipState_.find(RendererPartType::PART_S2);
			(*S2).second = false;

			std::map<RendererPartType, bool>::iterator TR = IsItemEquipState_.find(RendererPartType::PART_TR);
			(*TR).second = false;
			break;
		}
		case ItemEquipPart::Inv_Gloves:	// LA, RA ��Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator LA = IsItemEquipState_.find(RendererPartType::PART_LA);
			(*LA).second = false;

			std::map<RendererPartType, bool>::iterator RA = IsItemEquipState_.find(RendererPartType::PART_RA);
			(*RA).second = false;
			break;
		}
		case ItemEquipPart::Inv_Boots:	// LG ��Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator LG = IsItemEquipState_.find(RendererPartType::PART_LG);
			(*LG).second = false;
			break;
		}
		case ItemEquipPart::Inv_Weapon:	// RH ��Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator RH = IsItemEquipState_.find(RendererPartType::PART_RH);
			(*RH).second = false;
			break;
		}
		case ItemEquipPart::Inv_Shield:	// SH ��Ȱ��ȭ
		{
			std::map<RendererPartType, bool>::iterator SH = IsItemEquipState_.find(RendererPartType::PART_SH);
			(*SH).second = false;
			break;
		}
	}

	//
	ChangeAnimation(State_.GetCurStateName());

	// ������ ���������� ������ ������Ʈ �� ZOrder������Ʈ
	ChangeCheckProcess();
	StateAndDirectChangeZOrder();
}
