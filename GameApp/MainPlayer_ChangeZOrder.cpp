#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

// ���� ���°� �ٲ�ų� ���� �̵������� �ٲ� ȣ��Ǵ� �Լ���, DirectRenderOrder_�� DefaultZOrder_�� ZOrder�� �ʱ� �����Ѵ�.
void MainPlayer::StateAndDirectChangeZOrder()
{
	// ��� ��ǰ� ��ü ����� TR Ÿ�Է������� On �����̹Ƿ� �ٸ� ��Ʈ�� 0���� �����ϰ� TR��Ʈ�� 1�κ����Ѵ�.
	if (PlayerState::STAT_DD == CurState_ || PlayerState::STAT_DT == CurState_)
	{
		int DDAndDTPartCnt = static_cast<int>(PartRenderer_.size());
		for (int i = 0; i < DDAndDTPartCnt; ++i)
		{
			std::map<RendererPartType, bool>::iterator FindIter = IsItemEquipState_.find(static_cast<RendererPartType>(i));
			bool ItemEquipFlag = FindIter->second;
			if (false == ItemEquipFlag) // ������ ������
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
		if (false == ItemEquipFlag) // ������ ������
		{
			float ZOrder = static_cast<float>(DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].DefaultZOrder_[i]);
			PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->GetTransform()->SetZOrder(ZOrder);
		}
		else // ������ ����
		{
			float ZOrder = static_cast<float>(DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].DefaultZOrder_[i]);
			PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->GetTransform()->SetZOrder(ZOrder);
		}
	}
}

// �� �����Ӹ��� �ִϸ��̼� Ư�� �����ӿ� ZOrder�� ����Ǵ����� �Ǵ��Ͽ� ZOrder�� �����Ѵ�.
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
			// Animation Frame�� ZOrder ��ȭ����
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
			// Animation Frame�� ZOrder ��ȭ����
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
			// Animation Frame�� ZOrder ��ȭ����
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
		if (false == ItemEquipFlag) // ������ ������
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
