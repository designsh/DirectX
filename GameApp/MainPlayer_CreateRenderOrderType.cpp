#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

// 플레이어는 각 파트별 이미지집합이며, 각 이동방향에 따라 렌더링 오더가 결정나야한다.
// 그러므로 해당 파일에서 방향별 렌더링 오더변경 타입을 설정하고,
// 플레이어가 렌더링될때 해당 타입을 이용하여 렌더오더를 결정한다.
void MainPlayer::CreateDirectRenderOrderType()
{
	// 방향, 상태에 따라 렌더링 오더가 결정됨





}

void MainPlayer::ChangeZOrderType(int _Index, ItemEquipState _ItemEquipType)
{
	// 각 방향별 렌더오더를 변경하는 구문

	// 이동방향별 플레이어 파트별 렌더러의 렌더링 오더 순서 변경
	// 각 방향별 애니메이션 변경타이밍에 해당 함수 호출
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