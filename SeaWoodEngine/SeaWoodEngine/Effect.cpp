#include "stdafx.h"
#include "Effect.h"
#include "Director.h"
#include "D3DRenderer.h"
#include "D3DNode.h"
#include "Camera.h"
#include "Scene.h"
#include "SimpleColorEffect.h"
#include "SimpleLightEffect.h"
#include "BasicEffect.h"
#include <fstream>

USING_NS_SW;

SimpleColorEffect* Effects::m_SimpleColorFx = nullptr;
SimpleLightEffect* Effects::m_SimpleLightFx = nullptr;
BasicEffect* Effects::m_BasicFx = nullptr;

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

void SeaWood::Effect::updateByObject(D3DNode* object)
{

}

void SeaWood::Effects::destroyAll()
{
	SAFE_DELETE(m_SimpleColorFx);
	SAFE_DELETE(m_SimpleLightFx);
	SAFE_DELETE(m_BasicFx);
}

SimpleColorEffect* SeaWood::Effects::getSimpleColorEffect()
{
	if (m_SimpleColorFx == nullptr)
	{
		m_SimpleColorFx = new SimpleColorEffect();
	}

	return m_SimpleColorFx;
}

SimpleLightEffect* SeaWood::Effects::getSimpleLightEffect()
{
	if (m_SimpleLightFx == nullptr)
	{
		m_SimpleLightFx = new SimpleLightEffect();
	}

	return m_SimpleLightFx;

}

void SeaWood::Effects::beginFrame()
{
	if (m_SimpleColorFx != nullptr)
	{
		m_SimpleColorFx->updateByFrame();
	}

	if (m_SimpleLightFx != nullptr)
	{
		m_SimpleLightFx->updateByFrame();
	}

	if (m_BasicFx != nullptr)
	{
		m_BasicFx->updateByFrame();
	}
}

BasicEffect* SeaWood::Effects::getBasicEffect()
{
	if (m_BasicFx == nullptr)
	{
		m_BasicFx = new BasicEffect();
	}

	return m_BasicFx;
}
