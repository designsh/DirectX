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

UserGame::UserGame()
{
}

UserGame::~UserGame()
{
}

void UserGame::Initialize()
{
	// ������ : Ÿ��Ʋ-ĳ���ͻ���-ĳ���ͼ���(����)-�ε�-����-īŸ��-ī��������
	LevelCreate<TitleLevel>("TitleLevel");
	LevelCreate<CreateCharacterLevel>("CreateCharacterLevel");
	LevelCreate<SelectCharacterLevel>("SelectCharacterLevel");
	LevelCreate<LoadingLevel>("LoadingLevel");
	LevelCreate<TownLevel>("TownLevel");
	LevelCreate<CatacombsLevel>("CatacombsLevel");
	LevelCreate<ChaosSanctuaryLevel>("ChaosSanctuaryLevel");
	LevelCreate<EndingLevel>("EndingLevel");

	LevelChange("TitleLevel");


	// �׽�Ʈ�� Ű����
	if (false == GameEngineInput::GetInst().IsKey("NextScene"))
	{
		GameEngineInput::GetInst().CreateKey("NextScene", 'N');
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
	return float4(1280.f, 720.f, 0.f);
}

