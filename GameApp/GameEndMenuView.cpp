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
	// Ÿ��Ʋ ȭ�� or �ε�ȭ�� or ĳ���ͻ���ȭ�� or ĳ���ͼ���ȭ�� or ����ȭ�� �̵��� �����̵�����
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

	// ��������޴��� ����ִ� ��� ���� �ѱ�

}

void GameEndMenuView::InitGameEndMenuView()
{
}
