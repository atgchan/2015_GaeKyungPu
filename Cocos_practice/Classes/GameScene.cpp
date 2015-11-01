#include "pch.h"
#include "GameScene.h"
#include "GameMaster.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init()) return false;

//���� �ʱ�ȭ block�� ��뱸ó�� ���̴� ���̹Ƿ� �ٲ� ���� x
	//GameMaster�� �ν��Ͻ� ����. GameScene �ȿ��� ��� ���δ�.
	GameMaster* gmInstance = GameMaster::getInstance();
	//���� �׸��� ���� ���� �ʱ� ������ �Ѵ�.
	gmInstance->InitializeGame();
	//���� �� ��� node���� �߰�.�Ʒ��� ���� ȣ���ϸ� �ȴ�.
	this->addChild(gmInstance->getNodes());
//�ʱ�ȭ block ��

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//auto toggleButton = Label::createWithTTF("toggleTurn", "fonts/Marker Felt.ttf", 24);
	//auto menu_toggle = MenuItemLabel::create(toggleButton, CC_CALLBACK_1(GameMaster::ChangePlayer, gmInstance));
	//menu_toggle->setPosition(Vec2(visibleSize.width*4/5, visibleSize.height*1/5));
	//
	//auto mainMenu = Menu::create(menu_toggle);
	//mainMenu->setPosition(Vec2::ZERO);
	//this->addChild(menu_toggle);

//	Mouse Event
	auto clickListener = EventListenerMouse::create();
	
//���콺 �̺�Ʈ�� GameMaster�� �ٷ� �ѱ�� ���� �׽�Ʈ �ڵ�. ����� �Ѿ�ٸ� Ŭ���� Beep ���� �鸰��.
	clickListener->onMouseDown = CC_CALLBACK_1(GameMaster::mouseDownDispatcher, gmInstance);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	//tick�� �Ѱܺ���.
	this->schedule(schedule_selector(GameScene::scheduleCallback));
	return true;
}

void GameScene::scheduleCallback(float delta)
{
	GameMaster::getInstance()->scheduleCallback(delta);
}
