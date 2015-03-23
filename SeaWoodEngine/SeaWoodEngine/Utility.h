#include "Seawood.h"

NS_SW_BEGIN
#ifdef UNICODE
void debugLog(LPCWSTR format, ...);
#else
void debugLog(LPCSTR format, ...);
#endif
NS_SW_END