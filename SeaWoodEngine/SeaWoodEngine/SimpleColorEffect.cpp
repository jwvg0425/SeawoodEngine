#include "stdafx.h"
#include "SimpleColorEffect.h"
#include "Director.h"
#include "D3DRenderer.h"
#include "D3DNode.h"
#include "Camera.h"

USING_NS_SW;

SeaWood::SimpleColorEffect::SimpleColorEffect()
: Effect(GET_D3D_RENDERER()->getDevice(), L"fx/color.cso")
{
	m_Tech = m_Fx->GetTechniqueByName("ColorTech");
	m_FxWorldViewProj = m_Fx->GetVariableByName("gWorldViewProj")->AsMatrix();
}

SeaWood::SimpleColorEffect::~SimpleColorEffect()
{

}

void SeaWood::SimpleColorEffect::setWorldViewProj(CXMMATRIX M)
{
	m_FxWorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M));
}

ID3DX11EffectTechnique* SeaWood::SimpleColorEffect::getTech()
{
	return m_Tech;
}

void SeaWood::SimpleColorEffect::updateByObject(D3DNode* object)
{
	auto world = object->getWorld();
	auto viewProj = GET_D3D_RENDERER()->getCamera()->getViewProj();
	auto worldViewProj = world * viewProj;
	setWorldViewProj(worldViewProj);
}
