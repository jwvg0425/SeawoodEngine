#include "PlayingCamera.h"
#include "PlayingBox.h"

PlayingCamera::PlayingCamera()
{

}

PlayingCamera::~PlayingCamera()
{

}

bool PlayingCamera::init()
{
	if (!Camera::init())
	{
		return false;
	}

	return true;
}

void PlayingCamera::update(float dTime)
{
	if (m_Box == nullptr)
		return;


	float x, y, z;
	m_Box->getPosition(&x, &y, &z);

	XMVECTOR target = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR chaseVector = m_Distance * m_Box->getView();
	XMVECTOR chasePos = XMVectorSet(0.0f, -m_Distance / 2, 0.0f, 0.0f);

	chaseVector = chaseVector + chasePos;

	XMVECTOR pos = target - chaseVector;
	//up vector는 고정
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMStoreFloat4(&m_EyePos, pos);
	XMStoreFloat4(&m_TargetPos, target);
	XMStoreFloat4(&m_Up, up);

	//view matrix 생성
	updateView();
}

void PlayingCamera::setChase(PlayingBox* box, float distance)
{
	m_Box = box;
	m_Distance = distance;
}
