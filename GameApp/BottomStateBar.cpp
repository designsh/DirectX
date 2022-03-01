#include "PreCompile.h"
#include "BottomStateBar.h"

#include <GameEngine/GameEngineImageRenderer.h>
#include <GameEngine/GameEngineUIRenderer.h>

BottomStateBar::BottomStateBar() :
	BottomStateBar_(nullptr)
{
}

BottomStateBar::~BottomStateBar()
{
}

void BottomStateBar::Start()
{
	GameEngineTexture* BottomStateBarImage = GameEngineTextureManager::GetInst().Find("Player_BottomStatBar_UI.png");
	float4 WindowSize = GameEngineWindow::GetInst().GetSize();
	float4 WindowHarfSize = WindowSize.halffloat4();
	float4 ImageSize = BottomStateBarImage->GetImageSize();
	float4 ImageHarfSize = ImageSize.halffloat4();

	// 현재 ImageRenderer사용 -> 코드 적용시 UIRenderer로 변경
	// 단, UIRenderer에 텍스쳐 셋팅하는 기능 추가 필요
	BottomStateBar_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
	BottomStateBar_->SetImage("Player_BottomStatBar_UI.png", float4(WindowSize.x, ImageSize.y));
	BottomStateBar_->GetTransform()->SetLocalPosition(float4(0.f, ImageHarfSize.y - WindowHarfSize.y));
}

void BottomStateBar::Update(float _DeltaTime)
{
}
