#pragma once
#include "SWEngine.h"

class MouseCamera final : public SeaWood::Camera
{
public:
	MouseCamera();
	~MouseCamera();

	bool init() override;
	void update(float dTime) override;

	void setRadius(float radius);

	virtual void onMouseMove(SeaWood::MouseEvent e);

	CREATE_FUNC(MouseCamera);

private:
	float m_Radius = 5.0f;
	float m_Theta = 0.0f;
	float m_Phi = 0.1f;

	SeaWood::Point2 m_PrevMousePos;
};