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
	child->m_Parent = this;
	m_Childs.push_back(std::make_pair("NO_NAME",child));
}

void SeaWood::Node::addChild(Node* child, std::string name)
{
	child->m_Parent = this;
	m_Childs.push_back(std::make_pair(name, child));
}

Node* SeaWood::Node::getChild(std::string name)
{
	for (auto& child : m_Childs)
	{
		if (child.first == name)
		{
			return child.second;
		}
	}

	return nullptr;
}

Node* SeaWood::Node::getParent()
{
	return m_Parent;
}

void Node::removeChild(Node* child)
{
	for (auto it = m_Childs.begin(); it != m_Childs.end();)
	{
		if (it->second == child)
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
