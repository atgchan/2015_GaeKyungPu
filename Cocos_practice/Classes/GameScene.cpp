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

//이하 초기화 block은 상용구처럼 쓰이는 것이므로 바뀔 여지 x
	//GameMaster의 인스턴스 저장. GameScene 안에서 계속 쓰인다.
	GameMaster* gmInstance = GameMaster::getInstance();
	//맵을 그리는 등의 게임 초기 셋팅을 한다.
	gmInstance->InitializeGame();
	//게임 내 모든 node들을 추가.아래와 같이 호출하면 된다.
	this->addChild(gmInstance->getNodes());
//초기화 block 끝

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
	
//마우스 이벤트를 GameMaster로 바로 넘기기 위한 테스트 코드. 제대로 넘어갔다면 클릭시 Beep 음이 들린다.
	clickListener->onMouseDown = CC_CALLBACK_1(GameMaster::mouseDownDispatcher, gmInstance);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	//tick을 넘겨본다.
	this->schedule(schedule_selector(GameScene::scheduleCallback));
	return true;
}

void GameScene::scheduleCallback(float delta)
{
	GameMaster::getInstance()->scheduleCallback(delta);
}
