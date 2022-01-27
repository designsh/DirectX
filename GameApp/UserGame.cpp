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

}

float RotAngle = 0.0f;
float4 BoxPos = float4::ZERO;

void UserGame::ResourcesLoad()
{
	// Game Resources Load Function

	// Sound Load
	GameEngineDirectory SoundDir;
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

		//// 크기행렬
		//float4x4 ScaleMat;
		//ScaleMat.Scaling({ 20.f, 20.f, 20.f });

		//// 자전(회전) 행렬
		//float4x4 RotMat;
		//RotMat.RotationDeg({ 0.0f, 0.0f, 0.0f });

		//// 이동행렬
		//float4x4 PosMat;
		////PosMat.Translation({ 0.0f, 0.0f, 0.0f });
		//PosMat.Translation(BoxPos);

		//// 뷰행렬
		//float4x4 ViewMat;
		//ViewMat.ViewToLH({ 0.0f, 0.0f, -2000.0f }, {0.f, 0.f, 1.f}, { 0.0f, 1.0f, 0.0f }); // 관측자가 FDir을 바라보고 있다.
		////ViewMat.ViewAt({ 0.0f, 0.0f, -2000.0f }, { 0, 0, 0 }, { 0.0f, 1.0f, 0.0f }); // 관측자가 (0,0,0)에 있는 물체를 바라보고있다.

		//// 원근투영
		//float4x4 PerspectiveMat;
		//PerspectiveMat.PerspectiveFovLH(60.0f, 1280.0f, 720.0f, 0.1f, 1000.0f);

		//// 직교투영
		//float4x4 OrthographicMat;
		//OrthographicMat.OrthographicLH(1280.0f, 720.0f, 0.1f, 1000.0f);

		//// 크자이공부 순으로 각각의 행렬을 모두 곱하여 월드 행렬 생성
		//float4x4 WorldMat = ScaleMat * RotMat * PosMat;

		//// 월드행렬 * 뷰행렬 * 원근투영
		//float4x4 WorldViewProjectionMat = WorldMat * ViewMat * PerspectiveMat;

		//// 월드행렬 * 뷰행렬 * 직교투영
		//float4x4 WorldViewOrthographicMat = WorldMat * ViewMat * OrthographicMat;

		//float4 PersPos = _Value;
		//PersPos *= WorldViewProjectionMat;

		//float4 OrthPos = _Value;
		//OrthPos *= WorldViewOrthographicMat;

		float4 PersPos = _Value;
		return PersPos;

		return PersPos;
	});

	GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("TestReasterizer");
	Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

void UserGame::GameLoop()
{
	GameEngineDirectXDevice::RenderStart();

	// 
	//GameEngineRenderingPipeLine Pipe;

	//Pipe.SetInputAssembler1("Rect");
	//Pipe.SetVertexShader("TestShader");
	//Pipe.SetInputAssembler2("Rect");
	//Pipe.SetRasterizer("TestReasterizer");

	//RotAngle += 20.f * GameEngineTime::GetInst().GetDeltaTime();
	//BoxPos.x += 10.0f * GameEngineTime::GetInst().GetDeltaTime();

	//Pipe.Rendering();

	GameEngineDirectXDevice::RenderEnd();
}

void UserGame::Release()
{

}

