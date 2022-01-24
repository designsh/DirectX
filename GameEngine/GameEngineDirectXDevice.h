#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// 다이렉트X는 프로세스마다 GUIID를 부여해서 X프로세스가 디바이스를 이용하려고하는지 알아서 처리
#pragma comment(lib, "dxguid")

// 분류 : 
// 용도 : 
// 설명 : 그래픽카드에 접근할수 있는 권한(포인터)
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
	GameEngineDirectXDevice(); // default constructer 디폴트 생성자
	~GameEngineDirectXDevice(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineDirectXDevice(const GameEngineDirectXDevice& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineDirectXDevice(GameEngineDirectXDevice&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineDirectXDevice& operator=(const GameEngineDirectXDevice& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineDirectXDevice& operator=(const GameEngineDirectXDevice&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public: // 디바이스 초기화
	void Initialize();

private: // 스왑체인 생성
	void CreateSwapChain();

};

