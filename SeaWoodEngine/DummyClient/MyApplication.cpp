#include "MyApplication.h"
#include "FirstScene.h"

USING_NS_SW;

MyApplication::MyApplication()
{

}

MyApplication::~MyApplication()
{

}

void MyApplication::onCreate()
{
	auto renderer = Renderer::create();

	FLOAT color[4] = { 0.3f, 0.7f, 0.5f, 1.0f };

	renderer->setBackgroundColor(color);

	Director::getInstance()->registerRenderer(renderer);

	auto scene = FirstScene::create();
	Director::getInstance()->startScene(scene);
}

