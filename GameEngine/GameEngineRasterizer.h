#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRasterizer : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11RasterizerState*	State_;					// Rasterizer ����
	D3D11_VIEWPORT			ViewPort_;			// Viewport�� ġ���� ����
	D3D11_RECT						Scissor_;				// ����-�簢�� ġ���� ����

private:
	bool										SicssorFlag_;		// ����-�簢�� ���� ��� Flag

public:
	GameEngineRasterizer(); // default constructer ����Ʈ ������
	~GameEngineRasterizer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void SetViewPort(float _Width, float _Height, float _TopLeftX, float _TopLeftY, float _MinDepth, float _MaxDepth);
	void SetScissor(LONG _Left, LONG _Top, LONG _Right, LONG _Bottom);

public:
	void Create(const D3D11_RASTERIZER_DESC& _Value);

public:
	void SettingViewPort();

public:
	void SettingScissor();

public:
	void Setting();
};

