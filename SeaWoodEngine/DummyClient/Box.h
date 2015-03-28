﻿#pragma once
#include "SWEngine.h"


struct BoxVertex
{
	XMFLOAT3 m_Pos;
	XMFLOAT4 m_Color;
};

class Box : public SeaWood::D3DNode<SeaWood::SimpleColorEffect>
{
public:
	Box();
	~Box() override;

	bool init() override;
	void setBox(float width, float height, float depth, const std::vector<XMFLOAT4>& colors);
	void setBoxWithRandomColor(float width, float height, float depth);

	CREATE_FUNC(Box);

protected:
	static std::vector<UINT> m_Indices;
};