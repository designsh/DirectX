#pragma once
#include "GameEngineTransformComponent.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineRenderer : public GameEngineTransformComponent
{
	friend GameEngineLevel;

private:	// member Var

protected:
	GameEngineRenderingPipeLine* PipeLine_;

public:
	GameEngineRenderer(); // default constructer ����Ʈ ������
	~GameEngineRenderer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRenderer(const GameEngineRenderer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRenderer(GameEngineRenderer&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start();
	virtual void Render();

public:
	void SetRenderingPipeLine(const std::string& _Value);
};

