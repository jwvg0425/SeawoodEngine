#include "stdafx.h"
#include "Effect.h"
#include "Director.h"
#include "D3DRenderer.h"
#include "D3DNode.h"
#include "Camera.h"
#include "Scene.h"
#include <fstream>

USING_NS_SW;

SimpleColorEffect* Effects::m_SimpleColorFx = nullptr;
SimpleLightEffect* Effects::m_SimpleLightFx = nullptr;

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

SeaWood::SimpleColorEffect::SimpleColorEffect() : Effect(GET_D3D_RENDERER()->getDevice(), L"fx/color.cso")
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

void SeaWood::Effects::destroyAll()
{
	SAFE_DELETE(m_SimpleColorFx);
	SAFE_DELETE(m_SimpleLightFx);
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
}

SeaWood::SimpleLightEffect::SimpleLightEffect()
: Effect(GET_D3D_RENDERER()->getDevice(), L"fx/light.cso")
{
	m_Tech = m_Fx->GetTechniqueByName("Light");
	m_WorldViewProj = m_Fx->GetVariableByName("gWorldViewProj")->AsMatrix();
	m_World = m_Fx->GetVariableByName("gWorld")->AsMatrix();
	m_WorldInvTranspose = m_Fx->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	m_EyePosW = m_Fx->GetVariableByName("gEyePosW")->AsVector();
	m_DirLight = m_Fx->GetVariableByName("gDirLight");
	m_PointLight = m_Fx->GetVariableByName("gPointLight");
	m_SpotLight = m_Fx->GetVariableByName("gSpotLight");
	m_Material = m_Fx->GetVariableByName("gMaterial");
	m_DirNum = m_Fx->GetVariableByName("gDirLightNum");
	m_PointNum = m_Fx->GetVariableByName("gPointLightNum");
	m_SpotNum = m_Fx->GetVariableByName("gSpotLightNum");
}

SeaWood::SimpleLightEffect::~SimpleLightEffect()
{
}

void SeaWood::SimpleLightEffect::setWorldViewProj(CXMMATRIX M)
{
	m_WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M));
}

void SeaWood::SimpleLightEffect::setWorld(CXMMATRIX M)
{
	m_World->SetMatrix(reinterpret_cast<const float*>(&M));
}

void SeaWood::SimpleLightEffect::setWorldInvTranspose(CXMMATRIX M)
{
	m_WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M));
}

void SeaWood::SimpleLightEffect::setEyePosW(const XMFLOAT3& v)
{
	m_EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3));
}

void SeaWood::SimpleLightEffect::setDirLight(DirectionalLight* light)
{
	m_DirLight->SetRawValue(light, 0, sizeof(DirectionalLight) * 3);
}

void SeaWood::SimpleLightEffect::setMaterial(const Material& mat)
{
	m_Material->SetRawValue(&mat, 0, sizeof(Material));
}

ID3DX11EffectTechnique* SeaWood::SimpleLightEffect::getTech()
{
	return m_Tech;
}

void SeaWood::SimpleLightEffect::updateByObject(D3DNode* object)
{
	auto world = object->getWorld();
	auto viewProj = GET_D3D_RENDERER()->getCamera()->getViewProj();
	auto worldViewProj = world * viewProj;
	auto meterial = object->getMaterial();

	_ASSERT(meterial != nullptr);

	setWorldViewProj(worldViewProj);
	XMMATRIX worldInvTranspose = inverseTranspose(world);

	setWorld(world);
	setWorldInvTranspose(worldInvTranspose);
	setWorldViewProj(worldViewProj);
	setMaterial(*meterial);
}

void SeaWood::SimpleLightEffect::updateByFrame()
{
	auto dirLight = Director::getInstance()->getRunningScene()->getDirectionalLight();
	auto pointLight = Director::getInstance()->getRunningScene()->getPointLight();
	auto spotLight = Director::getInstance()->getRunningScene()->getSpotLight();
	DirectionalLight dLight[3];
	PointLight pLight[3];
	SpotLight sLight[3];

	for (int i = 0; i < dirLight.size(); i++)
	{
		dLight[i] = *dirLight[i];
	}

	for (int i = 0; i < pointLight.size(); i++)
	{
		pLight[i] = *pointLight[i];
	}

	for (int i = 0; i < spotLight.size(); i++)
	{
		sLight[i] = *spotLight[i];
	}
	
	setDirLight(dLight);
	setPointLight(pLight);
	setSpotLight(sLight);
	setDirLightNum(dirLight.size());
	setPointLightNum(pointLight.size());
	setSpotLightNum(spotLight.size());
	setEyePosW(GET_D3D_RENDERER()->getCamera()->getEyePosW());
}

void SeaWood::SimpleLightEffect::setPointLight(PointLight* light)
{
	m_PointLight->SetRawValue(light, 0, sizeof(PointLight)* 3);
}

void SeaWood::SimpleLightEffect::setSpotLight(SpotLight* light)
{
	m_SpotLight->SetRawValue(light, 0, sizeof(SpotLight)* 3);
}

void SeaWood::SimpleLightEffect::setDirLightNum(int n)
{
	m_DirNum->SetRawValue(&n, 0, sizeof(int));
}

void SeaWood::SimpleLightEffect::setPointLightNum(int n)
{
	m_PointNum->SetRawValue(&n, 0, sizeof(int));
}

void SeaWood::SimpleLightEffect::setSpotLightNum(int n)
{
	m_SpotNum->SetRawValue(&n, 0, sizeof(int));
}
