#include "PlayingBox.h"

USING_NS_SW;

PlayingBox::PlayingBox()
{

}

PlayingBox::~PlayingBox()
{

}

bool PlayingBox::init()
{
	if (!Box::init())
	{
		return false;
	}

	XMVECTOR view = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);

	m_PrevMouse = Director::getInstance()->getMouse()->m_Position;

	XMStoreFloat4(&m_View, view);

	Director::getInstance()->registerEvent(EventType::MOUSE_MOVE, this);

	return true;
}

void PlayingBox::update(float dTime)
{
	//좌표 이동
	if (GET_KEY_MANAGER()->getKeyState(VK_W) & KeyManager::PRESS)
	{
		XMVECTOR go = m_Speed * dTime * getView();
		float x = XMVectorGetX(go);
		float y = XMVectorGetY(go);
		float z = XMVectorGetZ(go);

		setPosition(x, y, z, true);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_S) & KeyManager::PRESS)
	{
		XMVECTOR go = -m_Speed * dTime * getView();
		float x = XMVectorGetX(go);
		float y = XMVectorGetY(go);
		float z = XMVectorGetZ(go);

		setPosition(x, y, z, true);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_D) & KeyManager::PRESS)
	{
		XMVECTOR go = m_Speed * dTime * XMVector3Cross(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), getView());
		float x = XMVectorGetX(go);
		float y = XMVectorGetY(go);
		float z = XMVectorGetZ(go);

		setPosition(x, y, z, true);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_A) & KeyManager::PRESS)
	{
		XMVECTOR go = -m_Speed * dTime * XMVector3Cross(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), getView());
		float x = XMVectorGetX(go);
		float y = XMVectorGetY(go);
		float z = XMVectorGetZ(go);

		setPosition(x, y, z, true);
	}
}

void PlayingBox::setSpeed(float speed)
{
	m_Speed = speed;
}

void PlayingBox::onMouseMove(MouseEvent e)
{
	if (e.m_Status & MouseEvent::RIGHT)
	{
		float dx = XMConvertToRadians(0.25f*(e.m_Position.m_X - m_PrevMouse.m_X));

		m_Theta += dx;

		setRotate(0, m_Theta, 0);
	}

	m_PrevMouse = e.m_Position;
}

XMVECTOR PlayingBox::getView()
{
	XMVECTOR view = XMLoadFloat4(&m_View);
	XMMATRIX rotate = XMMatrixRotationY(m_Theta);

	return XMVector4Transform(view, rotate);
}
