#pragma once
#include "SWEngine.h"

class FirstScene : public SeaWood::Scene
{
public:
	FirstScene();
	~FirstScene();

	bool init() override;

	void onMouseDown(SeaWood::MouseEvent e) override;

	CREATE_FUNC(FirstScene);

private:
};