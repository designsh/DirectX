#include "PreCompile.h"
#include "MainPlayer.h"

#include "InventoryView.h"

// �������� ������ �ش� �Լ� ȣ��
void MainPlayer::HPConsumption(float _Damage)
{
	// ���� ü���� ���ҽ�Ű��,



	// MainPlayer_CurrentHP�� �̹����� ���� ���ҽ��� ������



}

// ����(��ų)�� ����ϸ� �ش� �Լ� ȣ��
void MainPlayer::MPConsumption(float _MPConsumption)
{
	// ���� ������ ���ҽ�Ű��,




	// MainPlayer_CurrentMP�� �̹����� ���� ���ҽ��� ������



}

// ��带 ȹ���ϰų� â���� �����ö� ȣ��
void MainPlayer::HaveGoldAdd(int _Gold)
{
	// �� ��差 ����
	HaveGold_ += _Gold;

	// �κ��丮�� �������ִ� ����ؽ�Ʈ ������ ����
	InventoryView_->HaveGoldUpdate(HaveGold_);
}

// ��带 �������ų� â�� �����Ҷ� ȣ��
void MainPlayer::HaveGoldSub(int _Gold)
{
	// �� ��差 ����
	int Gold = HaveGold_ - _Gold;
	if (0 >= Gold)
	{
		HaveGold_ = 0;

		// �κ��丮�� �������ִ� ����ؽ�Ʈ ������ ����
		InventoryView_->HaveGoldUpdate(HaveGold_);

		return;
	}

	HaveGold_ = Gold;

	// �κ��丮�� �������ִ� ����ؽ�Ʈ ������ ����
	InventoryView_->HaveGoldUpdate(HaveGold_);
}
