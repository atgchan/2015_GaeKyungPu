#include "pch.h"
#include "HistoryEventRotateCharacter.h"
#include "Character.h"
#include "CharacterAnimation.h"

HistoryEventRotateCharacter::HistoryEventRotateCharacter()
{
}


HistoryEventRotateCharacter::~HistoryEventRotateCharacter()
{
}

std::shared_ptr<HistoryEventRotateCharacter> HistoryEventRotateCharacter::Create(std::shared_ptr<Character> targetCharacter, DirectionKind targetDirection)
{
	std::shared_ptr<HistoryEventRotateCharacter> newInst = std::make_shared<HistoryEventRotateCharacter>();
	newInst->_CharacterToRotate = targetCharacter;
	newInst->_DirectionToRotate = targetDirection;
	return newInst;
}

void HistoryEventRotateCharacter::Run()
{
	DirectionKind chracterDirection = _CharacterToRotate->getCurrentDirection();

	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(_CharacterToRotate->getCurrentPlayerInfo(), chracterDirection);
	_CharacterToRotate->init();
	_CharacterToRotate->stopAllActions();
	_CharacterToRotate->setAnchorPoint(Vec2(0.5f, 0.13f));
	_CharacterToRotate->runAction(Animate::create(animationDefault));
}

bool HistoryEventRotateCharacter::IsDone()
{
	return true;
}
