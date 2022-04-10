#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

// �÷��̾�� �� ��Ʈ�� �̹��������̸�, �� �̵����⿡ ���� ������ ������ ���������Ѵ�.
// �׷��Ƿ� �ش� ���Ͽ��� ���⺰ ������ �������� Ÿ���� �����ϰ�,
// �÷��̾ �������ɶ� �ش� Ÿ���� �̿��Ͽ� ���������� �����Ѵ�.
void MainPlayer::CreateDirectRenderOrderType()
{
#pragma region A1_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeStartIndex_ = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeEndIndex_ = 14;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeStartIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeEndIndex_ = 18;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeStartIndex_ = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeEndIndex_ = 14;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeStartIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeEndIndex_ = 18;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_ = 3;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeStartIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeStartIndex_ = 16;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeEndIndex_ = 17;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeStartIndex_ = 18;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeEndIndex_ = 18;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeStartIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeStartIndex_ = 16;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeEndIndex_ = 18;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region A2_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeStartIndex_ = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeEndIndex_ = 14;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeStartIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeEndIndex_ = 18;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderCnt_ = 5;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeStartIndex_ = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeEndIndex_ = 14;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeStartIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeEndIndex_ = 18;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_ = 3;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeStartIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeStartIndex_ = 16;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeEndIndex_ = 17;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeStartIndex_ = 18;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeEndIndex_ = 18;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeStartIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeStartIndex_ = 16;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeEndIndex_ = 18;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region BL_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region DD_ZOrder
	// TR ��Ʈ�� �����ϹǷ� ������������ : �ִ�ġ�� ������ ��
#pragma endregion

#pragma region DT_ZOrder
	// TR ��Ʈ�� �����ϹǷ� ������������ : �ִ�ġ�� ������ ��
#pragma endregion

#pragma region GH_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_ = 1;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeStartIndex_ = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeEndIndex_ = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;
	}

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeStartIndex_ = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeEndIndex_ = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeStartIndex_ = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeEndIndex_ = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;
	}

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region KK_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeStartIndex_ = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeEndIndex_ = 10;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeStartIndex_ = 11;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeEndIndex_ = 11;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 11;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 11;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderCnt_ = 4;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeStartIndex_ = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeEndIndex_ = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeStartIndex_ = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeEndIndex_ = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeStartIndex_ = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeEndIndex_ = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeStartIndex_ = 9;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeEndIndex_ = 11;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_ = 3;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeStartIndex_ = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeEndIndex_ = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeStartIndex_ = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeEndIndex_ = 9;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 8;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeStartIndex_ = 10;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeEndIndex_ = 11;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;
	}

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 11;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeStartIndex_ = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeEndIndex_ = 9;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeStartIndex_ = 10;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeEndIndex_ = 11;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 11;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region NU_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region RN_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeStartIndex_ = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeEndIndex_ = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeStartIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeEndIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;
	}

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeStartIndex_ = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeEndIndex_ = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeStartIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeEndIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region S1_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeStartIndex_ = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeEndIndex_ = 12;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeStartIndex_ = 13;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_ = 3;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeStartIndex_ = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeEndIndex_ = 10;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeStartIndex_ = 11;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeEndIndex_ = 11;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeStartIndex_ = 12;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;
	}

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_ = 3;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeStartIndex_ = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeEndIndex_ = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeStartIndex_ = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeEndIndex_ = 12;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeStartIndex_ = 13;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region SC_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_ = 3;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeStartIndex_ = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeEndIndex_ = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeStartIndex_ = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeEndIndex_ = 10;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeStartIndex_ = 11;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;
	}

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_ = 4;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeStartIndex_ = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeEndIndex_ = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeStartIndex_ = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeEndIndex_ = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeStartIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeEndIndex_ = 12;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[2].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeStartIndex_ = 13;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[3].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region TN_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeStartIndex_ = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeEndIndex_ = 10;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeStartIndex_ = 11;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;
	}

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeStartIndex_ = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeEndIndex_ = 10;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeStartIndex_ = 11;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;
	}

	// =============================================== Right Bottoms Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 7;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 15;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region TW_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region WL_ZOrder
	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 6;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 4;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultEndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 5;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion
}
