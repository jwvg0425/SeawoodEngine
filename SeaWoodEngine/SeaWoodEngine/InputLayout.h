#pragma once
#include "SeaWood.h"

NS_SW_BEGIN


class InputLayoutDesc final
{
	friend class InputLayouts;

	static const D3D11_INPUT_ELEMENT_DESC m_PosColor[2];
	static const D3D11_INPUT_ELEMENT_DESC m_PosNormal[2];
	static const D3D11_INPUT_ELEMENT_DESC m_PosBasic[3];
};

class InputLayouts final
{
public:
	static void destroyAll();

	static ID3D11InputLayout* getPosColor();
	static ID3D11InputLayout* getPosNormal();
	static ID3D11InputLayout* getPosBasic();

private:
	static ID3D11InputLayout* m_PosColor;
	static ID3D11InputLayout* m_PosNormal;
	static ID3D11InputLayout* m_PosBasic;
};

NS_SW_END