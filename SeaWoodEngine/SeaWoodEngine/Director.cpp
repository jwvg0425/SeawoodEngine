#include "stdafx.h"
#include "Director.h"
#include "Scene.h"
#include "Application.h"
#include "View.h"
#include "MouseEvent.h"
#pragma comment(lib, "winmm.lib")

USING_NS_SW;

Director* Director::m_Instance = nullptr;

Director::Director()
{
	if (QueryPerformanceFrequency(&m_TicksPerSecond))
	{
		// 지원함
		m_IsQueryPerformance = true;
	}

	m_Tick = getTick();
	m_Mouse = new MouseEvent;
}

Director::~Director()
{
	delete m_Mouse;
}

Director* Director::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new Director;
	}
	return m_Instance;
}

void Director::releaseInstance()
{
	SAFE_DELETE(m_Instance);
}

void Director::gameLoop()
{
	auto nowTick = getTick();

	float dTime = static_cast<float>(nowTick - m_Tick) / getTicksPerSecond();

	m_NowScene->update(dTime);

	draw();

	//autorelease 작업
	for (auto& ref : m_ReleasePool)
	{
		ref->release();
	}

	m_ReleasePool.clear();

	calculateFPS(dTime);
	m_Tick = nowTick;
}

void Director::draw()
{
	if (m_NowScene == nullptr)
	{
		return;
	}

	m_View->beginFrame();
	m_NowScene->draw();
	m_View->draw();
}

long long int Director::getTick()
{
	if (m_IsQueryPerformance)
	{
		LARGE_INTEGER ticks;
		QueryPerformanceCounter(&ticks);
		return ticks.QuadPart;
	}
	else
	{
		return GetTickCount();
	}
}

long long int Director::getTicksPerSecond()
{
	if (m_IsQueryPerformance)
	{
		return m_TicksPerSecond.QuadPart;
	}
	else
	{
		return 1000;
	}
}

void Director::startScene(Scene* scene)
{
	_ASSERT(m_NowScene == nullptr);

	m_NowScene = scene;
	m_NowScene->retain();
}

LRESULT CALLBACK SeaWood::Director::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
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
	case WM_MOUSEMOVE:
		onMouseMove(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_LBUTTONDOWN:
		onMouseDown(MouseEvent::Status::LEFT);
		return 0;
	case WM_LBUTTONUP:
		onMouseUp(MouseEvent::Status::LEFT);
		return 0;
	case WM_RBUTTONDOWN:
		onMouseDown(MouseEvent::Status::RIGHT);
		return 0;
	case WM_RBUTTONUP:
		onMouseUp(MouseEvent::Status::RIGHT);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void SeaWood::Director::registerView(View* view)
{
	_ASSERT(m_View == nullptr);

	m_View = view;
}

View* SeaWood::Director::getView()
{
	return m_View;
}

MouseEvent* SeaWood::Director::getMouse()
{
	return m_Mouse;
}

void SeaWood::Director::onMouseDown(MouseEvent::Status status)
{
	m_Mouse->m_Status = 
		static_cast<MouseEvent::Status>(m_Mouse->m_Status | status);

	for (auto& node : m_EventNodes[EventType::MOUSE_DOWN])
	{
		node->onMouseDown(*m_Mouse);
	}
}

void SeaWood::Director::onMouseUp(MouseEvent::Status status)
{
	m_Mouse->m_Status = 
		static_cast<MouseEvent::Status>(m_Mouse->m_Status & ~status);

	for (auto& node : m_EventNodes[EventType::MOUSE_UP])
	{
		node->onMouseUp(*m_Mouse);
	}
}

void SeaWood::Director::registerEvent(EventType type, Node* node)
{
	m_EventNodes[type].push_back(node);
}

void SeaWood::Director::onMouseMove(int x, int y)
{
	m_Mouse->m_Position.m_X = static_cast<float>(x);
	m_Mouse->m_Position.m_Y = static_cast<float>(y);

	for (auto& node : m_EventNodes[EventType::MOUSE_MOVE])
	{
		node->onMouseMove(*m_Mouse);
	}
}

void SeaWood::Director::calculateFPS(float dTime)
{
	static int frame = 0;
	static float time = 0;

	frame++;
	time += dTime;

	if (time >= 1)
	{
		m_FPS = frame / time;
		frame = 0;
		time = 0;
	}
}

void SeaWood::Director::autorelease(Ref* ref)
{
	m_ReleasePool.push_back(ref);
}

void SeaWood::Director::changeScene(Scene* scene)
{
	_ASSERT(m_NowScene != nullptr);

	m_NowScene->release();
	m_NowScene = scene;
	m_NowScene->retain();
}

void SeaWood::Director::end()
{
	_ASSERT(m_NowScene != nullptr);

	m_NowScene->release();

	PostQuitMessage(0);
}
