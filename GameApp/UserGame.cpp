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
#include "ChaosSanctuaryLevel.h"
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
	// 메인플레이어 정보 릴리즈
	MainPlayerInfomation::Destroy();

	// 스킬 정보 릴리즈
	AllSkillInfomation::Destroy();

	// 몬스터 정보 릴리즈
	AllMonsterInfomation::Destroy();

	// NPC 정보 릴리즈
	AllNPCInfomation::Destroy();

	// 아이템 정보 릴리즈
	AllItemInfomation::Destroy();
}

void UserGame::Initialize()
{
	// 조건없이 선택레벨로 이동하는 윈도우창 생성
	GameEngineGUI::GetInst()->CreateGUIWindow<GameEngineLevelControlWindow>("LevelControlWindow");

	// 씬구성 : 타이틀-캐릭터생성-캐릭터선택(보류)-로딩-마을-카타콤-카오스생츄어리
	LevelCreate<TitleLevel>("TitleLevel");
	LevelCreate<CreateCharacterLevel>("CreateCharacterLevel");
	LevelCreate<SelectCharacterLevel>("SelectCharacterLevel");
	LevelCreate<LoadingLevel>("LoadingLevel");
	LevelCreate<TownLevel>("TownLevel");
	LevelCreate<CatacombsLevel>("CatacombsLevel");
	LevelCreate<ChaosSanctuaryLevel>("ChaosSanctuaryLevel");
	LevelCreate<EndingLevel>("EndingLevel");

	// 그외 : 타일맵에디터
	LevelCreate<MapEditorLevel>("MapEditorLevel");
	
	LevelChange("TitleLevel");


	// 테스트용 키생성
	if (false == GameEngineInput::GetInst().IsKey("NextScene"))
	{
		GameEngineInput::GetInst().CreateKey("NextScene", 'N');
	}

	//=========================== 키생성 ===========================//

	// 마우스 왼쪽버튼
	if (false == GameEngineInput::GetInst().IsKey("MouseLButton"))
	{
		GameEngineInput::GetInst().CreateKey("MouseLButton", VK_LBUTTON);
	}

	// 마우스 오른쪽버튼
	if (false == GameEngineInput::GetInst().IsKey("MouseRButton"))
	{
		GameEngineInput::GetInst().CreateKey("MouseRButton", VK_RBUTTON);
	}

	// 방향키(특정 UI활성화에만 키체크)
	if (false == GameEngineInput::GetInst().IsKey("UP"))
	{
		GameEngineInput::GetInst().CreateKey("UP", VK_UP);
	}
	if (false == GameEngineInput::GetInst().IsKey("DOWN"))
	{
		GameEngineInput::GetInst().CreateKey("DOWN", VK_DOWN);
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

