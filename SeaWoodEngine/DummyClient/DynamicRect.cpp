#include "DynamicRect.h"

USING_NS_SW;

DynamicRect::DynamicRect(SeaWood::Rect rect) : RectNode(rect)
{

}

DynamicRect::~DynamicRect()
{

}
DynamicRect* DynamicRect::createWithRect(SeaWood::Rect rect)
{
	DynamicRect* node = new DynamicRect(rect);

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

bool DynamicRect::init()
{
	if (!RectNode::init())
	{
		return false;
	}

	return true;
}

void DynamicRect::draw()
{
	HBRUSH brush;
	HBRUSH oldBrush;
	if (collision())
	{
		brush = CreateSolidBrush(RGB(255, 0, 0));
	}
	else
	{
		brush = CreateSolidBrush(RGB(0, 255, 0));
	}

	auto view = static_cast<GdiView*>(Director::getInstance()->getView());

	HDC dc = view->getDC();
	oldBrush = (HBRUSH)SelectObject(dc, brush);

	RectNode::draw();

	SelectObject(dc, oldBrush);
	DeleteObject(brush);
}

void DynamicRect::update(float dTime)
{
	RectNode::update(dTime);

	m_Center = Director::getInstance()->getMouse()->m_Position;
}

bool DynamicRect::collision()
{
	auto rect = static_cast<RectNode*>(getParent()->getChild("rect"));

	auto relativePos = rect->getCenter() - m_Center;

	relativePos = m_Center + relativePos.rotate(-m_Angle);

	auto topleft = m_Center - m_Size / 2;
	auto bottomright = m_Center + m_Size / 2;
	auto topleft2 = relativePos - rect->getSize() / 2;
	auto bottomright2 = relativePos + rect->getSize() / 2;

	if (topleft.m_X > bottomright2.m_X ||
		bottomright.m_X < topleft2.m_X ||
		topleft.m_Y > bottomright2.m_Y ||
		bottomright.m_Y < topleft2.m_Y)
	{
		return false;
	}

	return true;
}
