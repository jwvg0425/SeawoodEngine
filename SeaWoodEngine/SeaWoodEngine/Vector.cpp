#include "stdafx.h"
#include "Vector.h"

USING_NS_SW;

Vector::operator XMVECTOR()
{
	return XMLoadFloat4(&m_Value);
}

SeaWood::Vector::Vector(XMFLOAT4& rhs)
{
	m_Value = rhs;
}

SeaWood::Vector::Vector(XMVECTOR& rhs)
{
	XMStoreFloat4(&m_Value, rhs);
}

Vector& SeaWood::Vector::operator=(XMFLOAT4& rhs)
{
	m_Value = rhs;

	return *this;
}

Vector& SeaWood::Vector::operator=(XMVECTOR& rhs)
{
	XMStoreFloat4(&m_Value, rhs);

	return *this;
}
