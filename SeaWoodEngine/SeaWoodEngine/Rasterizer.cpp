#include "stdafx.h"
#include "Rasterizer.h"
#include "Director.h"
#include "Renderer.h"
#include "Node.h"
#include "Camera.h"
#include "Scene.h"

USING_NS_SW;

ID3D11RasterizerState* Rasterizer::m_WireFrame = nullptr;
ID3D11RasterizerState* Rasterizer::m_NoCull = nullptr;
ID3D11RasterizerState* Rasterizer::m_ClockwiseCull = nullptr;

void SeaWood::Rasterizer::destroyAll()
{
	ReleaseCOM(m_WireFrame);
	ReleaseCOM(m_NoCull);
	ReleaseCOM(m_ClockwiseCull);
}

ID3D11RasterizerState* SeaWood::Rasterizer::getWireFrame()
{
	if (m_WireFrame == nullptr)
	{
		D3D11_RASTERIZER_DESC wireframeDesc;
		ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
		wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
		wireframeDesc.CullMode = D3D11_CULL_BACK;
		wireframeDesc.FrontCounterClockwise = false;
		wireframeDesc.DepthClipEnable = true;

		HR(GET_RENDERER()->getDevice()->CreateRasterizerState(&wireframeDesc, &m_WireFrame));
	}

	return m_WireFrame;
}

ID3D11RasterizerState* SeaWood::Rasterizer::getNoCull()
{
	if (m_NoCull == nullptr)
	{
		D3D11_RASTERIZER_DESC noCullDesc;
		ZeroMemory(&noCullDesc, sizeof(D3D11_RASTERIZER_DESC));
		noCullDesc.FillMode = D3D11_FILL_SOLID;
		noCullDesc.CullMode = D3D11_CULL_NONE;
		noCullDesc.FrontCounterClockwise = false;
		noCullDesc.DepthClipEnable = true;

		HR(GET_RENDERER()->getDevice()->CreateRasterizerState(&noCullDesc, &m_NoCull));
	}

	return m_NoCull;
}

ID3D11RasterizerState* SeaWood::Rasterizer::getClockwiseCull()
{
	if (m_ClockwiseCull == nullptr)
	{
		D3D11_RASTERIZER_DESC cullClockwiseDesc;
		ZeroMemory(&cullClockwiseDesc, sizeof(D3D11_RASTERIZER_DESC));
		cullClockwiseDesc.FillMode = D3D11_FILL_SOLID;
		cullClockwiseDesc.CullMode = D3D11_CULL_BACK;
		cullClockwiseDesc.FrontCounterClockwise = true;
		cullClockwiseDesc.DepthClipEnable = true;

		HR(GET_RENDERER()->getDevice()->CreateRasterizerState(&cullClockwiseDesc, &m_ClockwiseCull));
	}

	return m_ClockwiseCull;
}
