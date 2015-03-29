#include "stdafx.h"
#include "D3DNode.h"
#include "Director.h"
#include "D3DRenderer.h"

USING_NS_SW;

SeaWood::D3DNode::D3DNode()
{
	XMMATRIX I = XMMatrixIdentity();

	m_X = m_Y = m_Z = 0.0f;
	m_ScaleX = m_ScaleY = m_ScaleZ = 1.0f;
	m_AngleX = m_AngleY = m_AngleZ = 0.0f;
	XMStoreFloat4x4(&m_Scaling, I);
	XMStoreFloat4x4(&m_Rotation, I);
	XMStoreFloat4x4(&m_Translation, I);
	XMStoreFloat4x4(&m_World, I);
	XMStoreFloat4x4(&m_TextureTransform, I);
}

SeaWood::D3DNode::~D3DNode()
{
	SAFE_DELETE(m_Material);
	ReleaseCOM(m_DiffuseMapSRV);
}

bool SeaWood::D3DNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void SeaWood::D3DNode::setPosition(float x, float y, float z, bool relative /*= false*/)
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

void SeaWood::D3DNode::setScale(float x, float y, float z, bool relative /*= false*/)
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

void SeaWood::D3DNode::setRotate(float x, float y, float z, bool relative /*= false*/)
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

void SeaWood::D3DNode::getPosition(float* x, float* y, float* z)
{
	*x = m_X;
	*y = m_Y;
	*z = m_Z;
}

void SeaWood::D3DNode::getScale(float* scaleX, float* scaleY, float* scaleZ)
{
	*scaleX = m_ScaleX;
	*scaleY = m_ScaleY;
	*scaleZ = m_ScaleZ;
}

void SeaWood::D3DNode::getRotate(float* angleX, float* angleY, float* angleZ)
{
	*angleX = m_AngleX;
	*angleY = m_AngleY;
	*angleZ = m_AngleZ;
}

XMMATRIX SeaWood::D3DNode::getWorld()
{
	return XMLoadFloat4x4(&m_World);
}

void SeaWood::D3DNode::updateWorld()
{
	XMMATRIX S = XMLoadFloat4x4(&m_Scaling);
	XMMATRIX R = XMLoadFloat4x4(&m_Rotation);
	XMMATRIX T = XMLoadFloat4x4(&m_Translation);
	XMMATRIX W = S*R*T;

	XMStoreFloat4x4(&m_World, W);
}

const Material* SeaWood::D3DNode::getMaterial()
{
	return m_Material;
}

void SeaWood::D3DNode::setMaterial(Material material)
{
	if (m_Material == nullptr)
	{
		m_Material = new Material();
	}

	*m_Material = material;
}

void SeaWood::D3DNode::setTexture(const std::wstring& fileName)
{
	HR(D3DX11CreateShaderResourceViewFromFile(GET_D3D_RENDERER()->getDevice(),
		fileName.c_str(), nullptr, nullptr, &m_DiffuseMapSRV, nullptr));
}

ID3D11ShaderResourceView* SeaWood::D3DNode::getTexture()
{
	return m_DiffuseMapSRV;
}

XMFLOAT4X4 SeaWood::D3DNode::getTextureTransform()
{
	return m_TextureTransform;
}

void SeaWood::D3DNode::setTextureTransform(CXMMATRIX matrix)
{
	XMStoreFloat4x4(&m_TextureTransform, matrix);
}
