#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

void MainPlayer::CreateStateName()
{
	if (!StateName_.empty())
	{
		StateName_.clear();
	}

	// PlayerState ������ �����ϰ� ��Ī����
	// �ؽ��� ������ ����(SetImage() ȣ��)�� ����ϱ� ���� �̸� ����
	StateName_.push_back("Attack1");
	StateName_.push_back("Attack2");
	StateName_.push_back("Block");
	StateName_.push_back("Dead");
	StateName_.push_back("Death");
	StateName_.push_back("Gethit");
	StateName_.push_back("Kick");
	StateName_.push_back("Natural_Field");
	StateName_.push_back("Run");
	StateName_.push_back("Special_Attack");
	StateName_.push_back("Special_Cast");
	StateName_.push_back("Natural_Town");
	StateName_.push_back("Walk_Town");
	StateName_.push_back("Walk_Field");
}

std::string MainPlayer::ChangeStateCheck(RendererPartType _PartType)
{
	int Index = static_cast<int>(_PartType);

	// �÷��̾ LIT_(�⺻), HVY_(����������) ���� üũ�Ͽ� �ؽ��ĸ��� �����ϰ�,
	std::string EquipStateName = "";
	if (ItemEquipState::TP_HVY == PartRenderer_[Index].ItemEquipState_)
	{
		// ��, PART_SH�� HVY_ �����϶� ȭ�鿡 �������ϹǷ� ON() �Ѵ�.
		if (Index == static_cast<int>(RendererPartType::PART_SH))
		{
			PartRenderer_[Index].Renderer_->On();
		}

		PartRenderer_[Index].ItemEquipState_ = ItemEquipState::TP_HVY;
		EquipStateName = "HVY_";
	}
	else
	{
		// ��, PART_SH�� LIT_ �����϶� ȭ�鿡 �������ʾƾ��ϹǷ� OFF() �Ѵ�.
		if (Index == static_cast<int>(RendererPartType::PART_SH))
		{
			PartRenderer_[Index].Renderer_->Off();
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

			// ��ü��ǻ��� �Ǵ� �����ǻ��¶�� TR�� ������ ��� Off���°� �Ǹ�, �ؽ��ĸ� ���������ʴ´�.
			if ( (PlayerState::STAT_DD == CurState_ && i != static_cast<int>(RendererPartType::PART_TR)) 
				|| (PlayerState::STAT_DT == CurState_ && i != static_cast<int>(RendererPartType::PART_TR)) )
			{
				PartRenderer_[i].Renderer_->Off();
				continue;
			}

			PartRenderer_[i].Renderer_->SetImage(TextureName);
			PartRenderer_[i].Renderer_->GetTransform()->SetLocalScaling(PlayerSize_);
		}
	}
	else // ��Ǻ����� ������ �ؽ��ĸ��� ����ȵǾ��ִ� ��츦 ����Ͽ� �ؽ��ĸ�Ī�� �ٽ� �������ش�.
	{
		ReSettingTextureName();
	}

	// �̵������� ����Ǿ��ٸ�
	if (CurDirect_ != _MoveDir)
	{
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

			PartRenderer_[i].Renderer_->SetChangeAnimation(AnimationName);
		}
	}
}
