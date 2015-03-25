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
	auto view = D3DView::create();
	auto camera = new Camera(XMVectorSet(10.0f, 10.0f, 10.0f, 1.0f), XMVectorZero(), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	FLOAT color[4] = { 0.4f, 0.15f, 1.0f, 1.0f };

	view->setBackgroundColor(color);
	view->setProjection(0.25f, 1.0f, 1000.0f);
	view->registerCamera(camera);

	Director::getInstance()->registerView(view);

	auto scene = FirstScene::create();
	Director::getInstance()->startScene(scene);
}

