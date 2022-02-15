#pragma once
#include "GameEngineComponent.h"

class TransformData
{
	// ����
	float4 vWorldTranslation;
	float4 vWorldRotation;
	float4 vWorldScaling;

	// ����
	float4 vLocalTranslation;
	float4 vLocalRotation;
	float4 vLocalScaling;

	// ��ȯ���
	float4x4 Scaling;
	float4x4 Rotation;
	float4x4 Translation;
	float4x4 Revolve;
	float4x4 Parent;
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
};

// �з� : Ʈ������
// �뵵 : 
// ���� : ��ġ, ũ��, ȸ���� ���� ������ �����ϸ� 
class GameEngineTransform
{
private:	// member Var
	TransformData										TransData_;		// 
	GameEngineTransform*						Parent_;				// 
	std::list<GameEngineTransform*>	Childs_;				// 

public:
	GameEngineTransform(); // default constructer ����Ʈ ������
	~GameEngineTransform(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineTransform(const GameEngineTransform& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineTransform(GameEngineTransform&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineTransform& operator=(const GameEngineTransform& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineTransform& operator=(const GameEngineTransform&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void SetParent(GameEngineTransform* _Parent);
	void DetachChild(GameEngineTransform* _Child);
};

