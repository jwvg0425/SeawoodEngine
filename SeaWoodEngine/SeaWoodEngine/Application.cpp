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
	_ASSERT(title != nullptr);

	m_Title = title;

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

	m_ClientSize.m_Width = width;
	m_ClientSize.m_Height = height;

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
	_ASSERT(title != nullptr);

	m_InstanceHandle = GetModuleHandle(nullptr);

	m_ClientSize.m_Width = width;
	m_ClientSize.m_Height = height;

	if (!MakeWindow(title, width, height))
	{
		return false;
	}

	ShowWindow(m_WindowHandle, SW_SHOWNORMAL);

	onCreate();

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
				break;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			Director::getInstance()->gameLoop();
		}
	}

	Director::releaseInstance();
	return 0;
}

void Application::onCreate()
{

}

HWND SeaWood::Application::getWindowHandle() const
{
	return m_WindowHandle;
}

HINSTANCE SeaWood::Application::getInstanceHandle() const
{
	return m_InstanceHandle;
}

float SeaWood::Application::getAspectRatio() const
{
	return m_ClientSize.m_Width / m_ClientSize.m_Height;
}

TCHAR* SeaWood::Application::getTitle() const
{
	return m_Title;
}

void SeaWood::Application::setTitle(TCHAR* title)
{
	SetWindowText(m_WindowHandle, title);
	m_Title = title;
}

void SeaWood::Application::setClientSize(const Size& size)
{
	m_ClientSize = size;
}

const Size& Application::getClientSize() const
{
	return m_ClientSize;
}
