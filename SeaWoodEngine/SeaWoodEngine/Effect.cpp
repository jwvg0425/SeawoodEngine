#include "stdafx.h"
#include "Effect.h"
#include "Director.h"
#include "D3DRenderer.h"
#include "Node.h"
#include <fstream>
#include "D3DNode.h"

USING_NS_SW;

SeaWood::Effect::Effect(ID3D11Device* device, const std::wstring& filename)
{
	std::ifstream fin(filename, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size,
		0, device, &m_Fx));
}

SeaWood::Effect::~Effect()
{
	ReleaseCOM(m_Fx);
}

ID3DX11Effect* SeaWood::Effect::getFx()
{
	return m_Fx;
}

void SeaWood::Effect::updateByFrame()
{

}

SeaWood::SimpleColorEffect::SimpleColorEffect() : Effect(GET_D3D_RENDERER()->getDevice(), L"fx/color.cso")
{
	m_Tech = m_Fx->GetTechniqueByName("ColorTech");
	m_FxWorldViewProj = m_Fx->GetVariableByName("")->AsMatrix();
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

void SeaWood::Effects::destroyAll()
{
	SAFE_DELETE(m_SimpleColorFx);
}

SimpleColorEffect* Effects::m_SimpleColorFx = nullptr;

SimpleColorEffect* SeaWood::Effects::getSimpleColorEffect()
{
	if (m_SimpleColorFx == nullptr)
	{
		m_SimpleColorFx = new SimpleColorEffect();
	}

	return m_SimpleColorFx;
}
