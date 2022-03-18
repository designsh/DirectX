#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// 분류 : 렌더러(Renderer)
// 용도 : 
// 설명 : 
class GameEngineLevel;
class CameraComponent;
class GameEngineRenderingPipeLine;
class GameEngineRenderer : public GameEngineTransformComponent
{
	friend GameEngineLevel;
	friend CameraComponent;

private:	// member Var

public:
	GameEngineShaderResHelper ShaderHelper;

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

protected:
	void Start() override;

private:
	void Update(float _DeltaTime) override;
	virtual void Render();

public:
	void SetRenderingPipeLine(const std::string& _Value);
	virtual void SetRenderGroup(int _Order);
};

