#pragma once
#include "GameEngineDevice.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTexture;
class GameEngineRenderTarget : public GameEngineObjectNameBase
{
private:	// member Var
	std::vector<GameEngineTexture*> Textures_;
	std::vector<ID3D11RenderTargetView*> RenderTargetViews_;
	std::vector<float4> ClearColor_;

public:
	GameEngineRenderTarget(); // default constructer ����Ʈ ������
	~GameEngineRenderTarget(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRenderTarget(const GameEngineRenderTarget& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRenderTarget(GameEngineRenderTarget&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Clear();
	void Setting(int _Index = -1);

public:
	void Create(const std::string _TextureName, float4 _ClearColor);
};

