#include "SWEngine.h"

class RectNode : public SeaWood::Node
{
public:
	RectNode(SeaWood::Rect rect);
	~RectNode() override;

	bool init() override;
	void draw() override;
	void update(float dTime) override;
	SeaWood::Point2 getCenter();
	SeaWood::Size	getSize();

	static RectNode* createWithRect(SeaWood::Rect rect);

protected:
	SeaWood::Point2 m_Center = SeaWood::Point2::ZERO;
	SeaWood::Size	m_Size = SeaWood::Size::ZERO;
	double			m_Angle = 0;
	double			m_Speed = 1;
};