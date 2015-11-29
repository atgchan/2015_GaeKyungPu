#include "pch.h"
#include "HistoryEventAttack.h"
#include "Character.h"
#include "CharacterAnimation.h"

HistoryEventAttack::HistoryEventAttack()
{
}


HistoryEventAttack::~HistoryEventAttack()
{
}

std::shared_ptr<HistoryEventAttack> HistoryEventAttack::Create(std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender)
{
	std::shared_ptr<HistoryEventAttack> newInst = std::make_shared<HistoryEventAttack>();
	newInst->_Attacker = attacker;
	newInst->_Defender = defender;
	return newInst;
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


	FiniteTimeAction* seq = Spawn::create(actionAttack, moveTo, nullptr);
	FiniteTimeAction* seq1 = Sequence::create(seq, recover,actionDefault, nullptr);

	_Attacker->stopAllActions();
	_Attacker->runAction(seq1);
}

bool HistoryEventAttack::IsDone()
{
	if (_Attacker->getPositionX() == _CurrentX && _Attacker->getPositionY() == _CurrentY)
		if (_FirstTime == true)
			_FirstTime = false;
		else return true;
	return false;
}

