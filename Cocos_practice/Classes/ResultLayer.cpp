#include "pch.h"
#include "ResultLayer.h"

cocos2d::Scene* ResultLayer::scene()
{
	cocos2d::Scene *scene = Scene::create();
	ResultLayer* layer = ResultLayer::create();

	scene->addChild(layer);
	return scene;
}

bool ResultLayer::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //�����ϰ�
	{
		return false;
	}

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	//backLayer�߰�
	BackLayer = LayerColor::create(ccc4(0, 0, 0, 50), visibleSize.width, visibleSize.height);
	BackLayer->setAnchorPoint(Vec2(0, 0));
	BackLayer->setPosition(Vec2(0, 0));
	this->addChild(BackLayer);

	//popUpLayer�߰�
	PopUpLayer = LayerColor::create(ccc4(92, 92, 92, 255), visibleSize.width / 2, visibleSize.height / 2);
	PopUpLayer->setAnchorPoint(Vec2(0, 0));
	PopUpLayer->setPosition(Vec2((visibleSize.width - PopUpLayer->getContentSize().width) / 2, (visibleSize.height - PopUpLayer->getContentSize().height) / 2));

	float width = PopUpLayer->getContentSize().width;
	float height = PopUpLayer->getContentSize().height;

	cocos2d::Label* label_title = Label::createWithTTF("End", "fonts/Marker Felt.ttf", 50); ///# �̷� ���� ���ͷ��� �ѱ��� ��� ������.. �̰� �� ��� ��ä�� ��
	label_title->setPosition(Vec2(width/2, height - 20));

	PopUpLayer->addChild(label_title);
	this->addChild(PopUpLayer);

	return true;
}

void ResultLayer::SetValue(PlayerData* pData1, PlayerData* pData2)
{
	/*int pData1Food = pData1->getFood();
	int pData2Food = pData2->getFood();

	Label* p1Food = Label::createWithTTF(std::to_string(pData1Food), "fonts/Marker Felt.ttf", 20);
	Label* p2Food = Label::createWithTTF(std::to_string(pData2Food), "fonts/Marker Felt.ttf", 20);

	float width = PopUpLayer->getContentSize().width;
	float height = PopUpLayer->getContentSize().height;

	p1Food->setPosition(Vec2(100, height - 120));
	p2Food->setPosition(Vec2(100 + width / 2, height - 120));

	PopUpLayer->addChild(p1Food);
	PopUpLayer->addChild(p2Food);*/
}