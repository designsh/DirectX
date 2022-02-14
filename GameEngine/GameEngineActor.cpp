#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor() :
	Level_(nullptr)
{
}

GameEngineActor::~GameEngineActor()
{
}

void GameEngineActor::Update(float _DeltaTime)
{
}

GameEngineLevel* GameEngineActor::GetLevel() const
{
	return Level_;
}

void GameEngineActor::SetLevel(GameEngineLevel* _Level)
{
	Level_ = _Level;
}
