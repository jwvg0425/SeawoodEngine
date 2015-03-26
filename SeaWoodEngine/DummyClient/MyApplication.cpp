#include "MyApplication.h"
#include "FirstScene.h"
#include "MouseCamera.h"

USING_NS_SW;

MyApplication::MyApplication()
{

}

MyApplication::~MyApplication()
{

}

void MyApplication::onCreate()
{
	auto renderer = D3DRenderer::create();

	//고정 카메라
	auto camera = Camera::createWithPos(XMVectorSet(0.0f, 0.0f, -20.0f, 1.0f), XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

	FLOAT color[4] = { 0.7f, 0.15f, 1.0f, 1.0f };

	renderer->setBackgroundColor(color);
	renderer->setProjection(0.25f, 1.0f, 1000.0f);
	renderer->registerCamera(camera);

	Director::getInstance()->registerRenderer(renderer);

	auto scene = FirstScene::create();
	Director::getInstance()->startScene(scene);
}

