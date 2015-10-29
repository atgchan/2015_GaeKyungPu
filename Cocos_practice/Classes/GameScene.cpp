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


//	Mouse Event
	auto clickListener = EventListenerMouse::create();
	
//���콺 �̺�Ʈ�� GameMaster�� �ٷ� �ѱ�� ���� �׽�Ʈ �ڵ�. ����� �Ѿ�ٸ� Ŭ���� Beep ���� �鸰��.
	clickListener->onMouseDown = CC_CALLBACK_1(GameMaster::mouseDownDispatcher, gmInstance);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	//tick�� �Ѱܺ���.
	this->schedule(schedule_selector(gmInstance->scheduleCallback),1.0,CC_REPEAT_FOREVER,3);
	return true;
}