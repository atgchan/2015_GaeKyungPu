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
	if (!Layer::init())
	{
		return false;
	}
	GameMaster* gmInstance = GameMaster::getInstance();

	gmInstance->InitializeGame();
	this->addChild(gmInstance->getNodes());
	


//	Mouse Event
	auto clickListener = EventListenerMouse::create();
	
//마우스 이벤트를 GameMaster로 바로 넘기기 위한 테스트 코드. 제대로 넘어갔다면 클릭시 Beep 음이 들린다.
	clickListener->onMouseDown = CC_CALLBACK_1(GameMaster::mouseDownDispatcher, gmInstance);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	return true;
}