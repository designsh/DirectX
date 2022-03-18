#pragma once
#include "GameEngineImageRenderer.h"

// 분류 : UI Renderer
// 용도 : 
// 설명 : 
class GameEngineTexture;
class GameEngineFolderTexture;
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineUIRenderer : public GameEngineImageRenderer
{
private:	// member Var

public:
	GameEngineUIRenderer(); // default constructer 디폴트 생성자
	~GameEngineUIRenderer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineUIRenderer(const GameEngineUIRenderer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineUIRenderer(GameEngineUIRenderer&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;

public:
	void SetRenderGroup(int _Order) override;
};

