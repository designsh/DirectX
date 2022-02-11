#include "PreCompile.h"
#include "UserGame.h"

#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineWindow.h>

#include <GameEngine/GameEngineRenderingPipeLine.h>

UserGame::UserGame() // default constructer 디폴트 생성자
{

}

UserGame::~UserGame() // default destructer 디폴트 소멸자
{

}

UserGame::UserGame(UserGame&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
{

}

struct TransformData
{
	float4x4 World;
	float4x4 View;
	float4x4 Proj;
};

float4 Pos;
TransformData TransData;

void UserGame::Initialize()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	Pipe->ShaderHelper.SettingConstantBufferLink("TransformData", TransData);
}

void UserGame::GameLoop()
{
	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");



	// Update
	//Pos.x += 0.001f;
	//TransData.World.RotationXDeg(Pos.x);

	// Rendering
	GameEngineDevice::RenderStart();
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

