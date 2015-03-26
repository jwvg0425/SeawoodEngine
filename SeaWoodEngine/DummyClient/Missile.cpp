#include "Missile.h"

USING_NS_SW;

Missile::Missile()
{

}

Missile::~Missile()
{

}

bool Missile::init()
{
	if (!Box::init())
	{
		return false;
	}

	setBoxWithRandomColor(0.5f, 0.5f, 0.5f);

	return true;
}

void Missile::update(float dTime)
{
	XMVECTOR vector = XMLoadFloat4(&m_Vector) * dTime;
	float x = XMVectorGetX(vector);
	float y = XMVectorGetY(vector);
	float z = XMVectorGetZ(vector);

	setPosition(x, y, z, true);
}

void Missile::setDirection(XMVECTOR vector, float speed)
{
	XMStoreFloat4(&m_Vector, speed * vector);
}
