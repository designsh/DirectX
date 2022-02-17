#pragma once
#include "GameEngineTransformComponent.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineRenderer : public GameEngineTransformComponent
{
	friend GameEngineLevel;

private:	// member Var

protected:
	GameEngineRenderingPipeLine* PipeLine_;

public:
	GameEngineRenderer(); // default constructer 디폴트 생성자
	~GameEngineRenderer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRenderer(const GameEngineRenderer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRenderer(GameEngineRenderer&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start();
	virtual void Render();

public:
	void SetRenderingPipeLine(const std::string& _Value);
};

