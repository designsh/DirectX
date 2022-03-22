#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// ���̷�ƮX�� ���μ������� GUIID�� �ο��ؼ� X���μ����� ����̽��� �̿��Ϸ����ϴ��� �˾Ƽ� ó��
#pragma comment(lib, "dxguid")

// �з� : 
// �뵵 : 
// ���� : �׷���ī�忡 �����Ҽ� �ִ� ����(������)
class GameEngineDepthBuffer;
class GameEngineRenderTarget;
class GameEngineDevice
{
private:
	static GameEngineDevice* Inst;

private:
	static ID3D11Device* Device_;
	static ID3D11DeviceContext* Context_;
	static IDXGISwapChain* SwapChain_;
	static GameEngineRenderTarget* BackBufferTarget_;

public:
	static GameEngineDevice& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

public:
	static GameEngineRenderTarget* GetBackBufferTarget();
	static ID3D11Device* GetDevice();
	static ID3D11DeviceContext* GetContext();
	static void ShaderReset();
	static void ResourceReset();
	static void RenderStart();
	static void RenderEnd();

private:	// member Var

public:
	GameEngineDevice(); // default constructer ����Ʈ ������
	~GameEngineDevice(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineDevice(const GameEngineDevice& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineDevice(GameEngineDevice&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineDevice& operator=(const GameEngineDevice& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineDevice& operator=(const GameEngineDevice&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public: // ����̽� �ʱ�ȭ
	void Initialize();

public: // ����ü�� ����
	void CreateSwapChain();
};

