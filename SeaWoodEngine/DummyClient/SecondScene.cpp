#include "SecondScene.h"
#include "PlayingBox.h"
#include "PlayingCamera.h"

USING_NS_SW;

SecondScene::SecondScene()
{

}

SecondScene::~SecondScene()
{

}

bool SecondScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	const FLOAT color[] = { 0.0f, 0.6f, 0.3f, 1.0f };

	GET_D3D_RENDERER()->setBackgroundColor(color);

	auto box = PlayingBox::create();
	box->setBoxWithRandomColor(2.0f, 2.0f, 2.0f);
	box->setSpeed(50.0f);
	addChild(box);

	for (int i = 0; i < 100; i++)
	{
		auto randomBox = Box::create();
		randomBox->setBoxWithRandomColor(1.0f + 0.1f * (rand() % 20), 1.0f + 0.1f * (rand() % 20), 1.0f + 0.1f * (rand() % 20));
		randomBox->setPosition(-50 + rand() % 101, -50 + rand() % 101, -50 + rand() % 101);
		randomBox->setRotate(0.1f * (rand() % 32), 0.1f * (rand() % 32), 0.1f * (rand() % 32));
		addChild(randomBox);
	}

	auto camera = PlayingCamera::create();
	camera->setChase(box, 10.0f);

	GET_D3D_RENDERER()->changeCamera(camera);

	DirectionalLight directionalLight;

	directionalLight.m_Ambient = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	directionalLight.m_Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	directionalLight.m_Specular = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	directionalLight.m_Direction = XMFLOAT3(1.0f, 1.0f, 0.0f);

	auto light = Light<DirectionalLight>::createWithScene(this, directionalLight);

	addChild(light);
	

	return true;
}

void SecondScene::update(float dTime)
{
	Scene::update(dTime);
}
