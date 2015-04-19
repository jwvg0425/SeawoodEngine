#include "stdafx.h"
#include "SimpleLightEffect.h"
#include "Director.h"
#include "Renderer.h"
#include "Node.h"
#include "Camera.h"
#include "Scene.h"

USING_NS_SW;


SeaWood::SimpleLightEffect::SimpleLightEffect()
: Effect(GET_RENDERER()->getDevice(), L"fx/light.cso")
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
	_ASSERT(light != nullptr);

	m_DirLight->SetRawValue(light, 0, sizeof(DirectionalLight)* 3);
}

void SeaWood::SimpleLightEffect::setMaterial(const Material& mat)
{
	m_Material->SetRawValue(&mat, 0, sizeof(Material));
}

ID3DX11EffectTechnique* SeaWood::SimpleLightEffect::getTech()
{
	return m_Tech;
}

void SeaWood::SimpleLightEffect::updateByObject(Node* object)
{
	_ASSERT(object != nullptr);

	auto world = object->getWorld();
	auto viewProj = GET_RENDERER()->getCamera()->getViewProj();
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
	setEyePosW(GET_RENDERER()->getCamera()->getEyePos());
}

void SeaWood::SimpleLightEffect::setPointLight(PointLight* light)
{
	_ASSERT(light != nullptr);

	m_PointLight->SetRawValue(light, 0, sizeof(PointLight)* 3);
}

void SeaWood::SimpleLightEffect::setSpotLight(SpotLight* light)
{
	_ASSERT(light != nullptr);

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
