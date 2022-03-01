#include "PreCompile.h"
#include "MainPlayer.h"

#include "BottomStateBar.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineRenderer.h>

MainPlayer::MainPlayer() :
	PlayerInfomation_(nullptr),
	PlayerImageRenderer_(nullptr),
	BottomStateBar_(nullptr)
{
}

MainPlayer::~MainPlayer()
{
}

void MainPlayer::Start()
{
	// �ӽ��׽�Ʈ��
	PlayerImageRenderer_ = CreateTransformComponent<GameEngineRenderer>(GetTransform());
	PlayerImageRenderer_->SetRenderingPipeLine("Color");
	PlayerImageRenderer_->GetTransform()->SetLocalScaling(float4(100.f, 100.f, 1.f));
	PlayerImageRenderer_->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.f, 1.f, 1.f));

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

