#pragma once
#include "Box.h"

class Missile : public Box
{
public:
	Missile();
	~Missile() override;

	bool init() override;
	void update(float dTime) override;

	void setDirection(XMVECTOR vector, float speed);

	CREATE_FUNC(Missile);
private:
	XMFLOAT4 m_Vector;
};