#include "PreCompile.h"
#include "MainPlayer.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "MouseObject.h"

bool MainPlayer::MoveDirectCheck(const float4& _MousePos)
{
	// UI 활성화 여부 체크



	// 플레이어 현재 위치 Get
	float4 MyPos = GetTransform()->GetLocalPosition();

	// 마우스 클릭지점을 이용하여 이동방향을 얻어와서 현재 이동방향 변경
	PrevDirect_ = CurDirect_;

	// 두벡터(플레이어<->목표지점)의 각도 계산
	float4 MoveDirect = _MousePos - MyPos;
	MoveDirect.Normalize3D();

	// 플레이어의 Y축기준 방향벡터를 얻어온다.


	// 두 벡터를 내적하여 각도를 계산


	// 각도를 이용하여 플레이어의 이동방향을 알아낸다.



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

	// 타겟위치와 현재 위치를 계산하여 플레이어 방향 갱신
	Vector2 MousePos = CInput::GetInst()->GetMouse2DWorldPos();
	Vector3 CurPos = GetWorldPos();
	MoveDirectCalc(CurPos, Vector3(MousePos.x, MousePos.y, CurPos.z));

	// 플레이어가 마우스를 바라보는 마우스의 방향벡터를 알아낸다.
	Vector3 PlayerDir = TargetPos - CurPos;
	PlayerDir.Normalize();

	// 플레이어의 Y축기준 방향벡터를 얻어온다.
	Vector3 FrontVector = CurPos.Axis[(int)AXIS::AXIS_Y];

	// 두 벡터의 내적을 계산하여 각도를 계산한다.
	float cosAngle = FrontVector.Angle(PlayerDir);

	// 위에서 처리한 두벡터의 x,y값을 이용하여 해당 각도가 오른쪽 각도인지 왼쪽각도인지 알아낸다.
	float Angle = ((FrontVector.x * PlayerDir.y) - (FrontVector.y * PlayerDir.x) > 0.0f) ? cosAngle : -cosAngle;

	// 현재 플레이어가 뛰기/걷기 상태에 따라 애니메이션 변경이 달라진다.
	if (m_RunFlag) // 뛰기 상태라면
	{
		if (Angle < 0.0f) // 오른쪽
		{
			if (Angle > -60.f && Angle <= -30.f)
			{
				// 우상단
				m_Animation->ChangeAnimation("RT_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::RightTop);
			}
			else if (Angle > -150.f && Angle <= -120.f)
			{
				// 우하단
				m_Animation->ChangeAnimation("RB_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::RightBottom);
			}
			else if (Angle > -30.f && Angle <= 0.f)
			{
				// 상단
				m_Animation->ChangeAnimation("U_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Top);
			}
			else if (Angle > -120.f && Angle <= -60.f)
			{
				// 우단
				m_Animation->ChangeAnimation("R_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Right);
			}
			else if (Angle > -180.f && Angle <= -150.f)
			{
				// 하단
				m_Animation->ChangeAnimation("D_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Bottom);
			}
		}
		else // 왼쪽
		{
			if (Angle > 30.f && Angle <= 60.f)
			{
				// 좌상단
				m_Animation->ChangeAnimation("LT_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::LeftTop);
			}
			else if (Angle > 120.f && Angle <= 150.f)
			{
				// 좌하단
				m_Animation->ChangeAnimation("LB_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::LeftBottom);
			}
			else if (Angle > 0.f && Angle <= 30.f)
			{
				// 상단
				m_Animation->ChangeAnimation("U_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Top);
			}
			else if (Angle > 60.f && Angle <= 120.f)
			{
				// 좌단
				m_Animation->ChangeAnimation("L_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Left);
			}
			else if (Angle > 150.f && Angle <= 180.f)
			{
				// 하단
				m_Animation->ChangeAnimation("D_Nec_Run");
				m_Animation->SetMoveDir(MoveDirect::Bottom);
			}
		}
	}
	else // 걷기상태라면
	{
		if (Angle < 0.0f) // 오른쪽
		{
			if (Angle > -60.f && Angle <= -30.f)
			{
				// 우상단
				m_Animation->ChangeAnimation("RT_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::RightTop);
			}
			else if (Angle > -150.f && Angle <= -120.f)
			{
				// 우하단
				m_Animation->ChangeAnimation("RB_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::RightBottom);
			}
			else if (Angle > -30.f && Angle <= 0.f)
			{
				// 상단
				m_Animation->ChangeAnimation("U_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Top);
			}
			else if (Angle > -120.f && Angle <= -60.f)
			{
				// 우단
				m_Animation->ChangeAnimation("R_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Right);
			}
			else if (Angle > -180.f && Angle <= -150.f)
			{
				// 하단
				m_Animation->ChangeAnimation("D_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Bottom);
			}
		}
		else // 왼쪽
		{
			if (Angle > 30.f && Angle <= 60.f)
			{
				// 좌상단
				m_Animation->ChangeAnimation("LT_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::LeftTop);
			}
			else if (Angle > 120.f && Angle <= 150.f)
			{
				// 좌하단
				m_Animation->ChangeAnimation("LB_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::LeftBottom);
			}
			else if (Angle > 0.f && Angle <= 30.f)
			{
				// 상단
				m_Animation->ChangeAnimation("U_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Top);
			}
			else if (Angle > 60.f && Angle <= 120.f)
			{
				// 좌단
				m_Animation->ChangeAnimation("L_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Left);
			}
			else if (Angle > 150.f && Angle <= 180.f)
			{
				// 하단
				m_Animation->ChangeAnimation("D_Nec_TownWalk");
				m_Animation->SetMoveDir(MoveDirect::Bottom);
			}
		}
	}
	*/


	int a = 0;
	










	// 오른쪽
	if (MoveDirect.x > 0.0f)
	{
		// 위
		if (_MousePos.y > MyPos.y)
		{
			CurDirect_ = TargetDirect::DIR_RT;
		}
		else if (_MousePos.y < MyPos.y) // 아래
		{
			CurDirect_ = TargetDirect::DIR_RB;
		}
		else // 오른쪽만
		{
			CurDirect_ = TargetDirect::DIR_R;
		}
	}
	else if(MoveDirect.x < 0.0f) // 왼쪽
	{
		// 위
		if (_MousePos.y > MyPos.y)
		{
			CurDirect_ = TargetDirect::DIR_LT;
		}
		else if (_MousePos.y < MyPos.y) // 아래
		{
			CurDirect_ = TargetDirect::DIR_LB;
		}
		else // 왼쪽만
		{
			CurDirect_ = TargetDirect::DIR_L;
		}
	}
	else if (MoveDirect.y > 0.0f) // 위쪽
	{
		// 오른쪽
		if (_MousePos.x > MyPos.x)
		{
			CurDirect_ = TargetDirect::DIR_R;
		}
		else if (_MousePos.x < MyPos.x) // 왼쪽
		{
			CurDirect_ = TargetDirect::DIR_L;
		}
	}
	else if (MoveDirect.y < 0.0f) // 아래쪽
	{
		// 오른쪽
		if (_MousePos.x > MyPos.x)
		{
			CurDirect_ = TargetDirect::DIR_R;
		}
		else if (_MousePos.x < MyPos.x) // 왼쪽
		{
			CurDirect_ = TargetDirect::DIR_L;
		}
	}

	// 목표지점 저장
	MoveTargetPos_ = _MousePos;

	// 이동중 Flag On
	IsMove_ = true;



	return true;
}

void MainPlayer::MoveStart()
{
	// 이동가능한 구역이므로 방향을 이용하여 상태 및 애니메이션 변경
	// 단, 현재 플레이어가 마을인지 필드인지 체크한다.
	// 또한, 뛰기 상태인지 체크
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
