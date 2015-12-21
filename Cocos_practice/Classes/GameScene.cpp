#include "pch.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "EventManager.h"
#include "UILayer.h"
#include "SimpleAudioEngine.h"

GameScene::~GameScene()
{
	GameSceneManager* gm = GameSceneManager::getInstance();
	EventManager* em = EventManager::getInstance();
	delete gm;
	delete em;
}

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
	this->setName("GameScene");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCSprite * background = CCSprite::create(FILENAME_IMG_GAME_BACKGROUND);
	background->setScaleX((visibleSize.width / background->getContentSize().width) * 1);
	background->setScaleY((visibleSize.height / background->getContentSize().height) * 1);
	background->setAnchorPoint(Point(0, 0));
	this->addChild(background);
	
//이하 초기화 block은 상용구처럼 쓰이는 것이므로 바뀔 여지 x
	//GameMaster의 인스턴스 저장. GameScene 안에서 계속 쓰인다.
	GameSceneManager* gmInstance = GameSceneManager::getInstance();
	//맵을 그리는 등의 게임 초기 셋팅을 한다.
	gmInstance->InitializeGame();
	//게임 내 모든 node들을 추가.아래와 같이 호출하면 된다.
	this->addChild(gmInstance->getNodes());

//초기화 block 끝

//	UI 추가
	UILayer* layerUI = UILayer::create();

	this->addChild(layerUI);
//	Mouse Event
	EventListenerMouse* clickListener = EventListenerMouse::create();
	clickListener->onMouseDown = CC_CALLBACK_1(GameScene::MouseDownDispatcher,this);
	
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);
	_eventDispatcher->addEventListenerWithFixedPriority(clickListener, 99999);
//	Keyboard Event
	EventListenerKeyboard* keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(GameSceneManager::KeyReleasedDispatcher, gmInstance);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

//	tick을 넘겨본다.
	this->schedule(schedule_selector(GameScene::ScheduleCallback));

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FILENAME_SOUND_GAME_BGM,true);

	return true;
}

void GameScene::ScheduleCallback(float delta)
{
	RefreshFood();

	if (_GameIsEnd)
		GameSceneManager::getInstance()->EndGame();
	GameSceneManager::getInstance()->ScheduleCallback(delta);
}

void GameScene::MouseDownDispatcher(cocos2d::EventMouse* event)
{
	if (GameSceneManager::getInstance()->getIsInputAble() == false)
		return;
	GM->MouseDownDispatcher(event);
}

void GameScene::RefreshFood()
{
	(dynamic_cast<UILayer*>(getChildByName("UILayer")))->SetFoodValue(GM->getCurrentPlayerData());
}
