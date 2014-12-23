#include "stdafx.h"
#include "Rect.h"

USING_NS_SW;

SeaWood::Rect::Rect() : m_Origin(Point2::ZERO), m_Size(Size::ZERO)
{
}

SeaWood::Rect::Rect(float x, float y, float width, float height)
: m_Origin(x, y), m_Size(width, height)
{
}

SeaWood::Rect::Rect(const Point2& point, const Size& size)
: m_Origin(point), m_Size(size)
{

}

SeaWood::Rect::Rect(const Point2& point, float width, float height)
: m_Origin(point), m_Size(width, height)
{

}

SeaWood::Rect::Rect(float x, float y, const Size& size)
: m_Origin(x, y), m_Size(size)
{

}

SeaWood::Rect::Rect(const Rect& rect)
{
	this->m_Origin = rect.m_Origin;
	this->m_Size = rect.m_Size;
}

SeaWood::Rect::~Rect()
{

}

Rect& SeaWood::Rect::operator=(const Rect& other)
{
	this->m_Origin = other.m_Origin;
	this->m_Size = other.m_Size;

	return *this;
}
