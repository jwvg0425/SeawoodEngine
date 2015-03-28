#include "Seawood.h"

#ifdef UNICODE
#define LOG(format, ...) SeaWood::debugLogW(format, __VA_ARGS__)
#else
#define LOG(format, ...) SeaWood::debugLogA(format, __VA_AGRS__)
#endif


NS_SW_BEGIN

extern const float PI;

void debugLogA(LPCSTR format, ...);
void debugLogW(LPCWSTR format, ...);

XMMATRIX inverseTranspose(CXMMATRIX M);

NS_SW_END