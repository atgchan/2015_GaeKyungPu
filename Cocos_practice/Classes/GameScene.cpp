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
//���� �ʱ�ȭ block�� ��뱸ó�� ���̴� ���̹Ƿ� �ٲ� ���� x
	//GameMaster�� �ν��Ͻ� ����. GameScene �ȿ��� ��� ���δ�.
	GameSceneManager* gmInstance = GameSceneManager::getInstance();
	//���� �׸��� ���� ���� �ʱ� ������ �Ѵ�.
	gmInstance->InitializeGame();
	//���� �� ��� node���� �߰�.�Ʒ��� ���� ȣ���ϸ� �ȴ�.
	this->addChild(gmInstance->getNodes());

//�ʱ�ȭ block ��

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

//	tick�� �Ѱܺ���.
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