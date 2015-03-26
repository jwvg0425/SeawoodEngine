#pragma once
#include "SWEngine.h"

class PlayingBox;
//PlayingBox의 중앙점을 바라봄. FPS 시점처럼(TPS지만) 계속 쫓아 다님.
class PlayingCamera final : public SeaWood::Camera
{
public:
	PlayingCamera();
	~PlayingCamera() override;

	bool init() override;
	void update(float dTime) override;

	void setChase(PlayingBox* box, float distance);

	CREATE_FUNC(PlayingCamera);

private:
	PlayingBox* m_Box = nullptr;
	float m_Distance = 0.0f;
};