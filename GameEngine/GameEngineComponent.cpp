#include "PreCompile.h"
#include "GameEngineComponent.h"
#include "GameEngineActor.h"

GameEngineComponent::GameEngineComponent() :
	Actor_(nullptr),
	Level_(nullptr)
{
}

GameEngineComponent::~GameEngineComponent()
{
}

void GameEngineComponent::InitComponent(GameEngineActor* _Actor)
{
	// �θ� ����(ObjectBase)
	SetParent(_Actor);

	// �θ� ���͸� ����(Member Value)
	Actor_ = _Actor;

	// �θ������ ������ ���� ������ ��
	Level_ = Actor_->GetLevel();
}

