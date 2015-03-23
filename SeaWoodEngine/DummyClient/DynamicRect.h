#include "RectNode.h"

class DynamicRect : public RectNode
{
public:
	DynamicRect(SeaWood::Rect rect);
	~DynamicRect();

	bool init() override;
	void draw() override;
	void update(float dTime) override;

	static DynamicRect* createWithRect(SeaWood::Rect rect);

private:
	bool collision();
};