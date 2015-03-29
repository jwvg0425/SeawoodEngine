#pragma once
#include "SWEngine.h"

//빙글 빙글 도는 빛
class RoundLight : public SeaWood::Light<SeaWood::PointLight>
{
public:
	RoundLight(SeaWood::Scene* scene);
	~RoundLight() override;

	bool init() override;
	void update(float dTime) override;

	static RoundLight* createWithScene(SeaWood::Scene* scene);

protected:
	float m_Time = 0;
};