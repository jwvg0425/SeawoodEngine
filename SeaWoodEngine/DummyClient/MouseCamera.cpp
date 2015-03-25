#include "MouseCamera.h"

USING_NS_SW;


MouseCamera::MouseCamera()
{

}

MouseCamera::~MouseCamera()
{

}

bool MouseCamera::init()
{
	if (!Camera::init())
	{
		return false;
	}

	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMStoreFloat4(&m_Up, up);

	Director::getInstance()->registerEvent(EventType::MOUSE_MOVE, this);

	return true;
}

void MouseCamera::update(float dTime)
{
	//구면 좌표계를 데카르트 좌표계로 변환
	float x = m_Radius*sinf(m_Phi)*cosf(m_Theta);
	float y = m_Radius*cosf(m_Phi);
	float z = m_Radius*sinf(m_Phi)*sinf(m_Theta);
	
	//view matrix 생성
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMStoreFloat4(&m_EyePos, pos);
	XMStoreFloat4(&m_TargetPos, target);
	XMStoreFloat4(&m_Up, up);

	updateView();
}

void MouseCamera::setRadius(float radius)
{
	m_Radius = radius;
}

void MouseCamera::onMouseMove(SeaWood::MouseEvent e)
{
	if (e.m_Status == MouseEvent::LEFT)
	{
		float dx = XMConvertToRadians(0.25f*(e.m_Position.m_X - m_PrevMousePos.m_X));
		float dy = XMConvertToRadians(0.25f*(e.m_Position.m_Y - m_PrevMousePos.m_Y));

		m_Theta += dx;
		m_Phi += dy;

		if (m_Phi < 0.1f)
		{
			m_Phi = 0.1f;
		}

		if (m_Phi > PI - 0.1f)
		{
			m_Phi = PI - 0.1f;
		}
	}

	m_PrevMousePos = e.m_Position;
}

