#pragma once
#include "SWEngine.h"

namespace GeometryGenerator
{
	void createBox(float width, float height, float depth,
		std::vector<SeaWood::Vertex::PosBasic>& vertices, std::vector<UINT>& indices);

	void createSphere(float radius, UINT sliceCount, UINT stackCount,
		std::vector<SeaWood::Vertex::PosBasic>& vertices, std::vector<UINT>& indices);

	void createGrid(float width, float depth, UINT m, UINT n,
		std::vector<SeaWood::Vertex::PosBasic>& vertices, std::vector<UINT>& indices);
};