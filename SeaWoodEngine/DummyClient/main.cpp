#include "MyApplication.h"

USING_NS_SW;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	MyApplication program;
	program.init(_T("dummy client"), 500, 500);

	return program.run();
}