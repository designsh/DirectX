#pragma once
#include "GameEngineRenderer.h"

// 분류 : Image Renderer
// 용도 : 
// 설명 : 
class GameEngineImageRenderer : public GameEngineRenderer
{
private:	// member Var

public:
	GameEngineImageRenderer(); // default constructer 디폴트 생성자
	~GameEngineImageRenderer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineImageRenderer(const GameEngineImageRenderer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineImageRenderer(GameEngineImageRenderer&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

private:
	void Start() override;

public:
	void SetImage(const std::string& _ImageName);
};

