#include "PreCompile.h"
#include "MainPlayer.h"

// 게임 시작을 위한 텍스쳐, 애니메이션, FSM, ZOrder 생성...
void MainPlayer::MainPlayerinitialization()
{
	// 플레이어 애니메이션 관련 이미지 Cut
	AllAnimationCut();

	// 플레이어 애니메이션 생성 관련
	CreateAnimation();

	// 플레이어 FSM 상태 생성 관련
	CreatePlayerStateFSM();
	
	// 방향별 렌더링 오더 생성
	CreateDirectRenderOrderType();

	// 모든 생성 완료 시 호출되며, 초기 시작시 셋팅항목 처리
	MainPlayerStartSetting();
}

// 게임 시작시 초기화 되어야하는 항목들....
void MainPlayer::MainPlayerStartSetting()
{
	// FSM 초기 상태 지정
	State_.ChangeState("Natural_Town");
}
