#pragma once
#include "GameEngineComponent.h"

class TransformData
{
	// 월드
	float4 vWorldTranslation;
	float4 vWorldRotation;
	float4 vWorldScaling;

	// 로컬
	float4 vLocalTranslation;
	float4 vLocalRotation;
	float4 vLocalScaling;

	// 변환행렬
	float4x4 Scaling;
	float4x4 Rotation;
	float4x4 Translation;
	float4x4 Revolve;
	float4x4 Parent;
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
};

// 분류 : 트랜스폼
// 용도 : 
// 설명 : 위치, 크기, 회전에 대한 정보를 관리하며 
class GameEngineTransform
{
private:	// member Var
	TransformData										TransData_;		// 
	GameEngineTransform*						Parent_;				// 
	std::list<GameEngineTransform*>	Childs_;				// 

public:
	GameEngineTransform(); // default constructer 디폴트 생성자
	~GameEngineTransform(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineTransform(const GameEngineTransform& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineTransform(GameEngineTransform&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineTransform& operator=(const GameEngineTransform& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineTransform& operator=(const GameEngineTransform&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void SetParent(GameEngineTransform* _Parent);
	void DetachChild(GameEngineTransform* _Child);
};

