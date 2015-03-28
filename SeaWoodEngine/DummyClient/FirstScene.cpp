#include "FirstScene.h"
#include "DynamicBox.h"
#include "MouseCamera.h"
#include "ChasingCamera.h"
#include "SecondScene.h"

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

	//현재 scene에 맞는 카메라로 변경
	auto camera = Camera::createWithPos(XMVectorSet(0.0f, 0.0f, -20.0f, 1.0f), XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	GET_D3D_RENDERER()->changeCamera(camera);

	m_Box = DynamicBox::create();
	m_Box->setBoxWithRandomColor(2.0f, 2.0f, 2.0f);
	addChild(m_Box);

	for (int i = 0; i < 100; i++)
	{
		auto randomBox = Box::create();
		randomBox->setBoxWithRandomColor(1.0f + 0.1f * (rand() % 20), 1.0f + 0.1f * (rand() % 20), 1.0f + 0.1f * (rand() % 20));
		randomBox->setPosition(-50 + rand() % 101, -50 + rand() % 101, -50 + rand() % 101);
		randomBox->setRotate(0.1f * (rand() % 32), 0.1f * (rand() % 32), 0.1f * (rand() % 32));
		addChild(randomBox);
	}

	DirectionalLight directionalLight;

	directionalLight.m_Ambient = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	directionalLight.m_Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	directionalLight.m_Specular = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	directionalLight.m_Direction = XMFLOAT3(1.0f, 1.0f, 0.0f);

	registerLight(directionalLight);
	
	return true;
}

void FirstScene::update(float dTime)
{
	Scene::update(dTime);

	//고정 카메라
	if (GET_KEY_MANAGER()->getKeyState(VK_1) == KeyManager::PUSH)
	{
		GET_D3D_RENDERER()->changeCamera(Camera::createWithPos(XMVectorSet(0.0f, 0.0f, -20.0f, 1.0f), XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));
	}

	//mouse로 시점 변환 가능한 카메라
	if (GET_KEY_MANAGER()->getKeyState(VK_2) == KeyManager::PUSH)
	{
		auto camera = MouseCamera::create();
		camera->setRadius(20.0f);

		GET_D3D_RENDERER()->changeCamera(camera);
	}

	//dynamic box 계속 쫓아다님

	if (GET_KEY_MANAGER()->getKeyState(VK_3) == KeyManager::PUSH)
	{
		auto camera = ChasingCamera::create();
		camera->setChase(m_Box, XMVectorSet(0.0f, 5.0f, -20.0f, 0.0f));

		GET_D3D_RENDERER()->changeCamera(camera);
	}

	//다음 씬으로 넘어가기
	if(GET_KEY_MANAGER()->getKeyState(VK_F) == KeyManager::PUSH)
	{
		Director::getInstance()->changeScene(SecondScene::create());
	}
}
