#pragma once
#include "Box.h"

class PlayingBox : public Box
{
public:
	PlayingBox();
	~PlayingBox() override;

	bool init() override;
	void update(float dTime) override;

	void setSpeed(float speed);

	void onMouseMove(SeaWood::MouseEvent e) override;

	XMVECTOR getView();

	CREATE_FUNC(PlayingBox);

private:
	XMFLOAT4 m_View;
	float m_Speed = 10.0f;
	float m_Theta = 0.0f;
	SeaWood::Point2 m_PrevMouse;
};