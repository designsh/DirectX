#include "PreCompile.h"
#include "TopUI.h"
#include "GameEngine/GameEngineUIRenderer.h"

TopUI::TopUI()
{
}

TopUI::~TopUI()
{
}

void TopUI::Start()
{
	GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
	Renderer->SetRenderingPipeLine("Color");
	Renderer->GetTransform()->SetLocalScaling({ 1280.0f, 100.0f, 1.0f });
	Renderer->GetTransform()->SetLocalPosition({ 0.0f, 360.0f - 50.0f, 0.0f });
	Renderer->ShaderHelper.SettingConstantBufferSet("ResultColor", float4(1.0f, 0.0f, 1.0f));

}
