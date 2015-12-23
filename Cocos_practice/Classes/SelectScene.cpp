#include "pch.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "definition.h"

Scene* SelectScene::CreateScene()
{
	auto scene = Scene::create();
	auto layer = SelectScene::create();
	scene->addChild(layer);

	return scene;
}

bool SelectScene::init()
{
	if (!Layer::init())
		return false;

	this->setName("SelectScene");
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = CCSprite::create(FILENAME_IMG_MAIN_BACKGROUND);
	background->setScaleX((visibleSize.width / background->getContentSize().width) * 1);
	background->setScaleY((visibleSize.height / background->getContentSize().height) * 1);
	background->setAnchorPoint(Point(0,0));
	this->addChild(background);

	Label* title = Label::createWithTTF("color Select", FILENAME_FONT_MAINMENU, 80);
	title->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);
	this->addChild(title);

	Label* labelPrev = Label::createWithTTF("prev", FILENAME_FONT_MAINMENU, 40);
	Label* labelNext = Label::createWithTTF("next", FILENAME_FONT_MAINMENU, 40);

	Label* btnLabelExit = Label::createWithTTF("exit", FILENAME_FONT_MAINMENU, 80);

	MenuItemLabel* menu_prev = MenuItemLabel::create(labelPrev, CC_CALLBACK_1(SelectScene::MenuClickCallback, this));
	MenuItemLabel* menu_next = MenuItemLabel::create(labelNext, CC_CALLBACK_1(SelectScene::MenuCloseCallback, this));

	auto mainMenu = Menu::create(menu_prev, menu_next, nullptr);
	mainMenu->alignItemsVertically();
	menu_prev->setPosition(visibleSize.width/4, visibleSize.height/2);
	menu_next->setPosition(visibleSize.width *3/4, visibleSize.height / 2);
	mainMenu->setPosition(Vec2::ZERO);

	this->addChild(mainMenu);

//	Keyboard Event
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(SelectScene::OnKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(SelectScene::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FILENAME_SOUND_MAIN_BGM,true);

	return true;
}

void SelectScene::MenuClickCallback(cocos2d::Ref* pSender)
{
	cocos2d::Scene* gameScene = GameScene::CreateScene();
	Director::getInstance()->pushScene(gameScene);
}

void SelectScene::MenuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void SelectScene::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*auto target = event->getCurrentTarget()->getChildByName("cursor");
	Vec2 loc = target->getPosition();

	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;

	case EventKeyboard::KeyCode::KEY_ENTER:
		target->setPosition(loc.x -= 15, loc.y);
		break;
	}*/
}

void SelectScene::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	/*auto target = event->getCurrentTarget()->getChildByName("cursor");
	Vec2 loc = target->getPosition();

	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ENTER:
		target->setPosition(loc.x += 15, loc.y);
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		target->setPosition(loc.x, loc.y += 30);
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		target->setPosition(loc.x, loc.y -= 30);
		break;
	}*/
}
