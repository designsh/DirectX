#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

// �÷��̾�� �� ��Ʈ�� �̹��������̸�, �� �̵����⿡ ���� ������ ������ ���������Ѵ�.
// �׷��Ƿ� �ش� ���Ͽ��� ���⺰ ������ �������� Ÿ���� �����ϰ�,
// �÷��̾ �������ɶ� �ش� Ÿ���� �̿��Ͽ� ���������� �����Ѵ�.
void MainPlayer::CreateDirectRenderOrderType()
{
	// ����, ���¿� ���� ������ ������ ������





}

void MainPlayer::ChangeZOrderType(int _Index, ItemEquipState _ItemEquipType)
{
	// �� ���⺰ ���������� �����ϴ� ����

	// �̵����⺰ �÷��̾� ��Ʈ�� �������� ������ ���� ���� ����
	// �� ���⺰ �ִϸ��̼� ����Ÿ�ֿ̹� �ش� �Լ� ȣ��
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