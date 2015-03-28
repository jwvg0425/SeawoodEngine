#pragma once
#include "SeaWood.h"
#include "Ref.h"
#include "MouseEvent.h"

NS_SW_BEGIN

//엔진 기본 클래스.
class Node : public Ref
{
public:
	using Nodes = std::vector<Node*>;
					Node();
	virtual			~Node();
	const			Point2& getPosition();
	void			setPosition(Point2 position);
	int				getRefCount();

	virtual bool	init();

	//그리기 함수.
	virtual void	render();

	//매 프레임 해야 하는 작업
	virtual void    update(float dTime);

	//부모 자식 관계 관련 함수
	virtual void	addChild(Node* child);
	void			addChild(Node* child, std::string name);
	Node*			getChild(std::string name);
	//childs 배열에 해당 이름과 같은 이름을 가진 자식들을 전부 담아서 리턴
	void			getChilds(std::string name, Nodes* childs);
	Node*			getParent();
	void			setParent(Node* parent);
	void			removeChild(Node* child);
	void			removeAllChilds();

	//이벤트 관련 함수
	virtual void	onMouseDown(MouseEvent e);
	virtual void	onMouseMove(MouseEvent e);
	virtual void	onMouseUp(MouseEvent e);

	void			setEvent(EventType e);

protected:
	using Childs = std::vector<std::pair<std::string, Node*>>;

	Childs		m_Childs;
	Point2		m_Position;
	Size		m_Size;
	Node*		m_Parent = nullptr;

	std::vector<EventType> m_Events;
};

NS_SW_END