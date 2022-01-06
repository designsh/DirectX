#include "PreCompile.h"
#include "UserGame.h"

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

	// true 옵션을 주는경우 해당 경로의 있는 하위디렉터리를 모두 검사하여 모든 파일을 로드
	std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("wav", true);
	//std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("wav");
	for (size_t i = 0; i < AllFile.size(); ++i)
	{
		GameEngineSound::GetInst().LoadSound(AllFile[i].GetFullPath());
	}

	// Play Sound
	int a = 0;
}

void UserGame::GameLoop()
{

}

void UserGame::Release()
{
	// Game Release Function

	// Sound Release
	GameEngineSound::Destroy();
}

