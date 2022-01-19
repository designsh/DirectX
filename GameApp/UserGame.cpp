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

	// true �ɼ��� �ִ°�� �ش� ����� �ִ� �������͸��� ��� �˻��Ͽ� ��� ������ �ε�
	std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("wav", true);
	//std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("wav");
	for (size_t i = 0; i < AllFile.size(); ++i)
	{
		GameEngineSoundManager::GetInst().LoadSound(AllFile[i].GetFullPath());
	}

	// Vertex Buffer ����
	std::vector<float4> RectVertex = std::vector<float4>(4 * 6);
	RectVertex[0] = float4({ -0.5f, 0.5f, 0.5f });
	RectVertex[1] = float4({ 0.5f, 0.5f, 0.5f });
	RectVertex[2] = float4({ 0.5f, -0.5f, 0.5f });
	RectVertex[3] = float4({ -0.5f, -0.5f, 0.5f });

	// �ո��� x����� 180�� ȸ������ �޸��� ����
	RectVertex[4] = float4::RotateXDegree(RectVertex[0], 180.0f);
	RectVertex[5] = float4::RotateXDegree(RectVertex[1], 180.0f);
	RectVertex[6] = float4::RotateXDegree(RectVertex[2], 180.0f);
	RectVertex[7] = float4::RotateXDegree(RectVertex[3], 180.0f);

	// �ո��� y����� 90�� ȸ������ ���ʸ� ����
	RectVertex[8] = float4::RotateYDegree(RectVertex[0], 90.0f);
	RectVertex[9] = float4::RotateYDegree(RectVertex[1], 90.0f);
	RectVertex[10] = float4::RotateYDegree(RectVertex[2], 90.0f);
	RectVertex[11] = float4::RotateYDegree(RectVertex[3], 90.0f);

	// �ո��� y����� -90�� ȸ������ �����ʸ� ����
	RectVertex[12] = float4::RotateYDegree(RectVertex[0], -90.0f);
	RectVertex[13] = float4::RotateYDegree(RectVertex[1], -90.0f);
	RectVertex[14] = float4::RotateYDegree(RectVertex[2], -90.0f);
	RectVertex[15] = float4::RotateYDegree(RectVertex[3], -90.0f);

	// �ո��� x����� 90�� ȸ������ ���� ����
	RectVertex[16] = float4::RotateXDegree(RectVertex[0], 90.0f);
	RectVertex[17] = float4::RotateXDegree(RectVertex[1], 90.0f);
	RectVertex[18] = float4::RotateXDegree(RectVertex[2], 90.0f);
	RectVertex[19] = float4::RotateXDegree(RectVertex[3], 90.0f);

	// �ո��� x����� -90�� ȸ������ �Ʒ��� ����
	RectVertex[20] = float4::RotateXDegree(RectVertex[0], -90.0f);
	RectVertex[21] = float4::RotateXDegree(RectVertex[1], -90.0f);
	RectVertex[22] = float4::RotateXDegree(RectVertex[2], -90.0f);
	RectVertex[23] = float4::RotateXDegree(RectVertex[3], -90.0f);

	GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex);

	// �ε��� ���� ����
	// �� ������ ������� ������ü�� �����ϱ� ���Ͽ� �ε��� ���� ����
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

	// C++ ���ٽ�
	// 
	GameEngineVertexShaderManager::GetInst().Create("TestShader", [](const float4& _Value)
	{
		// ũ���̰���(ũ��/����(ȸ��)/�̵�/����/�θ�) ������ ����� ���ؾ��Ѵ�.
		// ���� : �Ϲ����� ����� ��ȯ��Ģ�� �������������Ƿ� ������ �޶����ԵǸ� �ǵ�ġ���� ��������� �����ȴ�.
		// ũ�� * ����(ȸ��) * �̵� * ����(�׵�) * �θ�(�׵�) * �����

		// ũ�����
		float4x4 ScaleMat;
		ScaleMat.Scaling({ 100.0f, 100.0f, 100.0f });

		// ����(ȸ��) ���
		float4x4 RotMat;
		RotMat.RotationDeg({ 0.0f, 0.0f, RotAngle });

		// �̵����
		float4x4 PosMat;
		PosMat.Translation({ 0.0f, 0.0f, 0.0f });

		// �����
		float4x4 ViewMat;

		// �θ�


		// ũ���̰��� ������ ������ ����� ��� ���Ͽ� ���� ��� ����
		float4x4 WorldMat = ScaleMat * RotMat * PosMat;

		float4 Pos = _Value;
		Pos *= WorldMat;


		//// ���ü���(Local Space)���� ��� ��ü�� ����
		//// ũ��/��ġ/ȸ�� ����
		//// ���ü��󿡼��� ������ ��ü�� ������ ������ ���� ������.
		//float4 Pos = _Value;
		//float4 LocalScale = { 100.0f, 100.0f, 100.0f };
		//float4 LocalMove = { 100.0f, 0.0f };
		//float4 LocalRot = { 0.0f, 0.0f, RotAngle };
		//Pos *= LocalScale;
		//Pos.RotateXDegree(LocalRot.x);
		//Pos.RotateYDegree(LocalRot.y);
		//Pos.RotateZDegree(LocalRot.z);
		//Pos += BoxPos;

		//// ���ü���(Local Space)���� ������ ��ü�� �����̵��Ͽ� ���弼��(World Space)�� ��ġ
		//// ��, ���ü��󿡼��� ������ ��ü�� ���弼���� ����(0,0,0)���ؿ��� ��ġ�Ͽ�
		//// ��� ��ü�� ���� ũ��/��ġ/ȸ�� ������ ���Ѵ�.
		//// ���弼�󿡴� ��� ��ü�� ����(0,0,0)�� �������� ��ġ�Ǹ� �ϳ��� ������ �� ���������� ���� �����Ѵ�.
		//float4 SpaceScale = { 1.0f, -1.0f, 1.0f };
		//float4 SpaceRot = { 0.0f, 0.0f, 0.0f };
		//float4 SpaceMove = { 1280.0f * 0.5f, 720*0.5f, 0.0f};
		//Pos *= SpaceScale;
		//Pos.RotateXDegree(SpaceRot.x);
		//Pos.RotateYDegree(SpaceRot.y);
		//Pos.RotateZDegree(SpaceRot.z);
		//Pos += SpaceMove;

		//// �����̵��� �Ҷ����� ��� ������ ������ �����ϸ�, �� ���������� ������ �ٸ���.
		//// �׷��Ƿ� �����̵��� �ɶ� ������ ���� ũ��/��ġ/ȸ�� ������ �Ͼ�� �ȴ�.
		//// ��, ���ü��󿡼��� ��ü�� ���� ������ �ϰ�, �����̵��� �ʿ��� �����
		//// �ش� ������ ���������� ũ��/��ġ/ȸ�� ������ ���ؼ� ������ ������ ��������Ѵٴ� ���̴�.

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

