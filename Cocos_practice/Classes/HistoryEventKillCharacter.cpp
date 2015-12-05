#include "pch.h"
#include "HistoryEventKillCharacter.h"
#include "CharacterAnimation.h"
#include "Character.h"
#include "GameSceneManager.h"
#include "EventManager.h"
#include "SimpleAudioEngine.h"

HistoryEventKillCharacter::HistoryEventKillCharacter()
{
	_IsDone = false;
}

HistoryEventKillCharacter::~HistoryEventKillCharacter()
{
}

std::shared_ptr<HistoryEventKillCharacter> HistoryEventKillCharacter::Create(Character* characterToKill)
{
	///# 마찬가지로 순환참조 유의
	std::shared_ptr<HistoryEventKillCharacter> newInst = std::make_shared<HistoryEventKillCharacter>();
	newInst->_CharacterToKill = characterToKill;

	return newInst;
}

void HistoryEventKillCharacter::Run()
{	
	//종성이형이 새로 만든 버전
	/*Animation* animationBeHit = CharacterAnimation::getInstance()->getAnimationBeHit(_CharacterToKill->GetOwnerPlayer(), _CharacterToKill->getCurrentDirectionToShow());
	ActionInterval* actionBeHit = Animate::create(animationBeHit);
	cocos2d::CallFunc* doneCall = CallFunc::create(CC_CALLBACK_0(HistoryEventKillCharacter::SetDone, this, true));

	Action* seq = Sequence::create(actionBeHit, doneCall, nullptr);
	_CharacterToKill->runAction(seq);

	TileMap::getInstance()->removeChild(_CharacterToKill);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Hit_03.wav");*/

	//기존 버전
	TileMap::getInstance()->removeChild(_CharacterToKill);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Hit_03.wav");
	SetDone(true);
}