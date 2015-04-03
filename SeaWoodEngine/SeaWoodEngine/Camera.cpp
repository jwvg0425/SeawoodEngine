#include "stdafx.h"
#include "Camera.h"
#include "Application.h"

USING_NS_SW;

Camera::Camera(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up)
{
	//default lens 설정.
	setLens(0.25f, Application::getInstance()->getAspectRatio(), 1.0f, 1000.0f);

	XMVECTOR L = XMVector3Normalize(XMVectorSubtract(targetPos, eyePos));
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(up, L));
	XMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat3(&m_Pos, eyePos);
	XMStoreFloat3(&m_Look, L);
	XMStoreFloat3(&m_Right, R);
	XMStoreFloat3(&m_Up, U);

	updateView();
}

Camera::~Camera()
{
}

void Camera::setEyePos(XMVECTOR eyePos)
{
	XMStoreFloat3(&m_Pos, eyePos);

	updateView();
}

void Camera::setUpVector(XMVECTOR up)
{
	XMStoreFloat3(&m_Up, up);

	updateView();
}

XMMATRIX Camera::getView() const
{
	return XMLoadFloat4x4(&m_View);
}

bool SeaWood::Camera::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

SeaWood::Camera::Camera()
{
	//default lens 설정.
	setLens(0.25f, Application::getInstance()->getAspectRatio(), 1.0f, 1000.0f);
}

Camera* SeaWood::Camera::createWithPos(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up)
{
	Camera* camera = new Camera(eyePos, targetPos, up);

	if (camera->init())
	{
		camera->autorelease();
		return camera;
	}
	else
	{
		delete camera;
		return nullptr;
	}
}

void SeaWood::Camera::setLens(FLOAT fovAngleY, FLOAT aspect, FLOAT nearZ, FLOAT farZ)
{
	m_FovAngleY = fovAngleY;
	m_Aspect = aspect;
	m_NearZ = nearZ;
	m_FarZ = farZ;

	updateProjection();
}

XMMATRIX SeaWood::Camera::getProjection() const
{
	return XMLoadFloat4x4(&m_Projection);
}

XMMATRIX SeaWood::Camera::getViewProj() const
{
	XMMATRIX view = getView();
	XMMATRIX proj = getProjection();
	XMMATRIX v = view * proj;
	return v;
}

void SeaWood::Camera::updateView()
{
	XMVECTOR R = XMLoadFloat3(&m_Right);
	XMVECTOR U = XMLoadFloat3(&m_Up);
	XMVECTOR L = XMLoadFloat3(&m_Look);
	XMVECTOR P = XMLoadFloat3(&m_Pos);

	// Keep camera's axes orthogonal to each other and of unit length.
	L = XMVector3Normalize(L);
	U = XMVector3Normalize(XMVector3Cross(L, R));

	// U, L already ortho-normal, so no need to normalize cross product.
	R = XMVector3Cross(U, L);

	// Fill in the view matrix entries.
	float x = -XMVectorGetX(XMVector3Dot(P, R));
	float y = -XMVectorGetX(XMVector3Dot(P, U));
	float z = -XMVectorGetX(XMVector3Dot(P, L));

	XMStoreFloat3(&m_Right, R);
	XMStoreFloat3(&m_Up, U);
	XMStoreFloat3(&m_Look, L);

	m_View(0, 0) = m_Right.x;
	m_View(1, 0) = m_Right.y;
	m_View(2, 0) = m_Right.z;
	m_View(3, 0) = x;

	m_View(0, 1) = m_Up.x;
	m_View(1, 1) = m_Up.y;
	m_View(2, 1) = m_Up.z;
	m_View(3, 1) = y;

	m_View(0, 2) = m_Look.x;
	m_View(1, 2) = m_Look.y;
	m_View(2, 2) = m_Look.z;
	m_View(3, 2) = z;

	m_View(0, 3) = 0.0f;
	m_View(1, 3) = 0.0f;
	m_View(2, 3) = 0.0f;
	m_View(3, 3) = 1.0f;
}

void SeaWood::Camera::updateProjection()
{
	XMMATRIX p = XMMatrixPerspectiveFovLH(m_FovAngleY*PI, m_Aspect, m_NearZ, m_FarZ);
	
	XMStoreFloat4x4(&m_Projection, p);
}

XMFLOAT3 SeaWood::Camera::getEyePos()
{
	return m_Pos;
}

void SeaWood::Camera::walk(float d)
{
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR l = XMLoadFloat3(&m_Look);
	XMVECTOR p = XMLoadFloat3(&m_Pos);
	XMStoreFloat3(&m_Pos, XMVectorMultiplyAdd(s, l, p));

	updateView();
}

void SeaWood::Camera::strafe(float d)
{
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR r = XMLoadFloat3(&m_Right);
	XMVECTOR p = XMLoadFloat3(&m_Pos);
	XMStoreFloat3(&m_Pos, XMVectorMultiplyAdd(s, r, p));

	updateView();
}

void SeaWood::Camera::pitch(float angle)
{
	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&m_Right), angle);

	XMStoreFloat3(&m_Up, XMVector3TransformNormal(XMLoadFloat3(&m_Up), R));
	XMStoreFloat3(&m_Look, XMVector3TransformNormal(XMLoadFloat3(&m_Look), R));

	updateView();
}

void SeaWood::Camera::rotateY(float angle)
{
	XMMATRIX R = XMMatrixRotationY(angle);

	XMStoreFloat3(&m_Right, XMVector3TransformNormal(XMLoadFloat3(&m_Right), R));
	XMStoreFloat3(&m_Up, XMVector3TransformNormal(XMLoadFloat3(&m_Up), R));
	XMStoreFloat3(&m_Look, XMVector3TransformNormal(XMLoadFloat3(&m_Look), R));

	updateView();
}

XMVECTOR SeaWood::Camera::getLookVector()
{
	return XMLoadFloat3(&m_Look);
}
