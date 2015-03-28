#include "stdafx.h"
#include "GdiRenderer.h"
#include "Application.h"

USING_NS_SW;

SeaWood::GdiRenderer::GdiRenderer()
{
	m_Type = ViewType::D2_GDI;
	HWND windowHandle = Application::getInstance()->getWindowHandle();
	HDC hdc = GetDC(windowHandle);

	RECT crt;
	GetClientRect(windowHandle, &crt);

	m_MemoryDC = CreateCompatibleDC(hdc);
	m_MemoryBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	m_OldBitmap = (HBITMAP)SelectObject(m_MemoryDC, m_MemoryBitmap);

	ReleaseDC(windowHandle, hdc);
}

SeaWood::GdiRenderer::~GdiRenderer()
{
	SelectObject(m_MemoryDC, m_OldBitmap);
	DeleteDC(m_MemoryDC);
}

void SeaWood::GdiRenderer::render()
{
	HWND windowHandle = Application::getInstance()->getWindowHandle();

	RECT crt;
	GetClientRect(windowHandle, &crt);

	HDC hdc = GetDC(windowHandle);

	BitBlt(hdc, 0, 0, crt.right, crt.bottom, m_MemoryDC, 0, 0, SRCCOPY);
	ReleaseDC(windowHandle, hdc);
}

HDC SeaWood::GdiRenderer::getDC()
{
	return m_MemoryDC;
}

void SeaWood::GdiRenderer::beginFrame()
{
	HWND windowHandle = Application::getInstance()->getWindowHandle();

	RECT crt;
	GetClientRect(windowHandle, &crt);

	FillRect(m_MemoryDC, &crt, GetSysColorBrush(COLOR_WINDOW));
}

bool SeaWood::GdiRenderer::init()
{
	return true;
}
