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

	//// 두벡터(플레이어<->목표지점)의 각도 계산
	//
	//float4 VectorMulti = _MousePos * MyPos;
	float4 MoveDirect = _MousePos - MyPos;
	MoveDirect.Normalize3D();

	//


	//// 두 벡터의 내적
	//float cos = float4::Dot3DToCos(VectorMulti, MoveDirect);


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
