#include "pch.h"
#include "HistoryEventAttack.h"
#include "Character.h"
#include "CharacterAnimation.h"
#include "SimpleAudioEngine.h"

HistoryEventAttack::HistoryEventAttack()
{
}


HistoryEventAttack::~HistoryEventAttack()
{
}

std::shared_ptr<HistoryEventAttack> HistoryEventAttack::Create(Character* attacker, Character* defender)
{
	///# shared_ptr이 shared_ptr을 멤버로 들고 있는 구조인데, 이 경우는 반드시 순환참조가 없는지 확인해야 한다.
	std::shared_ptr<HistoryEventAttack> newInst = std::make_shared<HistoryEventAttack>();
	newInst->_Attacker = attacker;
	newInst->_Defender = defender;
	return newInst;
}


void HistoryEventAttack::PlaySwordSound()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/swords.wav"); ///# 문자리터럴은 따로 모을 것
}

void HistoryEventAttack::Run()
{
	_CurrentX = _Attacker->getPositionX();
	_CurrentY = _Attacker->getPositionY();
	ActionInterval* moveTo = MoveTo::create(0.5, Vec2(_Defender->getCurrentTile()->getPositionX() + 80, _Defender->getCurrentTile()->getPositionY() + 60));
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
}