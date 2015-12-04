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

std::shared_ptr<HistoryEventRotateCharacter> HistoryEventRotateCharacter::Create(std::shared_ptr<Character> targetCharacter, DirectionKind targetDirection)
{
	///# 순환참조 유의
	std::shared_ptr<HistoryEventRotateCharacter> newInst = std::make_shared<HistoryEventRotateCharacter>();
	newInst->_CharacterToRotate = targetCharacter;
	newInst->_DirectionToRotate = targetDirection;
	return newInst;
}

void HistoryEventRotateCharacter::Run()
{
	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(_CharacterToRotate->getCurrentPlayerInfo(), _DirectionToRotate);
	_CharacterToRotate->stopAllActions();
	_CharacterToRotate->setAnchorPoint(Vec2(0.5f, 0.13f));
	_CharacterToRotate->runAction(Animate::create(animationDefault));
	_CharacterToRotate->setCurrentDirectionToShow(_DirectionToRotate);
	SetDone(true);
}

bool HistoryEventRotateCharacter::IsDone()
{
		return _IsDone;
}