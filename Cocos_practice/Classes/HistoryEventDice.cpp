#include "pch.h"
#include "HistoryEventDice.h"
#include "Character.h"

HistoryEventDice::HistoryEventDice()
{
}


HistoryEventDice::~HistoryEventDice()
{
}


void HistoryEventDice::Run()
{
	Sprite* dice = CreateDiceWithNumber();
	if (dice == nullptr)
	{
		return;
	}
	dice->setName("dice");
	dice->setZOrder(11);
	dice->setAnchorPoint(Vec2(0, 0));
	dice->setPosition(70, 50);
	dice->setScale(0.3);
	dice->setOpacity(0);

	_TargetCharacter->addChild(dice);

	dice->setAnchorPoint(Vec2(0.5, 0.5));
	auto rotateTo = RotateTo::create(0.5f, 1440.0f);
	auto moveBy = MoveBy::create(0.5, Vec2(0, 100));
	auto scaleTo = ScaleTo::create(0.5f, 1.0f);
	auto fadeIn = FadeIn::create(0.2f);
	dice->runAction(fadeIn);
	dice->runAction(moveBy);
	dice->runAction(scaleTo);
	dice->runAction(rotateTo);
	auto delayBefore = DelayTime::create(0.5f);
	auto delayAfter = DelayTime::create(1.5f);

	cocos2d::CallFunc* doneCall = CallFunc::create(CC_CALLBACK_0(HistoryEventDice::SetDone, this, true));

	auto seq = Sequence::create(delayBefore, doneCall, delayAfter, RemoveSelf::create(), nullptr);
	dice->runAction(seq);
}

std::shared_ptr<HistoryEventDice> HistoryEventDice::Create(Character* character, int num)
{
	std::shared_ptr<HistoryEventDice> newInst = std::make_shared<HistoryEventDice>();
	newInst->_TargetCharacter = character;
	newInst->_Num = num;
	return newInst;
}

Sprite* HistoryEventDice::CreateDiceWithNumber()
{
	switch (_Num)
	{
	case 1:
		return Sprite::create(FILENAME_IMG_DICE_1);
	case 2:
		return Sprite::create(FILENAME_IMG_DICE_2);
	case 3:
		return Sprite::create(FILENAME_IMG_DICE_3);
	case 4:
		return Sprite::create(FILENAME_IMG_DICE_4);
	case 5:
		return Sprite::create(FILENAME_IMG_DICE_5);
	case 6:
		return Sprite::create(FILENAME_IMG_DICE_6);
	default:
		return nullptr;
	}
}
