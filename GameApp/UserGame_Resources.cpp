#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine/EngineVertex.h>
#include "UserGame_Resources_Shader.h"

// InGame Infomation
#include "AllSkillInfomation.h"
#include "AllMonsterInfomation.h"
#include "AllNPCInfomation.h"
#include "AllItemInfomation.h"

void SoundLoading(GameEngineDirectory Dir)
{
	std::vector<GameEngineFile> SoundAllFile = Dir.GetAllFile();
	for (size_t i = 0; i < SoundAllFile.size(); ++i)
	{
		GameEngineSoundManager::GetInst().Load(SoundAllFile[i].GetFullPath());
	}

	--UserGame::LoadingSoundFolder;
}

void TextureLoading(GameEngineDirectory Dir)
{
	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();
	for (size_t i = 0; i < AllFile.size(); i++)
	{
		GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
	}
	--UserGame::LoadingImageFolder;
}

void UserGame::ResourcesLoad()
{
	// ======================================================= Resource Load ======================================================= // 

	// Sound Directory Serach 후 Thread Sound Load
	GameEngineDirectory SoundDir;
	SoundDir.MoveParent("DirectX");
	SoundDir.MoveChild("Resources");
	SoundDir.MoveChild("Sound");
	std::vector<GameEngineDirectory> AllSoundDir = SoundDir.GetAllDirectoryRecursive();
	LoadingSoundFolder = static_cast<int>(AllSoundDir.size());
	for (size_t i = 0; i < AllSoundDir.size(); i++)
	{
		GameEngineCore::ThreadQueue_.JobPost(std::bind(SoundLoading, AllSoundDir[i]));
	}

	// Image Directory Serach 후 Thread Image Load
	GameEngineDirectory TextureDir;
	TextureDir.MoveParent("DirectX");
	TextureDir.MoveChild("Resources");
	TextureDir.MoveChild("Image");
	std::vector<GameEngineDirectory> AllTextureDir = TextureDir.GetAllDirectoryRecursive();
	LoadingImageFolder = static_cast<int>(AllTextureDir.size());
	for (size_t i = 0; i < AllTextureDir.size(); i++)
	{
		GameEngineCore::ThreadQueue_.JobPost(std::bind(TextureLoading, AllTextureDir[i]));
	}

	// Font Load
	GameEngineFontManager::GetInst().Load("diablo");
	GameEngineFontManager::GetInst().Load("malgunbd");
	GameEngineFontManager::GetInst().Load("HMKMRHD");

	// 인게임 관련 모든 정보 로드(추후 로딩레벨로 이동 고민중.....)
	
	// 모든 클래스 스킬 정보
	AllSkillInfomation::GetInst().CreateAllSkillInfomation();

	// 구현하려는 모든 아이템 정보
	AllItemInfomation::GetInst().CreateAllItemInfomation();

	// 구현하려는 모든 몬스터 정보
	AllMonsterInfomation::GetInst().CreateAllMonsterInfomation();

	// 구현하려는 모든 NPC 정보
	AllNPCInfomation::GetInst().CreateAllNPCInfomation();

	// 셰이더 리소스 파일을 모두 읽어들여 셰이더를 생성
	//AppShaderLoad();
}