#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

//엔진 기본 클래스.
class Node
{
public:
	Node();
	~Node();
	const		Point2& getPosition();
	void		setPosition(Point2 position);
	void		release();
	int			getRefCount();

	//그리기 함수.
	void		render();

private:

	//reference count 변화시킴.
	void		incRefCount();
	void		decRefCount();

	void		autoRelease();

	Point2		m_Position;
	Size		m_Size;
	int			m_RefCount = 0;
};

NS_SW_END