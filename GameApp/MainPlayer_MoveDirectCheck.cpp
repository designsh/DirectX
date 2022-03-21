#include "PreCompile.h"
#include "MainPlayer.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MouseObject.h"

bool MainPlayer::MoveDirectCheck(const float4& _MousePos)
{
	// UI Ȱ��ȭ ���� üũ



	// �÷��̾� ���� ��ġ Get
	float4 MyPos = GetTransform()->GetLocalPosition();

	// ���콺 Ŭ�������� �̿��Ͽ� �̵������� ���ͼ� ���� �̵����� ����
	PrevDirect_ = CurDirect_;

	//// �κ���(�÷��̾�<->��ǥ����)�� ���� ���
	//
	//float4 VectorMulti = _MousePos * MyPos;
	float4 MoveDirect = _MousePos - MyPos;
	MoveDirect.Normalize3D();

	//


	//// �� ������ ����
	//float cos = float4::Dot3DToCos(VectorMulti, MoveDirect);


	int a = 0;
	










	// ������
	if (MoveDirect.x > 0.0f)
	{
		// ��
		if (_MousePos.y > MyPos.y)
		{
			CurDirect_ = TargetDirect::DIR_RT;
		}
		else if (_MousePos.y < MyPos.y) // �Ʒ�
		{
			CurDirect_ = TargetDirect::DIR_RB;
		}
		else // �����ʸ�
		{
			CurDirect_ = TargetDirect::DIR_R;
		}
	}
	else if(MoveDirect.x < 0.0f) // ����
	{
		// ��
		if (_MousePos.y > MyPos.y)
		{
			CurDirect_ = TargetDirect::DIR_LT;
		}
		else if (_MousePos.y < MyPos.y) // �Ʒ�
		{
			CurDirect_ = TargetDirect::DIR_LB;
		}
		else // ���ʸ�
		{
			CurDirect_ = TargetDirect::DIR_L;
		}
	}
	else if (MoveDirect.y > 0.0f) // ����
	{
		// ������
		if (_MousePos.x > MyPos.x)
		{
			CurDirect_ = TargetDirect::DIR_R;
		}
		else if (_MousePos.x < MyPos.x) // ����
		{
			CurDirect_ = TargetDirect::DIR_L;
		}
	}
	else if (MoveDirect.y < 0.0f) // �Ʒ���
	{
		// ������
		if (_MousePos.x > MyPos.x)
		{
			CurDirect_ = TargetDirect::DIR_R;
		}
		else if (_MousePos.x < MyPos.x) // ����
		{
			CurDirect_ = TargetDirect::DIR_L;
		}
	}

	// ��ǥ���� ����
	MoveTargetPos_ = _MousePos;

	// �̵��� Flag On
	IsMove_ = true;



	return true;
}

void MainPlayer::MoveStart()
{
	// �̵������� �����̹Ƿ� ������ �̿��Ͽ� ���� �� �ִϸ��̼� ����
	// ��, ���� �÷��̾ �������� �ʵ����� üũ�Ѵ�.
	// ����, �ٱ� �������� üũ
	if (true == IsRun_)
	{
		ChangeFSMState("Run");
	}
	else
	{
		if (true == IsTown_)
		{
			ChangeFSMState("Walk_Town");
		}
		else
		{
			ChangeFSMState("Walk_Field");
		}
	}
}
