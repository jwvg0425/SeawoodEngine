#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

class SimpleColorEffect;
class SimpleLightEffect;
class BasicEffect;

namespace Vertex
{
	struct PosColor
	{
		using EffectType = SimpleColorEffect*;

		XMFLOAT3 m_Pos;
		XMFLOAT4 m_Color;
	};

	struct PosNormal
	{
		using EffectType = SimpleLightEffect*;

		PosNormal() : m_Pos(0, 0, 0), m_Normal(0, 0, 0){}
		PosNormal(float x, float y, float z, float nx, float ny, float nz) :
		m_Pos(x, y, z), m_Normal(nx, ny, nz){}

		XMFLOAT3 m_Pos;
		XMFLOAT3 m_Normal;
	};

	struct PosBasic
	{
		using EffectType = BasicEffect*;

		PosBasic() : m_Pos(0, 0, 0), m_Normal(0, 0, 0), m_Tex(0, 0), m_Color(0.0f, 0.0f, 0.0f, 0.0f){}
		PosBasic(float x, float y, float z, float nx, float ny, float nz,
			float tx, float ty) :
			m_Pos(x, y, z), m_Normal(nx, ny, nz), m_Tex(tx, ty),
			m_Color(0.0f, 0.0f, 0.0f, 0.0f){}

		XMFLOAT3 m_Pos;
		XMFLOAT3 m_Normal;
		XMFLOAT2 m_Tex;
		XMFLOAT4 m_Color;
	};
};

NS_SW_END