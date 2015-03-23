#include "stdafx.h"
#include "Ref.h"
#include "Director.h"

SeaWood::Ref::Ref() : m_RefCount(1)
{

}

SeaWood::Ref::~Ref()
{

}

void SeaWood::Ref::retain()
{
	m_RefCount++;
}

void SeaWood::Ref::release()
{
	_ASSERT(m_RefCount > 0);
	m_RefCount--;

	if (m_RefCount <= 0)
	{
		delete this;
	}
}

void SeaWood::Ref::autorelease()
{
	Director::getInstance()->autorelease(this);
}
