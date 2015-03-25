#include "Seawood.h"

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                              \
	{                                                          \
	HRESULT hr = (x);                                      \
if (FAILED(hr))                                         \
		{                                                      \
		DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
#endif

#else
#ifndef HR
#define HR(x) (x)
#endif
#endif

#ifdef UNICODE
#define LOG(format, ...) SeaWood::debugLogW(format, __VA_ARGS__)
#else
#define LOG(format, ...) SeaWood::debugLogA(format, __VA_AGRS__)
#endif


NS_SW_BEGIN
void debugLogA(LPCSTR format, ...);
void debugLogW(LPCWSTR format, ...);
NS_SW_END