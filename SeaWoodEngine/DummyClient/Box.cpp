#include "Box.h"
#include "GeometryGenerator.h"

USING_NS_SW;

Box::Box()
{
}

Box::~Box()
{

}

bool Box::init()
{
	if (!Figure<Vertex::PosBasic>::init())
	{
		return false;
	}

	Director::getInstance()->registerEvent(EventType::PICK_TRIANGLE, this);

	return true;
}

void Box::setBoxWithRandomColor(float width, float height, float depth)
{
	float w2 = width / 2;
	float h2 = height / 2;
	float d2 = depth / 2;

	std::vector<FigureVertex> vertices;
	std::vector<UINT> indices;

	GeometryGenerator::createBox(width, height, depth, vertices, indices);

	setBuffer(vertices, indices);

	auto material = Material();
	material.m_Ambient = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 1.0f);
	material.m_Diffuse = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.5f);
	material.m_Specular = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 16.0f);

	setMaterial(material);

	
}

void Box::setBoxWithMaterial(float width, float height, float depth, SeaWood::Material material)
{
	float w2 = width / 2;
	float h2 = height / 2;
	float d2 = depth / 2;

	std::vector<FigureVertex> vertices;
	std::vector<UINT> indices;

	GeometryGenerator::createBox(width, height, depth, vertices, indices);

	setBuffer(vertices, indices, true);

	setMaterial(material);
}