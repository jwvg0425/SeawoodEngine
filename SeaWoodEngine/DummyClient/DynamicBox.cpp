#include "DynamicBox.h"

USING_NS_SW;

DynamicBox::DynamicBox()
{

}

DynamicBox::~DynamicBox()
{

}

bool DynamicBox::init()
{
	if (!Box::init())
	{
		return false;
	}

	return true;
}

void DynamicBox::update(float dTime)
{
	const float SPEED = 20.0f;
	const float SCALE_SPEED = 1.0f;
	const float ROTATE_SPEED = 1.0f;


	//좌표 이동
	if (GET_KEY_MANAGER()->getKeyState(VK_UP) & KeyManager::PRESS)
	{
		setPosition(0, 0, SPEED*dTime, true);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_DOWN) & KeyManager::PRESS)
	{
		setPosition(0, 0, -SPEED*dTime, true);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_RIGHT) & KeyManager::PRESS)
	{
		setPosition(SPEED*dTime, 0, 0, true);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_LEFT) & KeyManager::PRESS)
	{
		setPosition(-SPEED*dTime, 0, 0, true);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_W) & KeyManager::PRESS)
	{
		setPosition(0, SPEED*dTime, 0, true);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_S) & KeyManager::PRESS)
	{
		setPosition(0, -SPEED*dTime, 0, true);
	}


	//회전
	if (GET_KEY_MANAGER()->getKeyState(VK_A) & KeyManager::PRESS)
	{
		float rotate = ROTATE_SPEED*dTime;

		setRotate(rotate, 0, 0, true);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_D) & KeyManager::PRESS)
	{
		float rotate = ROTATE_SPEED*dTime;

		setRotate(-rotate, 0, 0, true);
	}


	//크기
	if (GET_KEY_MANAGER()->getKeyState(VK_Z) & KeyManager::PRESS)
	{
		float scale = SCALE_SPEED*dTime;

		setScale(scale, scale, scale, true);
	}

	if (GET_KEY_MANAGER()->getKeyState(VK_X) & KeyManager::PRESS)
	{
		float scale = SCALE_SPEED*dTime;

		setScale(-scale, -scale, -scale, true);
	}
}
