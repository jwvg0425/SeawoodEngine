﻿#pragma once
#include "Effect.h"
#include "InputLayout.h"
#include "D3DNode.h"

NS_SW_BEGIN

template<typename E>
class Figure : public D3DNode
{
public:

	using VertexType = typename E::VertexType;
	Figure();
	~Figure() override;

	bool init() override;

	void setEffect(E* effect);
	void setInputLayout(ID3D11InputLayout* inputLayout, D3D11_PRIMITIVE_TOPOLOGY topology);
	void setBuffer(const std::vector<VertexType>& vertices,
		const std::vector<UINT>& indices, bool isDynamic = false);

	void render() override;

	void setRasterizer(ID3D11RasterizerState* rasterizer);
	void setBlend(ID3D11BlendState* blend, const FLOAT blendFactor[4]);

	static Figure<E>* createWithEffect(E* effect);

protected:
	void setVertices(const std::vector<VertexType>& vertices);
	void setIndices(const std::vector<UINT>& indices);
	void buildBuffer(bool isDynamic);
	
	std::vector<VertexType> m_Vertices;
	std::vector<UINT> m_Indices;

	E* m_Effect = nullptr;
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;

	D3D11_PRIMITIVE_TOPOLOGY m_Topology;
	ID3D11InputLayout*	m_InputLayout = nullptr;
	ID3D11RasterizerState* m_RasterizerState = nullptr;
	ID3D11BlendState* m_BlendState = nullptr;
	FLOAT m_BlendFactor[4];
};

template<typename E>
void Figure<E>::setBlend(ID3D11BlendState* blend, const FLOAT blendFactor[4])
{
	m_BlendState = blend;
	m_BlendFactor[0] = blendFactor[0];
	m_BlendFactor[1] = blendFactor[1];
	m_BlendFactor[2] = blendFactor[2];
	m_BlendFactor[3] = blendFactor[3];
}

template<typename E>
void Figure<E>::setRasterizer(ID3D11RasterizerState* rasterizer)
{
	m_RasterizerState = rasterizer;
}

template<typename E>
Figure<E>::Figure()
{
	m_Effect = nullptr;
}

template<typename E>
Figure<E>::~Figure()
{
	ReleaseCOM(m_VertexBuffer);
	ReleaseCOM(m_IndexBuffer);
}

template<typename E>
bool Figure<E>::init()
{
	if (!D3DNode::init())
	{
		return false;
	}

	return true;
}

template<typename E>
void Figure<E>::setEffect(E* effect)
{
	m_Effect = effect;
}

template<typename E>
void Figure<E>::setBuffer(const std::vector<VertexType>& vertices, const std::vector<UINT>& indices, bool isDynamic)
{
	setVertices(vertices);
	setIndices(indices);
	buildBuffer(isDynamic);
}

template<typename E>
void Figure<E>::render()
{
	m_Effect->updateByObject(this);

	GET_D3D_RENDERER()->setInputLayout(m_InputLayout);
	GET_D3D_RENDERER()->setPrimitiveTopology(m_Topology);

	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	GET_D3D_RENDERER()->getDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	GET_D3D_RENDERER()->getDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
	if (m_RasterizerState != nullptr)
	{
		GET_D3D_RENDERER()->getDeviceContext()->RSSetState(m_RasterizerState);
	}

	if (m_BlendState != nullptr)
	{
		GET_D3D_RENDERER()->getDeviceContext()->OMSetBlendState(m_BlendState, m_BlendFactor, 0xffffffff);
	}

	D3DX11_TECHNIQUE_DESC techDesc;
	m_Effect->getTech()->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_Effect->getTech()->GetPassByIndex(p)->Apply(0, GET_D3D_RENDERER()->getDeviceContext());
		GET_D3D_RENDERER()->getDeviceContext()->DrawIndexed(m_Indices.size(), 0, 0);
	}

	if (m_RasterizerState != nullptr)
	{
		GET_D3D_RENDERER()->getDeviceContext()->RSSetState(nullptr);
	}

	if (m_BlendState != nullptr)
	{
		GET_D3D_RENDERER()->getDeviceContext()->OMSetBlendState(nullptr, m_BlendFactor, 0xffffffff);
	}
}

template<typename E>
Figure<E>* Figure<E>::createWithEffect(E* effect)
{
	Figure<E>* node = new Figure<E>();

	node->setEffect(effect);

	if (node->init())
	{
		node->autorelease();
		return node;
	}
	else
	{
		delete node;
		return nullptr;
	}
}

template<typename E>
void Figure<E>::setVertices(const std::vector<VertexType>& vertices)
{
	m_Vertices = vertices;
}

template<typename E>
void Figure<E>::setIndices(const std::vector<UINT>& indices)
{
	m_Indices = indices;
}

template<typename E>
void Figure<E>::buildBuffer(bool isDynamic)
{
	D3D11_BUFFER_DESC vbd;
	if (isDynamic)
	{
		vbd.Usage = D3D11_USAGE_DYNAMIC;
	}
	else
	{
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
	}
	vbd.ByteWidth = sizeof(VertexType)* m_Vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	if (isDynamic)
	{
		vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		vbd.CPUAccessFlags = 0;
	}

	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &m_Vertices[0];
	HR(GET_D3D_RENDERER()->getDevice()->CreateBuffer(&vbd, &vinitData, &m_VertexBuffer));

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT)* m_Indices.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &m_Indices[0];
	HR(GET_D3D_RENDERER()->getDevice()->CreateBuffer(&ibd, &iinitData, &m_IndexBuffer));
}

template<typename E>
void Figure<E>::setInputLayout(ID3D11InputLayout* inputLayout, D3D11_PRIMITIVE_TOPOLOGY topology)
{
	m_InputLayout = inputLayout;
	m_Topology = topology;
}

NS_SW_END