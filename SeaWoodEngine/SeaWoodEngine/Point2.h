#pragma once


NS_SW_BEGIN


// 2차원 좌표계의 한 점을 나타내는 구조체.
struct Size;
struct Point2
{
public:
	Point2();
	Point2(float x, float y);
	~Point2();
	Point2(const Point2& other);
	Point2& operator =(const Point2& other);

	//실수 오차를 고려하여 두 좌표가 같은 좌표인지를 비교한다.
	bool operator ==(const Point2& other);

	//실수 오차를 고려하여 두 좌표가 같은 좌표인지를 비교한다.
	bool operator !=(const Point2& other);

	//두 좌표의 값을 단순 더한 좌표를 리턴한다.
	const Point2 operator +(const Point2& other);

	//두 좌표의 값을 단순하게 뺀 좌표를 리턴한다.
	const Point2 operator -(const Point2& other);

	//해당 좌표에 크기를 더한 좌표를 리턴한다.
	const Point2 operator +(const Size& size);

	//해당 좌표에 크기를 뺀 좌표를 리턴한다.
	const Point2 operator -(const Size& size);

	//두 좌표 사이의 거리를 계산하여 리턴한다.
	float getDistance(const Point2& other);

public:
	static const Point2 ZERO;
	float m_X, m_Y;
};

NS_SW_END