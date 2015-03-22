#include "stdafx.h"
#include "Scene.h"

USING_NS_SW;


Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::draw()
{
	for (auto& child : m_Childs)
	{
		child->draw();
	}
}

void Scene::update(float dTime)
{
	for (auto& child : m_Childs)
	{
		child->update(dTime);
	}
}

bool SeaWood::Scene::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}
