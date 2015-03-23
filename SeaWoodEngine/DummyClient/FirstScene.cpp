#include "FirstScene.h"
#include "RectNode.h"

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

	auto rect = RectNode::createWithRect({ 20, 20, 80, 80 });

	addChild(rect);

	return true;
}
