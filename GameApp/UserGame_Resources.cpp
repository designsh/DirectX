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

	// Sound Directory Serach �� Thread Sound Load
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

	// Image Directory Serach �� Thread Image Load
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

	// �ΰ��� ���� ��� ���� �ε�(���� �ε������� �̵� �����.....)
	
	// ��� Ŭ���� ��ų ����
	AllSkillInfomation::GetInst().CreateAllSkillInfomation();

	// �����Ϸ��� ��� ������ ����
	AllItemInfomation::GetInst().CreateAllItemInfomation();

	// �����Ϸ��� ��� ���� ����
	AllMonsterInfomation::GetInst().CreateAllMonsterInfomation();

	// �����Ϸ��� ��� NPC ����
	AllNPCInfomation::GetInst().CreateAllNPCInfomation();

	// ���̴� ���ҽ� ������ ��� �о�鿩 ���̴��� ����
	//AppShaderLoad();
}