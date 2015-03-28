#pragma once
#include "Seawood.h"
#include "Node.h"
#include "Light.h"

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

	//평행광 등록
	void registerLight(DirectionalLight directionalLight);
	DirectionalLight getDirectionalLight();

protected:
	Childs				m_AddingChilds;
	DirectionalLight	m_DirectionalLight;
};

NS_SW_END