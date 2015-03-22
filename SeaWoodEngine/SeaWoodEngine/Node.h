﻿#pragma once
#include "SeaWood.h"

NS_SW_BEGIN

//엔진 기본 클래스.
class Node
{
public:
					Node();
	virtual			~Node();
	const			Point2& getPosition();
	void			setPosition(Point2 position);
	int				getRefCount();

	virtual bool	init();

	//그리기 함수.
	virtual void	draw();

	//매 프레임 해야 하는 작업
	virtual void    update(float dTime);

	//부모 자식 관계 관련 함수
	void			addChild(Node* child);
	void			removeChild(Node* child);

protected:
	using Childs = std::vector<Node*>;

	Childs		m_Childs;
	Point2		m_Position;
	Size		m_Size;
};

NS_SW_END