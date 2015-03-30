#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

class Blend final
{
public:
	static void destroyAll();

	static ID3D11BlendState* getTransparentBlend();

private:
	static ID3D11BlendState* m_TransparentBlend;
};

NS_SW_END