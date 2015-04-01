#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

class Rasterizer final
{
public:
	static void destroyAll();

	static ID3D11RasterizerState* getWireFrame();
	static ID3D11RasterizerState* getNoCull();
	static ID3D11RasterizerState* getClockwiseCull();

private:
	static ID3D11RasterizerState* m_WireFrame;
	static ID3D11RasterizerState* m_NoCull;
	static ID3D11RasterizerState* m_ClockwiseCull;
};

NS_SW_END