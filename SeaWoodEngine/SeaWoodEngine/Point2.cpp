#include "stdafx.h"
#include "Point2.h"
#include "Size.h"
#include <cfloat>
#include <math.h>
#include <stdlib.h>


USING_NS_SW;

const Point2 Point2::ZERO = Point2(0.0f, 0.0f);

Point2::Point2(float x, float y)
{
	m_X = x;
	m_Y = y;
}

Point2::Point2(const Point2& other)
{
	m_X = other.m_X;
	m_Y = other.m_Y;
}

Point2::Point2()
{
	m_X = 0.0f;
	m_Y = 0.0f;
}

Point2::~Point2()
{

}

Point2& Point2::operator=(const Point2& other)
{
	if (this != &other)
	{
		this->m_X = other.m_X;
		this->m_Y = other.m_Y;
	}

	return *this;
}

bool Point2::operator==(const Point2& other)
{
	float xDiff = fabs(other.m_X - this->m_X);
	float yDiff = fabs(other.m_Y - this->m_Y);
	float xLargest = max(fabs(this->m_X), fabs(other.m_X));
	float yLargest = max(fabs(this->m_Y), fabs(other.m_Y));
	
	
	if (xDiff <= xLargest*FLT_EPSILON && yDiff <= yLargest*FLT_EPSILON)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Point2::operator!=(const Point2& other)
{
	return !(*this == other);
}

const Point2 Point2::operator+(const Point2& other)
{
	Point2 point = *this;

	point.m_X += other.m_X;
	point.m_Y += other.m_Y;

	return point;
}

const Point2 Point2::operator+(const Size& size)
{
	Point2 point = *this;

	point.m_X += size.m_Width;
	point.m_Y += size.m_Height;

	return point;
}

const Point2 Point2::operator-(const Point2& other)
{
	Point2 point = *this;

	point.m_X -= other.m_X;
	point.m_Y -= other.m_Y;

	return point;

}

float Point2::getDistance(const Point2& other) const
{
	double xDiff = this->m_X - other.m_X;
	double yDiff = this->m_Y - other.m_Y;

	return static_cast<float>(sqrt(xDiff*xDiff + yDiff*yDiff));
}

const Point2 Point2::operator-(const Size& size)
{
	Point2 point = *this;

	point.m_X -= size.m_Width;
	point.m_Y -= size.m_Height;

	return point;
}

const Point2 SeaWood::Point2::rotate(double radian) const
{
	Point2 res;

	res.m_X = static_cast<float>(m_X*cos(radian) - m_Y*sin(radian));
	res.m_Y = static_cast<float>(m_X*sin(radian) + m_Y*cos(radian));

	return res;
}
