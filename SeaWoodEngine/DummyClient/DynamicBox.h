#pragma once
#include "Box.h"

class DynamicBox : public Box
{
public:
	DynamicBox();
	~DynamicBox() override;

	bool init() override;
	void update(float dTime) override;

	CREATE_FUNC(DynamicBox);
private:
};