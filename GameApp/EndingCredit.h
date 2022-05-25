#pragma once
#include <GameEngine/GameEngineActor.h>

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineUIRenderer;
class EndingCredit : public GameEngineActor
{
private:	// member Var
	GameEngineUIRenderer* EndingCredit_;

public:
	EndingCredit();
	~EndingCredit();

protected:		// delete constructer
	EndingCredit(const EndingCredit& _other) = delete;
	EndingCredit(EndingCredit&& _other) noexcept = delete;

private:		//delete operator
	EndingCredit& operator=(const EndingCredit& _other) = delete;
	EndingCredit& operator=(const EndingCredit&& _other) = delete;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

