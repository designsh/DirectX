#include "PreCompile.h"
#include "MainPlayer.h"

#include "GlobalEnumClass.h"
#include "GlobalValue.h"

#include "TownMap.h"
#include "MouseObject.h"

bool MainPlayer::MoveDirectCheck(const float4& _MousePos)
{
	// 플레이어 현재 위치 Get
	float4 MyPos = GetTransform()->GetLocalPosition();

	// 마우스 클릭지점을 이용하여 이동방향을 얻어와서 현재 이동방향 변경
	PrevDirect_ = CurDirect_;

	// 두벡터(플레이어<->목표지점)의 각도 계산
	float4 MoveDirect = _MousePos - MyPos;
	MoveDirect.Normalize3D();

	// 월드의 y축기준 방향벡터를 얻어온다.
	float4 FrontVector = float4::UP;

	// 두 벡터를 내적하여 COS(세타) 각도를 계산
	float cosAngle = float4::DegreeDot3DToACosAngle(FrontVector, MoveDirect);
	
	float Angle = ((FrontVector.x * MoveDirect.y) - (FrontVector.y * MoveDirect.x) > 0.0f) ? cosAngle : -cosAngle;

	// 각도별 방향 전환(각 방향별 범위 : 30도)
	if (Angle < 0.0f) // 오른쪽
	{
		if (Angle > -60.f && Angle <= -30.f)
		{
			// 우상단
			CurDirect_ = TargetDirect::DIR_RT;
		}
		else if (Angle > -150.f && Angle <= -120.f)
		{
			// 우하단
			CurDirect_ = TargetDirect::DIR_RB;
		}
		else if (Angle > -30.f && Angle <= 0.f)
		{
			// 상단
			CurDirect_ = TargetDirect::DIR_T;
		}
		else if (Angle > -120.f && Angle <= -60.f)
		{
			// 우단
			CurDirect_ = TargetDirect::DIR_R;
		}
		else if (Angle > -180.f && Angle <= -150.f)
		{
			// 하단
			CurDirect_ = TargetDirect::DIR_B;
		}
	}
	else // 왼쪽
	{
		if (Angle > 30.f && Angle <= 60.f)
		{
			// 좌상단
			CurDirect_ = TargetDirect::DIR_LT;
		}
		else if (Angle > 120.f && Angle <= 150.f)
		{
			// 좌하단
			CurDirect_ = TargetDirect::DIR_LB;
		}
		else if (Angle > 0.f && Angle <= 30.f)
		{
			// 상단
			CurDirect_ = TargetDirect::DIR_T;
		}
		else if (Angle > 60.f && Angle <= 120.f)
		{
			// 좌단
			CurDirect_ = TargetDirect::DIR_L;
		}
		else if (Angle > 150.f && Angle <= 180.f)
		{
			// 하단
			CurDirect_ = TargetDirect::DIR_B;
		}
	}

	// 목표지점 저장
	PrevMoveTargetPos_ = CurMoveTargetPos_;
	CurMoveTargetPos_ = _MousePos;

	// 이동중 Flag On
	IsMove_ = true;

	return true;
}

void MainPlayer::MoveStart(const float4& _MousePos)
{
	// 레벨체크
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
		// 맵이 존재하지않으면 이동 불가
		return;
	}

	// 이동경로의 타일인덱스를 모두 사용할때까지 이동처리





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
