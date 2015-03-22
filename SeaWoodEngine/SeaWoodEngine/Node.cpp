#include "stdafx.h"
#include "Node.h"

USING_NS_SW;

Node::Node() : m_Position(Point2::ZERO), m_Size(Size::ZERO)
{

}

Node::~Node()
{

}

const Point2& Node::getPosition()
{
	return m_Position;
}

void Node::setPosition(Point2 position)
{
	m_Position = position;
}

void Node::draw()
{

}

void Node::update(float dTime)
{

}

void Node::addChild(Node* child)
{
	m_Childs.push_back(child);
}

void Node::removeChild(Node* child)
{
	for (auto it = m_Childs.begin(); it != m_Childs.end();)
	{
		if (*it == child)
		{
			it = m_Childs.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool Node::init()
{
	return true;
}
