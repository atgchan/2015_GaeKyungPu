#include "pch.h"
#include "HistoryEventMoveCharacter.h"
#include "CharacterAnimation.h"
#include "Character.h"
#include "GameSceneManager.h"
#include "EventManager.h"
#include "SimpleAudioEngine.h"

HistoryEventMoveCharacter::HistoryEventMoveCharacter()
{
	_IsDone = false;
}


std::shared_ptr<HistoryEventMoveCharacter> HistoryEventMoveCharacter::Create(Character* characterToMove, Self_Tile* TargetTile)
{
	std::shared_ptr<HistoryEventMoveCharacter> newInst = std::make_shared<HistoryEventMoveCharacter>();
	newInst->_CharacterToMove = characterToMove;
	newInst->_TargetTile = TargetTile;
	newInst->_AttackPowerToShow = characterToMove->getAttackPower();
	return newInst;
}

HistoryEventMoveCharacter::~HistoryEventMoveCharacter()
{
}

void HistoryEventMoveCharacter::Run()
{
	Animation* animationMove = CharacterAnimation::getInstance()->getAnimationMove(_CharacterToMove->GetOwnerPlayer(), _CharacterToMove->getCurrentDirectionToShow());
	ActionInterval* actionMove = Animate::create(animationMove);

	ActionInterval* moveTo = MoveTo::create(1, Vec2(_TargetTile->getPositionX() + 80, _TargetTile->getPositionY() + 81));

	//검토가 필요함
	//cocos2d::CallFunc* nextCall = CallFunc::create(CC_CALLBACK_0(Character::setCurrentDirectionToShow,_CharacterToMove,_CharacterToMove->getCurrentDirection()));

	cocos2d::CallFunc* doneCall = CallFunc::create(CC_CALLBACK_0(HistoryEventMoveCharacter::SetDone, this, true));

	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(_CharacterToMove->GetOwnerPlayer(), _CharacterToMove->getCurrentDirectionToShow());

	ActionInterval* actionDefault = Animate::create(animationDefault);

	FiniteTimeAction* seq = Spawn::create(actionMove, moveTo, nullptr);
	FiniteTimeAction* seq1 = Sequence::create(seq, doneCall, actionDefault, /*nextCall,*/ nullptr);

	_CharacterToMove->stopAllActions();
	_CharacterToMove->setAnchorPoint(Vec2(0.5f, 0.13f));
	_CharacterToMove->runAction(seq1);
	_CharacterToMove->setAnimState(ANIM_MOVE);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FILENAME_SOUND_GAME_MOVE);
	_CharacterToMove->setAttackPowerToDisplay(_AttackPowerToShow);
}