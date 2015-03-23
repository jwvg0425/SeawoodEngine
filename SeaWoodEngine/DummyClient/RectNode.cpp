#include "RectNode.h"

USING_NS_SW;

RectNode::RectNode(SeaWood::Rect rect) : m_Rect(rect)
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

	Rectangle(dc,
		m_Rect.m_Origin.m_X - m_Rect.m_Size.m_Width / 2,
		m_Rect.m_Origin.m_Y - m_Rect.m_Size.m_Height / 2,
		m_Rect.m_Origin.m_X + m_Rect.m_Size.m_Width / 2,
		m_Rect.m_Origin.m_Y + m_Rect.m_Size.m_Height / 2);
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

	m_Rect.m_Origin = Director::getInstance()->getMouse()->m_Position;
}

