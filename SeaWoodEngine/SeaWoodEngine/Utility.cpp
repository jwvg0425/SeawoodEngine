#include "stdafx.h"
#include "Utility.h"

const float SeaWood::PI = 3.1415926535f;

void SeaWood::debugLogA(LPCSTR format, ...)
{
	char buf[1024];
	va_list marker;

	va_start(marker, format);
	vsprintf(buf, format, marker);

	strcat(buf, "\n");
	OutputDebugStringA(buf);
}

void SeaWood::debugLogW(LPCWSTR format, ...)
{
	wchar_t buf[1024];
	va_list marker;

	va_start(marker, format);
	vswprintf(buf, format, marker);

	wcscat(buf, L"\n");
	OutputDebugStringW(buf);
}
