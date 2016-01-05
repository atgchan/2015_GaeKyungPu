#include "pch.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "definition.h"
#include "SelectScene.h"

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

	Label* btnLabelStart = Label::createWithTTF("start ", FILENAME_FONT_MAINMENU, 80);
	Label* btnLabelExit = Label::createWithTTF("exit ", FILENAME_FONT_MAINMENU, 80);

	MenuItemLabel* menu_play = MenuItemLabel::create(btnLabelStart, CC_CALLBACK_1(MainScene::MenuClickCallback, this));
	MenuItemLabel* menu_exit = MenuItemLabel::create(btnLabelExit, CC_CALLBACK_1(MainScene::MenuCloseCallback, this));

	auto mainMenu = Menu::create(menu_play, menu_exit, nullptr);
	mainMenu->alignItemsVertically();
	menu_play->setPositionY(menu_play->getPositionY() + 30 - 100);
	menu_exit->setPositionY(menu_exit->getPositionY() - 30 - 100);
	mainMenu->setPositionY(mainMenu->getPositionY() - 100);

	this->addChild(mainMenu);

//	Keyboard Event

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FILENAME_SOUND_MAIN_BGM,true);

	return true;
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
