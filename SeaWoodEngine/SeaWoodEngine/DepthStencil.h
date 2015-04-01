#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

class DepthStencil final
{
public:
	static void destroyAll();

	static ID3D11DepthStencilState* getMarkMirror();
	static ID3D11DepthStencilState* getDrawReflection();
	static ID3D11DepthStencilState* getNoDoubleBlend();

private:
	static ID3D11DepthStencilState* m_MarkMirror;
	static ID3D11DepthStencilState* m_DrawReflection;
	static ID3D11DepthStencilState* m_NoDoubleBlend;
};

NS_SW_END