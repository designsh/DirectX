#include "PreCompile.h"
#include "BottomStateBar.h"

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

	// 하단상태바 틀
	BottomStateBar_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	BottomStateBar_->SetRenderingPipeLine("Texture");
	BottomStateBar_->ShaderHelper.SettingTexture("Tex", "Player_BottomStatBar_UI.png");
	BottomStateBar_->ShaderHelper.SettingConstantBufferSet("TextureCutData", float4(0.f, 0.f, 1.f, 1.f));
	BottomStateBar_->GetTransform()->SetLocalScaling(float4(WindowSize.x, ImageSize.y));
	BottomStateBar_->GetTransform()->SetLocalPosition(float4(0.f, ImageHarfSize.y - WindowHarfSize.y));

	// 액터 한개로 할지 쪼갤지 고민중......
	
	// 왼쪽무기 활성화 스킬버튼

	// 오른쪽무기 활성화 스킬버튼

	// 스태미나 활성/비활성 버튼

	// 스태미나 ProgressBar

	// 물약칸충돌체?

	// 미니메뉴관련

}

void BottomStateBar::Update(float _DeltaTime)
{
}
