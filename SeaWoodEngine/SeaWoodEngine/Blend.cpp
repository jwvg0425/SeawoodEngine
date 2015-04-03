#include "stdafx.h"
#include "Blend.h"
#include "Director.h"
#include "Renderer.h"
#include "Node.h"
#include "Camera.h"
#include "Scene.h"

USING_NS_SW;

ID3D11BlendState* Blend::m_AlphaToCoverage = nullptr;
ID3D11BlendState* Blend::m_TransparentBlend = nullptr;
ID3D11BlendState* Blend::m_RenderTargetNoWrite = nullptr;

void SeaWood::Blend::destroyAll()
{
	ReleaseCOM(m_AlphaToCoverage);
	ReleaseCOM(m_TransparentBlend);
	ReleaseCOM(m_RenderTargetNoWrite);
}

ID3D11BlendState* SeaWood::Blend::getTransparentBlend()
{
	if (m_TransparentBlend == nullptr)
	{
		D3D11_BLEND_DESC transparentDesc = { 0, };

		transparentDesc.AlphaToCoverageEnable = false;
		transparentDesc.IndependentBlendEnable = false;

		transparentDesc.RenderTarget[0].BlendEnable = true;
		transparentDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		transparentDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		transparentDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		transparentDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		transparentDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		transparentDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		transparentDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		HR(GET_RENDERER()->getDevice()->CreateBlendState(&transparentDesc, &m_TransparentBlend));
	}

	return m_TransparentBlend;
}

ID3D11BlendState* SeaWood::Blend::getRenderTargetNoWrite()
{
	if (m_RenderTargetNoWrite == nullptr)
	{
		D3D11_BLEND_DESC noRenderTargetWritesDesc = { 0 };
		noRenderTargetWritesDesc.AlphaToCoverageEnable = false;
		noRenderTargetWritesDesc.IndependentBlendEnable = false;

		noRenderTargetWritesDesc.RenderTarget[0].BlendEnable = false;
		noRenderTargetWritesDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		noRenderTargetWritesDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		noRenderTargetWritesDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		noRenderTargetWritesDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		noRenderTargetWritesDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		noRenderTargetWritesDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		noRenderTargetWritesDesc.RenderTarget[0].RenderTargetWriteMask = 0;

		HR(GET_RENDERER()->getDevice()->CreateBlendState(&noRenderTargetWritesDesc, &m_RenderTargetNoWrite));
	}

	return m_RenderTargetNoWrite;
}

ID3D11BlendState* SeaWood::Blend::getAlphaToCoverage()
{
	if (m_AlphaToCoverage == nullptr)
	{
		D3D11_BLEND_DESC alphaToCoverageDesc = { 0 };
		alphaToCoverageDesc.AlphaToCoverageEnable = true;
		alphaToCoverageDesc.IndependentBlendEnable = false;
		alphaToCoverageDesc.RenderTarget[0].BlendEnable = false;
		alphaToCoverageDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		HR(GET_RENDERER()->getDevice()->CreateBlendState(&alphaToCoverageDesc, &m_AlphaToCoverage));
	}

	return m_AlphaToCoverage;
}
