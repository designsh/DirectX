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
class GameEngineDirectXDevice
{
private:
	static GameEngineDirectXDevice* Inst;

public:
	static GameEngineDirectXDevice& GetInst()
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

private:	// member Var
	ID3D11Device* Device_;
	ID3D11DeviceContext* Context_;
	IDXGISwapChain* SwapChain_;

public:
	GameEngineDirectXDevice(); // default constructer ����Ʈ ������
	~GameEngineDirectXDevice(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineDirectXDevice(const GameEngineDirectXDevice& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineDirectXDevice(GameEngineDirectXDevice&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineDirectXDevice& operator=(const GameEngineDirectXDevice& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineDirectXDevice& operator=(const GameEngineDirectXDevice&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public: // ����̽� �ʱ�ȭ
	void Initialize();

private: // ����ü�� ����
	void CreateSwapChain();

};

