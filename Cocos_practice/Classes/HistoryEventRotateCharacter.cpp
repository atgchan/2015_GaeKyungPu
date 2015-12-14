#include "pch.h"
#include "HistoryEventRotateCharacter.h"
#include "Character.h"
#include "CharacterAnimation.h"

HistoryEventRotateCharacter::HistoryEventRotateCharacter()
{
	_IsDone = false;
}


HistoryEventRotateCharacter::~HistoryEventRotateCharacter()
{
}

std::shared_ptr<HistoryEventRotateCharacter> HistoryEventRotateCharacter::Create(Character* targetCharacter, DirectionKind targetDirection)
{
	std::shared_ptr<HistoryEventRotateCharacter> newInst = std::make_shared<HistoryEventRotateCharacter>();
	newInst->_CharacterToRotate = targetCharacter;
	newInst->_DirectionToRotate = targetDirection;
	newInst->_AttackPowerToShow = targetCharacter->getAttackPower();
	return newInst;
}

void HistoryEventRotateCharacter::Run()
{
	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(_CharacterToRotate->getCurrentPlayerInfo(), _DirectionToRotate);
	_CharacterToRotate->stopAllActions();
	_CharacterToRotate->setAnchorPoint(Vec2(0.5f, 0.13f));
	_CharacterToRotate->runAction(Animate::create(animationDefault));
	_CharacterToRotate->setCurrentDirectionToShow(_DirectionToRotate);
	_CharacterToRotate->setAttackPowerToDisplay(_AttackPowerToShow);
	SetDone(true);
}