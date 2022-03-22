#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

// �÷��̾�� �� ��Ʈ�� �̹��������̸�, �� �̵����⿡ ���� ������ ������ ���������Ѵ�.
// �׷��Ƿ� �ش� ���Ͽ��� ���⺰ ������ �������� Ÿ���� �����ϰ�,
// �÷��̾ �������ɶ� �ش� Ÿ���� �̿��Ͽ� ���������� �����Ѵ�.
void MainPlayer::CreateDirectRenderOrderType()
{
	// ���ݸ��1

	// �ִϸ��̼� ���� Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// �⺻ ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// ���� ZOrder Set

	// ����Ǵ� �������� �����Ҷ��� �����Ѵ�.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_ = 1;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_;

		// UnderChangeZOrderCnt_ ����ŭ �Ҵ�
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeStartIndex_ = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeEndIndex_ = 14;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 1;
	}

	// =============================================== Left Top Direct ZOrder Manager =============================================== //
















	int a = 0;





	// 

	// ���ݸ��2
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)];

	// �����
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)];

	// ��ü���
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_DD)];

	// ������
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_DT)];

	// �ǰݸ��
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)];

	// ű���
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)];

	// �ʵ�_�����
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)];

	// �ٱ���
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)];

	// ��ų���ݸ��
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)];

	// ��ųĳ���ø��
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)];

	// ����_�����
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)];

	// ����_�ȱ���
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)];

	// �ʵ�_�ȱ���
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)];
	
}
