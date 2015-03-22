#pragma once

NS_SW_BEGIN

class Scene;
class Director
{
public:
	static Director*	getInstance();
	static void			releaseInstance();

	void				gameLoop();

	//등록된 개체들을 모두 그림
	void				draw();

	void				startScene(Scene* scene);

	LRESULT CALLBACK	WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

protected:
	Director();
	~Director();

	long long int		getTick();
	long long int		getTicksPerSecond();

	static Director*	m_Instance;

	Scene*				m_NowScene;
	bool				m_IsQueryPerformance;
	LARGE_INTEGER		m_TicksPerSecond;
	long long int		m_Tick;
	
};

NS_SW_END