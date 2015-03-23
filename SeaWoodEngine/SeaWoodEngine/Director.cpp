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
		m_Mouse->m_Position.m_X = LOWORD(lParam);
		m_Mouse->m_Position.m_Y = HIWORD(lParam);
		return 0;
	case WM_LBUTTONDOWN:
		switch (m_Mouse->m_Status)
		{
		case MouseEvent::Status::NONE:
			m_Mouse->m_Status = MouseEvent::Status::LEFT;
			break;
		case MouseEvent::Status::RIGHT:
			m_Mouse->m_Status = MouseEvent::Status::LEFT_RIGHT;
			break;
		}
		return 0;
	case WM_LBUTTONUP:
		switch (m_Mouse->m_Status)
		{
		case MouseEvent::Status::LEFT:
			m_Mouse->m_Status = MouseEvent::Status::NONE;
			break;
		case MouseEvent::Status::LEFT_RIGHT:
			m_Mouse->m_Status = MouseEvent::Status::RIGHT;
			break;
		}
		return 0;
	case WM_RBUTTONDOWN:
		switch (m_Mouse->m_Status)
		{
		case MouseEvent::Status::NONE:
			m_Mouse->m_Status = MouseEvent::Status::RIGHT;
			break;
		case MouseEvent::Status::LEFT:
			m_Mouse->m_Status = MouseEvent::Status::LEFT_RIGHT;
			break;
		}
		return 0;
	case WM_RBUTTONUP:
		switch (m_Mouse->m_Status)
		{
		case MouseEvent::Status::RIGHT:
			m_Mouse->m_Status = MouseEvent::Status::NONE;
			break;
		case MouseEvent::Status::LEFT_RIGHT:
			m_Mouse->m_Status = MouseEvent::Status::LEFT;
			break;
		}
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
