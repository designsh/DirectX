#include "PreCompile.h"
#include "UserGame.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>

#include <GameEngine/GameEngineRenderingPipeLine.h>

UserGame::UserGame() // default constructer ����Ʈ ������
{

}

UserGame::~UserGame() // default destructer ����Ʈ �Ҹ���
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

void UserGame::Initialize()
{

}

void UserGame::GameLoop()
{
	GameEngineDevice::RenderStart();

	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("BoxRendering");
	Pipe->Rendering();

	GameEngineDevice::RenderEnd();
}

void UserGame::Release()
{

}

float4 UserGame::StartWindowPos()
{
	return float4(0.f, 0.f, 0.f);
}

float4 UserGame::StartWindowSize()
{
	return float4(1280.f, 720.f, 0.f);
}

