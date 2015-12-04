#include "pch.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "UILayer.h"
#include "SimpleAudioEngine.h"

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


	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCSprite * background = CCSprite::create("Background/ocean water.jpg");
	background->setScaleX((visibleSize.width / background->getContentSize().width) * 1);
	background->setScaleY((visibleSize.height / background->getContentSize().height) * 1);
	background->setAnchorPoint(Point(0, 0));
	this->addChild(background);

//���� �ʱ�ȭ block�� ��뱸ó�� ���̴� ���̹Ƿ� �ٲ� ���� x
	//GameMaster�� �ν��Ͻ� ����. GameScene �ȿ��� ��� ���δ�.
	GameSceneManager* gmInstance = GameSceneManager::getInstance();
	//���� �׸��� ���� ���� �ʱ� ������ �Ѵ�.
	gmInstance->InitializeGame();
	//���� �� ��� node���� �߰�.�Ʒ��� ���� ȣ���ϸ� �ȴ�.
	this->addChild(gmInstance->getNodes());

//�ʱ�ȭ block ��

//	UI �߰�
	UILayer* layerUI = UILayer::create();
	layerUI->setName("ui_layer");

	this->addChild(layerUI);

//	Mouse Event
	EventListenerMouse* clickListener = EventListenerMouse::create();
	clickListener->onMouseDown = CC_CALLBACK_1(GameScene::MouseDownDispatcher,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

//	Keyboard Event
	EventListenerKeyboard* keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(GameSceneManager::KeyReleasedDispatcher, gmInstance);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

//	tick�� �Ѱܺ���.
	this->schedule(schedule_selector(GameScene::ScheduleCallback));

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/battle.mp3",true);

	return true;
}

void GameScene::ScheduleCallback(float delta)
{
	RefreshFood();
	RefreshAttackPower();

	if (_GameIsEnd)
		GameSceneManager::getInstance()->EndGame();
	GameSceneManager::getInstance()->ScheduleCallback(delta);
}

void GameScene::RefreshAttackPower()
{
	for (int i = 0; i < NUM_OF_PLAYER; i++)
	{
		std::list<Character*>* list = GM->getPlayerDataByPlayerInfo(PlayerInfo(i))->getCharacterList();
		for (Character* iter : *list)
		{
			iter->UpdateAttackPowerSprite();
		}
	}
}

void GameScene::MouseDownDispatcher(cocos2d::EventMouse* event)
{
	if (GM->getIsInputAble() == false)
		return;
	GM->MouseDownDispatcher(event);
}

void GameScene::RefreshFood()
{
	(dynamic_cast<UILayer*>(getChildByName("ui_layer")))->SetFoodValue(GM->getPlayerDataByPlayerInfo(PLAYER_RED), GM->getPlayerDataByPlayerInfo(PLAYER_BLUE));
}
