#include "stdafx.h"
#include "Node.h"

USING_NS_SW;

SeaWood::Node::Node()
{
	m_RefCount = 0;
	m_Position = Point2::ZERO;
	m_Size = Size::ZERO;
}

SeaWood::Node::~Node()
{

}

const Point2& SeaWood::Node::getPosition()
{
	return m_Position;
}

void SeaWood::Node::setPosition(Point2 position)
{
	m_Position = position;
}
