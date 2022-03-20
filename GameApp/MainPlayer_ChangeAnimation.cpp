#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

std::string MainPlayer::ChangeStateCheck(RendererPartType _PartType)
{
	int Index = static_cast<int>(_PartType);

	// 플레이어가 각 부위별 아이템 착용여부에 따라 애니메이션 및 이미지 이름이 정해진다.
	std::string EquipStateName = "";

	// 해당 부위가 아이템 착용중이라면
	if (ItemEquipState::TP_HVY == PartRenderer_[Index].ItemEquipState_)
	{
		// 해당 부위가 아이템 착용중이기때문에 아이템 미착용 렌더러 off 상태로 전환되며,
		// 해당 타입의 렌더러는 on상태로 전환
		PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->Off();
		PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->On();

		// 단, LIT_ 일때 PART_SH 는 OFF 상태이므로 ON상태로 변경한다.
		if (_PartType == RendererPartType::PART_SH)
		{
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->On();
		}

		PartRenderer_[Index].ItemEquipState_ = ItemEquipState::TP_HVY;
		EquipStateName = "HVY_";
	}
	else // 해당 부위가 아이템 미착용중이라면
	{
		// 해당 부위가 아이템 미착용중이기때문에 아이템 착용 렌더러 off상태로 전환되며,
		// 해당 타입의 렌더러는 on상태 전환
		PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->On();
		PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->Off();

		// 단, LIT_ 일때 PART_SH 는 OFF 상태
		if (_PartType == RendererPartType::PART_SH)
		{
			PartRenderer_[Index].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->Off();
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

			// 시체모션상태 또는 사망모션상태라면 TR을 제외한 모두 Off상태가 되며, TR을 제외한 모든 텍스쳐를 셋팅하지않는다.
			if ( (PlayerState::STAT_DD == CurState_ && i != static_cast<int>(RendererPartType::PART_TR)) 
				|| (PlayerState::STAT_DT == CurState_ && i != static_cast<int>(RendererPartType::PART_TR)) )
			{
				PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)]->Off();
				PartRenderer_[i].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)]->Off();
				continue;
			}

			// 사망모션 or 시체모션이 아니라면 모든 렌더러는 On상태로 전환
			// 단, 해당 부위 렌더러의 아이템 착용여부에 따라 On상태로 전환되는 렌더러를 정한다.
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

			// 아이템 착용 / 아이템 미착용 타입에 따라 설정
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
	else // 모션변경이 없을때 텍스쳐명이 저장안되어있는 경우를 대비하여 텍스쳐명칭을 다시 세팅해준다.
	{
		ReSettingTextureName();
	}

	// 이동방향이 변경되었다면
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

		// 아이템 착용 / 아이템 미착용 타입에 따라 설정
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
