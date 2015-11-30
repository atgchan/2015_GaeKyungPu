#include "pch.h"
#include "GameScene.h"
#include "MainScene.h"

Scene* MainScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	///# 문자 리터럴은 따로 모아 놓을 것

	auto label_title = Label::createWithTTF("Testudo", "fonts/Marker Felt.ttf", 40);
	label_title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));

	auto label_play = Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 24);
	auto label_setting = Label::createWithTTF("Setting", "fonts/Marker Felt.ttf", 24);
	auto label_exit = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 24);

	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(MainScene::MenuCloseCallback, this));
	closeItem->setPosition(
			Vec2(
				origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
				origin.y + closeItem->getContentSize().height / 2
			)
		);

	auto menu_play = MenuItemLabel::create(label_play, CC_CALLBACK_1(MainScene::MenuClickCallback, this));
	auto menu_setting = MenuItemLabel::create(label_setting);
	auto menu_exit = MenuItemLabel::create(label_exit, CC_CALLBACK_1(MainScene::MenuCloseCallback, this));

	menu_play->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	menu_setting->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 30));
	menu_exit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 60));

	auto mainMenu = Menu::create(menu_play, menu_setting, menu_exit, closeItem, NULL);
	mainMenu->setPosition(Vec2::ZERO);

	Sprite* cursor = Sprite::createWithSpriteFrameName("cursor.png");
	
	cursor->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2));
	cursor->setName("cursor");

	this->addChild(label_title);
	this->addChild(mainMenu);
	this->addChild(cursor);

//	Keyboard Event
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(MainScene::OnKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(MainScene::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	return true;
}

void MainScene::MenuClickCallback(cocos2d::Ref* pSender)
{
	auto gameScene = GameScene::CreateScene();
	Director::getInstance()->pushScene(gameScene);
}

void MainScene::MenuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainScene::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto target = event->getCurrentTarget()->getChildByName("cursor");
	Vec2 loc = target->getPosition();

	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;

	case EventKeyboard::KeyCode::KEY_ENTER:
		target->setPosition(loc.x -= 15, loc.y);
		break;
	}
}

void MainScene::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto target = event->getCurrentTarget()->getChildByName("cursor");
	Vec2 loc = target->getPosition();

	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ENTER:
		target->setPosition(loc.x += 15, loc.y);
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		target->setPosition(loc.x, loc.y += 30);
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		target->setPosition(loc.x, loc.y -= 30);
		break;
	}
}
