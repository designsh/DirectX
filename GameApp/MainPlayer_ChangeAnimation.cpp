#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

void MainPlayer::ChangeAnimation(const std::string& _CurStateName)
{
	bool ChangeFlag = false;

	// 현재 상태로 애니메이션 변경
	for (int i = 0; i < static_cast<int>(RendererPartType::PART_MAX); ++i)
	{
		// 각 부위별 아이템 착용여부 판단
		std::string AnimationName = "";
		ChangeFlag = ItemEquipCheck(AnimationName, static_cast<RendererPartType>(i));
		if (false == ChangeFlag)
		{
			GameEngineDebug::MsgBoxError("아이템 착용을 했는지 안했는지 확인할 수 없습니다!!!!!");
			return;
		}

		// 현재상태값
		AnimationName += _CurStateName;

		// 부위값
		ChangeFlag = RnderPartType(AnimationName, static_cast<RendererPartType>(i));
		if (false == ChangeFlag)
		{
			GameEngineDebug::MsgBoxError("구분되어있지않은 렌더러 파트입니다!!!!!");
			return;
		}

		// 방향값
		ChangeFlag = RenderDirectCheck(AnimationName);
		if (false == ChangeFlag)
		{
			GameEngineDebug::MsgBoxError("현재 이동방향이 잘못된 이동방향입니다!!!!!");
			return;
		}

		// LIT_ 타입일때 SH 없으므로 Off상태가 되며 HVY_ 타입이되면 On상태로 전환
		ItemEquipState CurPartItemEquipState = CheckItemEquip(static_cast<RendererPartType>(i));
		if (CurPartItemEquipState == ItemEquipState::TP_LIT && static_cast<RendererPartType>(i) == RendererPartType::PART_SH)
		{
			PartRenderer_[i].Renderer_[static_cast<int>(CurPartItemEquipState)]->Off();
			continue;
		}
		else if (CurPartItemEquipState == ItemEquipState::TP_HVY && static_cast<RendererPartType>(i) == RendererPartType::PART_SH)
		{
			PartRenderer_[i].Renderer_[static_cast<int>(CurPartItemEquipState)]->On();
			continue;
		}

		// 애니메이션 변경
		PartRenderer_[i].Renderer_[static_cast<int>(CurPartItemEquipState)]->SetChangeAnimation(AnimationName);

		// 크기 지정
		PartRenderer_[i].Renderer_[static_cast<int>(CurPartItemEquipState)]->GetTransform()->SetLocalScaling(RenderSize_);

		// 현재 상태에 따른 렌더러 ZOrder 변경
		ChangeZOrderType(i, CurPartItemEquipState);
	}
}

bool MainPlayer::ItemEquipCheck(std::string& _AnimationName, RendererPartType _PartType)
{
	// IsItemEquipState_ 에서 아이템 착용상태 체크
	// 각 아이템 장착별 타입을 체크하여 수신한 string에 이어붙인다.
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
	// 각 부위별 텍스트를 편집하여 인자로 수신한 string에 이어붙인다.
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
	// 현재 방향 체크
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

void MainPlayer::ChangeZOrderType(int _Index, ItemEquipState _ItemEquipType)
{
	// 각 방향별 렌더오더를 변경하는 구문
	// DirectRenderOrder_ 사용해서 체크


	// 이동방향별 플레이어 파트별 렌더러의 렌더링 오더 순서 변경
	// 각 방향별 애니메이션 변경타이밍에 해당 함수 호출
	switch (CurDirect_)
	{
	case TargetDirect::DIR_LB:
	{

		break;
	}
	case TargetDirect::DIR_LT:
	{

		break;
	}
	case TargetDirect::DIR_RT:
	{

		break;
	}
	case TargetDirect::DIR_RB:
	{

		break;
	}
	case TargetDirect::DIR_B:
	{

		break;
	}
	case TargetDirect::DIR_L:
	{

		break;
	}
	case TargetDirect::DIR_T:
	{

		break;
	}
	case TargetDirect::DIR_R:
	{

		break;
	}
	case TargetDirect::DIR_MAX:
	{

		break;
	}
	}

	PartRenderer_[_Index].Renderer_[static_cast<int>(_ItemEquipType)]->GetTransform()->SetZOrder(static_cast<float>(_Index));
}
