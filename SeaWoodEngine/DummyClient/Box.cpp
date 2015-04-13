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

void Box::onPickTriangle(int pick)
{
	static UINT prev0 = -1, prev1 = -1, prev2 = -1;

	if (pick == -1)
	{
		if (prev0 != -1)
		{
			D3D11_MAPPED_SUBRESOURCE mappedData;
			HR(GET_RENDERER()->getDeviceContext()->Map(m_VertexBuffer, 0,
				D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedData));
			FigureVertex* v = reinterpret_cast<FigureVertex*>(mappedData.pData);

			m_Vertices[prev0].m_Color = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
			m_Vertices[prev1].m_Color = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
			m_Vertices[prev2].m_Color = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

			v[prev0] = m_Vertices[prev0];
			v[prev1] = m_Vertices[prev1];
			v[prev2] = m_Vertices[prev2];

			GET_RENDERER()->getDeviceContext()->Unmap(m_VertexBuffer, 0);
		}
		return;
	}

	UINT i0 = m_Indices[pick * 3 + 0];
	UINT i1 = m_Indices[pick * 3 + 1];
	UINT i2 = m_Indices[pick * 3 + 2];

	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(GET_RENDERER()->getDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedData));
	FigureVertex* v = reinterpret_cast<FigureVertex*>(mappedData.pData);

	m_Vertices[i0].m_Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	m_Vertices[i1].m_Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	m_Vertices[i2].m_Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	v[i0] = m_Vertices[i0];
	v[i1] = m_Vertices[i1];
	v[i2] = m_Vertices[i2];

	if (prev0 != -1 && !(prev0 == i0 && prev1 == i1 && prev2 == i2))
	{
		m_Vertices[prev0].m_Color = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		m_Vertices[prev1].m_Color = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		m_Vertices[prev2].m_Color = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

		v[prev0] = m_Vertices[prev0];
		v[prev1] = m_Vertices[prev1];
		v[prev2] = m_Vertices[prev2];
	}

	GET_RENDERER()->getDeviceContext()->Unmap(m_VertexBuffer, 0);

	prev0 = i0;
	prev1 = i1;
	prev2 = i2;
}
