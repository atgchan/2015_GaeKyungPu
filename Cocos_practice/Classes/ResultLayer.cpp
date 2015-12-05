#include "pch.h"
#include "ResultLayer.h"

cocos2d::Scene* ResultLayer::scene()
{
	cocos2d::Scene *scene = Scene::create();
	ResultLayer* layer = ResultLayer::create();

	scene->addChild(layer);
	return scene;
}

bool ResultLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //투명하게
		return false;

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	//backLayer추가
	BackLayer = LayerColor::create(ccc4(0, 0, 0, 50), visibleSize.width, visibleSize.height);
	BackLayer->setAnchorPoint(Vec2(0, 0));
	BackLayer->setPosition(Vec2(0, 0));
	this->addChild(BackLayer);

	Sprite* resultPage = Sprite::createWithSpriteFrameName("end_game.png");
	Sprite* replayButton = Sprite::createWithSpriteFrameName("replay.png");
	Sprite* replayButtonClicked = Sprite::createWithSpriteFrameName("replay_clicked.png");

	resultPage->setAnchorPoint(Vec2(400, 300));
	//resultPage->setPosition(visibleSize.width/2, visibleSize.);

	this->addChild(PopUpLayer);

	return true;
}

void ResultLayer::SetValue(PlayerData* pData1, PlayerData* pData2)
{

}