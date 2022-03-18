#pragma once
#include "GameEngineImageRenderer.h"

// �з� : UI Renderer
// �뵵 : 
// ���� : 
class GameEngineTexture;
class GameEngineFolderTexture;
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineUIRenderer : public GameEngineImageRenderer
{
private:	// member Var

public:
	GameEngineUIRenderer(); // default constructer ����Ʈ ������
	~GameEngineUIRenderer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineUIRenderer(const GameEngineUIRenderer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineUIRenderer(GameEngineUIRenderer&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;

public:
	void SetRenderGroup(int _Order) override;
};

