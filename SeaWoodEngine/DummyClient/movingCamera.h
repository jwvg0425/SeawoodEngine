#pragma once
#include "SWEngine.h"

class MovingCamera : public SeaWood::Camera
{
public:
	MovingCamera(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up);
	~MovingCamera() override;

	bool init() override;
	void update(float dTime) override;

	void onMouseMove(SeaWood::MouseEvent e) override;

	static MovingCamera* createWithPos(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up);
private:
	SeaWood::Point2	m_LastPos;
};