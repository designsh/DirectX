#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

//std::vector<PlayerZOrderManagement> DirectRenderOrder_[static_cast<int>(PlayerState::STAT_MAX)];

//// 플레이어 방향별 렌더오더
//struct UnderChangeZOrder
//{
//	int															StartIndex_;				// 애니메이션 변경 시작 인덱스
//	int															EndIndex_;					// 애니메이션 변경 종료 인덱스
//	std::vector<int>											DirectZOrder_;				// 애니메이션 실행 기본 렌더링 Z오더
//};
//
//struct PlayerZOrderManagement
//{
//	TargetDirect												Direct_;					// 현재 오더를 사용하는 방향
//	int															TotalAnimationCnt_;			// 현재 상태의 애니메이션 인덱스 Max
//	std::vector<UnderChangeZOrder>								DefaultDirectZOrder_;		// 기본 렌더링 ZOrder
//
//	// 애니메이션 실행중 Z오더가 변경되어야하는지 검사
//	bool														UnderChangeZOrderFlag_;		// 애니메이션 실행중 Z오더 변경유무 Flag(true : 변경필요)
//	std::vector<UnderChangeZOrder>								UnderChange_;				// 애니메이션 실행중 Z오더 변경시작하는 Animation Frame Index
//
//};

// 플레이어는 각 파트별 이미지집합이며, 각 이동방향에 따라 렌더링 오더가 결정나야한다.
// 그러므로 해당 파일에서 방향별 렌더링 오더변경 타입을 설정하고,
// 플레이어가 렌더링될때 해당 타입을 이용하여 렌더오더를 결정한다.
void MainPlayer::CreateDirectRenderOrderType()
{
	// 공격모션1
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)].push_back(NewZOrderManagement);
	}

	// LeftBottom ZOrder
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultDirectZOrder_.resize(static_cast<int>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChange1_.resize(static_cast<int>(RendererPartType::PART_MAX));

	// HD
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = true;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_ = 1;

	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChange1_[static_cast<int>(RendererPartType::PART_HD)].StartIndex_ = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChange1_[static_cast<int>(RendererPartType::PART_HD)].EndIndex_ = 14;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChange1_[static_cast<int>(RendererPartType::PART_HD)].DirectZOrder_ = 6;

	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultDirectZOrder_[static_cast<int>(RendererPartType::PART_HD)].StartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultDirectZOrder_[static_cast<int>(RendererPartType::PART_HD)].EndIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultDirectZOrder_[static_cast<int>(RendererPartType::PART_HD)].DirectZOrder_ = 5;

	// 

	// 공격모션2
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)];

	// 방어모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)];

	// 시체모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_DD)];

	// 사망모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_DT)];

	// 피격모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)];

	// 킥모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)];

	// 필드_대기모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)];

	// 뛰기모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)];

	// 스킬공격모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)];

	// 스킬캐스팅모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)];

	// 마을_대기모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)];

	// 마을_걷기모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)];

	// 필드_걷기모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)];
	
}
