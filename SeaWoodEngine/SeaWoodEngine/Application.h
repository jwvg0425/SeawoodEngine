#pragma once

NS_SW_BEGIN

class Application
{
public:
	static Application*		getInstance();
	bool					init(TCHAR* title, int width, int height);
	int						run();

	HWND					getWindowHandle();
	HINSTANCE				getInstanceHandle();
	const Size&				getClientSize() const;
	float					getAspectRatio() const;

							Application();
	virtual					~Application();
	virtual void			onCreate();
private:
	bool						MakeWindow(TCHAR* title, int width, int height);
	
	static Application*			m_Instance;
	HWND						m_WindowHandle;
	HINSTANCE					m_InstanceHandle;
	Size						m_ClientSize = Size::ZERO;
};

NS_SW_END