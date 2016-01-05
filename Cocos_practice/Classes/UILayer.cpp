#include "pch.h"
#include "UILayer.h"
#include "GameSceneManager.h"
#include "MainScene.h"
#include "OptionLayer.h"
#include "DefaultLayer.h"

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

	SetFoodValue(GM->getCurrentPlayerData());

	this->addChild(BackLayer);

	Sprite* endButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_ENDTURN);
	Sprite* endButtonClicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_ENDTURN_CLICKED);

	MenuItemSprite* toggleTurn = MenuItemSprite::create(endButton, endButtonClicked, CC_CALLBACK_0(UILayer::toggleTurn, this));
	toggleTurn->setPosition(Vec2(visibleSize.width * 1 / 2, visibleSize.height - 50));

	Sprite* optionButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_OPTION);
	Sprite* optionButton_clicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_OPTION_CLICKED);
	Sprite* optionButton2 = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_OPTION);
	Sprite* optionButton_clicked2 = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_OPTION_CLICKED);

	MenuItemSprite* sprOption = MenuItemSprite::create(optionButton, optionButton_clicked);
	MenuItemSprite* sprOption_clicked = MenuItemSprite::create(optionButton_clicked2, optionButton2);
	MenuItemToggle* optionToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(UILayer::ShowOptionWindow, this), sprOption, sprOption_clicked, nullptr);
	optionToggle->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 33));
	optionToggle->setName("option_toggle");

	Sprite* helpButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_HELP);
	Sprite* helpButton_clicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_HELP_CLICKED);
	MenuItemSprite* howToPlay = MenuItemSprite::create(helpButton, helpButton_clicked, CC_CALLBACK_0(UILayer::ShowHowToPlay, this));
	howToPlay->setPosition(Vec2(visibleSize.width - 160, visibleSize.height - 33));

	Menu* ingameMenu = Menu::create(toggleTurn, optionToggle, howToPlay, NULL);
	ingameMenu->setPosition(Vec2::ZERO);
	ingameMenu->setName("ingameMenu");

	_TurnLabel = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_RED);
	_TurnLabel->setPosition(Vec2(80, visibleSize.height - 55));
	_TurnLabel->setZOrder(12);
	_TurnLabel->setAnchorPoint(Vec2(0, 0));
	this->addChild(_TurnLabel);
	this->addChild(ingameMenu);

	return true;
}

void UILayer::ShowHowToPlay()
{
	GM->setInputMode(false);
	Director::getInstance()->pause();
	DefaultLayer* help = DefaultLayer::create();
	GM->AddChild(help);
}

void UILayer::ShowOptionWindow(Object *pSender)
{
	MenuItemToggle *item = static_cast<MenuItemToggle*>(pSender);
	if (item->getSelectedIndex() == 0)
	{
		item->setSelectedIndex(1);
		return;
	}
	GM->setInputMode(false);
	Director::getInstance()->pause();
	OptionLayer* option = OptionLayer::create();
	GM->AddChild(option);
}

const void UILayer::SetFoodValue(PlayerData* currentPlayerData) const
{
	int currentFood = currentPlayerData->getFood();

	BackLayer->removeAllChildren();
	cocos2d::Label* currentFoodLabel = Label::createWithTTF(std::to_string(currentFood), FILENAME_FONT_PIXEL, 50);

	float width = BackLayer->getContentSize().width;
	float height = BackLayer->getContentSize().height;

	currentFoodLabel->setPosition(Vec2(100 + width / 2, height - 10));

	BackLayer->addChild(currentFoodLabel);
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

	spritecornerArray[0] = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_LD_ANCHOR);
	spritecornerArray[1] = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_LU_ANCHOR);
	spritecornerArray[2] = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_RU_ANCHOR);
	spritecornerArray[3] = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_RD_ANCHOR);

	for (int i = 0; i < 4; ++i)
	{
		spritecornerArray[i]->setAnchorPoint(Vec2(0, 0));
		this->addChild(spritecornerArray[i]);
	}

	Sprite* grain = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_GRAIN_INDICATOR);
	grain->setAnchorPoint(Vec2(0, 0));
	grain->setPosition(240, visibleSize.height - 58);
	grain->setZOrder(11);
	this->addChild(grain);

	spriteBarArray[0]->setPosition(0, 0);
	spriteBarArray[0]->setZOrder(15);

	spriteBarArray[1]->setRotation(90);
	spriteBarArray[1]->setPosition(0, visibleSize.height);

	spriteBarArray[2]->setRotation(270);
	spriteBarArray[2]->setPosition(visibleSize.width, 0);

	spritecornerArray[0]->setPosition(0, 15);
	spritecornerArray[1]->setPosition(0, visibleSize.height - 85);
	spritecornerArray[2]->setPosition(visibleSize.width - 45, visibleSize.height - 85);
	spritecornerArray[3]->setPosition(visibleSize.width - 45, 15);

	Sprite* UIBar = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_UPPER_BAR);
	UIBar->setAnchorPoint(Vec2(0, 0));
	UIBar->setPosition(0, visibleSize.height - 70);
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

void UILayer::toggleTurn()
{
	if (GM->getIsInputAble() == false)
		return;

	PlayerInfo pInfo = GM->getCurrentPlayer();
	std::string usrn = "";
	if (pInfo == PLAYER_RED)
		usrn = FILENAME_IMG_UI_BLUE;
	else
		usrn = FILENAME_IMG_UI_RED;
	_TurnLabel->setSpriteFrame(usrn);
	GM->ToggleTurn();
	GM->setInputMode(true);
}