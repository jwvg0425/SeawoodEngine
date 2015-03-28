#include "stdafx.h"
#include "Utility.h"

USING_NS_SW;

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

XMMATRIX SeaWood::inverseTranspose(CXMMATRIX M)
{
	// Inverse-transpose is just applied to normals.  So zero out 
	// translation row so that it doesn't get into our inverse-transpose
	// calculation--we don't want the inverse-transpose of the translation.
	XMMATRIX A = M;
	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

	XMVECTOR det = XMMatrixDeterminant(A);
	return XMMatrixTranspose(XMMatrixInverse(&det, A));
}