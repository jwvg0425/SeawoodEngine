#pragma once
#include "SWEngine.h"

class DynamicBox;
class FirstScene : public SeaWood::Scene
{
public:
	FirstScene();
	~FirstScene();

	bool init() override;
	void update(float dTime) override;

	CREATE_FUNC(FirstScene);

private:
	DynamicBox* m_Box;
};