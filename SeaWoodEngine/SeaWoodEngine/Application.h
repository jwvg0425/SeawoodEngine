#pragma once

NS_SW_BEGIN

class Application
{
public:
	static Application*		getInstance();
	static void				releaseInstance();
	bool					init(TCHAR* title, int width, int height);
	int						run();

	HWND					getWindowHandle();
	HINSTANCE				getInstanceHandle();

private:
								Application();
	virtual						~Application();

	static LRESULT CALLBACK		WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	bool						MakeWindow(TCHAR* title, int width, int height);
	
	static Application*			m_Instance;
	HWND						m_WindowHandle;
	HINSTANCE					m_InstanceHandle;

	
};

NS_SW_END