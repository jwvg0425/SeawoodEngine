#include "SWEngine.h"

class RectNode : public SeaWood::Node
{
public:
	RectNode(SeaWood::Rect rect);
	~RectNode();

	bool init() override;
	void draw() override;
	void update(float dTime) override;

	static RectNode* createWithRect(SeaWood::Rect rect);

private:
	SeaWood::Rect m_Rect;
};