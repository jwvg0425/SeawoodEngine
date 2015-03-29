#include "stdafx.h"
#include "Director.h"
#include "Scene.h"
#include "Application.h"
#include "D3DRenderer.h"
#include "GdiRenderer.h"
#include "MouseEvent.h"
#include <time.h>
#include <iostream>
#include <sstream>
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

	//디버깅 용 플래그
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	srand((unsigned)time(nullptr));
	m_Tick = getTick();
	m_Mouse = new MouseEvent;
	m_KeyManager = new KeyManager;
}

Director::~Director()
{
	delete m_Mouse;
	delete m_KeyManager;

	if (m_Renderer != nullptr)
	{
		m_Renderer->release();
	}
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

	//view 갱신
	m_Renderer->update(dTime);

	//input device 갱신
	m_KeyManager->update(dTime);

	// 화면 갱신
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

	m_Renderer->beginFrame();
	m_NowScene->render();
	m_Renderer->render();
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
		end();
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void SeaWood::Director::registerRenderer(Renderer* renderer)
{
	_ASSERT(m_Renderer == nullptr);

	renderer->retain();

	m_Renderer = renderer;
}

Renderer* SeaWood::Director::getRenderer()
{
	return m_Renderer;
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
	_ASSERT(node != nullptr);

	m_EventNodes[type].push_back(node);
	node->setEvent(type);
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
		m_FPS = static_cast<int>(frame / time);
		frame = 0;
		time = 0;

#if defined(DEBUG) || defined(_DEBUG)
		LOG(L"fps : %d", m_FPS);
#endif
	}
}

void SeaWood::Director::autorelease(Ref* ref)
{
	_ASSERT(ref != nullptr);

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

KeyManager* SeaWood::Director::getKeyManager()
{
	return m_KeyManager;
}

D3DRenderer* SeaWood::Director::getD3DRenderer()
{
	if (m_Renderer->getType() == Renderer::ViewType::D3_DX)
	{
		return static_cast<D3DRenderer*>(m_Renderer);
	}
	else
	{
		return nullptr;
	}
}

GdiRenderer* SeaWood::Director::getGdiRenderer()
{
	if (m_Renderer->getType() == Renderer::ViewType::D2_GDI)
	{
		return static_cast<GdiRenderer*>(m_Renderer);
	}
	else
	{
		return nullptr;
	}
}

void SeaWood::Director::clearEvent(EventType type, Node* node)
{
	for (auto it = m_EventNodes[type].begin(); it != m_EventNodes[type].end();)
	{
		if (*it == node)
		{
			it = m_EventNodes[type].erase(it);
		}
		else
		{
			it++;
		}
	}
}

Scene* SeaWood::Director::getRunningScene()
{
	return m_NowScene;
}
