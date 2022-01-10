#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>

// �з� : ����
// �뵵 : winapi�� ������ â�� �����ϴ� ��ɵ鿡 ���� 
//       ����(�ٸ� api�� ����� �� �Ը��� �´� Ŭ������ �ѹ� ���մ�.)���ϰ�
//       ���� �Լ����� �����Ѵ�.
// ���� : 
class GameEngineWindow : public GameEngineObjectNameBase
{
private:
	static GameEngineWindow* Inst;

public:
	static GameEngineWindow& GetInst() 
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

private:
	std::string className_;
	std::string windowTitle_;
	HINSTANCE hInstance_;
	HWND windowhandle_;
	HDC devicecontext_;

	float4 size_;
	float4 pos_;

private:
	GameEngineWindow();
	~GameEngineWindow();

private:
	int CreateMainWindowClass();

public:
	void CreateMainWindow(const std::string& _titlename, const float4& _size, const float4& _pos);
	void SetSizeAndPos(const float4& _size, const float4& _pos);
	void Loop(void(*_loopFunc)());

public:
	HWND  GetWindowHWND()
	{
		return windowhandle_;
	}

	HDC  GetWindowDC()
	{
		return devicecontext_;
	}

	float4 GetSize()
	{
		return size_;
	}

	float4 GetPos()
	{
		return pos_;
	}
};
