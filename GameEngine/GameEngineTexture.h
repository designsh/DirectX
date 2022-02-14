#pragma once
#include "GameEngineDevice.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTexture : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11Texture2D* Texture2D_;
	ID3D11RenderTargetView* RenderTargetView_;

public:
	GameEngineTexture(); // default constructer ����Ʈ ������
	~GameEngineTexture(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineTexture(const GameEngineTexture& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineTexture(GameEngineTexture&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineTexture& operator=(const GameEngineTexture& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineTexture& operator=(const GameEngineTexture&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Create(ID3D11Texture2D* _Texture2D);
	ID3D11RenderTargetView* CreateRenderTargetView();
};

