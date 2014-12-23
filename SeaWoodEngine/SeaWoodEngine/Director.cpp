#include "stdafx.h"
#include "Director.h"
#include "Node.h"

SeaWood::Director* SeaWood::Director::m_Instance = nullptr;


SeaWood::Director::Director()
{

}

SeaWood::Director::~Director()
{

}

SeaWood::Director* SeaWood::Director::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new SeaWood::Director;
	}
	return m_Instance;
}

void SeaWood::Director::releaseInstance()
{
	SAFE_DELETE(m_Instance);
}

void SeaWood::Director::gameLoop()
{
}
