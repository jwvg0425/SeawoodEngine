#include "FirstScene.h"
#include "EyeLight.h"
#include "RoundLight.h"
#include "GeometryGenerator.h"
#include "MovingCamera.h"
#include "Box.h"
#include "RoundFigure.h"
#include <atomic>

USING_NS_SW;


FirstScene::FirstScene()
{
}

FirstScene::~FirstScene()
{
}

bool FirstScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto camera = MovingCamera::createWithPos(XMVectorSet(0.0f, 0.0f, -20.0f, 1.0f), XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	GET_RENDERER()->registerCamera(camera);


	auto direct = DirectionalLight();

	direct.m_Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	direct.m_Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	direct.m_Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	direct.m_Direction = XMFLOAT3(0.3f, 0.7f, 0.5f);

	auto light = Light<DirectionalLight>::createWithScene(this, direct);

	addChild(light);

	setFogEnable(true);
	setFog(20.0f, 100.0f, XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));


	return true;
}