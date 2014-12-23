#pragma once
#include "Point2.h"
#include "Size.h"


NS_SW_BEGIN

//사각형을 나타내는 구조체.
struct Rect
{
public:
	Rect();
	~Rect();
	Rect(float x, float y, float width, float height);
	Rect(const Point2& point, const Size& size);
	Rect(const Point2& point, float width, float height);
	Rect(float x, float y, const Size& size);
	Rect(const Rect& rect);

	Rect& operator =(const Rect& other);

public:
	Point2 m_Origin;
	Size m_Size;
};

NS_SW_END