#pragma once
#include "SWEngine.h"


class Box : public SeaWood::Figure<SeaWood::Vertex::PosBasic>
{
public:
	Box();
	~Box() override;

	bool init() override;
	void setBoxWithMaterial(float width, float height, float depth, SeaWood::Material material);
	void setBoxWithRandomColor(float width, float height, float depth);

	CREATE_FUNC(Box);

protected:
};