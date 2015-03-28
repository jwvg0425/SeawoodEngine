#include "stdafx.h"
#include "Scene.h"

USING_NS_SW;


Scene::Scene()
{

}

Scene::~Scene()
{

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
