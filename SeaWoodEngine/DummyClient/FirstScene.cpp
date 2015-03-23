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

	Director::getInstance()->registerEvent(EventType::MOUSE_DOWN, this);

	return true;
}

void FirstScene::onMouseDown(MouseEvent e)
{
	auto rect = RectNode::createWithRect
		({ e.m_Position.m_X - 40, e.m_Position.m_Y - 40, 80, 80 });

	addChild(rect, "rect");

	if (e.m_Status == MouseEvent::RIGHT)
	{
		Director::getInstance()->end();
	}
}