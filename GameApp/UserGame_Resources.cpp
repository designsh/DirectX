#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine/EngineVertex.h>
#include "UserGame_Resources_Shader.h"

// InGame Infomation
#include "AllSkillInfomation.h"
#include "AllMonsterInfomation.h"
#include "AllNPCInfomation.h"
#include "AllItemInfomation.h"

void UserGame::ResourcesLoad()
{
	// ======================================================= Resource Load ======================================================= // 

	// Sound Load
	GameEngineDirectory SoundDir;
	SoundDir.MoveParent("DirectX");
	SoundDir.MoveChild("Resources");
	SoundDir.MoveChild("Sound");
	std::vector<GameEngineFile> SoundAllFile = SoundDir.GetAllFile("wav", true); // true : �������͸� ��� �˻�
	for (size_t i = 0; i < SoundAllFile.size(); ++i)
	{
		GameEngineSoundManager::GetInst().Load(SoundAllFile[i].GetFullPath());
	}

	// Image Load
	GameEngineDirectory TextureDir;
	TextureDir.MoveParent("DirectX");
	TextureDir.MoveChild("Resources");
	TextureDir.MoveChild("Image");
	std::vector<GameEngineFile> TextureAllFile = TextureDir.GetAllFile("png", true); // true : �������͸� ��� �˻�
	for (size_t i = 0; i < TextureAllFile.size(); i++)
	{
		GameEngineTextureManager::GetInst().Load(TextureAllFile[i].GetFullPath());
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