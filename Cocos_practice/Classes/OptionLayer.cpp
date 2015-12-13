#include "pch.h"
#include "OptionLayer.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "MainScene.h"

cocos2d::Scene* OptionLayer::scene()
{
	cocos2d::Scene *scene = Scene::create();
	OptionLayer* layer = OptionLayer::create();

	scene->addChild(layer);
	return scene;
}

bool OptionLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //투명하게
		return false;
	this->setName("OptionLayer");
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	//backLayer추가
	BackLayer = LayerColor::create(ccc4(0, 0, 0, 50), visibleSize.width, visibleSize.height);
	BackLayer->setAnchorPoint(Vec2(0, 0));
	BackLayer->setPosition(Vec2(0, 0));
	this->addChild(BackLayer);

	Sprite* resultPage = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_OPTION_WINDOW);
	Sprite* replayButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_REPLAY);
	Sprite* replayButtonClicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_REPLAY_CLICKED);

	MenuItemSprite* replaybtn = MenuItemSprite::create(replayButton, replayButtonClicked, CC_CALLBACK_0(OptionLayer::ReturnToMenu, this));
	replaybtn->setPosition(Vec2(visibleSize.width * 1 / 2, visibleSize.height * 3/5 ));
	optionWindow->setPosition(visibleSize.width/2, visibleSize.height/2);

	Menu* resultMenu = Menu::create(replaybtn, NULL);
	resultMenu->setPosition(Vec2::ZERO);
	this->addChild(optionWindow);
	this->addChild(resultMenu);

	return true;
}

void OptionLayer::ReturnToMenu()
{
	cocos2d::Scene* mainMenu = MainScene::CreateScene();
	Director::getInstance()->replaceScene(mainMenu);
	Director::getInstance()->resume();
}

void OptionLayer::Mute()
{

}

void OptionLayer::Restart()
{

}
