#include "PreCompile.h"
#include "MainPlayer.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "TownMap.h"
#include "MouseObject.h"

bool MainPlayer::MoveDirectCheck(const float4& _MousePos)
{
	// �÷��̾� ���� ��ġ Get
	float4 MyPos = GetTransform()->GetLocalPosition();

	// ���콺 Ŭ�������� �̿��Ͽ� �̵������� ���ͼ� ���� �̵����� ����
	PrevDirect_ = CurDirect_;

	// �κ���(�÷��̾�<->��ǥ����)�� ���� ���
	float4 MoveDirect = _MousePos - MyPos;
	MoveDirect.Normalize3D();

	// ������ y����� ���⺤�͸� ���´�.
	float4 FrontVector = float4::UP;

	// �� ���͸� �����Ͽ� COS(��Ÿ) ������ ���
	float cosAngle = float4::DegreeDot3DToACosAngle(FrontVector, MoveDirect);
	
	float Angle = ((FrontVector.x * MoveDirect.y) - (FrontVector.y * MoveDirect.x) > 0.0f) ? cosAngle : -cosAngle;

	// ������ ���� ��ȯ(�� ���⺰ ���� : 30��)
	if (Angle < 0.0f) // ������
	{
		if (Angle > -60.f && Angle <= -30.f)
		{
			// ����
			CurDirect_ = TargetDirect::DIR_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// ���ϴ�
			CurDirect_ = TargetDirect::DIR_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// ���
			CurDirect_ = TargetDirect::DIR_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// ���
			CurDirect_ = TargetDirect::DIR_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// �ϴ�
			CurDirect_ = TargetDirect::DIR_B;
		}
	}
	else // ����
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// �»��
			CurDirect_ = TargetDirect::DIR_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// ���ϴ�
			CurDirect_ = TargetDirect::DIR_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// ���
			CurDirect_ = TargetDirect::DIR_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// �´�
			CurDirect_ = TargetDirect::DIR_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// �ϴ�
			CurDirect_ = TargetDirect::DIR_B;
		}
	}

	// ��ǥ���� ����
	PrevMoveTargetPos_ = CurMoveTargetPos_;
	CurMoveTargetPos_ = _MousePos;

	// �̵��� Flag On
	IsMove_ = true;

	return true;
}

void MainPlayer::MoveStart(const float4& _MousePos)
{
	// ����üũ
	if (std::string::npos != GetLevel()->GetName().find("TownLevel"))
	{
		GlobalValue::TownMap->NavgationFind4Way(GetTransform()->GetWorldPosition(), _MousePos);
	}
	else if(std::string::npos != GetLevel()->GetName().find("CatacombsLevel"))
	{

	}
	else if (std::string::npos != GetLevel()->GetName().find("ChaosSanctuaryLevel"))
	{

	}
	else
	{
		// ���� �������������� �̵� �Ұ�
		return;
	}

	// �̵������ Ÿ���ε����� ��� ����Ҷ����� �̵�ó��





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
