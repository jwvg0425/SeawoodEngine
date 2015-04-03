#pragma once
#include "SWEngine.h"


class FirstScene : public SeaWood::Scene
{
public:
	FirstScene();
	~FirstScene();

	bool init() override;
	void update(float dTime) override;

	CREATE_FUNC(FirstScene);

private:
};