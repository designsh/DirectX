#include "PreCompile.h"
#include "MainPlayer.h"

// 데미지를 받으면 해당 함수 호출
void MainPlayer::HPConsumption(float _Damage)
{
	// 나의 체력을 감소시키고,



	// MainPlayer_CurrentHP의 이미지를 일정 감소시켜 렌더링



}

// 마법(스킬)을 사용하면 해당 함수 호출
void MainPlayer::MPConsumption(float _MPConsumption)
{
	// 나의 마나를 감소시키고,




	// MainPlayer_CurrentMP의 이미지를 일정 감소시켜 렌더링



}

// 골드를 획득하거나 창고에서 꺼내올때 호출
void MainPlayer::HaveGoldAdd(int _Gold)
{
	// 내 골드량 증가
	HaveGold_ += _Gold;
}

// 골드를 내려놓거나 창고에 저장할때 호출
void MainPlayer::HaveGoldSub(int _Gold)
{
	// 내 골드량 감소
	int Gold = HaveGold_ - _Gold;
	if (0 >= Gold)
	{
		HaveGold_ = 0;
		return;
	}

	HaveGold_ = Gold;
}
