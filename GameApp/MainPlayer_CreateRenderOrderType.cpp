#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

//std::vector<PlayerZOrderManagement> DirectRenderOrder_[static_cast<int>(PlayerState::STAT_MAX)];

//// �÷��̾� ���⺰ ��������
//struct UnderChangeZOrder
//{
//	int															StartIndex_;				// �ִϸ��̼� ���� ���� �ε���
//	int															EndIndex_;					// �ִϸ��̼� ���� ���� �ε���
//	std::vector<int>											DirectZOrder_;				// �ִϸ��̼� ���� �⺻ ������ Z����
//};
//
//struct PlayerZOrderManagement
//{
//	TargetDirect												Direct_;					// ���� ������ ����ϴ� ����
//	int															TotalAnimationCnt_;			// ���� ������ �ִϸ��̼� �ε��� Max
//	std::vector<UnderChangeZOrder>								DefaultDirectZOrder_;		// �⺻ ������ ZOrder
//
//	// �ִϸ��̼� ������ Z������ ����Ǿ���ϴ��� �˻�
//	bool														UnderChangeZOrderFlag_;		// �ִϸ��̼� ������ Z���� �������� Flag(true : �����ʿ�)
//	std::vector<UnderChangeZOrder>								UnderChange_;				// �ִϸ��̼� ������ Z���� ��������ϴ� Animation Frame Index
//
//};

// �÷��̾�� �� ��Ʈ�� �̹��������̸�, �� �̵����⿡ ���� ������ ������ ���������Ѵ�.
// �׷��Ƿ� �ش� ���Ͽ��� ���⺰ ������ �������� Ÿ���� �����ϰ�,
// �÷��̾ �������ɶ� �ش� Ÿ���� �̿��Ͽ� ���������� �����Ѵ�.
void MainPlayer::CreateDirectRenderOrderType()
{
	// ���ݸ��1
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		NewZOrderManagement.Direct_ = static_cast<TargetDirect>(i);
		NewZOrderManagement.TotalAnimationCnt_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)].push_back(NewZOrderManagement);
	}

	// LeftBottom ZOrder
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultDirectZOrder_.resize(9);



	int a = 0;

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
