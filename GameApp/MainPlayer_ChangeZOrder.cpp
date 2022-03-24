#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

// 현재 상태가 바뀌거나 현재 이동방향이 바뀔때 호출되는 함수로, DirectRenderOrder_의 DefaultZOrder_로 ZOrder를 초기 셋팅한다.
void MainPlayer::StateAndDirectChangeZOrder()
{
	// 사망 모션과 시체 모션은 TR 타입렌더러만 On 상태이므로 다른 파트는 0으로 셋팅하고 TR파트만 1로변경한다.
	if (PlayerState::STAT_DD == CurState_ || PlayerState::STAT_DT == CurState_)
	{
		int DDAndDTPartCnt = static_cast<int>(PartRenderer_.size());
		for (int i = 0; i < DDAndDTPartCnt; ++i)
		{
			std::map<RendererPartType, bool>::iterator FindIter = IsItemEquipState_.find(static_cast<RendererPartType>(i));
			bool ItemEquipFlag = FindIter->second;
			if (false == ItemEquipFlag) // 아이템 미착용
			{
				if (RendererPartType::PART_TR != static_cast<RendererPartType>(i))
				{
					PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->GetTransform()->SetZOrder(0);
				}
				else
				{
					PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->GetTransform()->SetZOrder(1);
				}
			}
			else
			{
				if (RendererPartType::PART_TR != static_cast<RendererPartType>(i))
				{
					PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->GetTransform()->SetZOrder(0);
				}
				else
				{
					PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->GetTransform()->SetZOrder(1);
				}
			}
		}
		return;
	}

	int PartCnt = static_cast<int>(PartRenderer_.size());
	for (int i = 0; i < PartCnt; ++i)
	{
		std::map<RendererPartType, bool>::iterator FindIter = IsItemEquipState_.find(static_cast<RendererPartType>(i));
		bool ItemEquipFlag = FindIter->second;
		if (false == ItemEquipFlag) // 아이템 미착용
		{
			float ZOrder = static_cast<float>(DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].DefaultZOrder_[i]);
			PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->GetTransform()->SetZOrder(ZOrder);
		}
		else // 아이템 착용
		{
			float ZOrder = static_cast<float>(DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].DefaultZOrder_[i]);
			PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->GetTransform()->SetZOrder(ZOrder);
		}
	}
}

// 매 프레임마다 애니메이션 특정 프레임에 ZOrder가 변경되는지를 판단하여 ZOrder를 변경한다.
void MainPlayer::AnimationFrameCheckZOrderChange()
{
	switch (CurState_)
	{
		case PlayerState::STAT_A1:
		{
			Attack1ZorderCheckChange();
			break;
		}
		case PlayerState::STAT_A2:
		{
			Attack2ZorderCheckChange();
			break;
		}
		case PlayerState::STAT_BL:
		case PlayerState::STAT_DD:
		case PlayerState::STAT_DT:
		{
			// Animation Frame별 ZOrder 변화없음
			return;
		}
		case PlayerState::STAT_GH:
		{
			GetHitZorderCheckChange();
			break;
		}
		case PlayerState::STAT_KK:
		{
			KickZorderCheckChange();
			break;
		}
		case PlayerState::STAT_NU:
		{
			// Animation Frame별 ZOrder 변화없음
			return;
		}
		case PlayerState::STAT_RN:
		{
			RunZorderCheckChange();
			break;
		}
		case PlayerState::STAT_S1:
		{
			SkillAttackZorderCheckChange();
			break;
		}
		case PlayerState::STAT_SC:
		{
			SkillCastingZorderCheckChange();
			break;
		}
		case PlayerState::STAT_TN:
		{
			TownIdleZorderCheckChange();
			break;
		}
		case PlayerState::STAT_TW:
		case PlayerState::STAT_WL:
		{
			// Animation Frame별 ZOrder 변화없음
			return;
		}
		case PlayerState::STAT_MAX:
		default:
		{
			return;
		}
	}
}

void MainPlayer::Attack1ZorderCheckChange()
{
	// 

	int PartRendererCnt = static_cast<int>(PartRenderer_.size());
	for (int i = 0; i < PartRendererCnt; ++i)
	{
		std::map<RendererPartType, bool>::iterator FindIter = IsItemEquipState_.find(static_cast<RendererPartType>(i));
		bool ItemEquipFlag = FindIter->second;
		if (false == ItemEquipFlag) // 아이템 미착용
		{

		}
		else
		{

		}




	}
}

void MainPlayer::Attack2ZorderCheckChange()
{

}

void MainPlayer::GetHitZorderCheckChange()
{

}

void MainPlayer::KickZorderCheckChange()
{

}

void MainPlayer::RunZorderCheckChange()
{

}

void MainPlayer::SkillAttackZorderCheckChange()
{

}

void MainPlayer::SkillCastingZorderCheckChange()
{

}

void MainPlayer::TownIdleZorderCheckChange()
{

}
