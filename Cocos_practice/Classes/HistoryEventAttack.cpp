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
	ActionInterval* moveTo = MoveTo::create(1, Vec2(_Defender->getCurrentTile()->getPositionX() + 100, _Defender->getCurrentTile()->getPositionY() + 80));

	Animation* animationAttack = CharacterAnimation::getInstance()->getAnimationAttack(_Attacker->GetOwnerPlayer(), _Attacker->getCurrentDirectionToShow());
	ActionInterval* actionAttack = Animate::create(animationAttack);
	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(_Attacker->GetOwnerPlayer(), _Attacker->getCurrentDirectionToShow());

	ActionInterval* actionDefault = Animate::create(animationDefault);


	FiniteTimeAction* seq = Spawn::create(actionAttack, moveTo, nullptr);
	FiniteTimeAction* seq1 = Sequence::create(seq,/*defaultCall*/actionDefault, nullptr);

	_Attacker->stopAllActions();
	_Attacker->runAction(seq1);
	_Attacker->setAnimState(ANIM_MOVE);
}

bool HistoryEventAttack::IsDone()
{
	return false;
}

