#include "stdafx.h"
#include "Camera.h"

USING_NS_SW;

Camera::Camera(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up)
{
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

const XMFLOAT4X4& Camera::getView() const
{
	return m_View;
}

void Camera::updateView()
{
	XMVECTOR eyePos = XMLoadFloat4(&m_EyePos);
	XMVECTOR targetPos = XMLoadFloat4(&m_TargetPos);
	XMVECTOR up = XMLoadFloat4(&m_Up);
	XMMATRIX V = XMMatrixLookAtLH(eyePos, targetPos, up);
	XMStoreFloat4x4(&m_View, V);
}
