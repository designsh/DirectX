#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

// 현재 상태가 바뀌거나 현재 이동방향이 바뀔때 호출되는 함수로, DirectRenderOrder_의 DefaultZOrder_로 ZOrder를 초기 셋팅한다.
void MainPlayer::StateAndDirectChangeZOrder()
{
	if (false == IsDefaultZOrderChangeChk_)
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
}

// 매 프레임마다 애니메이션 특정 프레임에 ZOrder가 변경되는지를 판단하여 ZOrder를 변경한다.
void MainPlayer::AnimationFrameCheckZOrderChange()
{
	if (true == IsDefaultZOrderChangeChk_)
	{
		switch (CurState_)
		{
			case PlayerState::STAT_A1:
			case PlayerState::STAT_A2:
			case PlayerState::STAT_TN:
			case PlayerState::STAT_SC:
			case PlayerState::STAT_S1:
			case PlayerState::STAT_RN:
			case PlayerState::STAT_KK:
			case PlayerState::STAT_GH:
			{
				// Animation Frame별 ZOrder 변화있음
				ZorderCheckChange();
				break;
			}
			case PlayerState::STAT_BL:
			case PlayerState::STAT_DD:
			case PlayerState::STAT_DT:
			case PlayerState::STAT_NU:
			case PlayerState::STAT_TW:
			case PlayerState::STAT_WL:
			case PlayerState::STAT_MAX:
			default:
			{				
				// Animation Frame별 ZOrder 변화없음
				IsDefaultZOrderChangeChk_ = false;
				return;
			}
		}
	}

	// 기본 ZOrder의 마지막인덱스 프레임이 종료되었다면 Flag On
	if (false == IsDefaultZOrderChangeChk_)
	{
		if (CurState_ == PlayerState::STAT_DD || CurState_ == PlayerState::STAT_DT)
		{
			return;
		}

		GameEngineImageRenderer* CurRenderer = nullptr;
		int CheckAnimationFrame = DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].DefaultEndIndex_;
		std::map<RendererPartType, bool>::iterator FindIter = IsItemEquipState_.find(static_cast<RendererPartType>(RendererPartType::PART_TR));
		bool ItemEquipType = FindIter->second;
		if (false == ItemEquipType)
		{
			CurRenderer = PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)];
		}
		else
		{
			CurRenderer = PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)];
		}

		// 현재 애니메이션의 시작프레임과 종료프레임을 체크하여 일정범위의 프레임을 반환
		if (true == DefaultZOrderEndFrameCheck(CurRenderer, CheckAnimationFrame))
		{
			// 단, 현재 상태의 현재 방향의 변경되는 ZOrder값이 false이면 Flag On 못함
			if (false != DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeZOrderFlag_)
			{
				IsDefaultZOrderChangeChk_ = true;
			}
		}
	}
}

bool MainPlayer::DefaultZOrderEndFrameCheck(GameEngineImageRenderer* _Renderer, int _CheckFrame)
{
	// 현재 렌더러 애니메이션의 시작프레임과 종료프레임을 이용하여 현재 애니메이션 프레임을 
	int StartFrame = _Renderer->GetStartAnimationFrame();
	int CurFrame = _Renderer->GetCurAnimationFrame();

	// 프레임 계산
	if (0 != StartFrame)
	{
		CurFrame = CurFrame % StartFrame;
	}
	
	// _CheckFrame과 동일하면 true 반환
	if (_CheckFrame == CurFrame)
	{
		return true;
	}

	return false;
}

void MainPlayer::ZorderCheckChange()
{	
	int Index = DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeCurIndex_;

	// 현재 인덱스가 최대갯수와 같거나 커지면 변경완료 되었으므로 원래의 ZOrder로 돌아간다.
	if (Index >= DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeZOrderCnt_)
	{
		// 변경횟수를 넘어가면 현재 인덱스를 초기화하고,
		DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeCurIndex_ = 0;

		// ZOrder를 기본 ZOrder로 셋팅하고,
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

		// Flag 해제
		IsDefaultZOrderChangeChk_ = false;

		return;
	}

	if (false == IsFrameZOrderChangeChk_)
	{
		// 현재 변경되는 ZOrder의 인덱스의 StartIndex와 현재 실행중인 애니메이션의 CurFrame이 같다면 해당 ZOrder로 변경하고
		int ChangeStartFrame = DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeZOrder_[Index].ChangeStartIndex_;

		GameEngineImageRenderer* CurRenderer = nullptr;
		std::map<RendererPartType, bool>::iterator FindIter = IsItemEquipState_.find(static_cast<RendererPartType>(RendererPartType::PART_TR));
		bool ItemEquipType = FindIter->second;
		if (false == ItemEquipType)
		{
			CurRenderer = PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)];
		}
		else
		{
			CurRenderer = PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)];
		}

		if (nullptr != CurRenderer)
		{
			int StartFrame = CurRenderer->GetStartAnimationFrame();
			int CurFrame = CurRenderer->GetCurAnimationFrame();

			// 프레임 계산
			if (0 != StartFrame)
			{
				CurFrame = CurFrame % StartFrame;
			}

			// _CheckFrame과 동일하면 true 반환
			if (ChangeStartFrame == CurFrame)
			{
				// 현재 ZOrder로 변경
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

				// 현재 ZOrder의 종료프레임체크를 위해 Flag On
				IsFrameZOrderChangeChk_ = true;
			}
		}
	}

	if (true == IsFrameZOrderChangeChk_)
	{
		// 현재 변경되는 ZOrder의 인덱스의 EndIndex와 현재 실행중인 애니메이션의 CurFrame이 같다면 UnderChangeCurIndex_를 증가시킨다.
		int ChangeEndFrame = DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeZOrder_[Index].ChangeEndIndex_;

		GameEngineImageRenderer* CurRenderer = nullptr;
		std::map<RendererPartType, bool>::iterator FindIter = IsItemEquipState_.find(static_cast<RendererPartType>(RendererPartType::PART_TR));
		bool ItemEquipType = FindIter->second;
		if (false == ItemEquipType)
		{
			CurRenderer = PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_LIT)];
		}
		else
		{
			CurRenderer = PartRenderer_[static_cast<int>(RendererPartType::PART_TR)].Renderer_[static_cast<int>(ItemEquipState::TP_HVY)];
		}

		if (nullptr != CurRenderer)
		{
			int StartFrame = CurRenderer->GetStartAnimationFrame();
			int CurFrame = CurRenderer->GetCurAnimationFrame();

			// 프레임 계산
			if (0 != StartFrame)
			{
				CurFrame = CurFrame % StartFrame;
			}

			// _CheckFrame과 동일하면 true 반환
			if (ChangeEndFrame == CurFrame)
			{
				// 다음 변경 ZOrder 체크를 위해 인덱스 증가
				DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeCurIndex_ += 1;

				// 다음 변경된 인덱스의 ZOrder 체크를 위해 Flag 해제
				IsFrameZOrderChangeChk_ = false;
			}
		}
	}
}
