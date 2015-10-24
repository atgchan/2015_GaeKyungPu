#include "pch.h"
#include "GameScene.h"
#include "TileMap.h"
#include <iostream>

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	auto unitLayer = Layer::create();
	unitLayer->setName("unitLayer");

	scene->addChild(layer);
	scene->addChild(unitLayer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto map = TileMap::create();
	this->addChild(map);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label_title = Label::createWithTTF("In Game Scene!!!", "fonts/Marker Felt.ttf", 40);
	label_title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));

	this->addChild(label_title);

//	Keyboard Event
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

//	Mouse Event
	auto clickListener = EventListenerMouse::create();
	clickListener->onMouseDown = CC_CALLBACK_1(GameScene::setUnitByClick, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	return true;
}

void GameScene::setUnitByClick(Event* event)
{
	EventMouse* mouseEvent = nullptr;
	mouseEvent = dynamic_cast<EventMouse*>(event);
	
	if (mouseEvent)
	{
		float xPos = mouseEvent->getCursorX();
		float yPos = mouseEvent->getCursorY();

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto unit_spear = Sprite::create("spear_red_01.png");
		unit_spear->setPosition(Vec2(origin.x + xPos, visibleSize.height + yPos));

		//auto unit_layer = event->getCurrentTarget()->getChildByName("unitLayer");
		auto unit_layer = event->getCurrentTarget();
		unit_layer->addChild(unit_spear);
	}
}


void GameScene::rotateUnitByClick(Ref* pSender)
{

}

void GameScene::menuClickCallback(cocos2d::Ref* pSender)
{
	
}

void GameScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;

	case EventKeyboard::KeyCode::KEY_ENTER:

		break;
	}
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ENTER:
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		break;
	}
}