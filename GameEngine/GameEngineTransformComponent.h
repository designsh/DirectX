#pragma once
#include "GameEngineComponent.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTransform;
class GameEngineTransformComponent : public GameEngineComponent
{
private:	// member Var
	GameEngineTransform* Transform;

public:
	GameEngineTransformComponent();
	~GameEngineTransformComponent();

protected:		// delete constructer
	GameEngineTransformComponent(const GameEngineTransformComponent& _other) = delete;
	GameEngineTransformComponent(GameEngineTransformComponent&& _other) noexcept = delete;

private:		//delete operator
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent& _other) = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent&& _other) = delete;

public:
	virtual void InitComponent(GameEngineActor* Actor_) override;
};

