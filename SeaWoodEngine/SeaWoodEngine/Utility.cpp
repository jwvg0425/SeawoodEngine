#include "stdafx.h"
#include "Utility.h"

#ifdef UNICODE
void SeaWood::debugLog(LPCWSTR format, ...)
{
	wchar_t buf[1024];
	va_list marker;

	va_start(marker, format);
	vswprintf(buf, format, marker);

	wcscat(buf, L"\n");
	OutputDebugString(buf);
}
#else
void SeaWood::debugLog(LPCSTR format, ...)
{
	char buf[1024];
	va_list marker;

	va_start(marker, format);
	vsprintf(buf, format, marker);

	strcat(buf,"\n");
	OutputDebugString(buf);
}
#endif