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

