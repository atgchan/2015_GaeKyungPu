#include "pch.h"
#include "UILayer.h"
#include "GameSceneManager.h"
#include "MainScene.h"

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
		return false;

	this->setName("UILayer");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	SetUIBar();

	//backLayer추가
	BackLayer = LayerColor::create(ccc4(0, 0, 0, 0), 300, 50);
	BackLayer->setZOrder(12);
	BackLayer->setAnchorPoint(Vec2(0, 0));
	BackLayer->setPosition(50, visibleSize.height - 70);

	SetFoodValue(GM->getPlayerDataByPlayerInfo(PLAYER_RED), GM->getPlayerDataByPlayerInfo(PLAYER_BLUE));

	this->addChild(BackLayer);
	
	Sprite* endButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_ENDTURN);
	Sprite* endButtonClicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_ENDTURN_CLICKED);

	MenuItemSprite* toggleTurn = MenuItemSprite::create(endButton, endButtonClicked, CC_CALLBACK_1(GameSceneManager::ToggleTurn, GameSceneManager::getInstance()));
	toggleTurn->setPosition(Vec2(visibleSize.width * 1 / 2, visibleSize.height - 50));

	Sprite* replayButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_OPTION_BUTTON);
	MenuItemSprite* replaybtn = MenuItemSprite::create(replayButton, replayButton, CC_CALLBACK_0(UILayer::ReturnToMenu, this));
	replaybtn->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 30));

	Menu* mainMenu = Menu::create(toggleTurn, replaybtn, NULL);
	mainMenu->setPosition(Vec2::ZERO);

	this->addChild(mainMenu);

	return true;
}

void UILayer::ReturnToMenu()
{
	cocos2d::Scene* mainMenu = MainScene::CreateScene();
	Director::getInstance()->replaceScene(mainMenu);
	Director::getInstance()->resume();
}

const void UILayer::SetFoodValue(PlayerData* pData1, PlayerData* pData2) const
{
	int pData1Food = pData1->getFood();
	int pData2Food = pData2->getFood();

	BackLayer->removeAllChildren();
	cocos2d::Label* p1Food = Label::createWithTTF(std::to_string(pData1Food), FILENAME_FONT_PIXEL, 50);
	cocos2d::Label* p2Food = Label::createWithTTF(std::to_string(pData2Food), FILENAME_FONT_PIXEL, 50);

	float width = BackLayer->getContentSize().width;
	float height = BackLayer->getContentSize().height;

	p1Food->setPosition(Vec2(100, height - 10));
	p2Food->setPosition(Vec2(100 + width / 2, height - 10));

	BackLayer->addChild(p1Food);
	BackLayer->addChild(p2Food);
}

void UILayer::SetUIBar()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* spriteBarArray[3];
	Sprite* spritecornerArray[4];
	for (int i = 0; i < 3; ++i)
	{
		spriteBarArray[i] = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_OUTER_BAR);
		spriteBarArray[i]->setAnchorPoint(Vec2(0, 0));
		this->addChild(spriteBarArray[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		spritecornerArray[i] = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_OUTER_ANCHOR);
		spritecornerArray[i]->setAnchorPoint(Vec2(0, 0));
		this->addChild(spritecornerArray[i]);
	}

	Sprite* grain = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_GRAIN_INDICATOR);
	grain->setAnchorPoint(Vec2(0, 0));
	grain->setPosition(90, visibleSize.height - 56);
	grain->setZOrder(11);
	this->addChild(grain);

	/*
	Sprite* flag = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_FLAG_RED);
	flag->setAnchorPoint(Vec2(0, 0));
	flag->setPosition(90, visibleSize.height - 202);
	flag->setZOrder(11);
	this->addChild(flag);
	*/

	spriteBarArray[0]->setPosition(0, 0);

	spriteBarArray[1]->setRotation(90);
	spriteBarArray[1]->setPosition(0, visibleSize.height);

	spriteBarArray[2]->setRotation(270);
	spriteBarArray[2]->setPosition(visibleSize.width, 0);

	spritecornerArray[0]->setPosition(0, 0);
	spritecornerArray[1]->setPosition(visibleSize.width-30, 0);
	spritecornerArray[2]->setPosition(0, visibleSize.height-30);
	spritecornerArray[3]->setPosition(visibleSize.width-30, visibleSize.height - 30);

	Sprite* UIBar = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_UPPER_BAR);
	UIBar->setAnchorPoint(Vec2(0, 0));
	UIBar->setPosition(0, visibleSize.height-70);
	this->addChild(UIBar);
}

void UILayer::SelectCharacter(Character* character)
{
	if (this->getChildByName("indicator"))
		this->removeChildByName("indicator");

	if (character)
	{
		float posX = character->getPositionX();
		float posY = character->getPositionY();

		Sprite* indicator = Sprite::createWithSpriteFrameName(FILENAME_IMG_MAIN_SELECT);
		indicator->setName("indicator");
		indicator->setAnchorPoint(Vec2(25, 0));
		indicator->setPosition(posX, posY + 120);

		this->addChild(indicator);
	}
}