#pragma once
#include "Node.h"
#include "Director.h"
#include "D3DRenderer.h"

NS_SW_BEGIN

class Shader;

//vertex 구조체에 따라 다른 figure를 만들어 냄.
template <typename Vertex>
class Figure : public Node
{
public:
	Figure();
	Figure(Shader* shader);
	~Figure() override;

	bool init() override;

	void setShader(Shader* shader);
	void setBuffer(const std::vector<Vertex>& vertices,
		const std::vector<UINT>& indices);

	void setPosition(float x, float y, float z, bool relative = false);
	void setScale(float x, float y, float z, bool relative = false);
	void setAngle(float x, float y, float z, bool relative = false);

	//포인터로 넘어온 변수에 해당하는 값 저장해서 돌려줌
	void getPosition(float* x, float* y, float* z);
	void getScale(float* scaleX, float* scaleY, float* scaleZ);
	void getAngle(float* angleX, float* angleY, float* angleZ);

	XMFLOAT4X4 getWorld();

	void draw() override;
	
	static Figure<Vertex>* createWithShader(Shader* shader);

protected:
	void setVertices(const std::vector<Vertex>& vertices);
	void setIndices(const std::vector<UINT>& indices);
	void buildBuffer();
	void updateWorld();

	std::vector<Vertex> m_Vertices;
	std::vector<UINT> m_Indices;

	//world를 구하기 위한 요소. 기본적으로 I.
	XMFLOAT4X4 m_Translation;
	XMFLOAT4X4 m_Scaling;
	XMFLOAT4X4 m_Rotation;
	XMFLOAT4X4 m_World;
	float m_X, m_Y, m_Z;
	float m_ScaleX, m_ScaleY, m_ScaleZ;
	float m_AngleX, m_AngleY, m_AngleZ;

	Shader* m_Shader = nullptr;
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;
};

template <typename Vertex>
void SeaWood::Figure<Vertex>::getAngle(float* angleX, float* angleY, float* angleZ)
{
	*angleX = m_AngleX;
	*angleY = m_AngleY;
	*angleZ = m_AngleZ;
}

template <typename Vertex>
void SeaWood::Figure<Vertex>::getScale(float* scaleX, float* scaleY, float* scaleZ)
{
	*scaleX = m_ScaleX;
	*scaleY = m_ScaleY;
	*scaleZ = m_ScaleZ;
}

template <typename Vertex>
void SeaWood::Figure<Vertex>::getPosition(float* x, float* y, float* z)
{
	*x = m_X;
	*y = m_Y;
	*z = m_Z;
}

template <typename Vertex>
void SeaWood::Figure<Vertex>::setShader(Shader* shader)
{
	_ASSERT(m_Shader == nullptr);

	m_Shader = shader;
}

template <typename Vertex>
SeaWood::Figure<Vertex>::Figure()
{
	XMMATRIX I = XMMatrixIdentity();

	m_X = m_Y = m_Z = 0.0f;
	m_ScaleX = m_ScaleY = m_ScaleZ = 1.0f;
	m_AngleX = m_AngleY = m_AngleZ = 0.0f;
	XMStoreFloat4x4(&m_Scaling, I);
	XMStoreFloat4x4(&m_Rotation, I);
	XMStoreFloat4x4(&m_Translation, I);
	XMStoreFloat4x4(&m_World, I);

	m_Shader = nullptr;
}

template <typename Vertex>
bool SeaWood::Figure<Vertex>::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

template <typename Vertex>
Figure<Vertex>* SeaWood::Figure<Vertex>::createWithShader(Shader* shader)
{
	Figure<Vertex>* figure = new Figure<Vertex>(shader);

	if (figure->init())
	{
		figure->autorelease();
		return figure;
	}
	else
	{
		delete figure;
		return nullptr;
	}
}

template <typename Vertex>
void SeaWood::Figure<Vertex>::setBuffer(const std::vector<Vertex>& vertices, const std::vector<UINT>& indices)
{
	setVertices(vertices);
	setIndices(indices);
	buildBuffer();
}

template <typename Vertex>
void SeaWood::Figure<Vertex>::updateWorld()
{
	XMMATRIX S = XMLoadFloat4x4(&m_Scaling);
	XMMATRIX R = XMLoadFloat4x4(&m_Rotation);
	XMMATRIX T = XMLoadFloat4x4(&m_Translation);
	XMMATRIX W = S*R*T;

	XMStoreFloat4x4(&m_World, W);
}

template <typename Vertex>
void SeaWood::Figure<Vertex>::draw()
{
	GET_D3D_RENDERER()->setInputLayout(m_Shader->getInputLayout());
	GET_D3D_RENDERER()->setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	GET_D3D_RENDERER()->getDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	GET_D3D_RENDERER()->getDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	XMMATRIX world = XMLoadFloat4x4(&m_World);
	XMMATRIX viewProj = GET_D3D_RENDERER()->getCamera()->getViewProj();
	XMMATRIX worldViewProj = world*viewProj;

	m_Shader->getWorldViewProj()->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	D3DX11_TECHNIQUE_DESC techDesc;
	m_Shader->getTech()->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_Shader->getTech()->GetPassByIndex(p)->Apply(0, GET_D3D_RENDERER()->getDeviceContext());
		GET_D3D_RENDERER()->getDeviceContext()->DrawIndexed(m_Indices.size(), 0, 0);
	}
}

template <typename Vertex>
XMFLOAT4X4 SeaWood::Figure<Vertex>::getWorld()
{
	return m_World;
}

template <typename Vertex>
void SeaWood::Figure<Vertex>::setAngle(float x, float y, float z, bool relative)
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

template <typename Vertex>
void SeaWood::Figure<Vertex>::setScale(float x, float y, float z, bool relative)
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

template <typename Vertex>
void SeaWood::Figure<Vertex>::setPosition(float x, float y, float z, bool relative)
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

template <typename Vertex>
void SeaWood::Figure<Vertex>::buildBuffer()
{
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex)* m_Vertices.size();
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

template <typename Vertex>
void SeaWood::Figure<Vertex>::setIndices(const std::vector<UINT>& indices)
{
	m_Indices = indices;
}

template <typename Vertex>
void SeaWood::Figure<Vertex>::setVertices(const std::vector<Vertex>& vertices)
{
	m_Vertices = vertices;
}

template <typename Vertex>
SeaWood::Figure<Vertex>::~Figure()
{
	delete m_Shader;
	ReleaseCOM(m_VertexBuffer);
	ReleaseCOM(m_IndexBuffer);
}

template <typename Vertex>
SeaWood::Figure<Vertex>::Figure(Shader* shader)
{
	XMMATRIX I = XMMatrixIdentity();

	XMStoreFloat4x4(&m_Scaling, I);
	XMStoreFloat4x4(&m_Rotation, I);
	XMStoreFloat4x4(&m_Translation, I);
	XMStoreFloat4x4(&m_World, I);

	m_Shader = shader;
}

NS_SW_END