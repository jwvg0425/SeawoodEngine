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
		PosNormal() : m_Pos(0, 0, 0), m_Normal(0, 0, 0){}
		PosNormal(float x, float y, float z, float nx, float ny, float nz) :
		m_Pos(x, y, z), m_Normal(nx, ny, nz){}

		XMFLOAT3 m_Pos;
		XMFLOAT3 m_Normal;
	};

	struct PosBasic
	{
		PosBasic() : m_Pos(0, 0, 0), m_Normal(0, 0, 0), m_Tex(0,0){}
		PosBasic(float x, float y, float z, float nx, float ny, float nz,
			float tx, float ty) :
			m_Pos(x, y, z), m_Normal(nx, ny, nz), m_Tex(tx, ty){}

		XMFLOAT3 m_Pos;
		XMFLOAT3 m_Normal;
		XMFLOAT2 m_Tex;
	};
};

NS_SW_END