﻿#include "stdafx.h"
#include "InputLayout.h"
#include "Effect.h"
#include "Director.h"
#include "Renderer.h"
#include "SimpleColorEffect.h"
#include "SimpleLightEffect.h"
#include "BasicEffect.h"

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

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::m_PosBasic[4] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

ID3D11InputLayout* InputLayouts::m_PosColor = nullptr;
ID3D11InputLayout* InputLayouts::m_PosNormal = nullptr;
ID3D11InputLayout* InputLayouts::m_PosBasic = nullptr;


void InputLayouts::destroyAll()
{
	ReleaseCOM(m_PosColor);
	ReleaseCOM(m_PosNormal);
	ReleaseCOM(m_PosBasic);
}

ID3D11InputLayout* InputLayouts::getPosColor()
{
	if (m_PosColor == nullptr)
	{
		D3DX11_PASS_DESC passDesc;
		Effects::getSimpleColorEffect()->getTech()->GetPassByIndex(0)->GetDesc(&passDesc);
		HR(GET_RENDERER()->getDevice()->CreateInputLayout(InputLayoutDesc::m_PosColor, 2, passDesc.pIAInputSignature,
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
		HR(GET_RENDERER()->getDevice()->CreateInputLayout(InputLayoutDesc::m_PosNormal, 2, passDesc.pIAInputSignature,
			passDesc.IAInputSignatureSize, &m_PosNormal));
	}

	return m_PosNormal;
}

ID3D11InputLayout* SeaWood::InputLayouts::getPosBasic()
{
	if (m_PosBasic == nullptr)
	{
		D3DX11_PASS_DESC passDesc;
		Effects::getBasicEffect()->getTech()->GetPassByIndex(0)->GetDesc(&passDesc);
		HR(GET_RENDERER()->getDevice()->CreateInputLayout(InputLayoutDesc::m_PosBasic, 4, passDesc.pIAInputSignature,
			passDesc.IAInputSignatureSize, &m_PosBasic));
	}

	return m_PosBasic;
}