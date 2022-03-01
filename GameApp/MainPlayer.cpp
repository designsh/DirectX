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
	// 임시테스트용
	PlayerImageRenderer_ = CreateTransformComponent<GameEngineRenderer>(GetTransform());
	PlayerImageRenderer_->SetRenderingPipeLine("Color");
	PlayerImageRenderer_->GetTransform()->SetLocalScaling(float4(100.f, 100.f, 1.f));
	PlayerImageRenderer_->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.f, 1.f, 1.f));

	// 하단 상태바
	BottomStateBar_ = GetLevel()->CreateActor<BottomStateBar>();

	// 스킬창

	// 스탯창

	// 인벤토리창

}

void MainPlayer::Update(float _DeltaTime)
{
	// 카메라위치를 플레이어위치에 따라 갱신
	GetLevel()->GetMainCameraActor()->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());


}

