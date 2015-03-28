#define NS_SW_BEGIN namespace SeaWood{
#define NS_SW_END }
#define USING_NS_SW using namespace SeaWood

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

#define SAFE_DELETE(PTR)\
{\
	if (PTR != nullptr)\
	{\
		delete PTR; \
		PTR = nullptr; \
	}\
}
#define SAFE_RELEASE(PTR)\
{\
	if (PTR != nullptr)\
	{\
		PTR->release(); \
		PTR = nullptr; \
	}\
}
#define CREATE_FUNC(CLASS)\
static CLASS* create()\
{\
	CLASS* ptr = new CLASS; \
	if(ptr->init())\
	{\
		ptr->autorelease(); \
		return ptr; \
	}\
	else\
	{\
		delete ptr;\
		return nullptr;\
	}\
}

#define ReleaseCOM(x) { if(x){ x->Release(); x = nullptr; } }