#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

std::string MainPlayer::ChangeStateCheck(RendererPartType _PartType)
{
	int Index = static_cast<int>(_PartType);

	// �÷��̾ �� ������ ������ ���뿩�ο� ���� �ִϸ��̼� �� �̹��� �̸��� ��������.
	std::string EquipStateName = "";

	// �ش� ������ ������ �������̶��
	if (ItemEquipState::TP_HVY == PartRenderer_[Index].ItemEquipState_)
	{
		// �ش� ������ ������ �������̱⶧���� ������ ������ ������ off ���·� ��ȯ�Ǹ�,
		// �ش� Ÿ���� �������� on���·� ��ȯ
		PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->Off();
		PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->On();

		// ��, LIT_ �϶� PART_SH �� OFF �����̹Ƿ� ON���·� �����Ѵ�.
		if (_PartType == RendererPartType::PART_SH)
		{
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->On();
		}

		PartRenderer_[Index].ItemEquipState_ = ItemEquipState::TP_HVY;
		EquipStateName = "HVY_";
	}
	else // �ش� ������ ������ ���������̶��
	{
		// �ش� ������ ������ ���������̱⶧���� ������ ���� ������ off���·� ��ȯ�Ǹ�,
		// �ش� Ÿ���� �������� on���� ��ȯ
		PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->On();
		PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->Off();

		// ��, LIT_ �϶� PART_SH �� OFF ����
		if (_PartType == RendererPartType::PART_SH)
		{
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->Off();
		}

		PartRenderer_[Index].ItemEquipState_ = ItemEquipState::TP_LIT;
		EquipStateName = "LIT_";
	}
	
	// �����Ϸ��� ��ǻ���
	std::string StateName = StateName_[static_cast<int>(CurState_)];
	StateName += "_";

	// ������ �ؽ���
	std::string TextureName = "";
	TextureName += EquipStateName;
	TextureName += StateName;
	switch (static_cast<RendererPartType>(Index))
	{
		case RendererPartType::PART_HD:
		{
			TextureName += "HD";
			break;
		}
		case RendererPartType::PART_LA:
		{
			TextureName += "LA";
			break;
		}
		case RendererPartType::PART_LG:
		{
			TextureName += "LG";
			break;
		}
		case RendererPartType::PART_RA:
		{
			TextureName += "RA";
			break;
		}
		case RendererPartType::PART_RH:
		{
			TextureName += "RH";
			break;
		}
		case RendererPartType::PART_S1:
		{
			TextureName += "S1";
			break;
		}
		case RendererPartType::PART_S2:
		{
			TextureName += "S2";
			break;
		}
		case RendererPartType::PART_SH:
		{
			TextureName += "SH";
			break;
		}
		case RendererPartType::PART_TR:
		{
			TextureName += "TR";
			break;
		}
	}
	
	// .png ���̱��� �ؽ��� �̸��� ���� �� �ٿ��� �����Ѵ�.
	PartRenderer_[Index].TextureName_ = TextureName;
	TextureName += ".png";

	return TextureName;
}

void MainPlayer::ReSettingTextureName()
{
	// ��Ǻ����� ���� Texture��Ī�� �������� ���� ��츦 ����Ͽ� �ؽ��ĸ��� �ٽ� �����Ѵ�.
	for (int i = 0; i < static_cast<int>(RendererPartType::PART_MAX); ++i)
	{
		std::string ChkTextureName = "";
		if (ItemEquipState::TP_HVY == PartRenderer_[i].ItemEquipState_)
		{
			ChkTextureName = "HVY_";
		}
		else
		{
			ChkTextureName = "LIT_";
		}

		ChkTextureName += StateName_[static_cast<int>(CurState_)];
		ChkTextureName += "_";

		switch (static_cast<RendererPartType>(i))
		{
			case RendererPartType::PART_HD:
			{
				ChkTextureName += "HD";
				break;
			}
			case RendererPartType::PART_LA:
			{
				ChkTextureName += "LA";
				break;
			}
			case RendererPartType::PART_LG:
			{
				ChkTextureName += "LG";
				break;
			}
			case RendererPartType::PART_RA:
			{
				ChkTextureName += "RA";
				break;
			}
			case RendererPartType::PART_RH:
			{
				ChkTextureName += "RH";
				break;
			}
			case RendererPartType::PART_S1:
			{
				ChkTextureName += "S1";
				break;
			}
			case RendererPartType::PART_S2:
			{
				ChkTextureName += "S2";
				break;
			}
			case RendererPartType::PART_SH:
			{
				ChkTextureName += "SH";
				break;
			}
			case RendererPartType::PART_TR:
			{
				ChkTextureName += "TR";
				break;
			}
		}

		PartRenderer_[i].TextureName_ = ChkTextureName;
	}
}

std::string MainPlayer::ChangeDirectCheck(RendererPartType _PartType)
{
	int Index = static_cast<int>(_PartType);

	// �ִϸ��̼Ǹ�Ī : TextureName_ + �̵�����
	std::string AnimationName = PartRenderer_[Index].TextureName_;
	switch (CurDirect_)
	{
		case TargetDirect::DIR_LB:
		{
			AnimationName += "_LB";
			break;
		}
		case TargetDirect::DIR_LT:
		{
			AnimationName += "_LT";
			break;
		}
		case TargetDirect::DIR_RT:
		{
			AnimationName += "_RT";
			break;
		}
		case TargetDirect::DIR_RB:
		{
			AnimationName += "_RB";
			break;
		}
		case TargetDirect::DIR_B:
		{
			AnimationName += "_B";
			break;
		}
		case TargetDirect::DIR_L:
		{
			AnimationName += "_L";
			break;
		}
		case TargetDirect::DIR_T:
		{
			AnimationName += "_T";
			break;
		}
		case TargetDirect::DIR_R:
		{
			AnimationName += "_R";
			break;
		}
	}

	PartRenderer_[Index].AnimationName_ = AnimationName;

	return AnimationName;
}

void MainPlayer::ChangePlayerAnimation(PlayerState _ChangeState, TargetDirect _MoveDir)
{
	// ���¿� �ִϸ��̼�, �ؽ��� ������ ��� �����ϴ� ���

	// ��ǻ��°� ����Ǿ��ٸ�
	if (CurState_ != _ChangeState)
	{
		PrevState_ = CurState_;
		CurState_ = _ChangeState;

		// �� ������ ������ �������, ���� �����ϴ� ��ǻ���, ������ ����Ͽ� �ؽ��� �̸� �� �ִϸ��̼Ǹ��� ����
		for (int i = 0; i < static_cast<int>(RendererPartType::PART_MAX); ++i)
		{
			std::string TextureName = ChangeStateCheck(static_cast<RendererPartType>(i));

			// �ش� �������� LIT_ Ÿ���϶� SH ��Ʈ�� �����Ѵ�.
			if (ItemEquipState::TP_LIT == PartRenderer_[i].ItemEquipState_ && i == static_cast<int>(RendererPartType::PART_SH))
			{
				continue;
			}

			// ��ü��ǻ��� �Ǵ� �����ǻ��¶�� TR�� ������ ��� Off���°� �Ǹ�, TR�� ������ ��� �ؽ��ĸ� ���������ʴ´�.
			if ( (PlayerState::STAT_DD == CurState_ && i != static_cast<int>(RendererPartType::PART_TR)) 
				|| (PlayerState::STAT_DT == CurState_ && i != static_cast<int>(RendererPartType::PART_TR)) )
			{
				PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->Off();
				PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->Off();
				continue;
			}

			// ������ or ��ü����� �ƴ϶�� ��� �������� On���·� ��ȯ
			// ��, �ش� ���� �������� ������ ���뿩�ο� ���� On���·� ��ȯ�Ǵ� �������� ���Ѵ�.
			if ((PlayerState::STAT_DD != CurState_) || (PlayerState::STAT_DT != CurState_))
			{
				if (PartRenderer_[i].ItemEquipState_ == ItemEquipState::TP_HVY)
				{
					PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->On();
				}
				else
				{
					PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->On();
				}
			}

			// ������ ���� / ������ ������ Ÿ�Կ� ���� ����
			if (ItemEquipState::TP_HVY == PartRenderer_[i].ItemEquipState_)
			{
				//PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->SetImage(TextureName);
				PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->GetTransform()->SetLocalScaling(PlayerSize_);
			}
			else
			{
				//PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->SetImage(TextureName);
				PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->GetTransform()->SetLocalScaling(PlayerSize_);
			}
		}
	}
	else // ��Ǻ����� ������ �ؽ��ĸ��� ����ȵǾ��ִ� ��츦 ����Ͽ� �ؽ��ĸ�Ī�� �ٽ� �������ش�.
	{
		ReSettingTextureName();
	}

	// �̵������� ����Ǿ��ٸ�
	PrevDirect_ = CurDirect_;
	CurDirect_ = _MoveDir;

	for (int i = 0; i < static_cast<int>(RendererPartType::PART_MAX); ++i)
	{
		std::string AnimationName = ChangeDirectCheck(static_cast<RendererPartType>(i));

		// �ش� �������� LIT_ Ÿ���϶� SH ��Ʈ�� �����Ѵ�.
		if (ItemEquipState::TP_LIT == PartRenderer_[i].ItemEquipState_ && i == static_cast<int>(RendererPartType::PART_SH))
		{
			continue;
		}

		// ��ü��ǻ��� �Ǵ� �����ǻ��¶�� TR�� ������ ��� Off���°� �Ǹ�, �ִϸ��̼��� ���������ʴ´�.
		if ((PlayerState::STAT_DD == CurState_ && i != static_cast<int>(RendererPartType::PART_TR))
			|| (PlayerState::STAT_DT == CurState_ && i != static_cast<int>(RendererPartType::PART_TR)))
		{
			continue;
		}

		// ������ ���� / ������ ������ Ÿ�Կ� ���� ����
		if (ItemEquipState::TP_HVY == PartRenderer_[i].ItemEquipState_)
		{
			PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->SetChangeAnimation(AnimationName);
		}
		else
		{
			PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->SetChangeAnimation(AnimationName);
		}
	}
}
