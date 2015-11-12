#include "pch.h"
#include "DiceDice.h"
#include "TileMap.h"


DiceDice::DiceDice()
{
}


DiceDice::~DiceDice()
{
}

int DiceDice::RollDiceBetween(int start, int end)
{
	return cocos2d::RandomHelper::random_int(start, end);
}

void DiceDice::DisplayDiceOnScreen(int min, int max)
{
	int num = RollDiceBetween(min, max);
	cocos2d::Label* numToDisplay = cocos2d::Label::createWithTTF(std::to_string(num), "fonts/Marker Felt.ttf", 20);
	//numToDisplay->enableOutline(Color4B::WHITE, 1);

	float height = TileMap::getInstance()->getContentSize().height;
	float width = TileMap::getInstance()->getContentSize().width;

	numToDisplay->setPosition(cocos2d::Vec2(200, 200));

	TileMap::getInstance()->addChild(numToDisplay);

	auto delay = DelayTime::create(2);
	auto removeFunc = CallFunc::create(CC_CALLBACK_0(DiceDice::RemoveDiceFromScreen, this, numToDisplay));
	auto seq = Sequence::create(delay, removeFunc, NULL);
	numToDisplay->runAction(seq);
}

void DiceDice::RemoveDiceFromScreen(cocos2d::Label* numToDisplay)
{
	TileMap::getInstance()->removeChild(numToDisplay);
}
