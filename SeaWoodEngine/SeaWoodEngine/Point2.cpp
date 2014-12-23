#include "stdafx.h"
#include "Point2.h"
#include <cfloat>
#include <math.h>
#include <stdlib.h>


USING_NS_SW;

SeaWood::Point2::Point2(float x, float y)
{
	m_X = x;
	m_Y = y;
}

SeaWood::Point2::Point2(const Point2& other)
{
	m_X = other.m_X;
	m_Y = other.m_Y;
}

SeaWood::Point2::~Point2()
{

}

Point2& SeaWood::Point2::operator=(const Point2& other)
{
	if (this != &other)
	{
		this->m_X = other.m_X;
		this->m_Y = other.m_Y;
	}

	return *this;
}

bool SeaWood::Point2::operator==(const Point2& other)
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

bool SeaWood::Point2::operator!=(const Point2& other)
{
	return !(*this == other);
}

const Point2 SeaWood::Point2::operator+(const Point2& other)
{
	Point2 point = *this;

	point.m_X += other.m_X;
	point.m_Y += other.m_Y;

	return point;
}

const Point2 SeaWood::Point2::operator-(const Point2& other)
{
	Point2 point = *this;

	point.m_X -= other.m_X;
	point.m_Y -= other.m_Y;

	return point;

}

float SeaWood::Point2::getDistance(const Point2& other)
{
	double xDiff = this->m_X - other.m_X;
	double yDiff = this->m_Y - other.m_Y;

	return static_cast<float>(sqrt(xDiff*xDiff + yDiff*yDiff));
}
