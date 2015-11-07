#include "pch.h"
#include "DebugUI.h"

cocos2d::Scene* DebugUI::scene()
{
	cocos2d::Scene *scene = Scene::create();
	DebugUI *layer = DebugUI::create();

	scene->addChild(layer);
	return scene;
}

bool DebugUI::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //투명하게
	{
		return false;
	}

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	//backLayer추가
	backLayer = LayerColor::create(ccc4(0, 0, 0, 50), visibleSize.width, visibleSize.height);
	backLayer->setAnchorPoint(Vec2(0, 0));
	backLayer->setPosition(Vec2(0, 0));
	this->addChild(backLayer);

	//popUpLayer추가
	popUpLayer = LayerColor::create(ccc4(92, 92, 92, 255), visibleSize.width / 2, visibleSize.height / 2);
	popUpLayer->setAnchorPoint(Vec2(0, 0));
	popUpLayer->setPosition(Vec2((visibleSize.width - popUpLayer->getContentSize().width) / 2, (visibleSize.height - popUpLayer->getContentSize().height) / 2));

	float width = popUpLayer->getContentSize().width;
	float height = popUpLayer->getContentSize().height;

	cocos2d::Label* label_title = Label::createWithTTF("Testudo::Debug", "fonts/Marker Felt.ttf", 20);
	label_title->setPosition(Vec2(100, height - 20));

	popUpLayer->addChild(label_title);
	this->addChild(popUpLayer);

	return true;
}