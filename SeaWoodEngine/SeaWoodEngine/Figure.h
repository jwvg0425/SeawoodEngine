#pragma once
#include "Effect.h"
#include "InputLayout.h"
#include "Node.h"

NS_SW_BEGIN

template<typename VertexType>
class Figure : public Node
{
public:
	using FigureVertex = VertexType;
	using EffectType = typename VertexType::EffectType;

	Figure();
	~Figure() override;

	bool init() override;

	void setEffect(EffectType effect);
	void setBuffer(const std::vector<VertexType>& vertices,
		const std::vector<UINT>& indices, bool isDynamic = false);

	void render() override;

	static Figure<VertexType>* createWithEffect(EffectType effect);

protected:
	void setVertices(const std::vector<VertexType>& vertices);
	void setIndices(const std::vector<UINT>& indices);
	void buildBuffer(bool isDynamic);
	
	std::vector<VertexType> m_Vertices;
	std::vector<UINT> m_Indices;

	EffectType m_Effect = nullptr;
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;

	bool m_IsReflect = false;
};

template<typename VertexType>
Figure<VertexType>::Figure()
{
	m_Effect = nullptr;
}

template<typename VertexType>
Figure<VertexType>::~Figure()
{
	ReleaseCOM(m_VertexBuffer);
	ReleaseCOM(m_IndexBuffer);
}

template<typename VertexType>
bool Figure<VertexType>::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

template<typename VertexType>
void Figure<VertexType>::setEffect(EffectType effect)
{
	m_Effect = effect;
}

template<typename VertexType>
void Figure<VertexType>::setBuffer(const std::vector<VertexType>& vertices, const std::vector<UINT>& indices, bool isDynamic)
{
	setVertices(vertices);
	setIndices(indices);
	buildBuffer(isDynamic);
}

template<typename VertexType>
void Figure<VertexType>::render()
{
	m_Effect->updateByObject(this);

	GET_RENDERER()->setInputLayout(m_InputLayout);
	GET_RENDERER()->setPrimitiveTopology(m_Topology);

	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	GET_RENDERER()->getDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	GET_RENDERER()->getDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
	if (m_RasterizerState != nullptr)
	{
		GET_RENDERER()->getDeviceContext()->RSSetState(m_RasterizerState);
	}

	if (m_BlendState != nullptr)
	{
		GET_RENDERER()->getDeviceContext()->OMSetBlendState(m_BlendState, m_BlendFactor, 0xffffffff);
	}

	D3DX11_TECHNIQUE_DESC techDesc;
	m_Effect->getTech()->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_Effect->getTech()->GetPassByIndex(p)->Apply(0, GET_RENDERER()->getDeviceContext());
		GET_RENDERER()->getDeviceContext()->DrawIndexed(m_Indices.size(), 0, 0);
	}

	if (m_RasterizerState != nullptr)
	{
		GET_RENDERER()->getDeviceContext()->RSSetState(nullptr);
	}

	if (m_BlendState != nullptr)
	{
		GET_RENDERER()->getDeviceContext()->OMSetBlendState(nullptr, m_BlendFactor, 0xffffffff);
	}
}

template<typename VertexType>
Figure<VertexType>* Figure<VertexType>::createWithEffect(EffectType effect)
{
	Figure<VertexType>* node = new Figure<VertexType>();

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

template<typename VertexType>
void Figure<VertexType>::setVertices(const std::vector<VertexType>& vertices)
{
	m_Vertices = vertices;

	m_CenterPos.x = 0;
	m_CenterPos.y = 0;
	m_CenterPos.z = 0;

	for (auto& vertex : m_Vertices)
	{
		m_CenterPos.x += vertex.m_Pos.x;
		m_CenterPos.y += vertex.m_Pos.y;
		m_CenterPos.z += vertex.m_Pos.z;
	}

	m_CenterPos.x /= m_Vertices.size();
	m_CenterPos.y /= m_Vertices.size();
	m_CenterPos.z /= m_Vertices.size();
}

template<typename VertexType>
void Figure<VertexType>::setIndices(const std::vector<UINT>& indices)
{
	m_Indices = indices;
}

template<typename VertexType>
void Figure<VertexType>::buildBuffer(bool isDynamic)
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
	HR(GET_RENDERER()->getDevice()->CreateBuffer(&vbd, &vinitData, &m_VertexBuffer));

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT)* m_Indices.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &m_Indices[0];
	HR(GET_RENDERER()->getDevice()->CreateBuffer(&ibd, &iinitData, &m_IndexBuffer));
}

NS_SW_END