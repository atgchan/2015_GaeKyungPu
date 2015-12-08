#include "pch.h"
#include "HistoryEventHarvest.h"
#include "Character.h"
#include "GameSceneManager.h"
#include "SimpleAudioEngine.h"

HistoryEventHarvest::HistoryEventHarvest()
{
}


HistoryEventHarvest::~HistoryEventHarvest()
{
}

void HistoryEventHarvest::Run()
{
	Sprite* grain = Sprite::createWithSpriteFrameName("grain.png");
	grain->setPosition(_CharacterHarvest->getPosition());
	grain->setZOrder(13);
	FiniteTimeAction* floatAction = MoveTo::create(0.2f, Vec2(grain->getPositionX(), grain->getPositionY() + 80));
	int xMul = (GM->getCurrentPlayer() == PLAYER_RED) ? 0 : 1;
	FiniteTimeAction* flyAction = EaseIn::create(MoveTo::create(1.2, Vec2(130 + xMul * 200, 750)),3);


	cocos2d::CallFunc* doneCall = CallFunc::create(CC_CALLBACK_0(HistoryEventHarvest::SetDone, this, true));
	cocos2d::CallFunc* addCall = CallFunc::create(CC_CALLBACK_0(PlayerData::AddFood, GM->getCurrentPlayerData(), 1));
	Action*	delAction = RemoveSelf::create(true);

	FiniteTimeAction* seq = Sequence::create(floatAction, flyAction, addCall, doneCall, delAction, nullptr);
	grain->runAction(seq);
	GM->getNodes()->getParent()->getChildByName("ui_layer")->addChild(grain);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FILENAME_SOUND_GAME_HARVEST);
}

std::shared_ptr<HistoryEventHarvest> HistoryEventHarvest::Create(Character* characterHarvest)
{
	std::shared_ptr<HistoryEventHarvest> newInst = std::make_shared<HistoryEventHarvest>();
	newInst->_CharacterHarvest = characterHarvest;
	return newInst;
}