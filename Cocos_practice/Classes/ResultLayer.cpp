#include "pch.h"
#include "ResultLayer.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "MainScene.h"
#include "Odbc.h"
#include "ui\UIEditBox\UIEditBox.h"

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
	this->setName("ResultLayer");
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	//backLayer추가
	BackLayer = LayerColor::create(ccc4(0, 0, 0, 50), visibleSize.width, visibleSize.height);
	BackLayer->setAnchorPoint(Vec2(0, 0));
	BackLayer->setPosition(Vec2(0, 0));
	addChild(BackLayer);

	Sprite* resultPage = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_RESULT_WINDOW);

	Sprite* replayButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_GOTO_MAIN);
	Sprite* replayButtonClicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_GOTO_MAIN_CLICKED);

	Sprite* recentPlayButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_RECENTPLAY);
	Sprite* recentPlayButtonClicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_RECENTPLAY_CLICKED);

	Sprite* topPlayerButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_TOPPLAYER);
	Sprite* topPlayerButtonClicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_TOPPLAYER_CLICKED);

	Sprite* leastTurnButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_LEASTTURN);
	Sprite* leastTurnButtonClicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_LEASTTURN_CLICKED);

	MenuItemSprite* replaybtn = MenuItemSprite::create(replayButton, replayButtonClicked, CC_CALLBACK_0(ResultLayer::ReturnToMenu, this));
	replaybtn->setPosition(Vec2(visibleSize.width * 3 / 5, visibleSize.height* 2/3 - 40));
	resultPage->setPosition(visibleSize.width/2, visibleSize.height/2);

/*
	cocos2d::Size editSize(200.0f, 50.0f);
	cocos2d::ui::EditBox* _NumToGet = ui::EditBox::create(editSize, ui::Scale9Sprite::create(FILENAME_IMG_UI_INPUT_BOX));
	_NumToGet->setName("numtoget");
	_NumToGet->setFontSize(20);
	_NumToGet->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
	_NumToGet->setPlaceHolder("1 ~ 10");
	_NumToGet->setMaxLength(2);
	_NumToGet->setPosition(Vec2(visibleSize.width * 3 / 4 - 50, visibleSize.height * 4 / 5 + 50));
	_NumToGet->setZOrder(100);
	addChild(_NumToGet);

	int number = atoi(_NumToGet->getText());

	if (number < 1)
		number = 1;
	else if (number > 10)
		number = 10;
*/

	MenuItemSprite* ShowRecentListBtn = MenuItemSprite::create(recentPlayButton, recentPlayButtonClicked, CC_CALLBACK_0(ResultLayer::ShowRecentGame, this, 10));
	ShowRecentListBtn->setPosition(Vec2(visibleSize.width * 1 / 4 + 50, visibleSize.height * 4 / 5 -65));

	MenuItemSprite* ShowTopPlayerListBtn = MenuItemSprite::create(topPlayerButton, topPlayerButtonClicked, CC_CALLBACK_0(ResultLayer::ShowTopPlayer, this, 10));
	ShowTopPlayerListBtn->setPosition(Vec2(visibleSize.width * 1 / 2, visibleSize.height * 4 / 5 - 65));

	MenuItemSprite* ShowLeastTurnListBtn = MenuItemSprite::create(leastTurnButton, leastTurnButtonClicked, CC_CALLBACK_0(ResultLayer::ShowLeastTurn, this, 10));
	ShowLeastTurnListBtn->setPosition(Vec2(visibleSize.width * 3 / 4 - 50, visibleSize.height * 4 / 5 - 65));

	Menu* resultMenu = Menu::create(replaybtn, ShowRecentListBtn, ShowTopPlayerListBtn, ShowLeastTurnListBtn, NULL);
	resultMenu->setPosition(Vec2::ZERO);
	addChild(resultPage);
	addChild(resultMenu);

	ShowRecentGame(10);

	return true;
}

void ResultLayer::ReturnToMenu()
{
	cocos2d::Scene* mainMenu = MainScene::CreateScene();
	Director::getInstance()->replaceScene(mainMenu);
	Director::getInstance()->resume();
}

void ResultLayer::ShowRecentGame(int numOfGet)
{
	Odbc* mysql = Odbc::GetInstance();
	if (mysql->IsConnect() == false)
		mysql->Connect(L"me", L"testudo", L"next!!@@##$$");

	while (getChildByName("sqlresult"))
		removeChildByName("sqlresult");

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	std::string result = "Recent Game\nwinner loser map total_turn\n";
	result += mysql->GetRecentResult(numOfGet);

	cocos2d::Label* labelResult = cocos2d::Label::create(result, FILENAME_FONT_PIXEL, 30);
	labelResult->setName("sqlresult");
	labelResult->setAnchorPoint(Vec2(0.5, 1));
	labelResult->setPosition(visibleSize.width / 2, visibleSize.height * 2 / 3 - 70);

	addChild(labelResult);
}

void ResultLayer::ShowTopPlayer(int numOfGet)
{
	Odbc* mysql = Odbc::GetInstance();
	if (mysql->IsConnect() == false)
		mysql->Connect(L"me", L"testudo", L"next!!@@##$$");

	while (getChildByName("sqlresult"))
		removeChildByName("sqlresult");

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	std::string result = "Top Player\nrating total_play winRate name\n";
	result += mysql->GetTopPlayerList(numOfGet);

	cocos2d::Label* labelResult = cocos2d::Label::create(result, FILENAME_FONT_PIXEL, 30);
	labelResult->setName("sqlresult");
	labelResult->setAnchorPoint(Vec2(0.5, 1));
	labelResult->setPosition(visibleSize.width / 2, visibleSize.height * 2 / 3 - 70);

	addChild(labelResult);
}

void ResultLayer::ShowLeastTurn(int numOfGet)
{
	Odbc* mysql = Odbc::GetInstance();
	if (mysql->IsConnect() == false)
		mysql->Connect(L"me", L"testudo", L"next!!@@##$$");

	while (getChildByName("sqlresult"))
		removeChildByName("sqlresult");

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	std::string result = "Recent Game\nwinner loser map total_turn\n";
	result += mysql->GetResultByTurn(numOfGet);

	cocos2d::Label* labelResult = cocos2d::Label::create(result, FILENAME_FONT_PIXEL, 30);
	labelResult->setName("sqlresult");
	labelResult->setAnchorPoint(Vec2(0.5, 1));
	labelResult->setPosition(visibleSize.width / 2, visibleSize.height * 2 / 3 - 70);

	addChild(labelResult);
}