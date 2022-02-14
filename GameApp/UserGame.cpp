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

struct TransformData
{
	float4x4 Scale;
	float4x4 Rotation;
	float4x4 Position;
	float4x4 World;
	float4x4 View;
	float4x4 Proj;

public:
	void CalcWorld()
	{
		World = Scale * Rotation * Position;
	}
};

float4 Pos;
TransformData TransData;

void UserGame::Initialize()
{
	TransData.View.ViewToLH({ 0.0f, 0.0f, -10.0f }, { 0.0f, 0.0f , 1.0f }, { 0.0f, 1.0f , 0.0f });

	TransData.Proj.OrthographicLH(1280.f, 720.f, 0.1f, 1000.0f);


	TransData.Scale.Scaling2D(200.0f);
	TransData.Rotation.RotationDeg({ 0.0f, 0.0f, 45.0f });
	TransData.Position.Translation({ 0.0f, 0.0f, 0.0f });
	TransData.CalcWorld();

	GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Find("ColorRendering");
	Pipe->ShaderHelper.SettingConstantBufferLink("TransformData", TransData);
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

