#pragma once
#include "SWEngine.h"

class SecondScene : public SeaWood::Scene
{
public:
	SecondScene();
	~SecondScene();

	bool init() override;
	void update(float dTime) override;

	CREATE_FUNC(SecondScene);

private:
};