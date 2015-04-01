#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

class Blend final
{
public:
	static void destroyAll();

	static ID3D11BlendState* getAlphaToCoverage();
	static ID3D11BlendState* getTransparentBlend();
	static ID3D11BlendState* getRenderTargetNoWrite();

private:
	static ID3D11BlendState* m_AlphaToCoverage;
	static ID3D11BlendState* m_TransparentBlend;
	static ID3D11BlendState* m_RenderTargetNoWrite;
};

NS_SW_END