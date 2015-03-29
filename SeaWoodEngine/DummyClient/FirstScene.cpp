﻿#include "FirstScene.h"
#include "DynamicBox.h"
#include "MouseCamera.h"
#include "ChasingCamera.h"
#include "SecondScene.h"
#include "EyeLight.h"
#include "RoundLight.h"

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

	directionalLight.m_Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	directionalLight.m_Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	directionalLight.m_Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	directionalLight.m_Direction = XMFLOAT3(1.0f, 1.0f, 0.0f);

	m_Light = Light<DirectionalLight>::createWithScene(this, directionalLight);
	
	addChild(m_Light);

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
		camera->setChase(m_Box, XMVectorSet(0.0f, -5.0f, 20.0f, 0.0f));

		GET_D3D_RENDERER()->changeCamera(camera);
	}

	//빛 변경 - 평행광 켜기 끄기
	if (GET_KEY_MANAGER()->getKeyState(VK_4) == KeyManager::PUSH)
	{
		if (m_Light != nullptr)
		{
			removeChild(m_Light);
			m_Light = nullptr;
		}
		else
		{

			DirectionalLight directionalLight;

			directionalLight.m_Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			directionalLight.m_Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			directionalLight.m_Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			directionalLight.m_Direction = XMFLOAT3(1.0f, 1.0f, 0.0f);

			m_Light = Light<DirectionalLight>::createWithScene(this, directionalLight);

			addChild(m_Light);
		}
	}

	//빛 변경 - 점적광 켜기 끄기
	if (GET_KEY_MANAGER()->getKeyState(VK_5) == KeyManager::PUSH)
	{
		if (m_Light2 != nullptr)
		{
			removeChild(m_Light2);
			m_Light2 = nullptr;
		}
		else
		{
			m_Light2 = EyeLight::createWithScene(this);

			addChild(m_Light2);
		}
	}

	//빛 변경 - 점광 켜기 끄기
	if (GET_KEY_MANAGER()->getKeyState(VK_6) == KeyManager::PUSH)
	{
		if (m_Light3 != nullptr)
		{
			removeChild(m_Light3);
			m_Light3 = nullptr;
		}
		else
		{
			m_Light3 = RoundLight::createWithScene(this);
			addChild(m_Light3);
		}
	}

	//다음 씬으로 넘어가기
	if(GET_KEY_MANAGER()->getKeyState(VK_F) == KeyManager::PUSH)
	{
		Director::getInstance()->changeScene(SecondScene::create());
	}
}
