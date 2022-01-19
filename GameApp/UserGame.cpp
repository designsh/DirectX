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
float4 BoxPos = float4::ZERO;

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
	std::vector<float4> RectVertex = std::vector<float4>(4 * 6);
	RectVertex[0] = float4({ -0.5f, 0.5f, 0.5f });
	RectVertex[1] = float4({ 0.5f, 0.5f, 0.5f });
	RectVertex[2] = float4({ 0.5f, -0.5f, 0.5f });
	RectVertex[3] = float4({ -0.5f, -0.5f, 0.5f });

	// 앞면을 x축기준 180도 회전시켜 뒷면을 생성
	RectVertex[4] = float4::RotateXDegree(RectVertex[0], 180.0f);
	RectVertex[5] = float4::RotateXDegree(RectVertex[1], 180.0f);
	RectVertex[6] = float4::RotateXDegree(RectVertex[2], 180.0f);
	RectVertex[7] = float4::RotateXDegree(RectVertex[3], 180.0f);

	// 앞면을 y축기준 90도 회전시켜 왼쪽면 생성
	RectVertex[8] = float4::RotateYDegree(RectVertex[0], 90.0f);
	RectVertex[9] = float4::RotateYDegree(RectVertex[1], 90.0f);
	RectVertex[10] = float4::RotateYDegree(RectVertex[2], 90.0f);
	RectVertex[11] = float4::RotateYDegree(RectVertex[3], 90.0f);

	// 앞면을 y축기준 -90도 회전시켜 오른쪽면 생성
	RectVertex[12] = float4::RotateYDegree(RectVertex[0], -90.0f);
	RectVertex[13] = float4::RotateYDegree(RectVertex[1], -90.0f);
	RectVertex[14] = float4::RotateYDegree(RectVertex[2], -90.0f);
	RectVertex[15] = float4::RotateYDegree(RectVertex[3], -90.0f);

	// 앞면을 x축기준 90도 회전시켜 윗면 생성
	RectVertex[16] = float4::RotateXDegree(RectVertex[0], 90.0f);
	RectVertex[17] = float4::RotateXDegree(RectVertex[1], 90.0f);
	RectVertex[18] = float4::RotateXDegree(RectVertex[2], 90.0f);
	RectVertex[19] = float4::RotateXDegree(RectVertex[3], 90.0f);

	// 앞면을 x축기준 -90도 회전시켜 아랫면 생성
	RectVertex[20] = float4::RotateXDegree(RectVertex[0], -90.0f);
	RectVertex[21] = float4::RotateXDegree(RectVertex[1], -90.0f);
	RectVertex[22] = float4::RotateXDegree(RectVertex[2], -90.0f);
	RectVertex[23] = float4::RotateXDegree(RectVertex[3], -90.0f);

	GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex);

	// 인덱스 버퍼 생성
	// 각 정점을 연결시켜 정육면체를 생성하기 위하여 인덱스 버퍼 생성
	std::vector<int> RectIndex;
	for (int i = 0; i < 6; i++)
	{
		RectIndex.push_back(i * 4 + 0);
		RectIndex.push_back(i * 4 + 1);
		RectIndex.push_back(i * 4 + 2);

		RectIndex.push_back(i * 4 + 0);
		RectIndex.push_back(i * 4 + 2);
		RectIndex.push_back(i * 4 + 3);
	}

	GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex);

	// C++ 람다식
	// 
	GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
	{
		// 크자이공부(크기/자전(회전)/이동/공전/부모) 순으로 행렬을 곱해야한다.
		// 이유 : 일반적인 행렬은 교환법칙이 성립하지않으므로 순서가 달라지게되면 의도치않은 월드행렬이 생성된다.
		// 크기 * 자전(회전) * 이동 * 공전(항등) * 부모(항등) * 뷰행렬

		// 크기행렬
		float4x4 ScaleMat;
		ScaleMat.Scaling({ 100.0f, 100.0f, 100.0f });

		// 자전(회전) 행렬
		float4x4 RotMat;
		RotMat.RotationDeg({ 0.0f, 0.0f, RotAngle });

		// 이동행렬
		float4x4 PosMat;
		PosMat.Translation({ 0.0f, 0.0f, 0.0f });

		// 뷰행렬
		float4x4 ViewMat;

		// 부모


		// 크자이공부 순으로 각각의 행렬을 모두 곱하여 월드 행렬 생성
		float4x4 WorldMat = ScaleMat * RotMat * PosMat;

		float4 Pos = _Value;
		Pos *= WorldMat;


		//// 로컬세상(Local Space)에서 어떠한 물체를 변형
		//// 크기/위치/회전 변형
		//// 로컬세상에서는 각각의 물체가 각각의 원점과 축을 가진다.
		//float4 Pos = _Value;
		//float4 LocalScale = { 100.0f, 100.0f, 100.0f };
		//float4 LocalMove = { 100.0f, 0.0f };
		//float4 LocalRot = { 0.0f, 0.0f, RotAngle };
		//Pos *= LocalScale;
		//Pos.RotateXDegree(LocalRot.x);
		//Pos.RotateYDegree(LocalRot.y);
		//Pos.RotateZDegree(LocalRot.z);
		//Pos += BoxPos;

		//// 로컬세상(Local Space)에서 변형된 물체를 차원이동하여 월드세상(World Space)에 배치
		//// 단, 로컬세상에서의 각각의 물체를 월드세상의 원점(0,0,0)기준에서 배치하여
		//// 모든 물체에 대한 크기/위치/회전 변형을 가한다.
		//// 월드세상에는 모든 물체가 원점(0,0,0)을 기준으로 배치되며 하나의 원점과 그 원점에서의 축이 존재한다.
		//float4 SpaceScale = { 1.0f, -1.0f, 1.0f };
		//float4 SpaceRot = { 0.0f, 0.0f, 0.0f };
		//float4 SpaceMove = { 1280.0f * 0.5f, 720*0.5f, 0.0f};
		//Pos *= SpaceScale;
		//Pos.RotateXDegree(SpaceRot.x);
		//Pos.RotateYDegree(SpaceRot.y);
		//Pos.RotateZDegree(SpaceRot.z);
		//Pos += SpaceMove;

		//// 차원이동을 할때마다 어떠한 공간의 원점이 존재하며, 각 공간마다의 기준은 다르다.
		//// 그러므로 차원이동이 될때 공간에 대한 크기/위치/회전 변형이 일어나게 된다.
		//// 즉, 로컬세상에서의 물체가 각각 변형을 하고, 차원이동이 필요한 경우라면
		//// 해당 차원의 공간에서의 크기/위치/회전 정보를 통해서 차원의 기준을 맞춰줘야한다는 것이다.

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

	RotAngle += 20.f * GameEngineTime::GetInst().GetDeltaTime();

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

