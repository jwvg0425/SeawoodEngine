#include "RoundLight.h"

USING_NS_SW;

RoundLight::RoundLight(SeaWood::Scene* scene)
: Light<PointLight>(scene)
{

}

RoundLight::~RoundLight()
{

}

bool RoundLight::init()
{
	if (!Light<PointLight>::init())
	{
		return false;
	}

	PointLight light;

	light.m_Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	light.m_Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	light.m_Specular = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	light.m_Att = XMFLOAT3(0.0f, 0.1f, 0.0f);
	light.m_Range = 30.0f;

	setLight(light);

	return true;
}

void RoundLight::update(float dTime)
{
	m_Time += dTime;

	m_Light.m_Position.x = 30.0f*cosf(0.6f*m_Time);
	m_Light.m_Position.y = 0.0f;
	m_Light.m_Position.z = 30.0f*sinf(0.6f*m_Time);
}

RoundLight* RoundLight::createWithScene(SeaWood::Scene* scene)
{
	auto node = new RoundLight(scene);

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
