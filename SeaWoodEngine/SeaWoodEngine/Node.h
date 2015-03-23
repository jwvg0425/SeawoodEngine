#pragma once
#include "SeaWood.h"
#include "MouseEvent.h"

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
	void			addChild(Node* child, std::string name);
	Node*			getChild(std::string name);
	Node*			getParent();
	void			removeChild(Node* child);

	//이벤트 관련 함수
	virtual void	onMouseDown(MouseEvent e);
	virtual void	onMouseMove(MouseEvent e);
	virtual void	onMouseUp(MouseEvent e);

protected:
	using Childs = std::vector<std::pair<std::string, Node*>>;

	Childs		m_Childs;
	Point2		m_Position;
	Size		m_Size;
	Node*		m_Parent = nullptr;
};

NS_SW_END