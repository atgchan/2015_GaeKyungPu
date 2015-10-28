#include "pch.h"
#include "GameScene.h"
#include "TileMap.h"

int GameScene::turn = 0;

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
	/*
	auto tilemap = TileMap::getInstance();
	tilemap->createMap();
	tilemap->setName("tilemap");
	this->addChild(tilemap);
	auto unitLayer = Layer::create();
	unitLayer->setName("unitLayer");
	this->addChild(unitLayer);
	*/
//	Mouse Event
	auto clickListener = EventListenerMouse::create();
	clickListener->onMouseDown = CC_CALLBACK_1(GameScene::eventByClick, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	return true;
}

void GameScene::eventByClick(Event* event)
{
	EventMouse* mouseEvent = nullptr;
	mouseEvent = dynamic_cast<EventMouse*>(event);
	Beep(1000, 100);

}
