#include "FirstScene.h"
#include "Box.h"

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

	std::vector<XMFLOAT4> colors =
	{
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 0.5f, 1.0f },
		{ 0.0f, 0.5f, 0.0f, 1.0f },
		{ 0.5f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.7f, 1.0f, 1.0f },
	};

	auto box = Box::create();
	box->setBox(1.0f, 1.0f, 1.0f, colors);
	addChild(box);

	auto box2 = Box::create();
	box2->setBoxWithRandomColor(2.0f, 2.0f, 2.0f);
	box2->setPosition(-3.0f, 6.0f, 0.0f);
	addChild(box2);
	

	return true;
}