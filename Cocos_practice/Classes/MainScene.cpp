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

	Sprite* playButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_START);
	Sprite* playButtonClicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_START_CLICKED);
	MenuItemSprite* menu_play = MenuItemSprite::create(playButton, playButtonClicked, CC_CALLBACK_1(MainScene::MenuClickCallback, this));
	
	Sprite* exitButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_EXIT);
	Sprite* exitButtonClicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_EXIT_CLICKED);
	MenuItemSprite* menu_exit = MenuItemSprite::create(exitButton, exitButtonClicked, CC_CALLBACK_1(MainScene::MenuCloseCallback, this));

	menu_play->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 -100 + 20));
	menu_exit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 -200));

	auto mainMenu = Menu::create(menu_play, menu_exit, nullptr);
	mainMenu->setPosition(Vec2::ZERO);

	this->addChild(mainMenu);

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
	/*auto target = event->getCurrentTarget()->getChildByName("cursor");
	Vec2 loc = target->getPosition();

	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;

	case EventKeyboard::KeyCode::KEY_ENTER:
		target->setPosition(loc.x -= 15, loc.y);
		break;
	}*/
}

void MainScene::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*auto target = event->getCurrentTarget()->getChildByName("cursor");
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
	}*/
}
