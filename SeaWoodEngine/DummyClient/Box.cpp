#include "Box.h"

USING_NS_SW;

std::vector<UINT> Box::m_Indices =
{
	// front face
	0, 1, 2,
	0, 2, 3,

	// back face
	4, 6, 5,
	4, 7, 6,

	// left face
	4, 5, 1,
	4, 1, 0,

	// right face
	3, 2, 6,
	3, 6, 7,

	// top face
	1, 5, 6,
	1, 6, 2,

	// bottom face
	4, 0, 3,
	4, 3, 7
};

Box::Box()
{
}

Box::~Box()
{

}

bool Box::init()
{
	if (!D3DNode<SimpleColorEffect>::init())
	{
		return false;
	}

	setEffect(Effects::getSimpleColorEffect());
	setInputLayout(InputLayouts::getPosColor(), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}

void Box::setBox(float width, float height, float depth, const std::vector<XMFLOAT4>& colors)
{
	float w2 = width / 2;
	float h2 = height / 2;
	float d2 = depth / 2;

	std::vector<VertexType> vertices =
	{
		{ XMFLOAT3(-w2, -h2, -h2), colors[0] },
		{ XMFLOAT3(-w2, +h2, -h2), colors[1] },
		{ XMFLOAT3(+w2, +h2, -h2), colors[2] },
		{ XMFLOAT3(+w2, -h2, -h2), colors[3] },
		{ XMFLOAT3(-w2, -h2, +h2), colors[4] },
		{ XMFLOAT3(-w2, +h2, +h2), colors[5] },
		{ XMFLOAT3(+w2, +h2, +h2), colors[6] },
		{ XMFLOAT3(+w2, -h2, +h2), colors[7] }
	};

	auto indices = m_Indices;

	setBuffer(vertices, indices);
}

void Box::setBoxWithRandomColor(float width, float height, float depth)
{
	float w2 = width / 2;
	float h2 = height / 2;
	float d2 = depth / 2;

	std::vector<VertexType> vertices =
	{
		{ XMFLOAT3(-w2, -h2, -h2), { 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000) } },
		{ XMFLOAT3(-w2, +h2, -h2), { 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000) } },
		{ XMFLOAT3(+w2, +h2, -h2), { 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000) } },
		{ XMFLOAT3(+w2, -h2, -h2), { 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000) } },
		{ XMFLOAT3(-w2, -h2, +h2), { 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000) } },
		{ XMFLOAT3(-w2, +h2, +h2), { 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000) } },
		{ XMFLOAT3(+w2, +h2, +h2), { 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000) } },
		{ XMFLOAT3(+w2, -h2, +h2), { 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000), 0.001f * (rand() % 1000) } }
	};

	auto indices = m_Indices;

	setBuffer(vertices, indices);
}
