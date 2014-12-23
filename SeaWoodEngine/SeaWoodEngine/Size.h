#pragma once


NS_SW_BEGIN

//크기를 나타내는 구조체.
struct Size
{
public:
	Size();
	~Size();
	Size(float width, float height);
	Size(const Size& other);
	Size& operator =(const Size& other);

	//두 사이즈의 너비, 높이 값을 각각 더한 사이즈를 돌려준다.
	const Size operator +(const Size& other);

	//두 사이즈의 너비, 높이 값을 각각 뺀 사이즈를 돌려준다.
	const Size operator -(const Size& other);

	//너비와 높이를 곱한 면적을 돌려준다.
	float getArea();

public:
	static const Size ZERO;
	float m_Width, m_Height;
};

NS_SW_END