#include "PreCompile.h"
#include "GameEngineUIRenderer.h"
#include "GameEngineLevel.h"
#include "CameraComponent.h"

GameEngineUIRenderer::GameEngineUIRenderer()
{
}

GameEngineUIRenderer::~GameEngineUIRenderer()
{
}

void GameEngineUIRenderer::Start()
{
	GetLevel()->GetUICamera()->PushRenderer(GetOrder(), this);
}
