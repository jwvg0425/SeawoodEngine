#include "stdafx.h"
#include "InputLayout.h"
#include "Effect.h"
#include "Director.h"
#include "D3DRenderer.h"

USING_NS_SW;

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::m_PosColor[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::m_PosNormal[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

ID3D11InputLayout* InputLayouts::m_PosColor = nullptr;
ID3D11InputLayout* InputLayouts::m_PosNormal = nullptr;


void InputLayouts::destroyAll()
{
	ReleaseCOM(m_PosColor);
	ReleaseCOM(m_PosNormal);
}

ID3D11InputLayout* InputLayouts::getPosColor()
{
	if (m_PosColor == nullptr)
	{
		D3DX11_PASS_DESC passDesc;
		Effects::getSimpleColorEffect()->getTech()->GetPassByIndex(0)->GetDesc(&passDesc);
		HR(GET_D3D_RENDERER()->getDevice()->CreateInputLayout(InputLayoutDesc::m_PosColor, 2, passDesc.pIAInputSignature,
			passDesc.IAInputSignatureSize, &m_PosColor));
	}

	return m_PosColor;
}

ID3D11InputLayout* SeaWood::InputLayouts::getPosNormal()
{
	if (m_PosNormal == nullptr)
	{
		D3DX11_PASS_DESC passDesc;
		Effects::getSimpleLightEffect()->getTech()->GetPassByIndex(0)->GetDesc(&passDesc);
		HR(GET_D3D_RENDERER()->getDevice()->CreateInputLayout(InputLayoutDesc::m_PosNormal, 2, passDesc.pIAInputSignature,
			passDesc.IAInputSignatureSize, &m_PosNormal));
	}

	return m_PosNormal;
}
