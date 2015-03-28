#pragma once
#include "Seawood.h"
#include "Node.h"

NS_SW_BEGIN

//화면 담당 클래스
class Scene : public Node
{
public:
	Scene();
	~Scene() override;

	bool init() override;

	void render() override;
	void update(float dTime) override;

	void addChild(Node* child) override;

protected:
	Childs		m_AddingChilds;
};

NS_SW_END