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

void UserGame::Initialize()
{
	// Game Initialize Function

	// Sound Initialize(FMOD)
	GameEngineSoundManager::GetInst().Initialize();
}

float RotAngle = 0.0f;

void UserGame::ResourcesLoad()
{
	// Game Resources Load Function

	// Sound Load
	GameEngineDirectroy SoundDir;
	SoundDir.MoveParent("DirectX");
	SoundDir.MoveChild("Resources");
	SoundDir.MoveChild("Sound");

	// true 옵션을 주는경우 해당 경로의 있는 하위디렉터리를 모두 검사하여 모든 파일을 로드
	std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("wav", true);
	//std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("wav");
	for (size_t i = 0; i < AllFile.size(); ++i)
	{
		GameEngineSoundManager::GetInst().LoadSound(AllFile[i].GetFullPath());
	}

	// Vertex Buffer 생성
	std::vector<float4> RectVertex = std::vector<float4>(4);
	RectVertex[0] = float4({ -0.5f, 0.5f, 0.5f });
	RectVertex[1] = float4({ 0.5f, 0.5f, 0.5f });
	RectVertex[2] = float4({ 0.5f, -0.5f, 0.5f });
	RectVertex[3] = float4({ -0.5f, -0.5f, 0.5f });

	GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex);

	// 인덱스 버퍼 생성
	std::vector<int> RectIndex = { 0,1,2, 0,2,3 };
	GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex);

	// C++ 람다식
	// 
	GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
	{
			float4 MovePos = { 200.0f, 200.0f };
			float4 Pos = _Value;
			Pos *= 100.0f;
			Pos.RotateZfloat2Degree(RotAngle);
			Pos += MovePos;

			return Pos;
	});

}

void UserGame::GameLoop()
{
	// 
	GameEngineRenderingPipeLine Pipe;

	Pipe.SetInputAssembler1("Rect");
	Pipe.SetVertexShader("TestShader");
	Pipe.SetInputAssembler2("Rect");

	RotAngle += 360.0f * GameEngineTime::GetInst().GetDeltaTime();

	Pipe.Rendering();
}

void UserGame::Release()
{
	// Game Release Function

	// Resource Release
	GameEngineIndexBufferManager::Destroy();
	GameEngineVertexShaderManager::Destroy();
	GameEngineVertexBufferManager::Destroy();
	GameEngineTextureManager::Destroy();
	GameEngineSoundManager::Destroy();

	// Base Release
	GameEngineTime::Destroy();
	GameEngineWindow::Destroy();
}

