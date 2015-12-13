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
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //�����ϰ�
		return false;
	this->setName("OptionLayer");
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	//backLayer�߰�
	BackLayer = LayerColor::create(ccc4(0, 0, 0, 50), visibleSize.width, visibleSize.height);
	BackLayer->setAnchorPoint(Vec2(0, 0));
	BackLayer->setPosition(Vec2(0, 0));
	this->addChild(BackLayer);

	Sprite* resultPage = Sprite::createWithSpriteFrameName("end_game.png");
	Sprite* replayButton = Sprite::createWithSpriteFrameName("replay.png");
	Sprite* replayButtonClicked = Sprite::createWithSpriteFrameName("replay_clicked.png");

	MenuItemSprite* replaybtn = MenuItemSprite::create(replayButton, replayButtonClicked, CC_CALLBACK_0(OptionLayer::ReturnToMenu, this));
	replaybtn->setPosition(Vec2(visibleSize.width * 1 / 2, visibleSize.height * 3/5 ));
	resultPage->setPosition(visibleSize.width/2, visibleSize.height/2);

	Menu* resultMenu = Menu::create(replaybtn, NULL);
	resultMenu->setPosition(Vec2::ZERO);
	this->addChild(resultPage);
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
