#include "stdafx.h"
#include "Director.h"
#include "Scene.h"
#include "Application.h"
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
}

Director::~Director()
{

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
}

void Director::draw()
{
	if (m_NowScene == nullptr)
	{
		return;
	}

	m_NowScene->draw();
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
	_ASSERT(m_NowScene != nullptr);

	m_NowScene = scene;
}

LRESULT CALLBACK SeaWood::Director::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		Application::getInstance()->onCreate();
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
