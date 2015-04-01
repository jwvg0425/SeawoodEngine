#include "stdafx.h"
#include "DepthStencil.h"
#include "Director.h"
#include "D3DRenderer.h"
#include "D3DNode.h"
#include "Camera.h"
#include "Scene.h"

USING_NS_SW;

ID3D11DepthStencilState* DepthStencil::m_MarkMirror = nullptr;
ID3D11DepthStencilState* DepthStencil::m_DrawReflection = nullptr;
ID3D11DepthStencilState* DepthStencil::m_NoDoubleBlend = nullptr;

void SeaWood::DepthStencil::destroyAll()
{
	ReleaseCOM(m_MarkMirror);
	ReleaseCOM(m_DrawReflection);
	ReleaseCOM(m_NoDoubleBlend);
}

ID3D11DepthStencilState* SeaWood::DepthStencil::getMarkMirror()
{
	if (m_MarkMirror == nullptr)
	{
		D3D11_DEPTH_STENCIL_DESC mirrorDesc;
		mirrorDesc.DepthEnable = true;
		mirrorDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		mirrorDesc.DepthFunc = D3D11_COMPARISON_LESS;
		mirrorDesc.StencilEnable = true;
		mirrorDesc.StencilReadMask = 0xff;
		mirrorDesc.StencilWriteMask = 0xff;

		mirrorDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		mirrorDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		mirrorDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		mirrorDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// We are not rendering backfacing polygons, so these settings do not matter.
		mirrorDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		mirrorDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		mirrorDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		mirrorDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		HR(GET_D3D_RENDERER()->getDevice()->CreateDepthStencilState(&mirrorDesc, &m_MarkMirror));
	}

	return m_MarkMirror;
}

ID3D11DepthStencilState* SeaWood::DepthStencil::getDrawReflection()
{
	if (m_DrawReflection == nullptr)
	{
		D3D11_DEPTH_STENCIL_DESC drawReflectionDesc;
		drawReflectionDesc.DepthEnable = true;
		drawReflectionDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		drawReflectionDesc.DepthFunc = D3D11_COMPARISON_LESS;
		drawReflectionDesc.StencilEnable = true;
		drawReflectionDesc.StencilReadMask = 0xff;
		drawReflectionDesc.StencilWriteMask = 0xff;

		drawReflectionDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		drawReflectionDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		drawReflectionDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		drawReflectionDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;

		// We are not rendering backfacing polygons, so these settings do not matter.
		drawReflectionDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		drawReflectionDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		drawReflectionDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		drawReflectionDesc.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;

		HR(GET_D3D_RENDERER()->getDevice()->CreateDepthStencilState(&drawReflectionDesc, &m_DrawReflection));
	}

	return m_DrawReflection;
}

ID3D11DepthStencilState* SeaWood::DepthStencil::getNoDoubleBlend()
{
	if (m_NoDoubleBlend == nullptr)
	{
		D3D11_DEPTH_STENCIL_DESC noDoubleBlendDesc;
		noDoubleBlendDesc.DepthEnable = true;
		noDoubleBlendDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		noDoubleBlendDesc.DepthFunc = D3D11_COMPARISON_LESS;
		noDoubleBlendDesc.StencilEnable = true;
		noDoubleBlendDesc.StencilReadMask = 0xff;
		noDoubleBlendDesc.StencilWriteMask = 0xff;

		noDoubleBlendDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		noDoubleBlendDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		noDoubleBlendDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
		noDoubleBlendDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;

		// We are not rendering backfacing polygons, so these settings do not matter.
		noDoubleBlendDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		noDoubleBlendDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		noDoubleBlendDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
		noDoubleBlendDesc.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;

		HR(GET_D3D_RENDERER()->getDevice()->CreateDepthStencilState(&noDoubleBlendDesc, &m_NoDoubleBlend));
	}

	return m_NoDoubleBlend;
}
