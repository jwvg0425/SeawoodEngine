#include "stdafx.h"
#include "Blend.h"
#include "Director.h"
#include "D3DRenderer.h"
#include "D3DNode.h"
#include "Camera.h"
#include "Scene.h"

USING_NS_SW;

ID3D11BlendState* Blend::m_TransparentBlend = nullptr;

void SeaWood::Blend::destroyAll()
{
	ReleaseCOM(m_TransparentBlend);
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

		HR(GET_D3D_RENDERER()->getDevice()->CreateBlendState(&transparentDesc, &m_TransparentBlend));
	}

	return m_TransparentBlend;
}
