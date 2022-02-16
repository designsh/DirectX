#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineTransform.h"

GameEngineActor::GameEngineActor() :
	Level_(nullptr),
	Transform_(nullptr)
{
}

GameEngineActor::~GameEngineActor()
{
	if (nullptr != Transform_)
	{
		delete Transform_;
		Transform_ = nullptr;
	}
}

GameEngineLevel* GameEngineActor::GetLevel() const
{
	return Level_;
}

void GameEngineActor::SetLevel(GameEngineLevel* _Level)
{
	Level_ = _Level;
}
