#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

class Rasterizer final
{
public:
	static void destroyAll();

	static ID3D11RasterizerState* getWireFrame();

private:
	static ID3D11RasterizerState* m_WireFrame;
};

NS_SW_END