#include "stdafx.h"
#include "Application.h"
#include "Director.h"

USING_NS_SW;

Application* Application::m_Instance = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return Director::getInstance()->WndProc(hWnd, iMessage, wParam, lParam);
}

Application::Application()
{
	m_Instance = this;
}


Application::~Application()
{
	Director::releaseInstance();
}

Application* Application::getInstance()
{
	_ASSERT(m_Instance != nullptr);

	return m_Instance;
}

bool Application::MakeWindow(TCHAR* title, int width, int height)
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = m_InstanceHandle;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = _T("SWApplication");
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	m_WindowHandle = CreateWindow(_T("SWApplication"), title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, NULL, (HMENU)NULL, m_InstanceHandle, NULL);

	if (m_WindowHandle == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Application::init(TCHAR* title, int width, int height)
{
	m_InstanceHandle = GetModuleHandle(0);

	if (!MakeWindow(title, width, height))
	{
		return false;
	}

	ShowWindow(m_WindowHandle, SW_SHOWNORMAL);

	return true;
}

int Application::run()
{
	MSG message;

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				return 0;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			Director::getInstance()->gameLoop();
		}
	}
}

void Application::onCreate()
{

}
