#include "MovingCamera.h"

USING_NS_SW;

MovingCamera::MovingCamera(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up)
: Camera(eyePos, targetPos, up)
{
}

MovingCamera::~MovingCamera()
{

}

MovingCamera* MovingCamera::createWithPos(XMVECTOR eyePos, XMVECTOR targetPos, XMVECTOR up)
{
	MovingCamera* camera = new MovingCamera(eyePos, targetPos, up);

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

bool MovingCamera::init()
{
	if (!Camera::init())
	{
		return false;
	}

	Director::getInstance()->registerEvent(EventType::MOUSE_MOVE, this);

	scheduleUpdate();

	return true;
}

void MovingCamera::update(float dTime)
{
	if (GET_KEY_MANAGER()->getKeyState(VK_W) & KeyManager::PRESS)
	{
		walk(10.0f*dTime);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_S) & KeyManager::PRESS)
	{
		walk(-10.0f*dTime);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_A) & KeyManager::PRESS)
	{
		strafe(-10.0f*dTime);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_D) & KeyManager::PRESS)
	{
		strafe(10.0f*dTime);
	}
}

void MovingCamera::onMouseMove(MouseEvent e)
{
	if (e.m_Status & MouseEvent::RIGHT)
	{
		float dx = XMConvertToRadians(0.25f*(e.m_Position.m_X - m_LastPos.m_X));
		float dy = XMConvertToRadians(0.25f*(e.m_Position.m_Y - m_LastPos.m_Y));

		pitch(dy);
		rotateY(dx);
	}

	m_LastPos = e.m_Position;
}