#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

void MainPlayer::CreateStateName()
{
	if (!StateName_.empty())
	{
		StateName_.clear();
	}

	// PlayerState 순서와 동일하게 명칭관리
	// 텍스쳐 정보를 변경(SetImage() 호출)시 사용하기 위해 미리 저장
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

	// 플레이어가 LIT_(기본), HVY_(아이템착용) 인지 체크하여 텍스쳐명을 편집하고,
	std::string EquipStateName = "";
	if (ItemEquipState::TP_HVY == PartRenderer_[Index].ItemEquipState_)
	{
		// 단, PART_SH는 HVY_ 상태일때 화면에 보여야하므로 ON() 한다.
		if (Index == static_cast<int>(RendererPartType::PART_SH))
		{
			PartRenderer_[Index].Renderer_->On();
		}

		PartRenderer_[Index].ItemEquipState_ = ItemEquipState::TP_HVY;
		EquipStateName = "HVY_";
	}
	else
	{
		// 단, PART_SH는 LIT_ 상태일때 화면에 보이지않아야하므로 OFF() 한다.
		if (Index == static_cast<int>(RendererPartType::PART_SH))
		{
			PartRenderer_[Index].Renderer_->Off();
		}

		PartRenderer_[Index].ItemEquipState_ = ItemEquipState::TP_LIT;
		EquipStateName = "LIT_";
	}

	// 변경하려는 모션상태
	std::string StateName = StateName_[static_cast<int>(CurState_)];
	StateName += "_";

	// 부위별 텍스쳐
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
	
	// .png 붙이기전 텍스쳐 이름을 저장 후 붙여서 리턴한다.
	PartRenderer_[Index].TextureName_ = TextureName;
	TextureName += ".png";

	return TextureName;
}

void MainPlayer::ReSettingTextureName()
{
	// 모션변경이 없어 Texture명칭이 정해지지 않은 경우를 대비하여 텍스쳐명을 다시 셋팅한다.
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

	// 애니메이션명칭 : TextureName_ + 이동방향
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
	// 상태와 애니메이션, 텍스쳐 정보를 모두 변경하는 기능

	// 모션상태가 변경되었다면
	if (CurState_ != _ChangeState)
	{
		PrevState_ = CurState_;
		CurState_ = _ChangeState;

		// 각 부위별 아이템 착용상태, 현재 변경하는 모션상태, 방향을 고려하여 텍스쳐 이름 및 애니메이션명을 도출
		for (int i = 0; i < static_cast<int>(RendererPartType::PART_MAX); ++i)
		{
			std::string TextureName = ChangeStateCheck(static_cast<RendererPartType>(i));

			// 해당 렌더러가 LIT_ 타입일때 SH 파트는 제외한다.
			if (ItemEquipState::TP_LIT == PartRenderer_[i].ItemEquipState_ && i == static_cast<int>(RendererPartType::PART_SH))
			{
				continue;
			}

			// 시체모션상태 또는 사망모션상태라면 TR을 제외한 모두 Off상태가 되며, 텍스쳐를 셋팅하지않는다.
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
	else // 모션변경이 없을때 텍스쳐명이 저장안되어있는 경우를 대비하여 텍스쳐명칭을 다시 세팅해준다.
	{
		ReSettingTextureName();
	}

	// 이동방향이 변경되었다면
	if (CurDirect_ != _MoveDir)
	{
		PrevDirect_ = CurDirect_;
		CurDirect_ = _MoveDir;

		for (int i = 0; i < static_cast<int>(RendererPartType::PART_MAX); ++i)
		{
			std::string AnimationName = ChangeDirectCheck(static_cast<RendererPartType>(i));

			// 해당 렌더러가 LIT_ 타입일때 SH 파트는 제외한다.
			if (ItemEquipState::TP_LIT == PartRenderer_[i].ItemEquipState_ && i == static_cast<int>(RendererPartType::PART_SH))
			{
				continue;
			}

			// 시체모션상태 또는 사망모션상태라면 TR을 제외한 모두 Off상태가 되며, 애니메이션을 변경하지않는다.
			if ((PlayerState::STAT_DD == CurState_ && i != static_cast<int>(RendererPartType::PART_TR))
				|| (PlayerState::STAT_DT == CurState_ && i != static_cast<int>(RendererPartType::PART_TR)))
			{
				continue;
			}

			PartRenderer_[i].Renderer_->SetChangeAnimation(AnimationName);
		}
	}
}
