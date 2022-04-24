#include "PreCompile.h"
#include "GameEndMenuView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

GameEndMenuView::GameEndMenuView()
{
}

GameEndMenuView::~GameEndMenuView()
{
}

void GameEndMenuView::Start()
{



}

void GameEndMenuView::Update(float _DeltaTime)
{
}

void GameEndMenuView::LevelChangeEndEvent(GameEngineLevel* _NextLevel)
{
	// 타이틀 화면 or 로딩화면 or 캐릭터생성화면 or 캐릭터선택화면 or 엔딩화면 이동시 액터이동없음
	if (std::string::npos != _NextLevel->GetName().find("TitleLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("CreateCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("SelectCharacterLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("LoadingLevel"))
	{
		return;
	}
	else if (std::string::npos != _NextLevel->GetName().find("MapEditorLevel"))
	{
		return;
	}

	// 게임종료메뉴가 들고있는 모든 액터 넘김

}

void GameEndMenuView::InitGameEndMenuView()
{
}
