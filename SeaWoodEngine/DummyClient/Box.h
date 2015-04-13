#pragma once
#include "SWEngine.h"


struct BoxVertex
{
	XMFLOAT3 m_Pos;
	XMFLOAT4 m_Color;
};

class Box : public SeaWood::Figure<SeaWood::Vertex::PosBasic>
{
public:
	Box();
	~Box() override;

	bool init() override;
	void setBoxWithMaterial(float width, float height, float depth, SeaWood::Material material);
	void setBoxWithRandomColor(float width, float height, float depth);

	void onPickTriangle(int pick) override;

	CREATE_FUNC(Box);

protected:
};