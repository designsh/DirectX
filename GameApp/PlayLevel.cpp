#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "Monster.h"
#include "TopUI.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::LevelChangeEndEvent()
{
}

void PlayLevel::LevelChangeStartEvent()
{
}

void PlayLevel::LevelStart()
{
	GetMainCamera()->SetProjectionMode(ProjectionMode::Orthographic);
	GetMainCamera()->GetTransform()->SetLocalPosition(float4(0.0f, 0.0f, -100.0f));

	Player* NewPlayer = CreateActor<Player>();
	GetMainCameraActor()->GetTransform()->SetWorldPosition(NewPlayer->GetTransform()->GetLocalPosition());

	Monster* NewMonster = CreateActor<Monster>();
	NewMonster->GetTransform()->SetWorldPosition(float4(200.0f, 0.0f, 0.0f));

	TopUI* NewUI = CreateActor<TopUI>();
	NewUI->GetTransform()->SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
}

void PlayLevel::LevelUpdate(float _DeltaTime)
{
}

