#include "PreCompile.h"
#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSoundManager.h>
#include <iostream>

bool GameEngineWindow::WindowLoopFlag = true;

// 포인터형 싱글톤
GameEngineWindow* GameEngineWindow::Inst = new GameEngineWindow();

// 220315 윈도우 메세지 처리 함수 변경
//LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
//{
//	switch (_message)
//	{
//		case WM_PAINT:
//		{
//			PAINTSTRUCT ps;
//
//			// HDC 윈도우에 픽셀에 색깔을 바꿀수 있는 권한이입니다.
//			// 윈도우창이 그려지는 2차원 배열에 접근할수 있는 권한입니다.
//			HDC hdc = BeginPaint(_hWnd, &ps);
//			EndPaint(_hWnd, &ps);
//			break;
//		}
//		case WM_SIZE:
//		{
//			return DefWindowProc(_hWnd, _message, _wParam, _lParam);
//			break;
//		}
//		case WM_DESTROY:
//		{
//			
//			break;
//		}
//		default:
//		{
//			return DefWindowProc(_hWnd, _message, _wParam, _lParam);
//		}
//	}
//
//	return 0;
//}

// constructer destructer
GameEngineWindow::GameEngineWindow() 
	: className_("")
	, windowTitle_("")
	, windowhandle_(nullptr)
	, hInstance_(nullptr)
	, devicecontext_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow() 
{
	if (nullptr != windowhandle_)
	{
		DestroyWindow(windowhandle_);
		windowhandle_ = nullptr;
	}
}

//member Func
int GameEngineWindow::CreateMainWindowClass()
{
	hInstance_ = GetModuleHandle(NULL);

	if (nullptr == hInstance_)
	{
		GameEngineDebug::AssertFalse();
		return 0;
	}

	className_ = "DEF";

	WNDCLASSEXA wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; // 화면 재갱신 옵션
	//wcex.lpfnWndProc = WndProc;
	wcex.lpfnWndProc = WindowEvent;	// 220315 SJH : 윈도우 강제종료 Flag 셋팅을 위해 전역멤버함수로 변경
	wcex.cbClsExtra = 0; // 신경안써도 됨
	wcex.cbWndExtra = 0; // 신경안써도 됨.
	wcex.hInstance = hInstance_;
	wcex.hIcon = nullptr;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT3));
	wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.hCursor = nullptr;//LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT3);
	wcex.lpszClassName = className_.c_str();

	return RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateMainWindow(const std::string& _titlename, const float4& _size, const float4& _pos)
{
	// 반환값이 '0'인경우 윈도우클래스 등록 실패로 간주
	if (0 == CreateMainWindowClass())
	{
		GameEngineDebug::MsgBoxError("윈도우 클래스 등록에 실패하였습니다.");
		return;
	}

	if (nullptr == hInstance_)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	if (true == className_.empty())
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	windowhandle_ = nullptr;
	windowTitle_ = _titlename;

	// 윈도우 타이틀 깨짐현상 : GameEngine 속성변경(속성/고급/고급속성(문자집합) : 유니코드문자집합사용 -> 멀티바이트문자집합사용)
	windowhandle_ = CreateWindowA(className_.c_str(), windowTitle_.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance_, nullptr);
	if (0 == windowhandle_)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	// 윈도우 클라이언트영역(작업영역) 설정
	SetSizeAndPos(_size, _pos);

	// 윈도우 띄우기 및 갱신
	ShowWindow(windowhandle_, SW_SHOW);
	UpdateWindow(windowhandle_);

	devicecontext_ = ::GetDC(windowhandle_);

	return;
}

void GameEngineWindow::SetSizeAndPos(const float4& _size, const float4& _pos)
{
	size_ = _size;
	pos_ = _pos;

	//          1920          
	RECT Rc = { 0, 0, _size.ix(), _size.iy() };
	// 내가 넣어준 렉트에 타이틀바와 메뉴등의 사이즈가 들어간 녀석으로 만들어주세요.
	AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, false);

	// 0넣으면 그냥 보통 기본이다.
	SetWindowPos(windowhandle_, nullptr, _pos.ix(), _pos.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, 0);
}

void GameEngineWindow::Loop(void(*_loopFunc)()) 
{
	MSG msg;
	while (WindowLoopFlag)
	{
		if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (nullptr == _loopFunc)
			{
				GameEngineDebug::AssertFalse();
				return;
			}

			_loopFunc();

			// Window메세지가 있든 없든 돌아간다.
			if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg); // WNDPROC
			}
		}
		else 
		{
			if (nullptr == _loopFunc)
			{
				GameEngineDebug::AssertFalse();
				return;
			}

			_loopFunc();
		}
	}
}

__int64 GameEngineWindow::WindowEvent(HWND _hWnd, unsigned int _EventType, unsigned __int64 _LValue, __int64 _SubValue)
{
	switch (_EventType)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;

			// HDC 윈도우에 픽셀에 색깔을 바꿀수 있는 권한이입니다.
			// 윈도우창이 그려지는 2차원 배열에 접근할수 있는 권한입니다.
			HDC hdc = BeginPaint(_hWnd, &ps);
			EndPaint(_hWnd, &ps);
			break;
		}
		case WM_SIZE:
		{
			return DefWindowProc(_hWnd, _EventType, _LValue, _SubValue);
			break;
		}
		case WM_DESTROY:
		{
			WindowLoopFlag = false;
			break;
		}
		default:
		{
			return DefWindowProc(_hWnd, _EventType, _LValue, _SubValue);
		}
	}

	return 0;
}

void GameEngineWindow::CloseWindow()
{
	// GameLoop 종료시 엔진의 모든 리소스 릴리즈하기때문에 Loop Flag만 해제
	WindowLoopFlag = false;
	//DestroyWindow(windowhandle_);
}

