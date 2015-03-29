#include "ChasingCamera.h"
#include "Box.h"

USING_NS_SW;

ChasingCamera::ChasingCamera()
{

}

ChasingCamera::~ChasingCamera()
{

}

bool ChasingCamera::init()
{
	if (!Camera::init())
	{
		return false;
	}

	return true;
}

void ChasingCamera::update(float dTime)
{
	if (m_Box == nullptr)
		return;

	
	float x, y, z;
	m_Box->getPosition(&x, &y, &z);

	XMVECTOR target = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR chaseVector = XMLoadFloat4(&m_ChaseVector);

	XMVECTOR pos = target - chaseVector;
	//up vector는 고정
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMStoreFloat4(&m_EyePos, pos);
	XMStoreFloat4(&m_TargetPos, target);
	XMStoreFloat4(&m_Up, up);

	//view matrix 생성
	updateView();
}

void ChasingCamera::setChase(Box* box, XMVECTOR chaseVector)
{
	m_Box = box;

	XMStoreFloat4(&m_ChaseVector, chaseVector);
}