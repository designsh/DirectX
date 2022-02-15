#pragma once

// 분류 : 컴포넌트
// 용도 : 
// 설명 : 
class GameEngineActor;
class GameEngineComponent : public GameEngineObjectNameBase
{
private:	// member Var
	GameEngineActor* Actor_;

public:
	GameEngineComponent();
	~GameEngineComponent();

protected:		// delete constructer
	GameEngineComponent(const GameEngineComponent& _other) = delete;
	GameEngineComponent(GameEngineComponent&& _other) noexcept = delete;

private:		//delete operator
	GameEngineComponent& operator=(const GameEngineComponent& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineComponent& operator=(const GameEngineComponent&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	GameEngineActor* GetActor()
	{
		return Actor_;
	}

public:
	virtual void InitComponent(GameEngineActor* _Actor);
};

