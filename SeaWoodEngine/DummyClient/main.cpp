#include "MyApplication.h"

USING_NS_SW;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	MyApplication program;

	program.init(_T("dummy client"), 800, 600);

	return program.run();
}