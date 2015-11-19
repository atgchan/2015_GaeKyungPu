#include "pch.h"
#include "HistoryEventMoveCharacter.h"
#include "CharacterAnimation.h"
#include "Character.h"
#include "GameSceneManager.h"
#include "AnimationManager.h"

HistoryEventMoveCharacter::HistoryEventMoveCharacter()
{
}


std::shared_ptr<HistoryEventMoveCharacter> HistoryEventMoveCharacter::Create(std::shared_ptr<Character> characterToMove, std::shared_ptr<Self_Tile> TargetTile)
{
	std::shared_ptr<HistoryEventMoveCharacter> newInst = std::make_shared<HistoryEventMoveCharacter>();
	newInst->_CharacterToMove = characterToMove;
	newInst->_TargetTile = TargetTile;

	return newInst;
}

HistoryEventMoveCharacter::~HistoryEventMoveCharacter()
{
}

void HistoryEventMoveCharacter::Run()
{
	Animation* animationMove = CharacterAnimation::CreateAnimationMove(_CharacterToMove->GetOwnerPlayer(), _CharacterToMove->getCurrentDirection());
	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(_CharacterToMove->GetOwnerPlayer(), _CharacterToMove->getCurrentDirection());

	ActionInterval* actionMove = Animate::create(animationMove);

	ActionInterval* moveTo = MoveTo::create(1, Vec2(_TargetTile->getPositionX() + 80, _TargetTile->getPositionY() + 60));
	ActionInterval* actionDefault = Animate::create(animationDefault);

	
	auto nextCall = CallFunc::create(CC_CALLBACK_0(AnimationManager::PlayHistory, AnimationManager::getInstance()));
	

	FiniteTimeAction* seq = Spawn::create(actionMove, moveTo, NULL);
	FiniteTimeAction* seq1 = Sequence::create(seq, nextCall,actionDefault, NULL);

	_CharacterToMove->init();
	_CharacterToMove->stopAllActions();
	_CharacterToMove->setAnchorPoint(Vec2(0.5f, 0.13f));
	_CharacterToMove->setZOrder(_TargetTile->getZOrder() + 100);
	_CharacterToMove->runAction(seq1);

}
