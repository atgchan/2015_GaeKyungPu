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
	//DirectionKind characterDirection = _CharacterToRotate->getCurrentDirection();

	//Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(_CharacterToRotate->getCurrentPlayerInfo(), _DirectionToRotate /*characterDirection*/);
	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(_CharacterToRotate->getCurrentPlayerInfo(), _DirectionToRotate /*characterDirection*/);
	_CharacterToRotate->init();
	_CharacterToRotate->stopAllActions();
	_CharacterToRotate->setAnchorPoint(Vec2(0.5f, 0.13f));

	//auto nextCall = CallFunc::create(CC_CALLBACK_0(Character::setCurrentDirectionToShow, _CharacterToRotate, _CharacterToRotate->getCurrentDirection()));

	//auto seq = Sequence::create(Animate::create(animationDefault), nextCall, nullptr);
	_CharacterToRotate->runAction(Animate::create(animationDefault));
	_CharacterToRotate->setCurrentDirectionToShow(_DirectionToRotate);
	//_CharacterToRotate->setCurrentDirectionToShow(_CharacterToRotate->getCurrentDirection());
}

bool HistoryEventRotateCharacter::IsDone()
{
	//if (_CharacterToRotate->getCurrentDirectionToShow() == _CharacterToRotate->getCurrentDirection())
		return true;
	//return false;
}
