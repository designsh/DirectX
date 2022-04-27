#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

ItemEquipState MainPlayer::CheckItemEquip(RendererPartType _PlayerPart)
{
	// Flag On 상태면 아이템을 착용중인것이다.
	std::map<RendererPartType, bool>::iterator FindIter = IsItemEquipState_.find(_PlayerPart);
	if (true == (*FindIter).second)
	{
		return ItemEquipState::TP_HVY;
	}

	return ItemEquipState::TP_LIT;
}

void MainPlayer::ItemPutOn(ItemEquipPart _ItemPart)
{
	// 아이템 장착으로 인한 각 부위별 상태 Flag On
	switch (_ItemPart)
	{
		case ItemEquipPart::Inv_Helm:	// HD 활성화
		{
			std::map<RendererPartType, bool>::iterator HD = IsItemEquipState_.find(RendererPartType::PART_HD);
			(*HD).second = true;
			break;
		}
		case ItemEquipPart::Inv_Armor:	// S1, S2, TR 활성화
		{
			std::map<RendererPartType, bool>::iterator S1 = IsItemEquipState_.find(RendererPartType::PART_S1);
			(*S1).second = true;

			std::map<RendererPartType, bool>::iterator S2 = IsItemEquipState_.find(RendererPartType::PART_S2);
			(*S2).second = true;

			std::map<RendererPartType, bool>::iterator TR = IsItemEquipState_.find(RendererPartType::PART_TR);
			(*TR).second = true;
			break;
		}
		case ItemEquipPart::Inv_Gloves:	// LA, RA 활성화
		{
			std::map<RendererPartType, bool>::iterator LA = IsItemEquipState_.find(RendererPartType::PART_LA);
			(*LA).second = true;

			std::map<RendererPartType, bool>::iterator RA = IsItemEquipState_.find(RendererPartType::PART_RA);
			(*RA).second = true;
			break;
		}
		case ItemEquipPart::Inv_Boots:	// LG 활성화
		{
			std::map<RendererPartType, bool>::iterator LG = IsItemEquipState_.find(RendererPartType::PART_LG);
			(*LG).second = true;
			break;
		}
		case ItemEquipPart::Inv_Weapon:	// RH 활성화
		{
			std::map<RendererPartType, bool>::iterator RH = IsItemEquipState_.find(RendererPartType::PART_RH);
			(*RH).second = true;
			break;
		}
		case ItemEquipPart::Inv_Shield:	// SH 활성화
		{
			std::map<RendererPartType, bool>::iterator SH = IsItemEquipState_.find(RendererPartType::PART_SH);
			(*SH).second = true;
			break;
		}
	}

	//
	ChangeAnimation(State_.GetCurStateName());

	// 아이템 장착시 렌더러 업데이트 및 ZOrder업데이트
	ChangeCheckProcess();
	StateAndDirectChangeZOrder();
}

void MainPlayer::ItemPutOff(ItemEquipPart _ItemPart)
{
	// 아이템 장착으로 인한 각 부위별 상태 Flag Off
	switch (_ItemPart)
	{
		case ItemEquipPart::Inv_Helm:	// HD 비활성화
		{
			std::map<RendererPartType, bool>::iterator HD = IsItemEquipState_.find(RendererPartType::PART_HD);
			(*HD).second = false;
			break;
		}
		case ItemEquipPart::Inv_Armor:	// S1, S2, TR 비활성화
		{
			std::map<RendererPartType, bool>::iterator S1 = IsItemEquipState_.find(RendererPartType::PART_S1);
			(*S1).second = false;

			std::map<RendererPartType, bool>::iterator S2 = IsItemEquipState_.find(RendererPartType::PART_S2);
			(*S2).second = false;

			std::map<RendererPartType, bool>::iterator TR = IsItemEquipState_.find(RendererPartType::PART_TR);
			(*TR).second = false;
			break;
		}
		case ItemEquipPart::Inv_Gloves:	// LA, RA 비활성화
		{
			std::map<RendererPartType, bool>::iterator LA = IsItemEquipState_.find(RendererPartType::PART_LA);
			(*LA).second = false;

			std::map<RendererPartType, bool>::iterator RA = IsItemEquipState_.find(RendererPartType::PART_RA);
			(*RA).second = false;
			break;
		}
		case ItemEquipPart::Inv_Boots:	// LG 비활성화
		{
			std::map<RendererPartType, bool>::iterator LG = IsItemEquipState_.find(RendererPartType::PART_LG);
			(*LG).second = false;
			break;
		}
		case ItemEquipPart::Inv_Weapon:	// RH 비활성화
		{
			std::map<RendererPartType, bool>::iterator RH = IsItemEquipState_.find(RendererPartType::PART_RH);
			(*RH).second = false;
			break;
		}
		case ItemEquipPart::Inv_Shield:	// SH 비활성화
		{
			std::map<RendererPartType, bool>::iterator SH = IsItemEquipState_.find(RendererPartType::PART_SH);
			(*SH).second = false;
			break;
		}
	}

	//
	ChangeAnimation(State_.GetCurStateName());

	// 아이템 장착해제시 렌더러 업데이트 및 ZOrder업데이트
	ChangeCheckProcess();
	StateAndDirectChangeZOrder();
}
