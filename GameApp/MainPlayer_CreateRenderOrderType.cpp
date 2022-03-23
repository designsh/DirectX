#include "PreCompile.h"
#include "MainPlayer.h"

#include <GameEngine/GameEngineImageRenderer.h>

// 플레이어는 각 파트별 이미지집합이며, 각 이동방향에 따라 렌더링 오더가 결정나야한다.
// 그러므로 해당 파일에서 방향별 렌더링 오더변경 타입을 설정하고,
// 플레이어가 렌더링될때 해당 타입을 이용하여 렌더오더를 결정한다.
void MainPlayer::CreateDirectRenderOrderType()
{
#pragma region A1_ZOrder
	// 애니메이션 방향 Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_ = 1;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ 수만큼 할당
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeStartIndex_ = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeEndIndex_ = 14;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 1;
	}

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderCnt_ = 1;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ 수만큼 할당
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeStartIndex_ = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeEndIndex_ = 14;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;
	}

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ 수만큼 할당
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeStartIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeStartIndex_ = 16;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeEndIndex_ = 17;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 2;
	}

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_ = 1;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ 수만큼 할당
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeStartIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;
	}

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A1)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region A2_ZOrder
	// 애니메이션 방향 Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_ = 1;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ 수만큼 할당
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeStartIndex_ = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeEndIndex_ = 14;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 1;
	}

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderCnt_ = 1;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ 수만큼 할당
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeStartIndex_ = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeEndIndex_ = 14;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;
	}

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_ = 2;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ 수만큼 할당
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeStartIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeStartIndex_ = 16;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeEndIndex_ = 17;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 3;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrder_[1].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 2;
	}

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = true;
	if (true == DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_)
	{
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_ = 1;
		int Count = DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderCnt_;

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeCurIndex_ = 0;

		// UnderChangeZOrderCnt_ 수만큼 할당
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_.resize(static_cast<size_t>(Count));

		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeStartIndex_ = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeEndIndex_ = 15;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrder_[0].ChangeZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;
	}

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 18;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_A2)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region BL_ZOrder
	// 애니메이션 방향 Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Bottom Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultStartIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 3;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 2;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_RB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Bottom Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultStartIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_B)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultStartIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_L)].UnderChangeZOrderFlag_ = false;

	// =============================================== Top Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultStartIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_T)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultStartIndex_ = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_BL)][static_cast<int>(TargetDirect::DIR_R)].UnderChangeZOrderFlag_ = false;

#pragma endregion

#pragma region DD_ZOrder
	// TR 파트만 존재하므로 지정하지않음 : 최대치가 오더가 됨
#pragma endregion

#pragma region DT_ZOrder
	// TR 파트만 존재하므로 지정하지않음 : 최대치가 오더가 됨
#pragma endregion

#pragma region GH_ZOrder
	// 애니메이션 방향 Push Back
	for (int i = 0; i < static_cast<int>(TargetDirect::DIR_MAX); ++i)
	{
		PlayerZOrderManagement NewZOrderManagement = {};
		DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)].push_back(NewZOrderManagement);
	}

	// =============================================== Left Bottom Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultStartIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LB)].UnderChangeZOrderFlag_ = false;

	// =============================================== Left Top Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;

	// =============================================== Right Top Direct ZOrder Manager =============================================== //

	// 기본 ZOrder Set
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_RT)].DefaultStartIndex_ = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultStartIndex_ = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_.resize(static_cast<size_t>(RendererPartType::PART_MAX));
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_HD)] = 5;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LA)] = 6;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_LG)] = 2;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RA)] = 1;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_RH)] = 0;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S1)] = 4;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_S2)] = 7;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_SH)] = 8;
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].DefaultZOrder_[static_cast<int>(RendererPartType::PART_TR)] = 3;

	// 변경 ZOrder Set

	// 변경되는 프레임이 존재할때만 생성한다.
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_GH)][static_cast<int>(TargetDirect::DIR_LT)].UnderChangeZOrderFlag_ = false;



#pragma endregion

#pragma region KK_ZOrder
	// 킥모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_KK)];
#pragma endregion

#pragma region NU_ZOrder
	// 필드_대기모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_NU)];
#pragma endregion

#pragma region RN_ZOrder
	// 뛰기모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_RN)];
#pragma endregion

#pragma region S1_ZOrder
	// 스킬공격모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_S1)];
#pragma endregion

#pragma region SC_ZOrder
	// 스킬캐스팅모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_SC)];
#pragma endregion

#pragma region TN_ZOrder
	// 마을_대기모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TN)];
#pragma endregion

#pragma region TW_ZOrder
	// 마을_걷기모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_TW)];
#pragma endregion

#pragma region WL_ZOrder
	// 필드_걷기모션
	DirectRenderOrder_[static_cast<int>(PlayerState::STAT_WL)];
#pragma endregion
}
