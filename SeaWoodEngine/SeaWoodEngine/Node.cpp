#include "stdafx.h"
#include "Node.h"
#include "Director.h"
#include "Renderer.h"
#include "Camera.h"

USING_NS_SW;


bool SeaWood::Node::init()
{
	return true;
}

void SeaWood::Node::setPosition(float x, float y, float z, bool relative /*= false*/)
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

void SeaWood::Node::setScale(float x, float y, float z, bool relative /*= false*/)
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

void SeaWood::Node::setRotate(float x, float y, float z, bool relative /*= false*/)
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

void SeaWood::Node::getPosition(float* x, float* y, float* z)
{
	*x = m_X;
	*y = m_Y;
	*z = m_Z;
}

void SeaWood::Node::getScale(float* scaleX, float* scaleY, float* scaleZ)
{
	*scaleX = m_ScaleX;
	*scaleY = m_ScaleY;
	*scaleZ = m_ScaleZ;
}

void SeaWood::Node::getRotate(float* angleX, float* angleY, float* angleZ)
{
	*angleX = m_AngleX;
	*angleY = m_AngleY;
	*angleZ = m_AngleZ;
}

XMMATRIX SeaWood::Node::getWorld() const
{
	return XMLoadFloat4x4(&m_World);
}

void SeaWood::Node::updateWorld()
{
	XMMATRIX S = XMLoadFloat4x4(&m_Scaling);
	XMMATRIX R = XMLoadFloat4x4(&m_Rotation);
	XMMATRIX T = XMLoadFloat4x4(&m_Translation);
	XMMATRIX W = S*R*T;

	XMStoreFloat4x4(&m_World, W);
}

const Material* SeaWood::Node::getMaterial()
{
	return m_Material;
}

void SeaWood::Node::setMaterial(Material material)
{
	if (m_Material == nullptr)
	{
		m_Material = new Material();
	}

	*m_Material = material;
}

void SeaWood::Node::setTexture(const std::wstring& fileName)
{
	HR(D3DX11CreateShaderResourceViewFromFile(GET_RENDERER()->getDevice(),
		fileName.c_str(), nullptr, nullptr, &m_DiffuseMapSRV, nullptr));
}

ID3D11ShaderResourceView* SeaWood::Node::getTexture()
{
	return m_DiffuseMapSRV;
}

XMFLOAT4X4 SeaWood::Node::getTextureTransform()
{
	return m_TextureTransform;
}

void SeaWood::Node::setTextureTransform(CXMMATRIX matrix)
{
	XMStoreFloat4x4(&m_TextureTransform, matrix);
}


Node::Node() : m_CenterPos(0.0f,0.0f,0.0f,1.0f)
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

Node::~Node()
{
	SAFE_DELETE(m_Material);
	ReleaseCOM(m_DiffuseMapSRV);

	removeAllChilds();
	for (auto& e : m_Events)
	{
		Director::getInstance()->clearEvent(e, this);
	}
}

void Node::render()
{
	for (auto& child : m_Childs)
	{
		child.second->render();
	}
}

void Node::update(float dTime)
{

}

void Node::addChild(Node* child)
{
	child->m_Parent = this;
	child->retain();
	m_Childs.push_back(std::make_pair("NO_NAME", child));
}

void SeaWood::Node::addChild(Node* child, std::string name)
{
	child->m_Parent = this;
	child->retain();
	m_Childs.push_back(std::make_pair(name, child));
}

Node* SeaWood::Node::getChild(std::string name)
{
	for (auto& child : m_Childs)
	{
		if (child.first == name)
		{
			return child.second;
		}
	}

	return nullptr;
}

Node* SeaWood::Node::getParent()
{
	return m_Parent;
}

void SeaWood::Node::onMouseDown(MouseEvent e)
{

}

void SeaWood::Node::onMouseMove(MouseEvent e)
{

}

void SeaWood::Node::onMouseUp(MouseEvent e)
{

}

void SeaWood::Node::removeAllChilds()
{
	//자식 모두 release 작업.
	for (auto& child : m_Childs)
	{
		child.second->release();
	}

	m_Childs.clear();
}

void SeaWood::Node::getChilds(std::string name, Nodes* childs)
{
	for (auto& child : m_Childs)
	{
		if (child.first == name)
		{
			childs->push_back(child.second);
		}
	}
}

void SeaWood::Node::setEvent(EventType e)
{
	m_Events.push_back(e);
}

void SeaWood::Node::setParent(Node* parent)
{
	_ASSERT(parent != nullptr);

	m_Parent = parent;
}

void SeaWood::Node::removeFromParent()
{
	m_Parent->removeChild(this);
}

XMMATRIX SeaWood::Node::getParentWorld() const
{
	if (m_Parent == nullptr)
	{
		return XMMatrixIdentity();
	}
	else
	{
		return m_Parent->getWorld() * m_Parent->getParentWorld();
	}
}

float SeaWood::Node::getDistanceToCamera(Camera* camera) const
{
	XMFLOAT3 cameraPos = camera->getEyePosW();
	XMVECTOR worldPointV = XMLoadFloat4(&XMFLOAT4(m_CenterPos.x, m_CenterPos.y, m_CenterPos.z, 1.0f));
	XMMATRIX world = getWorld() * getParentWorld();

	worldPointV = XMVector4Transform(worldPointV, world);

	XMFLOAT4 worldPoint;

	XMStoreFloat4(&worldPoint, worldPointV);

	worldPoint.x -= cameraPos.x;
	worldPoint.y -= cameraPos.y;
	worldPoint.z -= cameraPos.z;

	float distance = sqrt(worldPoint.x*worldPoint.x + worldPoint.y*worldPoint.y + worldPoint.z*worldPoint.z);

	return distance;
}

bool SeaWood::Node::isRender()
{
	return m_IsRender;
}

const Node::Childs& SeaWood::Node::getChildList()
{
	return m_Childs;
}

void SeaWood::Node::setInputLayout(ID3D11InputLayout* inputLayout, D3D11_PRIMITIVE_TOPOLOGY topology)
{
	m_InputLayout = inputLayout;
	m_Topology = topology;
}

void SeaWood::Node::setRasterizer(ID3D11RasterizerState* rasterizer)
{
	m_RasterizerState = rasterizer;
}

void SeaWood::Node::setBlend(ID3D11BlendState* blend, const FLOAT* blendFactor /*= nullptr*/)
{
	m_BlendState = blend;

	if (blendFactor != nullptr)
	{
		m_BlendFactor[0] = blendFactor[0];
		m_BlendFactor[1] = blendFactor[1];
		m_BlendFactor[2] = blendFactor[2];
		m_BlendFactor[3] = blendFactor[3];
	}
}

ID3D11BlendState* SeaWood::Node::getBlend() const
{
	return m_BlendState;
}

void Node::removeChild(Node* child)
{
	_ASSERT(child != nullptr);
	if (child == nullptr)
	{
		return;
	}

	for (auto it = m_Childs.begin(); it != m_Childs.end();)
	{
		if (it->second == child)
		{
			it->second->release();
			it = m_Childs.erase(it);
		}
		else
		{
			++it;
		}
	}
}