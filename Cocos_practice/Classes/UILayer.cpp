#include "pch.h"
#include "UILayer.h"
#include "GameSceneManager.h"

cocos2d::Scene* UILayer::scene()
{
	cocos2d::Scene *scene = Scene::create();
	UILayer* layer = UILayer::create();

	scene->addChild(layer);
	return scene;
}

bool UILayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //투명하게
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//backLayer추가
	BackLayer = LayerColor::create(ccc4(0, 0, 0, 0), 300, 50);
	BackLayer->setAnchorPoint(Vec2(0, 0));
	BackLayer->setPosition(50, visibleSize.height - 100);

	SetFoodValue(GM->getPlayerDataByPlayerInfo(PLAYER_RED), GM->getPlayerDataByPlayerInfo(PLAYER_BLUE));

	this->addChild(BackLayer);
	
	SetUIBar();

	return true;
}

const void UILayer::SetFoodValue(PlayerData* pData1, PlayerData* pData2) const
{
	int pData1Food = pData1->getFood();
	int pData2Food = pData2->getFood();

	BackLayer->removeAllChildren();

	auto p1Food = Label::createWithTTF(std::to_string(pData1Food), "fonts/upheavtt.ttf", 50);
	auto p2Food = Label::createWithTTF(std::to_string(pData2Food), "fonts/upheavtt.ttf", 50);

	float width = BackLayer->getContentSize().width;
	float height = BackLayer->getContentSize().height;

	p1Food->setPosition(Vec2(100, height - 20));
	p2Food->setPosition(Vec2(100 + width / 2, height - 20));

	BackLayer->addChild(p1Food);
	BackLayer->addChild(p2Food);
}


void UILayer::SetUIBar()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* spriteBarArray[4];
	for (int i = 0; i < 4; ++i)
	{
		spriteBarArray[i] = Sprite::createWithSpriteFrameName("bar.png");
		spriteBarArray[i]->setAnchorPoint(Vec2(0, 0));
		this->addChild(spriteBarArray[i]);
	}

	Sprite* grain = Sprite::createWithSpriteFrameName("grain.png");
	grain->setPosition(50, visibleSize.height - 50);
	this->addChild(grain);

	spriteBarArray[0]->setPosition(0, 0);

	spriteBarArray[1]->setRotation(90);
	spriteBarArray[1]->setPosition(0, visibleSize.height);

	spriteBarArray[2]->setRotation(180);
	spriteBarArray[2]->setPosition(visibleSize.width, visibleSize.height);

	spriteBarArray[3]->setRotation(270);
	spriteBarArray[3]->setPosition(visibleSize.width, 0);
}