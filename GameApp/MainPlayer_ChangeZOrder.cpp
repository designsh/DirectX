#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

// ���� ���°� �ٲ�ų� ���� �̵������� �ٲ� ȣ��Ǵ� �Լ���, DirectRenderOrder_�� DefaultZOrder_�� ZOrder�� �ʱ� �����Ѵ�.
void MainPlayer::StateAndDirectChangeZOrder()
{
	if (false == IsDefaultZOrderChangeChk_)
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
}

// �� �����Ӹ��� �ִϸ��̼� Ư�� �����ӿ� ZOrder�� ����Ǵ����� �Ǵ��Ͽ� ZOrder�� �����Ѵ�.
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
				// Animation Frame�� ZOrder ��ȭ����
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
				// Animation Frame�� ZOrder ��ȭ����
				IsDefaultZOrderChangeChk_ = false;
				return;
			}
		}
	}

	// �⺻ ZOrder�� �������ε��� �������� ����Ǿ��ٸ� Flag On
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

		// ���� �ִϸ��̼��� ���������Ӱ� ������������ üũ�Ͽ� ���������� �������� ��ȯ
		if (true == DefaultZOrderEndFrameCheck(CurRenderer, CheckAnimationFrame))
		{
			// ��, ���� ������ ���� ������ ����Ǵ� ZOrder���� false�̸� Flag On ����
			if (false != DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeZOrderFlag_)
			{
				IsDefaultZOrderChangeChk_ = true;
			}
		}
	}
}

bool MainPlayer::DefaultZOrderEndFrameCheck(GameEngineImageRenderer* _Renderer, int _CheckFrame)
{
	// ���� ������ �ִϸ��̼��� ���������Ӱ� ������������ �̿��Ͽ� ���� �ִϸ��̼� �������� 
	int StartFrame = _Renderer->GetStartAnimationFrame();
	int CurFrame = _Renderer->GetCurAnimationFrame();

	// ������ ���
	if (0 != StartFrame)
	{
		CurFrame = CurFrame % StartFrame;
	}
	
	// _CheckFrame�� �����ϸ� true ��ȯ
	if (_CheckFrame == CurFrame)
	{
		return true;
	}

	return false;
}

void MainPlayer::ZorderCheckChange()
{	
	int Index = DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeCurIndex_;

	// ���� �ε����� �ִ밹���� ���ų� Ŀ���� ����Ϸ� �Ǿ����Ƿ� ������ ZOrder�� ���ư���.
	if (Index >= DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeZOrderCnt_)
	{
		// ����Ƚ���� �Ѿ�� ���� �ε����� �ʱ�ȭ�ϰ�,
		DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeCurIndex_ = 0;

		// ZOrder�� �⺻ ZOrder�� �����ϰ�,
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

		// Flag ����
		IsDefaultZOrderChangeChk_ = false;

		return;
	}

	if (false == IsFrameZOrderChangeChk_)
	{
		// ���� ����Ǵ� ZOrder�� �ε����� StartIndex�� ���� �������� �ִϸ��̼��� CurFrame�� ���ٸ� �ش� ZOrder�� �����ϰ�
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

			// ������ ���
			if (0 != StartFrame)
			{
				CurFrame = CurFrame % StartFrame;
			}

			// _CheckFrame�� �����ϸ� true ��ȯ
			if (ChangeStartFrame == CurFrame)
			{
				// ���� ZOrder�� ����
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

				// ���� ZOrder�� ����������üũ�� ���� Flag On
				IsFrameZOrderChangeChk_ = true;
			}
		}
	}

	if (true == IsFrameZOrderChangeChk_)
	{
		// ���� ����Ǵ� ZOrder�� �ε����� EndIndex�� ���� �������� �ִϸ��̼��� CurFrame�� ���ٸ� UnderChangeCurIndex_�� ������Ų��.
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

			// ������ ���
			if (0 != StartFrame)
			{
				CurFrame = CurFrame % StartFrame;
			}

			// _CheckFrame�� �����ϸ� true ��ȯ
			if (ChangeEndFrame == CurFrame)
			{
				// ���� ���� ZOrder üũ�� ���� �ε��� ����
				DirectRenderOrder_[static_cast<int>(CurState_)][static_cast<int>(CurDirect_)].UnderChangeCurIndex_ += 1;

				// ���� ����� �ε����� ZOrder üũ�� ���� Flag ����
				IsFrameZOrderChangeChk_ = false;
			}
		}
	}
}
