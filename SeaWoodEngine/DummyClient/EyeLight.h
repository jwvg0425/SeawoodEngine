#pragma once
#include "SWEngine.h"

//시야를 기준으로 따라다니는 빛
class EyeLight : public SeaWood::Light<SeaWood::SpotLight>
{
public:
	EyeLight(SeaWood::Scene* scene);
	~EyeLight() override;

	bool init() override;
	void update(float dTime) override;

	static EyeLight* createWithScene(SeaWood::Scene* scene);

protected:
};