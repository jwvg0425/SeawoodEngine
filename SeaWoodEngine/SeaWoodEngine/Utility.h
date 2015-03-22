#include "Seawood.h"

NS_SW_BEGIN

#ifdef UNICODE
void log(LPCWSTR format, ...);
#else
void log(LPCSTR format, ...);
#endif

NS_SW_END