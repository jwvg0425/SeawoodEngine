#pragma once
#include "Scene.h"

NS_SW_BEGIN


template<typename LightType>
class Light : public Node
{
public:
	Light(Scene* scene);
	~Light() override;

	bool init() override;
	void setLight(LightType light);
	const LightType& getLight();

	static Light<LightType>* createWithScene(Scene* scene, LightType light);

protected:
	LightType m_Light;
	Scene* m_Scene;
};

template<typename LightType>
Light<LightType>* SeaWood::Light<LightType>::createWithScene(Scene* scene, LightType light)
{
	Light<LightType>* node = new Light<LightType>(scene);

	node->setLight(light);

	if (node->init())
	{
		node->autorelease();
		return node;
	}
	else
	{
		delete node;
		return nullptr;
	}
}

template<typename LightType>
const LightType& SeaWood::Light<LightType>::getLight()
{
	return m_Light;
}

template<typename LightType>
void SeaWood::Light<LightType>::setLight(LightType light)
{
	m_Light = light;
}

template<typename LightType>
bool SeaWood::Light<LightType>::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

template<typename LightType>
SeaWood::Light<LightType>::~Light()
{
	m_Scene->deleteLight(&m_Light);
}

template<typename LightType>
SeaWood::Light<LightType>::Light(Scene* scene)
{
	m_Scene = scene;
	m_Scene->registerLight(&m_Light);
}


NS_SW_END