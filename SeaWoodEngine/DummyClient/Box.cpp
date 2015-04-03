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

	setEffect(Effects::getBasicEffect());
	setInputLayout(InputLayouts::getPosBasic(), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}

void Box::setBox(float width, float height, float depth, const std::vector<XMFLOAT4>& colors)
{
	float w2 = width / 2;
	float h2 = height / 2;
	float d2 = depth / 2;

	std::vector<FigureVertex> vertices;
	std::vector<UINT> indices;

	GeometryGenerator::createBox(width, height, depth, vertices, indices);

	setBuffer(vertices, indices);

	auto material = Material(); 
	material.m_Ambient = XMFLOAT4(0.1f, 0.2f, 0.3f, 1.0f);
	material.m_Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	material.m_Specular = XMFLOAT4(0.9f, 0.9f, 0.9f, 16.0f);

	setMaterial(material);	
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
