#pragma once
#include "MouseEvent.h"
#include "KeyManager.h"
#define GET_KEY_MANAGER() SeaWood::Director::getInstance()->getKeyManager()
#define GET_VIEW() SeaWood::Director::getInstance()->getView()
#define GET_D3D_VIEW() SeaWood::Director::getInstance()->getD3DView()
#define GET_GDI_VIEW() SeaWood::Director::getInstance()->getGdiView()

NS_SW_BEGIN

class Scene;
class View;
class Node;
class Ref;
class D3DView;
class GdiView;
class Director
{
public:
	using Nodes = std::vector<Node*>;
	using Refs = std::vector<Ref*>;
	using EventNodes = std::map<EventType, Nodes>;

	static Director*	getInstance();
	static void			releaseInstance();

	void				gameLoop();

	//프로그램 종료
	void				end();

	//등록된 개체들을 모두 그림
	void				draw();

	void				startScene(Scene* scene);
	void				changeScene(Scene* scene);

	void				registerView(View* view);
	View*				getView();
	D3DView*			getD3DView();
	GdiView*			getGdiView();

	//input 관련
	KeyManager*			getKeyManager();
	MouseEvent*			getMouse();

	//특정 이벤트에 대해 해당 이벤트 처리할 노드 등록.
	void				registerEvent(EventType type, Node* node);

	
	void				onMouseDown(MouseEvent::Status status);
	void				onMouseMove(int x, int y);
	void				onMouseUp(MouseEvent::Status status);
	void				autorelease(Ref* ref);

	LRESULT CALLBACK	WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

protected:
	Director();
	~Director();

	long long int		getTick();
	long long int		getTicksPerSecond();
	void				calculateFPS(float dTime);

	static Director*	m_Instance;

	Scene*				m_NowScene = nullptr;
	View*				m_View = nullptr;
	KeyManager*			m_KeyManager = nullptr;
	bool				m_IsQueryPerformance = false;
	LARGE_INTEGER		m_TicksPerSecond;
	long long int		m_Tick = 0;
	MouseEvent*			m_Mouse;
	EventNodes			m_EventNodes;
	int					m_FPS = 0;
	Refs				m_ReleasePool;
	
};

NS_SW_END