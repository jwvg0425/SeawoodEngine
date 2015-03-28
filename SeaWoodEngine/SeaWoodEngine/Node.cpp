#include "stdafx.h"
#include "Node.h"
#include "Director.h"

USING_NS_SW;

Node::Node() : m_Position(Point2::ZERO), m_Size(Size::ZERO)
{

}

Node::~Node()
{
	removeAllChilds();
	for (auto& e : m_Events)
	{
		Director::getInstance()->clearEvent(e, this);
	}
}

const Point2& Node::getPosition()
{
	return m_Position;
}

void Node::setPosition(Point2 position)
{
	m_Position = position;
}

void Node::render()
{

}

void Node::update(float dTime)
{

}

void Node::addChild(Node* child)
{
	child->m_Parent = this;
	child->retain();
	m_Childs.push_back(std::make_pair("NO_NAME",child));
}

void SeaWood::Node::addChild(Node* child, std::string name)
{
	child->m_Parent = this;
	child->retain();
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

void SeaWood::Node::onMouseDown(MouseEvent e)
{

}

void SeaWood::Node::onMouseMove(MouseEvent e)
{

}

void SeaWood::Node::onMouseUp(MouseEvent e)
{

}

void SeaWood::Node::removeAllChilds()
{
	//자식 모두 release 작업.
	for (auto& child : m_Childs)
	{
		child.second->release();
	}

	m_Childs.clear();
}

void SeaWood::Node::getChilds(std::string name, Nodes* childs)
{
	for (auto& child : m_Childs)
	{
		if (child.first == name)
		{
			childs->push_back(child.second);
		}
	}
}

void SeaWood::Node::setEvent(EventType e)
{
	m_Events.push_back(e);
}

void SeaWood::Node::setParent(Node* parent)
{
	_ASSERT(parent != nullptr);

	m_Parent = parent;
}

void Node::removeChild(Node* child)
{
	_ASSERT(child != nullptr);
	if (child == nullptr)
	{
		return;
	}

	for (auto it = m_Childs.begin(); it != m_Childs.end();)
	{
		if (it->second == child)
		{
			it->second->release();
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
