#pragma once
#include "GameEngineRenderer.h"

// �з� : Image Renderer
// �뵵 : 
// ���� : 
class GameEngineImageRenderer : public GameEngineRenderer
{
private:	// member Var

public:
	GameEngineImageRenderer(); // default constructer ����Ʈ ������
	~GameEngineImageRenderer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineImageRenderer(const GameEngineImageRenderer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineImageRenderer(GameEngineImageRenderer&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineImageRenderer& operator=(const GameEngineImageRenderer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

private:
	void Start() override;

public:
	void SetImage(const std::string& _ImageName);
};

