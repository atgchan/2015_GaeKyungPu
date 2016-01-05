#include "pch.h"
#include "CreditLayer.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

cocos2d::Scene* CreditLayer::scene()
{
	cocos2d::Scene *scene = Scene::create();
	CreditLayer* layer = CreditLayer::create();

	scene->addChild(layer);
	return scene;
}

bool CreditLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //투명하게
		return false;

	this->setName("credit");
	this->setZOrder(20);
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//backLayer추가
	BackLayer = LayerColor::create(ccc4(0, 0, 0, 1000), visibleSize.width, visibleSize.height);
	BackLayer->setAnchorPoint(Vec2(0, 0));
	BackLayer->setPosition(Vec2(0, 0));
	this->addChild(BackLayer);

	Sprite* resumeButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_CREDIT);
	Sprite* resumeButton_clicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_CREDIT_CLICKED);
	MenuItemSprite* resumeMenu = MenuItemSprite::create(resumeButton, resumeButton_clicked, CC_CALLBACK_0(CreditLayer::Resume, this));
	resumeMenu->setPosition(visibleSize.width * 7/8, visibleSize.height * 1/8);

	Menu* helpMenu = Menu::create(resumeMenu, nullptr);
	helpMenu->setPosition(Vec2::ZERO);
	this->addChild(helpMenu);

	Label* name1 = Label::create("Programming : \n        Noh SeokMin\n        Song WonSeok\n        Hwang JongSung", FILENAME_FONT_MAINMENU, 40);
	Label* name2 = Label::create("Design : \n        Hwang JongSung", FILENAME_FONT_MAINMENU, 40);

	name1->setAnchorPoint(Vec2(0, 0));
	name2->setAnchorPoint(Vec2(0, 0));
	//name3->setAnchorPoint(Vec2(0, 0));

	name1->setPosition(visibleSize.width / 12, visibleSize.height / 2 - 50);
	name2->setPosition(visibleSize.width / 12, visibleSize.height / 2 - 200);
	//name3->setPosition(visibleSize.width / 12, visibleSize.height / 2 - 150);

	this->addChild(name1);
	this->addChild(name2);
	//this->addChild(name3);
	return true;
}

void CreditLayer::Resume()
{
	Director::getInstance()->resume();
	this->removeFromParentAndCleanup(true);
}