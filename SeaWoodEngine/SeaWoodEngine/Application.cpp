#include "stdafx.h"
#include "Application.h"

USING_NS_SW;

Application* Application::m_Instance = nullptr;

Application::Application()
{
}


Application::~Application()
{
}

Application* SeaWood::Application::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new Application;
	}
	return m_Instance;
}

void SeaWood::Application::releaseInstance()
{
	SAFE_DELETE(m_Instance);
}

bool SeaWood::Application::MakeWindow(TCHAR* title, int width, int height)
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

bool SeaWood::Application::init(TCHAR* title, int width, int height)
{
	m_InstanceHandle = GetModuleHandle(0);

	if (!MakeWindow(title, width, height))
	{
		return false;
	}

	ShowWindow(m_WindowHandle, SW_SHOWNORMAL);

	return true;
}

LRESULT CALLBACK SeaWood::Application::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void SeaWood::Application::run()
{
	MSG message;

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				return;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			gameLoop();
		}
	}
}

void SeaWood::Application::gameLoop()
{

}


