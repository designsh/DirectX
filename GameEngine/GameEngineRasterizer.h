#pragma once
#include "GameEngineDevice.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineRasterizer : public GameEngineObjectNameBase
{
private:	// member Var
	// ��������Ǹ� ���� �ΰ��� ����(SOLID, WIREFRAME)�� �������� ��ü ����
	ID3D11RasterizerState*		State_;								// �ʱ� : SOLD�� Rasterizer ����
	ID3D11RasterizerState*		OldState_;						// �ʱ� : WIREFRAME�� Rasterizer ����

private:
	D3D11_RASTERIZER_DESC Desc_;								// D3D11_RASTERIZER_DESC.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID �� ��������
	D3D11_RASTERIZER_DESC WireDesc_;						// D3D11_RASTERIZER_DESC.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME �� ��������

private:
	D3D11_VIEWPORT				ViewPort_;						// Viewport�� ġ���� ����

private:
	std::vector<D3D11_RECT>	ScissorRects_;					// ����-�簢�� ġ���� ����(������ ������ �����ϹǷ� ���ͷ� ����)
	int												ChangeScissorIndex_;	// ����-�簢����� �� ���� ����� ġ������
	
public:
	GameEngineRasterizer(); // default constructer ����Ʈ ������
	~GameEngineRasterizer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineRasterizer(const GameEngineRasterizer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineRasterizer(GameEngineRasterizer&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineRasterizer& operator=(const GameEngineRasterizer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public: // Solid <-> WireFrame Rasterizer State Change
	void SwitchState();

public: // ViewPort
	void SetViewPort(float _Width, float _Height, float _TopLeftX, float _TopLeftY, float _MinDepth, float _MaxDepth);

public: // Add Scissor & Current Scissor Change
	void PushScissorRect(D3D11_RECT _Rect);
	void ChangeScissorRect(int _Index);

public: // Rasterizer State ���� �� Ŭ����
	void Create(const D3D11_RASTERIZER_DESC& _Value);
	void Clear();

public:
	void SettingViewPort();

public:
	void SettingScissor();

public:
	void Setting();
};

