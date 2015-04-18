#include "stdafx.h"
#include "Director.h"
#include "Scene.h"
#include "Application.h"
#include "Renderer.h"
#include "MouseEvent.h"
#include "Camera.h"
#include "DebugNodes.h"
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>
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

	//TODO : dTime 매 오브젝트별로 갱신가능하도록
	float dTime = static_cast<float>(nowTick - m_Tick) / getTicksPerSecond();

	//view 갱신
	m_Renderer->update(dTime);

	//input device 갱신
	m_KeyManager->update(dTime);

	//mouse pick 계산
	onPickTriangle();

	//업데이트 등록된 노드들 업데이트 작업
	for (auto& node : m_EventNodes[EventType::UPDATE_FRAME])
	{
		node->update(dTime);
	}

	render();

	//autorelease 작업
	for (auto& ref : m_ReleasePool)
	{
		ref->release();
	}

	m_ReleasePool.clear();

	calculateFPS(dTime);

	m_Tick = nowTick;
}

void Director::render()
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
		SetCapture(hWnd);
		return 0;
	case WM_LBUTTONUP:
		onMouseUp(MouseEvent::Status::LEFT);
		ReleaseCapture();
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
	case WM_SIZE:
		Application::getInstance()->setClientSize(Size(LOWORD(lParam), HIWORD(lParam)));
		return 0;
	case WM_EXITSIZEMOVE:
		if (GET_RENDERER() != nullptr)
		{
			GET_RENDERER()->initRenderTarget();
		}
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

void SeaWood::Director::cacheModel(const std::string& fileName)
{
	if (m_ModelInfo.find(fileName) != m_ModelInfo.end())
	{
		return;
	}

	ModelInfo info;

	loadModel(fileName, info);

	m_ModelInfo[fileName] = info;
}

void SeaWood::Director::loadModel(const std::string& fileName, ModelInfo& info)
{
	if (m_ModelInfo.find(fileName) != m_ModelInfo.end())
	{
		info = m_ModelInfo[fileName];

		return;
	}

	std::ifstream file;

	file.open(fileName, std::ios_base::in | std::ios_base::binary);

	if (!file.is_open())
	{
		return;
	}

	int size;

	file.read((char*)&size, sizeof(size_t));

	for (int i = 0; i < size; i++)
	{
		Vertex::PosBasic vertex;

		file.read((char*)&vertex.m_Pos.x, sizeof(float));
		file.read((char*)&vertex.m_Pos.y, sizeof(float));
		file.read((char*)&vertex.m_Pos.z, sizeof(float));

		file.read((char*)&vertex.m_Normal.x, sizeof(float));
		file.read((char*)&vertex.m_Normal.y, sizeof(float));
		file.read((char*)&vertex.m_Normal.z, sizeof(float));

		file.read((char*)&vertex.m_Tex.x, sizeof(float));
		file.read((char*)&vertex.m_Tex.y, sizeof(float));

		info.m_Vertices.push_back(vertex);
	}

	file.read((char*)&size, sizeof(size_t));

	for (int i = 0; i < size; i++)
	{
		UINT idx;

		file.read((char*)&idx, sizeof(unsigned));

		info.m_Indices.push_back(idx);
	}

	file.read((char*)&info.m_Material.m_Ambient.x, sizeof(float));
	file.read((char*)&info.m_Material.m_Ambient.y, sizeof(float));
	file.read((char*)&info.m_Material.m_Ambient.z, sizeof(float));
	file.read((char*)&info.m_Material.m_Ambient.w, sizeof(float));

	file.read((char*)&info.m_Material.m_Diffuse.x, sizeof(float));
	file.read((char*)&info.m_Material.m_Diffuse.y, sizeof(float));
	file.read((char*)&info.m_Material.m_Diffuse.z, sizeof(float));
	file.read((char*)&info.m_Material.m_Diffuse.w, sizeof(float));

	file.read((char*)&info.m_Material.m_Specular.x, sizeof(float));
	file.read((char*)&info.m_Material.m_Specular.y, sizeof(float));
	file.read((char*)&info.m_Material.m_Specular.z, sizeof(float));
	file.read((char*)&info.m_Material.m_Specular.w, sizeof(float));

	file.read((char*)&info.m_UTile, sizeof(float));
	file.read((char*)&info.m_VTile, sizeof(float));

	file.read((char*)&size, sizeof(size_t));

	char buffer[512];

	file.read(buffer, sizeof(char)*size);

	buffer[size] = '\0';

	info.m_Texture = buffer;
}

void SeaWood::Director::getEyeRay(OUT XMVECTOR& rayOrigin, OUT XMVECTOR& rayDir)
{
	XMMATRIX proj = GET_RENDERER()->getCamera()->getProjection();
	auto clientSize = Application::getInstance()->getClientSize();

	float vx = (+2.0f*m_Mouse->m_Position.m_X / clientSize.m_Width - 1.0f) / proj(0, 0);
	float vy = (-2.0f*m_Mouse->m_Position.m_Y / clientSize.m_Height + 1.0f) / proj(1, 1);

	rayOrigin = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	rayDir = XMVectorSet(vx, vy, 1.0f, 0.0f);
}

void SeaWood::Director::onPickTriangle()
{
	static Node* prevNode = nullptr;
	float minDis = FLT_MAX;
	Node* minNode = nullptr;
	XMVECTOR minPickPos = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	
	int minPick;
	std::vector<Node*> nodes;
	m_NowScene->getAllChilds(nodes);

	for (auto& node : nodes)
	{
		int pick;
		XMVECTOR pickPos;

		minDis = node->getPickedTriangle(&pick, &pickPos, minDis);

		if (pick != -1)
		{
			minPick = pick;
			minNode = node;
			minPickPos = pickPos;
		}
	}

	if (prevNode != nullptr && prevNode != minNode)
	{
		prevNode->onPickTriangle(-1, minPickPos);
	}

	if (minNode != nullptr)
	{
		minNode->onPickTriangle(minPick, minPickPos);
		prevNode = minNode;
	}
	else
	{
		prevNode = nullptr;
	}
}
