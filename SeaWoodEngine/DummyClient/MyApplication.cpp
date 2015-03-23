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
	auto scene = FirstScene::create();
	Director::getInstance()->startScene(scene);

	auto view = new GdiView;
	Director::getInstance()->registerView(view);

	
}

