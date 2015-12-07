#include "pch.h"
#include "HistoryEventKillCharacter.h"
#include "CharacterAnimation.h"
#include "Character.h"
#include "GameSceneManager.h"
#include "EventManager.h"
#include "SimpleAudioEngine.h"

HistoryEventKillCharacter::HistoryEventKillCharacter()
{
	_ActionHitEffect = Animate::create(CharacterAnimation::getInstance()->getAnimationHitEffect());
	_IsDone = false;
}

HistoryEventKillCharacter::~HistoryEventKillCharacter()
{
}

std::shared_ptr<HistoryEventKillCharacter> HistoryEventKillCharacter::Create(Character* characterToKill, bool hitEffect /*= false*/)
{
	///# 마찬가지로 순환참조 유의
	std::shared_ptr<HistoryEventKillCharacter> newInst = std::make_shared<HistoryEventKillCharacter>();
	newInst->_CharacterToKill = characterToKill;
	newInst->_ShowHitEffect = hitEffect;
	return newInst;
}

void HistoryEventKillCharacter::Run()
{	
	Animation* animationBeHit = CharacterAnimation::getInstance()->getAnimationBeHit(_CharacterToKill->GetOwnerPlayer(), _CharacterToKill->getCurrentDirectionToShow());
	ActionInterval* actionBeHit = Animate::create(animationBeHit);
	cocos2d::CallFunc* doneCall = CallFunc::create(CC_CALLBACK_0(HistoryEventKillCharacter::SetDone, this, true));
	cocos2d::CallFunc* removeCharacter = CallFunc::create(CC_CALLBACK_0(HistoryEventKillCharacter::RemoveCharacterToKill, this));
	if (_ShowHitEffect == true)
	{
		_HitEffect = Sprite::create();
		_HitEffect->initWithFile("Effect/HitEffect/HitEffect_01.png");
		_HitEffect->setPosition(_CharacterToKill->getPositionX(),_CharacterToKill->getPositionY()+30);
		//_HitEffect->setZOrder(_CharacterToKill->getZOrder() + 1);
		GM->getNodes()->addChild(_HitEffect);
		_HitEffect->runAction(Sequence::create(_ActionHitEffect,RemoveSelf::create(),nullptr));
	}

	FiniteTimeAction* seq = Sequence::create(actionBeHit, doneCall, removeCharacter, nullptr);
	_CharacterToKill->stopAllActions();
	_CharacterToKill->runAction(seq);
}

void HistoryEventKillCharacter::RemoveCharacterToKill()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Hit_03.wav");
	TileMap::getInstance()->KillCharacter(_CharacterToKill);
	_CharacterToKill = nullptr;
}