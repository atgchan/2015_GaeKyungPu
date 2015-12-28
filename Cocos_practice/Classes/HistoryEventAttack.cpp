#include "pch.h"
#include "HistoryEventAttack.h"
#include "Character.h"
#include "CharacterAnimation.h"
#include "SimpleAudioEngine.h"

HistoryEventAttack::HistoryEventAttack()
{
	///# 생성자든 소멸자든 구현체가 없으면 아예 선언하지 마라.
}


HistoryEventAttack::~HistoryEventAttack()
{
}

std::shared_ptr<HistoryEventAttack> HistoryEventAttack::Create(Character* attacker, Character* defender)
{
	std::shared_ptr<HistoryEventAttack> newInst = std::make_shared<HistoryEventAttack>();
	newInst->_Attacker = attacker;
	newInst->_Defender = defender;
	newInst->_AttackerPower = attacker->getAttackPower();
	newInst->_DefenderPower = defender->getAttackPower();
	return newInst;
}

void HistoryEventAttack::PlaySwordSound()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FILENAME_SOUND_GAME_SWORD);
}

void HistoryEventAttack::Run()
{
	_CurrentX = _Attacker->getPositionX();
	_CurrentY = _Attacker->getPositionY();
	ActionInterval* moveTo = MoveTo::create(0.5, Vec2(_Defender->getPositionX() + ((_Defender->getPositionX() >_Attacker->getPositionX()) ? -10 : 10), _Defender->getPositionY() + ((_Defender->getPositionY()>_Attacker->getPositionY()) ? -10 : 10)));
	ActionInterval* recover = MoveTo::create(0.3, Vec2(_CurrentX, _CurrentY));
	Animation* animationAttack = CharacterAnimation::getInstance()->getAnimationAttack(_Attacker->GetOwnerPlayer(), _Attacker->getCurrentDirectionToShow());
	ActionInterval* actionAttack = Animate::create(animationAttack);
	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(_Attacker->GetOwnerPlayer(), _Attacker->getCurrentDirectionToShow());

	ActionInterval* actionDefault = Animate::create(animationDefault);

	cocos2d::CallFunc* doneCall = CallFunc::create(CC_CALLBACK_0(HistoryEventAttack::SetDone, this, true));
	cocos2d::CallFunc* soundCall = CallFunc::create(CC_CALLBACK_0(HistoryEventAttack::PlaySwordSound, this));
	
	FiniteTimeAction* seqSound = Sequence::create(DelayTime::create(0.5), soundCall,nullptr);
	FiniteTimeAction* seq = Spawn::create(actionAttack, moveTo,seqSound, nullptr);
	FiniteTimeAction* seq1 = Sequence::create(seq, recover,doneCall,actionDefault, nullptr);

	_Attacker->stopAllActions();
	_Attacker->runAction(seq1);
	_Attacker->setAttackPowerToDisplay(_AttackerPower);
	_Defender->setAttackPowerToDisplay(_DefenderPower);
}