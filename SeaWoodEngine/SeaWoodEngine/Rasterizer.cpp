#include "stdafx.h"
#include "Rasterizer.h"
#include "Director.h"
#include "D3DRenderer.h"
#include "D3DNode.h"
#include "Camera.h"
#include "Scene.h"

USING_NS_SW;

ID3D11RasterizerState* Rasterizer::m_WireFrame = nullptr;

void SeaWood::Rasterizer::destroyAll()
{
	ReleaseCOM(m_WireFrame);
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

		HR(GET_D3D_RENDERER()->getDevice()->CreateRasterizerState(&wireframeDesc, &m_WireFrame));
	}

	return m_WireFrame;
}