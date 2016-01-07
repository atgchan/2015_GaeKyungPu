#include "pch.h"
#include "OptionLayer.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

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
	this->setZOrder(20);
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	//backLayer추가
	BackLayer = LayerColor::create(ccc4(0, 0, 0, 50), visibleSize.width, visibleSize.height);
	BackLayer->setAnchorPoint(Vec2(0, 0));
	BackLayer->setPosition(Vec2(0, 0));
	this->addChild(BackLayer);

	Sprite* optionWindow = Sprite::createWithSpriteFrameName(FILENAME_IMG_UI_OPTION_WINDOW);

	Sprite* resumeButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_RESUME);
	Sprite* resumeButton_clicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_RESUME_CLICKED);
	MenuItemSprite* sprResume = MenuItemSprite::create(resumeButton, resumeButton_clicked, CC_CALLBACK_0(OptionLayer::Resume, this));
	sprResume->setPosition(Vec2(visibleSize.width * 1 / 2, visibleSize.height * 3 / 5));

	Sprite* gotoMainButton = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_GOTO_MAIN);
	Sprite* gotoMainButton_clicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_GOTO_MAIN_CLICKED);
	MenuItemSprite* sprGotoMain = MenuItemSprite::create(gotoMainButton, gotoMainButton_clicked, CC_CALLBACK_0(OptionLayer::ReturnToMenu, this));
	sprGotoMain->setPosition(Vec2(visibleSize.width * 1 / 2, visibleSize.height * 3 / 5 - 120));

	Sprite* muteImage = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_MUTE);
	Sprite* muteImage_clicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_MUTE_CLICKED);
	Sprite* muteImage2 = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_MUTE);
	Sprite* muteImage_clicked2 = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_MUTE_CLICKED);
	MenuItemSprite* sprMute = MenuItemSprite::create(muteImage, muteImage_clicked);
	MenuItemSprite* sprMute_clicked = MenuItemSprite::create(muteImage_clicked2, muteImage2);
	MenuItemToggle* muteToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(OptionLayer::Mute, this), sprMute, sprMute_clicked, nullptr);
	muteToggle->setPosition(Vec2(visibleSize.width * 1 / 2, visibleSize.height * 3 / 5 - 240));

	optionWindow->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying() == false)
		muteToggle->setSelectedIndex(1);


	Menu* optionMenu = Menu::create(sprResume,sprGotoMain,muteToggle, nullptr);
	optionMenu->setPosition(Vec2::ZERO);
	this->addChild(optionWindow);
	this->addChild(optionMenu);

	return true;
}

void OptionLayer::ReturnToMenu()
{
	cocos2d::Scene* mainMenu = MainScene::CreateScene();
	Director::getInstance()->replaceScene(mainMenu);
	Director::getInstance()->resume();
}

void OptionLayer::Mute(Object *pSender)
{
	MenuItemToggle *item = static_cast<MenuItemToggle*>(pSender);
	int index = item->getSelectedIndex();
	if (index == 1)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	else
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FILENAME_SOUND_GAME_BGM, true);
}

void OptionLayer::Resume()
{
	Director::getInstance()->resume();
	static_cast<MenuItemToggle*>(GM->GetNodes()->getParent()->getChildByName("UILayer")->getChildByName("ingameMenu")->getChildByName("option_toggle"))->setSelectedIndex(0); ///# 더 좋은 방법이 없을까?
	this->removeFromParentAndCleanup(true);
	GM->setInputMode(false);
}