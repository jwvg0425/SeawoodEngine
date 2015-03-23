#include "Seawood.h"

NS_SW_BEGIN
#ifdef UNICODE
#define LOG(format, ...) debugLogW(format, __VA_ARGS__)
#else
#define LOG(format, ...) debugLogA(format, __VA_AGRS__)
#endif

void debugLogA(LPCSTR format, ...);
void debugLogW(LPCWSTR format, ...);
NS_SW_END