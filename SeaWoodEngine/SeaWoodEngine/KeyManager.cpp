#include "stdafx.h"
#include "KeyManager.h"


SeaWood::KeyManager::KeyManager()
{
	init();
}

SeaWood::KeyManager::~KeyManager()
{

}

bool SeaWood::KeyManager::init()
{
	for (int i = 0; i < KEY_NUM; i++)
	{
		m_States[i] = FREE;
		m_OldStates[i] = FREE;
	}
	return true;
}

void SeaWood::KeyManager::update(float dTime)
{
	for (int i = 0; i < KEY_NUM; i++)
	{
		int nowState = GetAsyncKeyState(i);

		if (nowState & 0x8000)
		{
			switch(m_OldStates[i])
			{
			case FREE:
			case PULL:
				m_States[i] = PUSH;
				break;
			case PUSH:
			case HOLD:
				m_States[i] = HOLD;
				break;
			}
		}
		else
		{
			switch (m_OldStates[i])
			{
			case PULL:
			case FREE:
				m_States[i] = FREE;
				break;
			case PUSH:
			case HOLD:
				m_States[i] = PULL;
				break;
			}
		}

		m_OldStates[i] = m_States[i];
	}
}

SeaWood::KeyManager::KeyState SeaWood::KeyManager::getKeyState(int keyCode)
{
	_ASSERT(keyCode >= 0 && keyCode < KEY_NUM);

	return m_States[keyCode];
}

bool SeaWood::KeyManager::isKeyState(int keyCode, KeyState state)
{
	_ASSERT(keyCode >= 0 && keyCode < KEY_NUM);
	
	return (m_States[keyCode] & state) != 0;
}

