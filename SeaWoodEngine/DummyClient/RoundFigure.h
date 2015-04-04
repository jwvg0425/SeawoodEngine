#pragma once
#include "SWEngine.h"

template <typename VertexType>
class RoundFigure : public SeaWood::Figure<VertexType>
{
public:

	RoundFigure();
	~RoundFigure() override;

	bool init() override;

	void update(float dTime) override;

	void setOption(float radius, XMFLOAT3 direction, float speed);

	static RoundFigure<VertexType>* createWithEffect(EffectType effect);

private:
	float		m_Radius;
	float		m_Speed;
	XMFLOAT3	m_Direction;
	float		m_Theta = 0;
};

template <typename VertexType>
bool RoundFigure<VertexType>::init()
{
	if (!Figure<VertexType>::init())
	{
		return false;
	}

	scheduleUpdate();

	return true;
}

template<typename VertexType>
void RoundFigure<VertexType>::setOption(float radius, XMFLOAT3 direction, float speed)
{
	m_Radius = radius;
	m_Direction = direction;
	m_Speed = speed;
}

template<typename VertexType>
RoundFigure<VertexType>* RoundFigure<VertexType>::createWithEffect(EffectType effect)
{
	RoundFigure<VertexType>* node = new RoundFigure<VertexType>();

	node->setEffect(effect);

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

template<typename VertexType>
void RoundFigure<VertexType>::update(float dTime)
{
	m_Theta += m_Speed*dTime;
	
	auto dirVector = XMLoadFloat3(&m_Direction);

	dirVector = XMVector3Normalize(dirVector);

	auto axisCross = m_Radius * XMVector3Cross(dirVector, XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));

	auto rotate = XMMatrixRotationAxis(dirVector, m_Theta);

	auto rotatePos = XMVector3Transform(axisCross, rotate);

	XMFLOAT3 pos;

	XMStoreFloat3(&pos, rotatePos);

	setPosition(pos.x, pos.y, pos.z);
}

template<typename VertexType>
RoundFigure<VertexType>::~RoundFigure()
{

}

template<typename VertexType>
RoundFigure<VertexType>::RoundFigure()
{

}
