#include "pch.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "definition.h"
#include "SelectScene.h"
#include "CreditLayer.h"

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

	Sprite* start_btn = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_START);
	Sprite* start_btn_clicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_START_CLICKED);

	Sprite* exit_btn = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_EXIT);
	Sprite* exit_btn_clicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_EXIT_CLICKED);

	MenuItemSprite* menu_play = MenuItemSprite::create(start_btn, start_btn_clicked, CC_CALLBACK_1(MainScene::MenuClickCallback, this));
	MenuItemSprite* menu_exit = MenuItemSprite::create(exit_btn, exit_btn_clicked, CC_CALLBACK_1(MainScene::MenuCloseCallback, this));

	Sprite* credit_btn = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_CREDIT);
	Sprite* credit_btn_clicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_CREDIT_CLICKED);
	MenuItemSprite* menu_credit = MenuItemSprite::create(credit_btn, credit_btn_clicked, CC_CALLBACK_0(MainScene::ShowCredit, this));

	auto mainMenu = Menu::create(menu_play, menu_exit, menu_credit, nullptr);
	menu_play->setPosition(visibleSize.width/2, visibleSize.height/2-100);
	menu_exit->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
	menu_credit->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 8);

	mainMenu->setPosition(Vec2::ZERO);
	this->addChild(mainMenu);

//	Keyboard Event

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FILENAME_SOUND_MAIN_BGM,true);

	return true;
}

void MainScene::ShowCredit()
{
	while (getChildByName("credit"))
		removeChildByName("credit");

	CreditLayer* credit = CreditLayer::create();
	this->addChild(credit);
}

void MainScene::MenuClickCallback(cocos2d::Ref* pSender)
{
	cocos2d::Scene* gameScene = SelectScene::CreateScene();
	Director::getInstance()->pushScene(gameScene);
}

void MainScene::MenuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
