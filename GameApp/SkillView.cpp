#include "PreCompile.h"
#include "SkillView.h"

#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

#include "GlobalValue.h"

#include "MainPlayerInfomation.h"
#include "MainPlayer.h"

SkillView::SkillView() :
	PanelRenderer_(nullptr),
	CloseButton_(nullptr),
	MainCollider_(nullptr),
	ButtonState_(Button_State::Normal)
{
}

SkillView::~SkillView()
{
}

void SkillView::Start()
{

}

void SkillView::Update(float _DeltaTime)
{
}

void SkillView::InitSkillView()
{
}
