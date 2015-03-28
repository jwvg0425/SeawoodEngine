#pragma once
#include "SeaWood.h"

NS_SW_BEGIN


class InputLayoutDesc
{
	friend class InputLayouts;

	static const D3D11_INPUT_ELEMENT_DESC m_PosColor[2];
};

class InputLayouts
{
public:
	static void destroyAll();

	static ID3D11InputLayout* getPosColor();

private:
	static ID3D11InputLayout* m_PosColor;
};

NS_SW_END