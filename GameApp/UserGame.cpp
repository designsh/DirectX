#include "PreCompile.h"
#include "UserGame.h"

#include <GameEngine/GameEngineRenderingPipeLine.h>

// Level
#include "TitleLevel.h"
#include "CreateCharacterLevel.h"
#include "SelectCharacterLevel.h"
#include "LoadingLevel.h"
#include "TownLevel.h"
#include "CatacombsLevel.h"
#include "EndingLevel.h"
#include "MapEditorLevel.h"

// InGame Infomation
#include "MainPlayerInfomation.h"
#include "AllSkillInfomation.h"
#include "AllItemInfomation.h"
#include "AllMonsterInfomation.h"
#include "AllNPCInfomation.h"

// IMGUI Window View
#include <GameEngine/GameEngineLevelControlWindow.h>

std::atomic<int> UserGame::LoadingImageFolder = 0;
std::atomic<int> UserGame::LoadingSoundFolder = 0;

UserGame::UserGame()
{
}

UserGame::~UserGame()
{
	// �����÷��̾� ���� ������
	MainPlayerInfomation::Destroy();

	// ��ų ���� ������
	AllSkillInfomation::Destroy();

	// ���� ���� ������
	AllMonsterInfomation::Destroy();

	// NPC ���� ������
	AllNPCInfomation::Destroy();

	// ������ ���� ������
	AllItemInfomation::Destroy();
}

void UserGame::Initialize()
{
	// ���Ǿ��� ���÷����� �̵��ϴ� ������â ����
	GameEngineGUI::GetInst()->CreateGUIWindow<GameEngineLevelControlWindow>("LevelControlWindow");

	// ������ : Ÿ��Ʋ-ĳ���ͻ���-ĳ���ͼ���(����)-�ε�-����-īŸ��(����óġ)-����
	LevelCreate<TitleLevel>("TitleLevel");
	LevelCreate<CreateCharacterLevel>("CreateCharacterLevel");
	LevelCreate<SelectCharacterLevel>("SelectCharacterLevel");
	LevelCreate<LoadingLevel>("LoadingLevel");
	LevelCreate<TownLevel>("TownLevel");
	LevelCreate<CatacombsLevel>("CatacombsLevel");
	LevelCreate<EndingLevel>("EndingLevel");

	// �׿� : Ÿ�ϸʿ�����
	LevelCreate<MapEditorLevel>("MapEditorLevel");
	
	// ����ȭ�� ����
	LevelChange("TitleLevel");

	// �׽�Ʈ�� Ű����
	if (false == GameEngineInput::GetInst().IsKey("NextScene"))
	{
		GameEngineInput::GetInst().CreateKey("NextScene", 'N');
	}

	// ����ī�޶�
	if (false == GameEngineInput::GetInst().IsKey("FREECAMERA"))
	{
		GameEngineInput::GetInst().CreateKey("FREECAMERA", 'L');
	}

	//=========================== Ű���� ===========================//

	// ���콺 ���ʹ�ư
	if (false == GameEngineInput::GetInst().IsKey("MouseLButton"))
	{
		GameEngineInput::GetInst().CreateKey("MouseLButton", VK_LBUTTON);
	}

	// ���콺 �����ʹ�ư
	if (false == GameEngineInput::GetInst().IsKey("MouseRButton"))
	{
		GameEngineInput::GetInst().CreateKey("MouseRButton", VK_RBUTTON);
	}

	// ����Ű(Ư�� UIȰ��ȭ���� Űüũ)
	//if (false == GameEngineInput::GetInst().IsKey("UP"))
	//{
	//	GameEngineInput::GetInst().CreateKey("UP", VK_UP);
	//}
	//if (false == GameEngineInput::GetInst().IsKey("DOWN"))
	//{
	//	GameEngineInput::GetInst().CreateKey("DOWN", VK_DOWN);
	//}

	// ������� ����
	if (false == GameEngineInput::GetInst().IsKey("VolumeUp"))
	{
		GameEngineInput::GetInst().CreateKey("VolumeUp", VK_UP);
	}
	if (false == GameEngineInput::GetInst().IsKey("VolumeDown"))
	{
		GameEngineInput::GetInst().CreateKey("VolumeDown", VK_DOWN);
	}
}

void UserGame::Release()
{

}

float4 UserGame::StartWindowPos()
{
	return float4(0.f, 0.f, 0.f);
}

float4 UserGame::StartWindowSize()
{
	return float4(800.f, 600.f, 0.f);
}

