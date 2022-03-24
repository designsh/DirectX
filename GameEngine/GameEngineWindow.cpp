#include "PreCompile.h"
#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSoundManager.h>
#include <iostream>

#include <GameEngineBase/GameEngineDirectory.h>

#include "KeyboardClass.h"

std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> GameEngineWindow::MessageCallBack_ = nullptr;
bool GameEngineWindow::WindowLoopFlag = true;

// �������� �̱���
GameEngineWindow* GameEngineWindow::Inst = new GameEngineWindow();

// 220315 ������ �޼��� ó�� �Լ� ����
//LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
//{
//	switch (_message)
//	{
//		case WM_PAINT:
//		{
//			PAINTSTRUCT ps;
//
//			// HDC �����쿡 �ȼ��� ������ �ٲܼ� �ִ� �������Դϴ�.
//			// ������â�� �׷����� 2���� �迭�� �����Ҽ� �ִ� �����Դϴ�.
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
	wcex.style = CS_HREDRAW | CS_VREDRAW; // ȭ�� �簻�� �ɼ�
	//wcex.lpfnWndProc = WndProc;
	wcex.lpfnWndProc = WindowEvent;	// 220315 SJH : ������ �������� Flag ������ ���� ��������Լ��� ����
	wcex.cbClsExtra = 0; // �Ű�Ƚᵵ ��
	wcex.cbWndExtra = 0; // �Ű�Ƚᵵ ��.
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
	// ��ȯ���� '0'�ΰ�� ������Ŭ���� ��� ���з� ����
	if (0 == CreateMainWindowClass())
	{
		GameEngineDebug::MsgBoxError("������ Ŭ���� ��Ͽ� �����Ͽ����ϴ�.");
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

	// ������ Ÿ��Ʋ �������� : GameEngine �Ӽ�����(�Ӽ�/���/��޼Ӽ�(��������) : �����ڵ幮�����ջ�� -> ��Ƽ����Ʈ�������ջ��)
	windowhandle_ = CreateWindowA(className_.c_str(), windowTitle_.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance_, nullptr);
	if (0 == windowhandle_)
	{
		GameEngineDebug::AssertFalse();
		return;
	}

	// ������ Ŭ���̾�Ʈ����(�۾�����) ����
	SetSizeAndPos(_size, _pos);

	// ������ ���� �� ����
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
	// ���� �־��� ��Ʈ�� Ÿ��Ʋ�ٿ� �޴����� ����� �� �༮���� ������ּ���.
	AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, false);

	// 0������ �׳� ���� �⺻�̴�.
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

			// Window�޼����� �ֵ� ���� ���ư���.
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
	// IMGUI Message Proc
	if (nullptr != GameEngineWindow::MessageCallBack_)
	{
		if (0 != GameEngineWindow::MessageCallBack_(_hWnd, _EventType, _LValue, _SubValue))
		{
			return true;
		}
	}

	switch (_EventType)
	{
		case WM_CREATE :
		{
			// ������ ������ ���ÿ� �ý��ۿ� ��Ʈ ���
			GameEngineDirectory SoundDir;
			SoundDir.MoveParent("DirectX");
			SoundDir.MoveChild("Resources");
			SoundDir.MoveChild("Font");

			std::string FontPathName = SoundDir.GetFullPath();
			FontPathName += "\\diablo.ttf";

			AddFontResource(FontPathName.c_str());
			//AddFontResourceEx(FontPathName.c_str(), FR_PRIVATE, 0);


			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;

			// HDC �����쿡 �ȼ��� ������ �ٲܼ� �ִ� �������Դϴ�.
			// ������â�� �׷����� 2���� �迭�� �����Ҽ� �ִ� �����Դϴ�.
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
			// ������ ���ſ� ���ÿ� ��ϵ� ��Ʈ ����
			GameEngineDirectory SoundDir;
			SoundDir.MoveParent("DirectX");
			SoundDir.MoveChild("Resources");
			SoundDir.MoveChild("Font");

			std::string FontPathName = SoundDir.GetFullPath();
			FontPathName += "\\diablo.ttf";

			RemoveFontResource(FontPathName.c_str());
			//RemoveFontResourceEx(FontPathName.c_str(), FR_PRIVATE, 0);

			WindowLoopFlag = false;

			break;
		}

		// ===================================================== Ű�����Է��� �״�� �ޱ����� ó�� ===================================================== //
		case WM_CHAR:
		{
			unsigned char ch = static_cast<unsigned char>(_LValue);

			// ����ó�� : �ش� Ű���� input�� ����Ͽ� �����
			if (ch == '\b') // BackSpace Key Down
			{
				int a = 0;

				break;
			}
			else if (ch == '\r') // Enter Key Down
			{
				int a = 0;

				break;
			}
			else if (ch == ' ') // Space Key Down
			{
				int a = 0;

				break;
			}

			// ���� �Է¿� ���� ť ���
			if (KeyboardClass::GetInst().IsCharsAutoRepeat())
			{
				KeyboardClass::GetInst().OnChar(ch);
			}
			else
			{
				const bool wasPressed = _LValue & 0x40000000;
				if (!wasPressed)
				{
					KeyboardClass::GetInst().OnChar(ch);
				}
			}
			return 0;

			break;
		}
		case WM_KEYDOWN:
		{
			unsigned char keycode = static_cast<unsigned char>(_LValue);

			if (KeyboardClass::GetInst().IsKeysAutoRepeat())
			{
				KeyboardClass::GetInst().OnKeyPressed(keycode);
			}
			else
			{
				const bool wasPressed = _SubValue & 0x40000000;
				if (!wasPressed)
				{
					KeyboardClass::GetInst().OnKeyPressed(keycode);
				}
			}

			return 0;
		}
		case WM_KEYUP:
		{
			unsigned char keycode = static_cast<unsigned char>(_LValue);
			KeyboardClass::GetInst().OnKeyReleased(keycode);

			return 0;
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
	// Window Message Send
	DestroyWindow(windowhandle_);
}

