#include "stdafx.h"
#include "Camera.h"
#include "Application.h"

USING_NS_SW;

Camera::Camera(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up)
{
	//default lens 설정.
	setLens(0.25f, Application::getInstance()->getAspectRatio(), 1.0f, 1000.0f);

	XMStoreFloat4(&m_EyePos, eyePos);
	XMStoreFloat4(&m_TargetPos, targetPos);
	XMStoreFloat4(&m_Up, up);

	updateView();
}

Camera::~Camera()
{
}

void Camera::setEyePos(XMVECTOR eyePos)
{
	XMStoreFloat4(&m_EyePos, eyePos);

	updateView();
}

void Camera::setTargetPos(XMVECTOR targetPos)
{
	XMStoreFloat4(&m_TargetPos, targetPos);

	updateView();
}

void Camera::setUpVector(XMVECTOR up)
{
	XMStoreFloat4(&m_Up, up);

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
	XMVECTOR eyePos = XMLoadFloat4(&m_EyePos);
	XMVECTOR targetPos = XMLoadFloat4(&m_TargetPos);
	XMVECTOR up = XMLoadFloat4(&m_Up);
	XMMATRIX v = XMMatrixLookAtLH(eyePos, targetPos, up);

	XMStoreFloat4x4(&m_View, v);
}

void SeaWood::Camera::updateProjection()
{
	XMMATRIX p = XMMatrixPerspectiveFovLH(m_FovAngleY*PI, m_Aspect, m_NearZ, m_FarZ);
	
	XMStoreFloat4x4(&m_Projection, p);
}
