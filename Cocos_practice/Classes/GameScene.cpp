#include "pch.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "UILayer.h"

Scene* GameScene::CreateScene()
{
	Scene* scene = Scene::create();
	GameScene* layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init()) return false;
	_GameIsEnd = false;
//이하 초기화 block은 상용구처럼 쓰이는 것이므로 바뀔 여지 x
	//GameMaster의 인스턴스 저장. GameScene 안에서 계속 쓰인다.
	GameSceneManager* gmInstance = GameSceneManager::getInstance();
	//맵을 그리는 등의 게임 초기 셋팅을 한다.
	gmInstance->InitializeGame();
	//게임 내 모든 node들을 추가.아래와 같이 호출하면 된다.
	this->addChild(gmInstance->getNodes());

//초기화 block 끝

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Label* toggleButton = Label::createWithTTF("Toggle Turn", "fonts/upheavtt.ttf", 50);
	MenuItemLabel* menu_toggle = MenuItemLabel::create(toggleButton, CC_CALLBACK_1(GameSceneManager::ToggleTurn, gmInstance));
	menu_toggle->setPosition(Vec2(visibleSize.width * 4 / 5, visibleSize.height * 1 / 5));

	Menu* mainMenu = Menu::create(menu_toggle, NULL);
	mainMenu->setPosition(Vec2::ZERO);	

	UILayer* layerUI = UILayer::create();
	layerUI->setName("ui_layer");

	this->addChild(mainMenu);
	this->addChild(layerUI);

//	Mouse Event
	EventListenerMouse* clickListener = EventListenerMouse::create();
	clickListener->onMouseDown = CC_CALLBACK_1(GameSceneManager::MouseDownDispatcher, gmInstance);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

//	Keyboard Event
	EventListenerKeyboard* keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(GameSceneManager::KeyReleasedDispatcher, gmInstance);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

//	tick을 넘겨본다.
	this->schedule(schedule_selector(GameScene::ScheduleCallback));
	return true;
}

void GameScene::ScheduleCallback(float delta)
{
	RefreshFood();
	if (_GameIsEnd)
		GameSceneManager::getInstance()->EndGame();
	GameSceneManager::getInstance()->ScheduleCallback(delta);
}

void GameScene::RefreshFood()
{
	(dynamic_cast<UILayer*>(getChildByName("ui_layer")))->SetFoodValue(GM->getPlayerDataByPlayerInfo(PLAYER_RED), GM->getPlayerDataByPlayerInfo(PLAYER_BLUE));
}