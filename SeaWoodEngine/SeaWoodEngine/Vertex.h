#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

namespace Vertex
{
	struct PosColor
	{
		XMFLOAT3 m_Pos;
		XMFLOAT4 m_Color;
	};

	struct PosNormal
	{
		PosNormal(float x, float y, float z, float nx, float ny, float nz) :
		m_Pos(x, y, z), m_Normal(nx, ny, nz){}

		XMFLOAT3 m_Pos;
		XMFLOAT3 m_Normal;
	};
};

NS_SW_END