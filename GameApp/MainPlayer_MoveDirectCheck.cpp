#include "PreCompile.h"
#include "MainPlayer.h"

bool MainPlayer::MoveDirectCheck()
{
	// 마우스 클릭 지점 Get



	// UI 활성화 여부 체크





	// 마우스 클릭지점을 이용하여 이동방향을 얻어와서 현재 이동방향 변경
	PrevDirect_ = CurDirect_;

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
