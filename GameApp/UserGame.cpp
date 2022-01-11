#include "PreCompile.h"
#include "UserGame.h"

#include <GameEngineBase/GameEngineTime.h>

#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineVertexBufferManager.h>

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

	// Play Sound

}

static float4 RectPoint[4] = { {0, 0}, {100, 0}, {100, 100}, {0, 100} };

void UserGame::GameLoop()
{
	POINT PolygonPoint[4] = {};
	for (size_t i = 0; i < 4; ++i)
	{
		RectPoint[i].Rotatefloat2Degree(45 * GameEngineTime::GetInst().GetDeltaTime());
	}

	for (size_t i = 0; i < 4; ++i)
	{
		PolygonPoint[i] = RectPoint[i].GetWindowPoint();
	}

	Polygon(GameEngineWindow::GetInst().GetWindowDC(), PolygonPoint, 4);
}

void UserGame::Release()
{
	// Game Release Function

	// Vertex Buffer Release
	GameEngineVertexBufferManager::Destroy();

	// Sound Release
	GameEngineSoundManager::Destroy();

	// Window Release
	GameEngineWindow::Destroy();
}

