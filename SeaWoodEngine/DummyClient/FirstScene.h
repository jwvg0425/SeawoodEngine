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
	DynamicBox* m_Box = nullptr;
	Node*		m_Light = nullptr;
	Node*		m_Light2 = nullptr;
	Node*		m_Light3 = nullptr;
};