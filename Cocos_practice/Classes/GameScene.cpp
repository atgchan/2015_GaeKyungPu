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
	
//���콺 �̺�Ʈ�� GameMaster�� �ٷ� �ѱ�� ���� �׽�Ʈ �ڵ�. ����� �Ѿ�ٸ� Ŭ���� Beep ���� �鸰��.
	clickListener->onMouseDown = CC_CALLBACK_1(GameMaster::mouseDownDispatcher, gmInstance);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	return true;
}