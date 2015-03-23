#include "FirstScene.h"
#include "DynamicRect.h"

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

	auto rect = RectNode::createWithRect({ 40, 40, 120, 60 });
	addChild(rect, "rect");

	auto mouseRect = DynamicRect::createWithRect({ 0, 0, 50, 50 });
	addChild(mouseRect);

	return true;
}
