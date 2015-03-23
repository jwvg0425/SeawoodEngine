#include "RectNode.h"

USING_NS_SW;

RectNode::RectNode(SeaWood::Rect rect)
: m_Center(rect.m_Origin + rect.m_Size / 2), m_Size(rect.m_Size)
{

}

bool RectNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void RectNode::draw()
{
	auto view = static_cast<GdiView*>(Director::getInstance()->getView());

	HDC dc = view->getDC();

	Point2 topleft = { -m_Size.m_Width / 2, -m_Size.m_Height / 2 };
	Point2 topright = { -m_Size.m_Width / 2, m_Size.m_Height / 2 };
	Point2 bottomleft = { m_Size.m_Width / 2, -m_Size.m_Height / 2 };
	Point2 bottomright = { m_Size.m_Width / 2, m_Size.m_Height / 2 };

	topleft = m_Center + topleft.rotate(m_Angle);
	topright = m_Center + topright.rotate(m_Angle);
	bottomleft = m_Center + bottomleft.rotate(m_Angle);
	bottomright = m_Center + bottomright.rotate(m_Angle);

	POINT points[4];

	points[0].x = topleft.m_X;
	points[0].y = topleft.m_Y;

	points[1].x = topright.m_X;
	points[1].y = topright.m_Y;

	points[2].x = bottomright.m_X;
	points[2].y = bottomright.m_Y;

	points[3].x = bottomleft.m_X;
	points[3].y = bottomleft.m_Y;

	Polygon(dc, points, 4);

}

RectNode* RectNode::createWithRect(SeaWood::Rect rect)
{
	RectNode* node = new RectNode(rect);

	if (node->init())
	{
		return node;
	}
	else
	{
		delete node;
		return nullptr;
	}
}

RectNode::~RectNode()
{

}

void RectNode::update(float dTime)
{
	Node::update(dTime);

	m_Angle += dTime*m_Speed;
}

SeaWood::Point2 RectNode::getCenter()
{
	return m_Center;
}

SeaWood::Size RectNode::getSize()
{
	return m_Size;
}

