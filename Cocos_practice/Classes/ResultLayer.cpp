#include "pch.h"
#include "ResultLayer.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "MainScene.h"

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
	this->addChild(BackLayer);

	Sprite* resultPage = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_RESULT_WINDOW);
	Sprite* replayButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_GOTO_MAIN);
	Sprite* replayButtonClicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_GOTO_MAIN_CLICKED);

	MenuItemSprite* replaybtn = MenuItemSprite::create(replayButton, replayButtonClicked, CC_CALLBACK_0(ResultLayer::ReturnToMenu, this));
	replaybtn->setPosition(Vec2(visibleSize.width * 1 / 2, visibleSize.height* 2/5 ));
	resultPage->setPosition(visibleSize.width/2, visibleSize.height/2);

	Menu* resultMenu = Menu::create(replaybtn, NULL);
	resultMenu->setPosition(Vec2::ZERO);
	this->addChild(resultPage);
	this->addChild(resultMenu);

//#	resultTable SELECT results
//#	print top 10 result

	return true;
}

void ResultLayer::ReturnToMenu()
{
	cocos2d::Scene* mainMenu = MainScene::CreateScene();
	Director::getInstance()->replaceScene(mainMenu);
	Director::getInstance()->resume();
}

void ResultLayer::SetValue(PlayerData* pData1, PlayerData* pData2)
{

}