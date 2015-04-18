#include "stdafx.h"
#include "DebugNodes.h"
#include "Vertex.h"
#include "InputLayout.h"
#include "SimpleColorEffect.h"
#include "Renderer.h"
#include "Director.h"
#include "Blend.h"
#include "Rasterizer.h"
#include "Camera.h"
#include "Figure.h"

USING_NS_SW;

Figure<Vertex::PosColor>* axisNode = nullptr;

void DebugNodes::destroyAll()
{
	SAFE_RELEASE(axisNode);
}

Node* DebugNodes::getDebugNode(DebugMode mode)
{
	switch (mode)
	{
	case DebugMode::PRINT_AXIS:
		if (axisNode == nullptr)
		{
			createAxis();
		}
		return axisNode;
	}

	return nullptr;
}

void SeaWood::DebugNodes::createAxis()
{
	axisNode = Figure<Vertex::PosColor>::createWithEffect(Effects::getSimpleColorEffect());

	std::vector<Vertex::PosColor> vertices;
	Vertex::PosColor vertex;

	//x축
	vertex.m_Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	vertex.m_Pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertices.push_back(vertex);
	vertex.m_Pos = XMFLOAT3(10000.0f, 0.0f, 0.0f);
	vertices.push_back(vertex);

	//y축
	vertex.m_Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	vertex.m_Pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertices.push_back(vertex);
	vertex.m_Pos = XMFLOAT3(0.0f, 10000.0f, 0.0f);
	vertices.push_back(vertex);

	//z축
	vertex.m_Color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	vertex.m_Pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertices.push_back(vertex);
	vertex.m_Pos = XMFLOAT3(0.0f, 0.0f, 10000.0f);
	vertices.push_back(vertex);

	std::vector<UINT> indices = { 0, 1, 2, 3, 4, 5 };

	axisNode->setBuffer(vertices, indices);
	axisNode->setTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	axisNode->retain();
}
