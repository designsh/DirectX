#include "PreCompile.h"
#include "UserGame.h"

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

	// Sound Initialize
	GameEngineSound::GetInst().Initialize();
}

void UserGame::ResourcesLoad()
{
	// Game Resources Load Function

	// Sound Load
	GameEngineDirectroy SoundDir;
	SoundDir.MoveParent("DirectX");
	SoundDir.MoveChild("Resources");
	SoundDir.MoveChild("Sound");
	GameEngineSound::GetInst().LoadSound("introedit.wav", SoundDir.PathToPlusFileName("introedit.wav"));

	// Play Sound
	GameEngineSound::GetInst().PlaySoundOneShot("introedit.wav");
}

void UserGame::GameLoop()
{
	// GameLoop Function
	switch (_getch())
	{
	case 'q':
	case 'Q':
		EngineDestory();
		break;
	}
}

void UserGame::Release()
{
	// Game Release Function

	// Sound Release
	GameEngineSound::Destroy();
}

