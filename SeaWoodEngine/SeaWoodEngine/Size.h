#pragma once


NS_SW_BEGIN

//크기를 나타내는 구조체.
struct Size final
{
public:
	Size();
	~Size();
	Size(float width, float height);
	Size(const Size& other);
	Size& operator =(const Size& other);

	//두 사이즈의 너비, 높이 값을 각각 더한 사이즈를 돌려준다.
	const Size operator +(const Size& other) const;

	//두 사이즈의 너비, 높이 값을 각각 뺀 사이즈를 돌려준다.
	const Size operator -(const Size& other) const;

	//사이즈를 확대한 값을 돌려준다
	const Size operator *(int n) const;

	//사이즈를 축소한 값을 돌려준다
	const Size operator /(int n) const;

	//너비와 높이를 곱한 면적을 돌려준다.
	float getArea() const;

public:
	static const Size ZERO;
	float m_Width, m_Height;
};

NS_SW_END