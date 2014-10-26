#include "stdafx.h"
#include "Application.h"

USING_NS_SW;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	Application::getInstance()->init(_T("dummy client"), 500, 500);
	Application::getInstance()->run();

	return 0;
}