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

void SeaWood::Node::incRefCount()
{
	m_RefCount++;
}

int SeaWood::Node::getRefCount()
{
	return m_RefCount;
}

void SeaWood::Node::decRefCount()
{
	_ASSERT(m_RefCount > 0);

	m_RefCount--;

	//reference Count가 0이 되면 할당 해제.
	if (m_RefCount == 0)
	{
		delete this;
	}
}

void SeaWood::Node::release()
{
	decRefCount();
}
