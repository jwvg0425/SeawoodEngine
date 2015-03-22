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

	void draw() override;
	void update(float dTime) override;
};

NS_SW_END