#include "Eyelight.h"

USING_NS_SW;

EyeLight::EyeLight(SeaWood::Scene* scene) : Light<SpotLight>(scene)
{

}

EyeLight::~EyeLight()
{

}

bool EyeLight::init()
{
	if (!Light<SpotLight>::init())
	{
		return false;
	}

	m_Light.m_Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light.m_Diffuse = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
	m_Light.m_Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light.m_Att = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_Light.m_Spot = 20.0f;
	m_Light.m_Range = 10000.0f;

	return true;
}

void EyeLight::update(float dTime)
{
	m_Light.m_Position = GET_RENDERER()->getCamera()->getEyePosW();
	XMVECTOR pos = XMLoadFloat3(&m_Light.m_Position);
	XMVectorSetW(pos, 1.0f);
	XMVECTOR target = GET_RENDERER()->getCamera()->getTarget();
	XMStoreFloat3(&m_Light.m_Direction,
		XMVector3Normalize(target - pos));
}

EyeLight* EyeLight::createWithScene(SeaWood::Scene* scene)
{
	auto node = new EyeLight(scene);

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
