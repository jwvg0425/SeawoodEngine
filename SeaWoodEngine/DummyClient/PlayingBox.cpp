#include "PlayingBox.h"
#include "Missile.h"

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
	Director::getInstance()->registerEvent(EventType::MOUSE_UP, this);
	Director::getInstance()->registerEvent(EventType::MOUSE_DOWN, this);

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

	//미사일 발사
	m_Delay += dTime;

	if (m_IsClick)
	{
		//0.2초마다 한 번씩 발싸!

		if (m_Delay >= 0.2f)
		{
			auto missile = Missile::create();

			missile->setPosition(m_X, m_Y, m_Z);
			missile->setDirection(getView(), 100.0f);

			getParent()->addChild(missile);

			m_Delay = 0.0f;
		}
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

		setAngle(0, m_Theta, 0);
	}

	m_PrevMouse = e.m_Position;
}

XMVECTOR PlayingBox::getView()
{
	XMVECTOR view = XMLoadFloat4(&m_View);
	XMMATRIX rotate = XMMatrixRotationY(m_Theta);

	return XMVector4Transform(view, rotate);
}

void PlayingBox::onMouseDown(SeaWood::MouseEvent e)
{
	if (e.m_Status & MouseEvent::LEFT)
	{
		m_IsClick = true;
	}
}

void PlayingBox::onMouseUp(SeaWood::MouseEvent e)
{
	if (!(e.m_Status & MouseEvent::LEFT))
	{
		m_IsClick = false;
	}
}
