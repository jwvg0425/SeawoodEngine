#pragma once
#include "Effect.h"
#include "InputLayout.h"
#include "Node.h"

NS_SW_BEGIN

template<typename E>
class D3DNode : public Node
{
public:
	using VertexType = typename E::VertexType;
	D3DNode();
	~D3DNode() override;

	bool init() override;

	void setEffect(E* effect);
	void setInputLayout(ID3D11InputLayout* inputLayout, D3D11_PRIMITIVE_TOPOLOGY topology);
	void setBuffer(const std::vector<VertexType>& vertices,
		const std::vector<UINT>& indices);

	void setPosition(float x, float y, float z, bool relative = false);
	void setScale(float x, float y, float z, bool relative = false);
	void setAngle(float x, float y, float z, bool relative = false);

	//포인터로 넘어온 변수에 해당하는 값 저장해서 돌려줌
	void getPosition(float* x, float* y, float* z);
	void getScale(float* scaleX, float* scaleY, float* scaleZ);
	void getAngle(float* angleX, float* angleY, float* angleZ);

	XMMATRIX getWorld();

	void draw() override;

	static D3DNode<E>* createWithEffect(E* effect);

protected:
	void setVertices(const std::vector<VertexType>& vertices);
	void setIndices(const std::vector<UINT>& indices);
	void buildBuffer();
	void updateWorld();

	std::vector<VertexType> m_Vertices;
	std::vector<UINT> m_Indices;

	//world를 구하기 위한 요소. 기본적으로 I.
	XMFLOAT4X4 m_Translation;
	XMFLOAT4X4 m_Scaling;
	XMFLOAT4X4 m_Rotation;
	XMFLOAT4X4 m_World;
	float m_X, m_Y, m_Z;
	float m_ScaleX, m_ScaleY, m_ScaleZ;
	float m_AngleX, m_AngleY, m_AngleZ;

	E* m_Effect = nullptr;
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;

	D3D11_PRIMITIVE_TOPOLOGY m_Topology;
	ID3D11InputLayout*	m_InputLayout = nullptr;
};

template<typename E>
D3DNode<E>::D3DNode()
{
	XMMATRIX I = XMMatrixIdentity();

	m_X = m_Y = m_Z = 0.0f;
	m_ScaleX = m_ScaleY = m_ScaleZ = 1.0f;
	m_AngleX = m_AngleY = m_AngleZ = 0.0f;
	XMStoreFloat4x4(&m_Scaling, I);
	XMStoreFloat4x4(&m_Rotation, I);
	XMStoreFloat4x4(&m_Translation, I);
	XMStoreFloat4x4(&m_World, I);

	m_Effect = nullptr;
}

template<typename E>
D3DNode<E>::~D3DNode()
{
	ReleaseCOM(m_VertexBuffer);
	ReleaseCOM(m_IndexBuffer);
}

template<typename E>
bool D3DNode<E>::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

template<typename E>
void D3DNode<E>::setEffect(E* effect)
{
	m_Effect = effect;
}

template<typename E>
void D3DNode<E>::setBuffer(const std::vector<VertexType>& vertices, const std::vector<UINT>& indices)
{
	setVertices(vertices);
	setIndices(indices);
	buildBuffer();
}

template<typename E>
void D3DNode<E>::setPosition(float x, float y, float z, bool relative /*= false*/)
{
	if (relative)
	{
		m_X += x;
		m_Y += y;
		m_Z += z;
	}
	else
	{
		m_X = x;
		m_Y = y;
		m_Z = z;
	}

	XMMATRIX T = XMMatrixTranslation(m_X, m_Y, m_Z);

	XMStoreFloat4x4(&m_Translation, T);

	updateWorld();
}

template<typename E>
void D3DNode<E>::setScale(float x, float y, float z, bool relative /*= false*/)
{
	if (relative)
	{
		m_ScaleX += x;
		m_ScaleY += y;
		m_ScaleZ += z;
	}
	else
	{
		m_ScaleX = x;
		m_ScaleY = y;
		m_ScaleZ = z;
	}

	XMMATRIX S = XMMatrixScaling(m_ScaleX, m_ScaleY, m_ScaleZ);

	XMStoreFloat4x4(&m_Scaling, S);

	updateWorld();
}

template<typename E>
void D3DNode<E>::setAngle(float x, float y, float z, bool relative /*= false*/)
{
	if (relative)
	{
		m_AngleX += x;
		m_AngleY += y;
		m_AngleZ += z;
	}
	else
	{
		m_AngleX = x;
		m_AngleY = y;
		m_AngleZ = z;
	}

	XMMATRIX X = XMMatrixRotationX(m_AngleX);
	XMMATRIX Y = XMMatrixRotationY(m_AngleY);
	XMMATRIX Z = XMMatrixRotationZ(m_AngleZ);
	XMMATRIX R = X*Y*Z;

	XMStoreFloat4x4(&m_Rotation, R);

	updateWorld();
}

template<typename E>
void D3DNode<E>::getPosition(float* x, float* y, float* z)
{
	*x = m_X;
	*y = m_Y;
	*z = m_Z;
}

template<typename E>
void D3DNode<E>::getScale(float* scaleX, float* scaleY, float* scaleZ)
{
	*scaleX = m_ScaleX;
	*scaleY = m_ScaleY;
	*scaleZ = m_ScaleZ;
}

template<typename E>
void D3DNode<E>::getAngle(float* angleX, float* angleY, float* angleZ)
{
	*angleX = m_AngleX;
	*angleY = m_AngleY;
	*angleZ = m_AngleZ;
}

template<typename E>
XMMATRIX D3DNode<E>::getWorld()
{
	return XMLoadFloat4x4(&m_World);
}

template<typename E>
void D3DNode<E>::draw()
{
	GET_D3D_RENDERER()->setInputLayout(m_InputLayout);
	GET_D3D_RENDERER()->setPrimitiveTopology(m_Topology);

	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	GET_D3D_RENDERER()->getDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	GET_D3D_RENDERER()->getDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	m_Effect->updateByObject(this);

	D3DX11_TECHNIQUE_DESC techDesc;
	m_Effect->getTech()->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_Effect->getTech()->GetPassByIndex(p)->Apply(0, GET_D3D_RENDERER()->getDeviceContext());
		GET_D3D_RENDERER()->getDeviceContext()->DrawIndexed(m_Indices.size(), 0, 0);
	}
}

template<typename E>
D3DNode<E>* D3DNode<E>::createWithEffect(E* effect)
{
	D3DNode<E>* node = new D3DNode<E>();

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
void D3DNode<E>::setVertices(const std::vector<VertexType>& vertices)
{
	m_Vertices = vertices;
}

template<typename E>
void D3DNode<E>::setIndices(const std::vector<UINT>& indices)
{
	m_Indices = indices;
}

template<typename E>
void D3DNode<E>::buildBuffer()
{
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(VertexType)* m_Vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
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
void D3DNode<E>::updateWorld()
{
	XMMATRIX S = XMLoadFloat4x4(&m_Scaling);
	XMMATRIX R = XMLoadFloat4x4(&m_Rotation);
	XMMATRIX T = XMLoadFloat4x4(&m_Translation);
	XMMATRIX W = S*R*T;

	XMStoreFloat4x4(&m_World, W);
}

template<typename E>
void D3DNode<E>::setInputLayout(ID3D11InputLayout* inputLayout, D3D11_PRIMITIVE_TOPOLOGY topology)
{
	m_InputLayout = inputLayout;
	m_Topology = topology;
}

NS_SW_END