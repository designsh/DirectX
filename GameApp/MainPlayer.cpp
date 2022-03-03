#include "PreCompile.h"
#include "MainPlayer.h"

#include "BottomStateBar.h"

#include <GameEngine/GameEngineImageRenderer.h>

MainPlayer::MainPlayer() :
	PlayerInfomation_(nullptr),
	BottomStateBar_(nullptr),
	HD_Renderer_(nullptr),
	LA_Renderer_(nullptr),
	LG_Renderer_(nullptr),
	RA_Renderer_(nullptr),
	RH_Renderer_(nullptr),
	S1_Renderer_(nullptr),
	S2_Renderer_(nullptr),
	SH_Renderer_(nullptr),
	TR_Renderer_(nullptr)
{
}

MainPlayer::~MainPlayer()
{
}

void MainPlayer::ChangeAnimaton(const std::string& _Name)
{
	// ������ ���ڸ� �̿��Ͽ� �ִϸ��̼� ��Ī ����




}

void MainPlayer::Start()
{
	// �÷��̾� �ִϸ��̼� ���� �̹��� Cut
	AllAnimationCut();

	// �÷��̾� �ִϸ��̼� ���� ����
	CreateAnimation();

	// �ϴ� ���¹�
	BottomStateBar_ = GetLevel()->CreateActor<BottomStateBar>();

	// ��ųâ

	// ����â

	// �κ��丮â

}

void MainPlayer::Update(float _DeltaTime)
{
	// ī�޶���ġ�� �÷��̾���ġ�� ���� ����
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());


}

