#pragma once

NS_SW_BEGIN

class Scene;
class View;
struct MouseEvent;
class Director
{
public:
	static Director*	getInstance();
	static void			releaseInstance();

	void				gameLoop();

	//등록된 개체들을 모두 그림
	void				draw();

	void				startScene(Scene* scene);

	void				registerView(View* view);
	View*				getView();

	MouseEvent*			getMouse();

	LRESULT CALLBACK	WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

protected:
	Director();
	~Director();

	long long int		getTick();
	long long int		getTicksPerSecond();

	static Director*	m_Instance;

	Scene*				m_NowScene = nullptr;
	View*				m_View = nullptr;
	bool				m_IsQueryPerformance = false;
	LARGE_INTEGER		m_TicksPerSecond;
	long long int		m_Tick = 0;
	MouseEvent*			m_Mouse;
	
};

NS_SW_END