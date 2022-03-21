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

	// �κ���(�÷��̾�<->��ǥ����)�� ���� ���
	float4 MoveDirect = _MousePos - MyPos;
	MoveDirect.Normalize3D();

	// �÷��̾��� Y����� ���⺤�͸� ���´�.


	// �� ���͸� �����Ͽ� ������ ���


	// ������ �̿��Ͽ� �÷��̾��� �̵������� �˾Ƴ���.



	/*
	Vector3 Vector3::Axis[(int)AXIS::AXIS_END] =
	{
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 1.f)
	};

	float Vector3::Angle(const Vector3& v) const
	{
		Vector3 v1 = *this;
		Vector3 v2 = v;

		v1.Normalize();
		v2.Normalize();

		float   Angle = v1.Dot(v2);

		Angle = RadianToDegree(acosf(Angle));

		return Angle;
	}

	// Ÿ����ġ�� ���� ��ġ�� ����Ͽ� �÷��̾� ���� ����
	Vector2 MousePos = CInput::GetInst()->GetMouse2DWorldPos();
	Vector3 CurPos = GetWorldPos();
	MoveDirectCalc(CurPos, Vector3(MousePos.x, MousePos.y, CurPos.z));

	// �÷��̾ ���콺�� �ٶ󺸴� ���콺�� ���⺤�͸� �˾Ƴ���.
	Vector3 PlayerDir = TargetPos - CurPos;
	PlayerDir.Normalize();

	// �÷��̾��� Y����� ���⺤�͸� ���´�.
	Vector3 FrontVector = CurPos.Axis[(int)AXIS::AXIS_Y];

	// �� ������ ������ ����Ͽ� ������ ����Ѵ�.
	float cosAngle = FrontVector.Angle(PlayerDir);

	// ������ ó���� �κ����� x,y���� �̿��Ͽ� �ش� ������ ������ �������� ���ʰ������� �˾Ƴ���.
	float Angle = ((FrontVector.x * PlayerDir.y) - (FrontVector.y * PlayerDir.x) > 0.0f) ? cosAngle : -cosAngle;

	// ���� �÷��̾ �ٱ�/�ȱ� ���¿� ���� �ִϸ��̼� ������ �޶�����.
	if (m_RunFlag) // �ٱ� ���¶��
	{
		if (Angle < 0.0f) // ������
		{
			if (Angle > -60.f && Angle <= -30.f)
			{
				// ����
				m_Animation->ChangeAnimation("RT_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::RightTop);
			}
			else if (Angle > -150.f && Angle <= -120.f)
			{
				// ���ϴ�
				m_Animation->ChangeAnimation("RB_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::RightBottom);
			}
			else if (Angle > -30.f && Angle <= 0.f)
			{
				// ���
				m_Animation->ChangeAnimation("U_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Top);
			}
			else if (Angle > -120.f && Angle <= -60.f)
			{
				// ���
				m_Animation->ChangeAnimation("R_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Right);
			}
			else if (Angle > -180.f && Angle <= -150.f)
			{
				// �ϴ�
				m_Animation->ChangeAnimation("D_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Bottom);
			}
		}
		else // ����
		{
			if (Angle > 30.f && Angle <= 60.f)
			{
				// �»��
				m_Animation->ChangeAnimation("LT_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::LeftTop);
			}
			else if (Angle > 120.f && Angle <= 150.f)
			{
				// ���ϴ�
				m_Animation->ChangeAnimation("LB_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::LeftBottom);
			}
			else if (Angle > 0.f && Angle <= 30.f)
			{
				// ���
				m_Animation->ChangeAnimation("U_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Top);
			}
			else if (Angle > 60.f && Angle <= 120.f)
			{
				// �´�
				m_Animation->ChangeAnimation("L_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Left);
			}
			else if (Angle > 150.f && Angle <= 180.f)
			{
				// �ϴ�
				m_Animation->ChangeAnimation("D_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Bottom);
			}
		}
	}
	else // �ȱ���¶��
	{
		if (Angle < 0.0f) // ������
		{
			if (Angle > -60.f && Angle <= -30.f)
			{
				// ����
				m_Animation->ChangeAnimation("RT_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::RightTop);
			}
			else if (Angle > -150.f && Angle <= -120.f)
			{
				// ���ϴ�
				m_Animation->ChangeAnimation("RB_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::RightBottom);
			}
			else if (Angle > -30.f && Angle <= 0.f)
			{
				// ���
				m_Animation->ChangeAnimation("U_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Top);
			}
			else if (Angle > -120.f && Angle <= -60.f)
			{
				// ���
				m_Animation->ChangeAnimation("R_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Right);
			}
			else if (Angle > -180.f && Angle <= -150.f)
			{
				// �ϴ�
				m_Animation->ChangeAnimation("D_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Bottom);
			}
		}
		else // ����
		{
			if (Angle > 30.f && Angle <= 60.f)
			{
				// �»��
				m_Animation->ChangeAnimation("LT_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::LeftTop);
			}
			else if (Angle > 120.f && Angle <= 150.f)
			{
				// ���ϴ�
				m_Animation->ChangeAnimation("LB_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::LeftBottom);
			}
			else if (Angle > 0.f && Angle <= 30.f)
			{
				// ���
				m_Animation->ChangeAnimation("U_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Top);
			}
			else if (Angle > 60.f && Angle <= 120.f)
			{
				// �´�
				m_Animation->ChangeAnimation("L_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Left);
			}
			else if (Angle > 150.f && Angle <= 180.f)
			{
				// �ϴ�
				m_Animation->ChangeAnimation("D_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Bottom);
			}
		}
	}
	*/


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
