#include "FirstScene.h"
#include "DynamicBox.h"

USING_NS_SW;

struct Vertex
{
	XMFLOAT3 m_Pos;
	XMFLOAT4 m_Color;
};

struct MeshData
{
	std::vector<Vertex> m_Vertices;
	std::vector<UINT> m_Indices;
};


FirstScene::FirstScene()
{
}

FirstScene::~FirstScene()
{

}

bool FirstScene::init()
{
	if (!Scene::init())
	{
		return false;
	}	

	auto dynamicBox = DynamicBox::create();
	dynamicBox->setBoxWithRandomColor(2.0f, 2.0f, 2.0f);
	addChild(dynamicBox);

	for (int i = 0; i < 20; i++)
	{
		auto randomBox = Box::create();
		randomBox->setBoxWithRandomColor(1.0f, 1.0f, 1.0f);
		randomBox->setPosition(-10 + rand() % 21, -10 + rand() % 21, -10 + rand() % 21);
		addChild(randomBox);
	}
	

	return true;
}