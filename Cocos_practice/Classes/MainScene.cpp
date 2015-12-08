#include "pch.h"
#include "GameScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "definition.h"

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
	this->setName("MainScene");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CCSprite * background = CCSprite::create(FILENAME_IMG_MAIN_BACKGROUND);
	background->setScaleX((visibleSize.width / background->getContentSize().width) * 1);
	background->setScaleY((visibleSize.height / background->getContentSize().height) * 1);
	background->setAnchorPoint(Point(0,0));
	this->addChild(background);

	auto label_title = Label::createWithTTF("Testudo", FILENAME_FONT_MAINMENU, 40);
	label_title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));

	auto label_play = Label::createWithTTF("Play", FILENAME_FONT_MAINMENU, 24);
	auto label_setting = Label::createWithTTF("Setting", FILENAME_FONT_MAINMENU, 24);
	auto label_exit = Label::createWithTTF("Exit", FILENAME_FONT_MAINMENU, 24);

	auto menu_play = MenuItemLabel::create(label_play, CC_CALLBACK_1(MainScene::MenuClickCallback, this));
	auto menu_setting = MenuItemLabel::create(label_setting);
	auto menu_exit = MenuItemLabel::create(label_exit, CC_CALLBACK_1(MainScene::MenuCloseCallback, this));

	menu_play->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	menu_setting->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 30));
	menu_exit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 60));

	auto mainMenu = Menu::create(menu_play, menu_setting, menu_exit, nullptr);
	mainMenu->setPosition(Vec2::ZERO);

	Sprite* cursor = Sprite::createWithSpriteFrameName(FILENAME_IMG_MAIN_CURSOR);
	
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

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FILENAME_SOUND_MAIN_BGM,true);

	return true;
}

void MainScene::MenuClickCallback(cocos2d::Ref* pSender)
{
	cocos2d::Scene* gameScene = GameScene::CreateScene();
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
