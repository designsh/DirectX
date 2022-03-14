#pragma once
#include <GameEngine/GameEngineActor.h>

enum class MouseState
{
	Move,
	Stay
};

// 분류 : 마우스
// 용도 : 인게임 마우스
// 설명 : 
class GameEngineImageRenderer;
class GameEngineCollision;
class MouseObject : public GameEngineActor
{
private:	// member Var
	GameEngineImageRenderer* Mouse_;
	GameEngineCollision* MouseCollider_;

private:
	MouseState State_;

public:
	MouseObject();
	~MouseObject();

protected:		// delete constructer
	MouseObject(const MouseObject& _other) = delete;
	MouseObject(MouseObject&& _other) noexcept = delete;

private:		//delete operator
	MouseObject& operator=(const MouseObject& _other) = delete;
	MouseObject& operator=(const MouseObject&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

