#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

struct Vector
{
	Vector() = default;
	~Vector() = default;

	Vector(Vector& rhs) = default;
	Vector& operator=(Vector& rhs) = default;

	Vector(XMFLOAT4& rhs);
	Vector& operator=(XMFLOAT4& rhs);

	Vector(XMVECTOR& rhs);
	Vector& operator=(XMVECTOR& rhs);

	operator XMVECTOR();

	XMFLOAT4 m_Value;
};

NS_SW_END