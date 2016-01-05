#include "pch.h"
#include "DefaultLayer.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

cocos2d::Scene* DefaultLayer::scene()
{
	cocos2d::Scene *scene = Scene::create();
	DefaultLayer* layer = DefaultLayer::create();

	scene->addChild(layer);
	return scene;
}

bool DefaultLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //투명하게
		return false;

	this->setName("howtoplay");
	this->setZOrder(20);
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	//backLayer추가
	BackLayer = LayerColor::create(ccc4(0, 0, 0, 50), visibleSize.width, visibleSize.height);
	BackLayer->setAnchorPoint(Vec2(0, 0));
	BackLayer->setPosition(Vec2(0, 0));
	this->addChild(BackLayer);

	Sprite* optionWindow = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_OPTION_WINDOW);
	optionWindow->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(optionWindow);

	float height = optionWindow->getContentSize().height;
	float width = optionWindow->getContentSize().width;

	Sprite* resumeButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_X);
	Sprite* resumeButton_clicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_X_CLICKED);
	MenuItemSprite* resumeMenu = MenuItemSprite::create(resumeButton, resumeButton_clicked, CC_CALLBACK_0(DefaultLayer::Resume, this));
	resumeMenu->setAnchorPoint(Vec2(1, 1));
	resumeMenu->setPosition(visibleSize.width / 2 + width / 2 - 50, visibleSize.height/2 + height/2 - 12);

	Menu* helpMenu = Menu::create(resumeMenu, nullptr);
	helpMenu->setPosition(Vec2::ZERO);
	this->addChild(helpMenu);

	return true;
}

void DefaultLayer::Resume()
{
	Director::getInstance()->resume();
	static_cast<MenuItemToggle*>(GM->getNodes()->getParent()->getChildByName("UILayer")->getChildByName("ingameMenu")->getChildByName("option_toggle"))->setSelectedIndex(0); ///# 더 좋은 방법이 없을까?
	this->removeFromParentAndCleanup(true);
	GM->setInputMode(false);
}