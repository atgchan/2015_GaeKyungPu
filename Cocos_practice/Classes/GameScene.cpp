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

	auto map = TileMap::create();
	this->addChild(map);

	auto unitLayer = Layer::create();
	unitLayer->setName("unitLayer");
	this->addChild(unitLayer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label_title = Label::createWithTTF("In Game Scene!!!", "fonts/Marker Felt.ttf", 40);
	label_title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));

	this->addChild(label_title);

//	Keyboard Event
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

//	Mouse Event
	auto clickListener = EventListenerMouse::create();
	clickListener->onMouseDown = CC_CALLBACK_1(GameScene::setUnitByClick, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	return true;
}

void GameScene::setUnitByClick(Event* event)
{
	EventMouse* mouseEvent = nullptr;
	mouseEvent = dynamic_cast<EventMouse*>(event);
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto unit_layer = event->getCurrentTarget()->getChildByName("unitLayer");

	if ( mouseEvent->getMouseButton() == 0 )
	{
		float xPos = mouseEvent->getCursorX();
		float yPos = mouseEvent->getCursorY();

		auto button = mouseEvent->getMouseButton();
		auto unit_spear = Sprite::create("spear_red_01.png");
		unit_spear->setName("unit");

//	일단 turn 표시를 정수로... 0인 경우 red, 1인 경우 blue
		if (turn == 1)
		{
			unit_spear = Sprite::create("spear_blue_01.png");
		}

		unit_spear->setPosition(Vec2(origin.x + xPos, visibleSize.height + yPos));
		unit_layer->addChild(unit_spear);
	}

	if ( mouseEvent->getMouseButton() == 1 )
	{
		auto point = mouseEvent->getLocationInView();
		auto children = unit_layer->getChildren();

		for (auto iter = children.begin(); iter != children.end(); ++iter)
		{
			if ((*iter)->getName() != "unit")
			{
				continue;
			}

			auto sprite = dynamic_cast<Sprite*>(*iter);
			if (sprite->boundingBox().containsPoint(Vec2(point.x, visibleSize.height + point.y)))
			{
				unit_layer->removeChild(sprite);
			}
		}
	}
}

void GameScene::delUnitByClick(Event* event)
{

}

void GameScene::rotateUnitByClick(Event* event)
{

}

void GameScene::menuClickCallback(cocos2d::Ref* pSender)
{
	
}

void GameScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;

	case EventKeyboard::KeyCode::KEY_ENTER:

		break;
	}
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ENTER:
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		break;
	}
}