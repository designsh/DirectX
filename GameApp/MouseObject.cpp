#include "PreCompile.h"
#include "MouseObject.h"

#include <GameEngine/GameEngineUIRenderer.h>

MouseObject::MouseObject() :
	Mouse_(nullptr)
{
}

MouseObject::~MouseObject()
{
}

void MouseObject::Start()
{
	Mouse_ = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	Mouse_->SetRenderingPipeLine("Texture");
	Mouse_->ShaderHelper.SettingTexture("Tex", "Mouse_Default.png");



	//Mouse_->GetTransform()->SetLocalScaling(float4(WindowSize.x, ImageSize.y));
	//Mouse_->GetTransform()->SetLocalPosition(float4(0.f, ImageHarfSize.y - WindowHarfSize.y));
}

void MouseObject::Update(float _DeltaTime)
{
	// 마우스 위치 갱신

}
