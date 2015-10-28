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

	auto tilemap = TileMap::getInstance();
	tilemap->createMap();
	tilemap->setName("tilemap");
	this->addChild(tilemap);
	auto unitLayer = Layer::create();
	unitLayer->setName("unitLayer");
	this->addChild(unitLayer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto turn_ui = Label::createWithTTF("Turn Red", "fonts/Marker Felt.ttf", 40);
	turn_ui->setPosition(Vec2(visibleSize.width * 3 / 4, visibleSize.height * 1 / 4));
	turn_ui->setName("turn_ui");
	this->addChild(turn_ui);

//	Keyboard Event
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

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


}
