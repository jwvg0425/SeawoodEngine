#include "stdafx.h"
#include "Scene.h"

USING_NS_SW;


Scene::Scene()
{

}

Scene::~Scene()
{
	removeAllChilds();
}

void Scene::render()
{
	for (auto& child : m_Childs)
	{
		child.second->render();
	}
}

void Scene::update(float dTime)
{
	for (auto& child : m_Childs)
	{
		child.second->update(dTime);
	}

	for (auto& child : m_AddingChilds)
	{
		m_Childs.push_back(child);
	}

	m_AddingChilds.clear();
}

bool SeaWood::Scene::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void SeaWood::Scene::addChild(Node* child)
{
	child->setParent(this);
	child->retain();
	m_AddingChilds.push_back(std::make_pair("NO_NAME", child));
}

void SeaWood::Scene::registerLight(const DirectionalLight* directionalLight)
{
	m_DirectionalLight.push_back(directionalLight);
}

void SeaWood::Scene::registerLight(const PointLight* pointLight)
{
	m_PointLight.push_back(pointLight);
}

void SeaWood::Scene::registerLight(const SpotLight* spotLight)
{
	m_SpotLight.push_back(spotLight);
}

const Scene::DLights& SeaWood::Scene::getDirectionalLight()
{
	return m_DirectionalLight;
}

void SeaWood::Scene::deleteLight(const DirectionalLight* directionalLight)
{
	for (auto it = m_DirectionalLight.begin(); it != m_DirectionalLight.end();)
	{
		if (*it == directionalLight)
		{
			it = m_DirectionalLight.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void SeaWood::Scene::deleteLight(const PointLight* pointLight)
{
	for (auto it = m_PointLight.begin(); it != m_PointLight.end();)
	{
		if (*it == pointLight)
		{
			it = m_PointLight.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void SeaWood::Scene::deleteLight(const SpotLight* spotLight)
{
	for (auto it = m_SpotLight.begin(); it != m_SpotLight.end();)
	{
		if (*it == spotLight)
		{
			it = m_SpotLight.erase(it);
		}
		else
		{
			++it;
		}
	}
}

const Scene::PLights& SeaWood::Scene::getPointLight()
{
	return m_PointLight;
}

const Scene::SLights& SeaWood::Scene::getSpotLight()
{
	return m_SpotLight;
}

void SeaWood::Scene::setFog(float fogStart, float fogRange, XMVECTOR fogColor)
{
	m_FogStart = fogStart;
	m_FogRange = fogRange;
	XMStoreFloat4(&m_FogColor, fogColor);
}

void SeaWood::Scene::setFogEnable(bool isEnable)
{
	m_IsFogEnabled = isEnable;
}

float SeaWood::Scene::getFogStart()
{
	return m_FogStart;
}

float SeaWood::Scene::getFogRange()
{
	return m_FogRange;
}

XMFLOAT4 SeaWood::Scene::getFogColor()
{
	return m_FogColor;
}

bool SeaWood::Scene::getFogEnable()
{
	return m_IsFogEnabled;
}
