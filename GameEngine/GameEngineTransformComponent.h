#pragma once
#include "GameEngineComponent.h"
#include "GameEngineTransform.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineTransformComponent : public GameEngineComponent
{
	friend GameEngineActor;

private:	// member Var
	GameEngineTransform Transform_;

public:
	GameEngineTransformComponent();
	virtual ~GameEngineTransformComponent() = 0;

protected:		// delete constructer
	GameEngineTransformComponent(const GameEngineTransformComponent& _other) = delete;
	GameEngineTransformComponent(GameEngineTransformComponent&& _other) noexcept = delete;

private:		//delete operator
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent& _other) = delete;
	GameEngineTransformComponent& operator=(const GameEngineTransformComponent&& _other) = delete;

public:
	GameEngineTransform* GetTransform();

public:
	void AttachTransform(GameEngineTransform* _Transform);
};

