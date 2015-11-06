#include "pch.h"
#include "PopLayer.h"

//using namespace cocos2d;

cocos2d::Scene* PopLayer::scene()
{
	cocos2d::Scene *scene = Scene::create();
	PopLayer *layer = PopLayer::create();

	scene->addChild(layer);
	return scene;
}

bool PopLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //투명하게
	{
		return false;
	}

	//cocos2d::String* popParam = CCString::create("0");
	//CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //노티피케이션 보내기

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	//메뉴추가
	CCMenuItemFont* pMenuItem = CCMenuItemFont::create("close", this,
		menu_selector(PopLayer::doClose));
	pMenuItem->setColor(ccc3(0, 0, 0));
	CCMenu* pMenu2 = CCMenu::create(pMenuItem, NULL);
	pMenu2->setPosition(ccp(240, 100));
	this->addChild(pMenu2, 10);

	//backLayer추가
	backLayer = LayerColor::create(ccc4(0, 0, 0, 50), visibleSize.width, visibleSize.height);
	backLayer->setAnchorPoint(Vec2(0, 0));
	backLayer->setPosition(Vec2(0, 0));
	this->addChild(backLayer);

	//popUpLayer추가
	popUpLayer = LayerColor::create(ccc4(255, 0, 0, 255), 250, 150);
	popUpLayer->setAnchorPoint(Vec2(0, 0));
	popUpLayer->setPosition( Vec2((visibleSize.width - popUpLayer->getContentSize().width) / 2,	(visibleSize.height - popUpLayer->getContentSize().height) / 2 ));
	this->addChild(popUpLayer);

	return true;
}


void PopLayer::doClose(CCObject* pSender)
{
	//CCString* popParam = CCString::create("1");
	//CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //노티피케이션 보내기
	//팝업창 제거
	this->removeFromParentAndCleanup(true);
}