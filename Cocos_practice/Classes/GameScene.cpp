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
	CCSprite * background = CCSprite::create("Background/Total_War_Rome_2_Roman_Soldier_Sword_warrior_warriors_fantasy_battle_1920x1080.jpg");
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
	layerUI->setName("ui_layer");

	this->addChild(layerUI);

//	Mouse Event
	EventListenerMouse* clickListener = EventListenerMouse::create();
	clickListener->onMouseDown = CC_CALLBACK_1(GameSceneManager::MouseDownDispatcher, gmInstance);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

//	Keyboard Event
	EventListenerKeyboard* keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(GameSceneManager::KeyReleasedDispatcher, gmInstance);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

//	tick을 넘겨본다.
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
	for (int i = 0; i < 2; i++)
	{
		std::list<std::shared_ptr<Character>>* list = GM->getPlayerDataByPlayerInfo(PlayerInfo(i))->getCharacterList();
		for (std::shared_ptr<Character> iter : *list)
		{
			iter->UpdateAttackPowerSprite();
		}
	}
}

void GameScene::RefreshFood()
{
	(dynamic_cast<UILayer*>(getChildByName("ui_layer")))->SetFoodValue(GM->getPlayerDataByPlayerInfo(PLAYER_RED), GM->getPlayerDataByPlayerInfo(PLAYER_BLUE));
}
