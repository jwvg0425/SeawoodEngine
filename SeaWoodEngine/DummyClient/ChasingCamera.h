#pragma once
#include "SWEngine.h"

class Box;
//특정 박스의 중앙점을 바라봄. 계속 쫓아 다님.
class ChasingCamera final : public SeaWood::Camera
{
public:
	ChasingCamera();
	~ChasingCamera() override;

	bool init() override;
	void update(float dTime) override;

	//해당 box의 중앙지점을 항상 chaseVector 방향으로 바라봄.
	void setChase(Box* box, XMVECTOR chaseVector);

	CREATE_FUNC(ChasingCamera);
private:
	float m_Theta = 0.0f;
	Box* m_Box = nullptr;
	XMFLOAT4 m_ChaseVector;
};