#include "Box.h"

USING_NS_SW;

std::vector<UINT> Box::m_Indices =
{
	// front face
	0, 1, 2,
	0, 2, 3,

	// back face
	4, 5, 6,
	4, 6, 7,

	// left face
	8, 9, 10,
	8, 10, 11,

	// right face
	12, 13, 14,
	12, 14, 15,

	// top face
	16, 17, 18,
	16, 18, 19,

	// bottom face
	20, 21, 22,
	20, 22, 23
};

Box::Box()
{
}

Box::~Box()
{

}

bool Box::init()
{
	if (!Figure<SimpleLightEffect>::init())
	{
		return false;
	}

	setEffect(Effects::getSimpleLightEffect());
	setInputLayout(InputLayouts::getPosNormal(), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}

void Box::setBox(float width, float height, float depth, const std::vector<XMFLOAT4>& colors)
{
	float w2 = width / 2;
	float h2 = height / 2;
	float d2 = depth / 2;

	std::vector<VertexType> vertices =
	{
		{ -w2, -h2, -d2, 0.0f, 0.0f, -1.0f },
		{ -w2, +h2, -d2, 0.0f, 0.0f, -1.0f },
		{ +w2, +h2, -d2, 0.0f, 0.0f, -1.0f },
		{ +w2, -h2, -d2, 0.0f, 0.0f, -1.0f },

		{ -w2, -h2, +d2, 0.0f, 0.0f, 1.0f },
		{ +w2, -h2, +d2, 0.0f, 0.0f, 1.0f },
		{ +w2, +h2, +d2, 0.0f, 0.0f, 1.0f },
		{ -w2, +h2, +d2, 0.0f, 0.0f, 1.0f },

		{ -w2, +h2, -d2, 0.0f, 1.0f, 0.0f },
		{ -w2, +h2, +d2, 0.0f, 1.0f, 0.0f },
		{ +w2, +h2, +d2, 0.0f, 1.0f, 0.0f },
		{ +w2, +h2, -d2, 0.0f, 1.0f, 0.0f },

		{ -w2, -h2, -d2, 0.0f, -1.0f, 0.0f },
		{ +w2, -h2, -d2, 0.0f, -1.0f, 0.0f },
		{ +w2, -h2, +d2, 0.0f, -1.0f, 0.0f },
		{ -w2, -h2, +d2, 0.0f, -1.0f, 0.0f },

		{ -w2, -h2, +d2, -1.0f, 0.0f, 0.0f },
		{ -w2, +h2, +d2, -1.0f, 0.0f, 0.0f },
		{ -w2, +h2, -d2, -1.0f, 0.0f, 0.0f },
		{ -w2, -h2, -d2, -1.0f, 0.0f, 0.0f },

		{ +w2, -h2, -d2, 1.0f, 0.0f, 0.0f },
		{ +w2, +h2, -d2, 1.0f, 0.0f, 0.0f },
		{ +w2, +h2, +d2, 1.0f, 0.0f, 0.0f },
		{ +w2, -h2, +d2, 1.0f, 0.0f, 0.0f },
	};

	auto indices = m_Indices;

	setBuffer(vertices, indices);

	auto material = Material(); 
	material.m_Ambient = XMFLOAT4(0.1f, 0.2f, 0.3f, 1.0f);
	material.m_Diffuse = XMFLOAT4(0.2f, 0.4f, 0.6f, 1.0f);
	material.m_Specular = XMFLOAT4(0.9f, 0.9f, 0.9f, 16.0f);

	setMaterial(material);	
}

void Box::setBoxWithRandomColor(float width, float height, float depth)
{
	float w2 = width / 2;
	float h2 = height / 2;
	float d2 = depth / 2;

	std::vector<VertexType> vertices =
	{
		{ -w2, -h2, -d2, 0.0f, 0.0f, -1.0f },
		{ -w2, +h2, -d2, 0.0f, 0.0f, -1.0f },
		{ +w2, +h2, -d2, 0.0f, 0.0f, -1.0f },
		{ +w2, -h2, -d2, 0.0f, 0.0f, -1.0f },

		{ -w2, -h2, +d2, 0.0f, 0.0f, 1.0f },
		{ +w2, -h2, +d2, 0.0f, 0.0f, 1.0f },
		{ +w2, +h2, +d2, 0.0f, 0.0f, 1.0f },
		{ -w2, +h2, +d2, 0.0f, 0.0f, 1.0f },

		{ -w2, +h2, -d2, 0.0f, 1.0f, 0.0f },
		{ -w2, +h2, +d2, 0.0f, 1.0f, 0.0f },
		{ +w2, +h2, +d2, 0.0f, 1.0f, 0.0f },
		{ +w2, +h2, -d2, 0.0f, 1.0f, 0.0f },

		{ -w2, -h2, -d2, 0.0f, -1.0f, 0.0f },
		{ +w2, -h2, -d2, 0.0f, -1.0f, 0.0f },
		{ +w2, -h2, +d2, 0.0f, -1.0f, 0.0f },
		{ -w2, -h2, +d2, 0.0f, -1.0f, 0.0f },

		{ -w2, -h2, +d2, -1.0f, 0.0f, 0.0f },
		{ -w2, +h2, +d2, -1.0f, 0.0f, 0.0f },
		{ -w2, +h2, -d2, -1.0f, 0.0f, 0.0f },
		{ -w2, -h2, -d2, -1.0f, 0.0f, 0.0f },

		{ +w2, -h2, -d2, 1.0f, 0.0f, 0.0f },
		{ +w2, +h2, -d2, 1.0f, 0.0f, 0.0f },
		{ +w2, +h2, +d2, 1.0f, 0.0f, 0.0f },
		{ +w2, -h2, +d2, 1.0f, 0.0f, 0.0f },
	};

	auto indices = m_Indices;

	setBuffer(vertices, indices);

	auto material = Material();
	material.m_Ambient = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 1.0f);
	material.m_Diffuse = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 1.0f);
	material.m_Specular = XMFLOAT4(0.01f * (rand() % 100), 0.01f * (rand() % 100), 0.01f * (rand() % 100), 16.0f);

	setMaterial(material);

	
}
