#pragma once

#include "Macro.h"
#include "Point2.h"
#include "Size.h"
#include "Rect.h"
#include "Vertex.h"
#include "Light.h"

NS_SW_BEGIN

struct ModelInfo
{
	std::vector<Vertex::PosBasic> m_Vertices;
	std::vector<UINT> m_Indices;
	std::string	m_Texture;
	Material m_Material;
	float m_UTile, m_VTile;
};

NS_SW_END