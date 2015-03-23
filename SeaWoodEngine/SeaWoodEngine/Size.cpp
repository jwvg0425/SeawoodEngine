#include "stdafx.h"
#include "Size.h"

USING_NS_SW;

const Size Size::ZERO = Size(0.0f, 0.0f);

Size::Size()
{
	m_Width = 0.0f;
	m_Height = 0.0f;
}

Size::Size(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

Size::Size(const Size& other)
{
	this->m_Width = other.m_Width;
	this->m_Height = other.m_Height;
}

Size::~Size()
{

}

float Size::getArea()
{
	return m_Width * m_Height;
}

Size& Size::operator=(const Size& other)
{
	this->m_Width = other.m_Width;
	this->m_Height = other.m_Height;

	return *this;
}

const Size Size::operator+(const Size& other)
{
	Size size = *this;

	size.m_Width += other.m_Width;
	size.m_Height += other.m_Height;

	return size;
}

const Size Size::operator-(const Size& other)
{
	Size size = *this;

	size.m_Width -= other.m_Width;
	size.m_Height -= other.m_Height;

	return size;
}

const Size SeaWood::Size::operator*(int n)
{
	Size size = *this;

	size.m_Width *= n;
	size.m_Height *= n;

	return size;
}

const Size SeaWood::Size::operator/(int n)
{
	Size size = *this;

	size.m_Width /= n;
	size.m_Height /= n;

	return size;
}
