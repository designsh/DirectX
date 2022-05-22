#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

#include "InventoryView.h"
#include "InventoryTileBox.h"

void MainPlayer::ChangeAnimation(const std::string& _CurStateName)
{
	bool ChangeFlag = false;

	// ���� ���·� �ִϸ��̼� ����
	for (int i = 0; i < static_cast<int>(RendererPartType::PART_MAX); ++i)
	{
		// �� ������ ������ ���뿩�� �Ǵ�
		std::string AnimationName = "";
		ChangeFlag = ItemEquipCheck(AnimationName, static_cast<RendererPartType>(i));
		if (false == ChangeFlag)
		{
			GameEngineDebug::MsgBoxError("������ ������ �ߴ��� ���ߴ��� Ȯ���� �� �����ϴ�!!!!!");
			return;
		}

		// ������°�
		AnimationName += _CurStateName;

		// ������
		ChangeFlag = RnderPartType(AnimationName, static_cast<RendererPartType>(i));
		if (false == ChangeFlag)
		{
			GameEngineDebug::MsgBoxError("���еǾ��������� ������ ��Ʈ�Դϴ�!!!!!");
			return;
		}

		// ���Ⱚ
		ChangeFlag = RenderDirectCheck(AnimationName);
		if (false == ChangeFlag)
		{
			GameEngineDebug::MsgBoxError("���� �̵������� �߸��� �̵������Դϴ�!!!!!");
			return;
		}

		// LIT_ Ÿ���϶� SH �����Ƿ� Off���°� �Ǹ� HVY_ Ÿ���̵Ǹ� On���·� ��ȯ
		ItemEquipState CurPartItemEquipState = CheckItemEquip(static_cast<RendererPartType>(i));
		if (CurPartItemEquipState == ItemEquipState::TP_LIT && static_cast<RendererPartType>(i) == RendererPartType::PART_SH)
		{
			PartRenderer_[i].Renderer_[static_cast<int>(CurPartItemEquipState)]->Off();
			continue;
		}
		else if (CurPartItemEquipState == ItemEquipState::TP_HVY && static_cast<RendererPartType>(i) == RendererPartType::PART_SH)
		{
			PartRenderer_[i].Renderer_[static_cast<int>(CurPartItemEquipState)]->On();
		}

		// DD / DT �� TR�������� �����ϰ� ��� Off���·� �����ϰ� �ִϸ��̼� ������ �����ʴ´�.
		if ((CurState_ == PlayerState::STAT_DD || CurState_ == PlayerState::STAT_DT) && static_cast<RendererPartType>(i) != RendererPartType::PART_TR)
		{
			PartRenderer_[i].Renderer_[static_cast<int>(CurPartItemEquipState)]->Off();
			continue;
		}
		else
		{
			// LIT_ Ÿ���϶� ���Ⱑ ���������� �Ѵ�(LIT/HVY) Off���·� ��ȯ
			// �κ�â���� wnd / crs ���� ������ �� ���º� On���� ��ȯ��
			if (CurPartItemEquipState == ItemEquipState::TP_LIT && static_cast<RendererPartType>(i) == RendererPartType::PART_RH)
			{
				// �κ�â�� ������ �������¸� üũ
				if (false == InventoryView_->GetInvenCurEquipState(ItemLocType::Inven_Weapon))
				{
					// �����ǿ� ��� ���⵵ �����������϶�
					PartRenderer_[i].Renderer_[static_cast<int>(CurPartItemEquipState)]->Off();
				}
			}
			else
			{
				PartRenderer_[i].Renderer_[static_cast<int>(CurPartItemEquipState)]->On();
			}
		}

		// �ִϸ��̼� ����
		PartRenderer_[i].Renderer_[static_cast<int>(CurPartItemEquipState)]->SetChangeAnimation(AnimationName);

		// ũ�� ����
		PartRenderer_[i].Renderer_[static_cast<int>(CurPartItemEquipState)]->GetTransform()->SetLocalScaling(RenderSize_);
	}
}

bool MainPlayer::ItemEquipCheck(std::string& _AnimationName, RendererPartType _PartType)
{
	// IsItemEquipState_ ���� ������ ������� üũ
	// �� ������ ������ Ÿ���� üũ�Ͽ� ������ string�� �̾���δ�.
	// Ex) LIT_, HVY_
	ItemEquipState CurPartItemEquipState = CheckItemEquip(_PartType);
	if (CurPartItemEquipState == ItemEquipState::TP_LIT)
	{
		_AnimationName += "LIT_";
	}
	else if(CurPartItemEquipState == ItemEquipState::TP_HVY)
	{
		_AnimationName += "HVY_";
	}
	else
	{
		return false;
	}


	return true;
}

bool MainPlayer::RnderPartType(std::string& _AnimationName, RendererPartType _PartType)
{
	// �� ������ �ؽ�Ʈ�� �����Ͽ� ���ڷ� ������ string�� �̾���δ�.
	// Ex) _HD_, _LA_, ...
	switch (_PartType)
	{
		case RendererPartType::PART_HD:
		{
			_AnimationName += "_HD_";
			break;
		}
		case RendererPartType::PART_LA:
		{
			_AnimationName += "_LA_";
			break;
		}
		case RendererPartType::PART_LG:
		{
			_AnimationName += "_LG_";
			break;
		}
		case RendererPartType::PART_RA:
		{
			_AnimationName += "_RA_";
			break;
		}
		case RendererPartType::PART_RH:
		{
			_AnimationName += "_RH_";
			break;
		}
		case RendererPartType::PART_S1:
		{
			_AnimationName += "_S1_";
			break;
		}
		case RendererPartType::PART_S2:
		{
			_AnimationName += "_S2_";
			break;
		}
		case RendererPartType::PART_SH:
		{
			_AnimationName += "_SH_";
			break;
		}
		case RendererPartType::PART_TR:
		{
			_AnimationName += "_TR_";
			break;
		}
		case RendererPartType::PART_MAX:
		default:
		{
			return false;
		}
	}

	return true;
}

bool MainPlayer::RenderDirectCheck(std::string& _AnimationName)
{
	// ���� ���� üũ
	switch (CurDirect_)
	{
		case TargetDirect::DIR_LB:
		{
			_AnimationName += "LB";
			break;
		}
		case TargetDirect::DIR_LT:
		{
			_AnimationName += "LT";
			break;
		}
		case TargetDirect::DIR_RT:
		{
			_AnimationName += "RT";
			break;
		}
		case TargetDirect::DIR_RB:
		{
			_AnimationName += "RB";
			break;
		}
		case TargetDirect::DIR_B:
		{
			_AnimationName += "B";
			break;
		}
		case TargetDirect::DIR_L:
		{
			_AnimationName += "L";
			break;
		}
		case TargetDirect::DIR_T:
		{
			_AnimationName += "T";
			break;
		}
		case TargetDirect::DIR_R:
		{
			_AnimationName += "R";
			break;
		}
		case TargetDirect::DIR_MAX:
		default:
		{
			return false;
		}
	}

	return true;
}

// �� �ִϸ��̼� ���� ���� ȣ�� �Լ�
void MainPlayer::Attack1AnimationEnd()
{
	// �����·� ��ȯ
	ChangeFSMState("Natural_Field");
}

void MainPlayer::Attack2AnimationEnd()
{
	// �����·� ��ȯ
	ChangeFSMState("Natural_Field");
}

void MainPlayer::BlockAnimationEnd()
{
	// �����·� ��ȯ
	ChangeFSMState("Natural_Field");
}

void MainPlayer::DeathAnimationEnd()
{
	// �����·� ��ȯ
	ChangeFSMState("Natural_Field");
}

void MainPlayer::GetHitAnimationEnd()
{
	// �����·� ��ȯ
	ChangeFSMState("Natural_Field");
}

void MainPlayer::KickAnimationEnd()
{
	// �����·� ��ȯ
	ChangeFSMState("Natural_Field");
}

void MainPlayer::SkillAttackAnimationEnd()
{
	// �����·� ��ȯ
	ChangeFSMState("Natural_Field");
}

void MainPlayer::SkillCastingAnimationEnd()
{
	// �����·� ��ȯ
	ChangeFSMState("Natural_Field");
}

