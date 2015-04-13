#pragma once
#include "SWEngine.h"


class GridMap : public SeaWood::Figure<SeaWood::Vertex::PosBasic>
{
public:
	enum Mode
	{
		INCREASE,	//높이 상승
		DECREASE,	//높이 감소
		FLAT,		//평평하게
	};
	GridMap();
	~GridMap() override;

	bool init() override;

	void onPickTriangle(int pick, XMVECTOR pickPos) override;
	void update(float dTime) override;

	CREATE_FUNC(GridMap);

protected:
	void pickHighlight();
	int m_Pick = -1;
	XMFLOAT3 m_PickPos;

	Mode m_Mode = INCREASE;
	float m_NowRadius = 10.0f;
	float m_Radius = 10.0f;
	float m_Speed = 5.0f;
	float m_UpMulti = 2.0f;
	float m_NowSpeed = 5.0f;
	float m_Width = 100.0f, m_Depth = 100.0f;
	int m_M = 50, m_N = 50;
};