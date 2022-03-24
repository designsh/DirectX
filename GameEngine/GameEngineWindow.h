#pragma once

// 분류 : 엔진
// 용도 : winapi의 윈도우 창을 제어하는 기능들에 대한 
//       랩핑(다른 api의 기능을 내 입맛에 맞는 클래스로 한번 감쌌다.)을하고
//       편의 함수들을 제공한다.
// 설명 : 
class GameEngineWindow : public GameEngineObjectNameBase
{
	friend LRESULT CALLBACK WindowEvent(HWND _hWnd, unsigned int _EventType, unsigned __int64 _LValue, __int64 _SubValue);

private:
	static bool WindowLoopFlag;
	static std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> MessageCallBack_;
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

public:
	static inline void SetMessageCallBack(std::function<LRESULT(HWND, unsigned int, unsigned __int64, __int64)> _CallBack)
	{
		MessageCallBack_ = _CallBack;
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
	static __int64 WindowEvent(HWND _hWnd, unsigned int _EventType, unsigned __int64 _LValue, __int64 _SubValue);

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

public:
	void CloseWindow();
};
