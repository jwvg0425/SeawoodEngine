﻿#include "stdafx.h"
#include "BasicEffect.h"
#include "Director.h"
#include "D3DRenderer.h"
#include "D3DNode.h"
#include "Camera.h"
#include "Scene.h"

SeaWood::BasicEffect::BasicEffect()
: Effect(GET_D3D_RENDERER()->getDevice(), L"fx/Basic.cso")
{
	m_Tech = m_Fx->GetTechniqueByName("Light");
	m_TexTech = m_Fx->GetTechniqueByName("Tex");
	m_WorldViewProj = m_Fx->GetVariableByName("gWorldViewProj")->AsMatrix();
	m_World = m_Fx->GetVariableByName("gWorld")->AsMatrix();
	m_WorldInvTranspose = m_Fx->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	m_TexTransform = m_Fx->GetVariableByName("gTexTransform")->AsMatrix();
	m_EyePosW = m_Fx->GetVariableByName("gEyePosW")->AsVector();
	m_DirLight = m_Fx->GetVariableByName("gDirLight");
	m_PointLight = m_Fx->GetVariableByName("gPointLight");
	m_SpotLight = m_Fx->GetVariableByName("gSpotLight");
	m_Material = m_Fx->GetVariableByName("gMaterial");
	m_DirNum = m_Fx->GetVariableByName("gDirLightNum");
	m_PointNum = m_Fx->GetVariableByName("gPointLightNum");
	m_SpotNum = m_Fx->GetVariableByName("gSpotLightNum");
	m_DiffuseMap = m_Fx->GetVariableByName("gDiffuseMap")->AsShaderResource();
}

SeaWood::BasicEffect::~BasicEffect()
{
	
}

void SeaWood::BasicEffect::setWorldViewProj(CXMMATRIX M)
{
	m_WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M));
}

void SeaWood::BasicEffect::setWorld(CXMMATRIX M)
{
	m_World->SetMatrix(reinterpret_cast<const float*>(&M));
}

void SeaWood::BasicEffect::setWorldInvTranspose(CXMMATRIX M)
{
	m_WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M));
}

void SeaWood::BasicEffect::setEyePosW(const XMFLOAT3& v)
{
	m_EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3));
}

void SeaWood::BasicEffect::setDirLight(DirectionalLight* light)
{
	m_DirLight->SetRawValue(light, 0, sizeof(DirectionalLight)* 3);
}

void SeaWood::BasicEffect::setPointLight(PointLight* light)
{
	m_PointLight->SetRawValue(light, 0, sizeof(PointLight)* 3);
}

void SeaWood::BasicEffect::setSpotLight(SpotLight* light)
{
	m_SpotLight->SetRawValue(light, 0, sizeof(SpotLight)* 3);
}

void SeaWood::BasicEffect::setMaterial(const Material& mat)
{
	m_Material->SetRawValue(&mat, 0, sizeof(Material));
}

void SeaWood::BasicEffect::setDirLightNum(int n)
{
	m_DirNum->SetRawValue(&n, 0, sizeof(int));
}

void SeaWood::BasicEffect::setPointLightNum(int n)
{
	m_PointNum->SetRawValue(&n, 0, sizeof(int));
}

void SeaWood::BasicEffect::setSpotLightNum(int n)
{
	m_SpotNum->SetRawValue(&n, 0, sizeof(int));
}

ID3DX11EffectTechnique* SeaWood::BasicEffect::getTech()
{
	if (m_IsTexture)
	{
		return m_TexTech;
	}
	else
	{
		return m_Tech;
	}
}

void SeaWood::BasicEffect::updateByFrame()
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

void SeaWood::BasicEffect::updateByObject(D3DNode* object)
{
	auto world = object->getWorld();
	auto viewProj = GET_D3D_RENDERER()->getCamera()->getViewProj();
	auto worldViewProj = world * viewProj;
	auto meterial = object->getMaterial();
	auto texture = object->getTexture();

	_ASSERT(meterial != nullptr);

	setWorldViewProj(worldViewProj);
	XMMATRIX worldInvTranspose = inverseTranspose(world);

	setWorld(world);
	setWorldInvTranspose(worldInvTranspose);
	setWorldViewProj(worldViewProj);
	setMaterial(*meterial);

	if (texture != nullptr)
	{
		setTexTransform(XMLoadFloat4x4(&object->getTextureTransform()));
		setDiffuseMap(texture);
		m_IsTexture = true;
	}
	else
	{
		m_IsTexture = false;
	}
}

void SeaWood::BasicEffect::setDiffuseMap(ID3D11ShaderResourceView* tex)
{
	m_DiffuseMap->SetResource(tex);
}

void SeaWood::BasicEffect::setTexTransform(CXMMATRIX M)
{
	m_TexTransform->SetMatrix(reinterpret_cast<const float*>(&M));
}