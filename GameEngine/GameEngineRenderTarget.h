#pragma once
#include "GameEngineDevice.h"
#include "GameEngineShaderResHelper.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineTexture;
class GameEngineRenderingPipeLine;
class GameEngineRenderTarget : public GameEngineObjectNameBase
{
private:	// member Var
	std::vector<GameEngineTexture*> ReleaseTextures_;
	std::vector<GameEngineTexture*> Textures_;
	std::vector<ID3D11RenderTargetView*> RenderTargetViews_;
	std::vector<float4> ClearColor_;

private:
	GameEngineRenderingPipeLine* Pipe_;
	GameEngineShaderResHelper Res_;

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
	void Create(float4 _Scale, float4 _ClearColor);
	void Create(GameEngineTexture* _Texture, float4 _ClearColor);

public:
	void Merge(GameEngineRenderTarget* _Other, int _Index = 0);		// ������ �׷��� �׸� ���� �� ����Ÿ���� �׸��� ��ģ��.
	void Copy(GameEngineRenderTarget* _Other);										// ������ ���� �׷����� �װ� �����. �־��ذɷ� �ٲ۴�.
};

