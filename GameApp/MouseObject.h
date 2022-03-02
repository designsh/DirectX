#pragma once
#include <GameEngine/GameEngineActor.h>

// �з� : ���콺
// �뵵 : �ΰ��� ���콺
// ���� : 
class GameEngineUIRenderer;
class MouseObject : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* Mouse_;

public:
	MouseObject();
	~MouseObject();

protected:		// delete constructer
	MouseObject(const MouseObject& _other) = delete;
	MouseObject(MouseObject&& _other) noexcept = delete;

private:		//delete operator
	MouseObject& operator=(const MouseObject& _other) = delete;
	MouseObject& operator=(const MouseObject&& _other) = delete;

public:
	void Start() override;
	void Update(float _DeltaTime) override;
};

