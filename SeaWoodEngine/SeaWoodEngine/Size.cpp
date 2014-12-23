#include "stdafx.h"
#include "Size.h"

USING_NS_SW;

const Size Size::ZERO = Size(0.0f, 0.0f);

SeaWood::Size::Size()
{
	m_Width = 0.0f;
	m_Height = 0.0f;
}

SeaWood::Size::Size(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

SeaWood::Size::Size(const Size& other)
{
	this->m_Width = other.m_Width;
	this->m_Height = other.m_Height;
}

SeaWood::Size::~Size()
{

}

float SeaWood::Size::getArea()
{
	return m_Width * m_Height;
}

Size& SeaWood::Size::operator=(const Size& other)
{
	this->m_Width = other.m_Width;
	this->m_Height = other.m_Height;

	return *this;
}

const Size SeaWood::Size::operator+(const Size& other)
{
	Size size = *this;

	size.m_Width += other.m_Width;
	size.m_Height += other.m_Height;

	return size;
}

const Size SeaWood::Size::operator-(const Size& other)
{
	Size size = *this;

	size.m_Width -= other.m_Width;
	size.m_Height -= other.m_Height;

	return size;
}
