#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineShaderResHelper.h"

// �з� : ������(Renderer)
// �뵵 : 
// ���� : 
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
	GameEngineRenderer(); // default constructer ����Ʈ ������
	~GameEngineRenderer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRenderer(const GameEngineRenderer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRenderer(GameEngineRenderer&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRenderer& operator=(const GameEngineRenderer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRenderer& operator=(const GameEngineRenderer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	void Start() override;

private:
	void Update(float _DeltaTime) override;
	virtual void Render();

public:
	void SetRenderingPipeLine(const std::string& _Value);
	virtual void SetRenderGroup(int _Order);
};

