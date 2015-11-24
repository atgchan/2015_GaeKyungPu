#include "pch.h"
#include "HistoryEventMoveCharacter.h"
#include "CharacterAnimation.h"
#include "Character.h"
#include "GameSceneManager.h"
#include "EventManager.h"
#include "SimpleAudioEngine.h"

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
	Animation* animationMove = CharacterAnimation::getInstance()->getAnimationMove(_CharacterToMove->GetOwnerPlayer(), _CharacterToMove->getCurrentDirectionToShow());
	ActionInterval* actionMove = Animate::create(animationMove);

	ActionInterval* moveTo = MoveTo::create(1, Vec2(_TargetTile->getPositionX() + 80, _TargetTile->getPositionY() + 60));

	
	cocos2d::CallFunc* nextCall = CallFunc::create(CC_CALLBACK_0(Character::setCurrentDirectionToShow,_CharacterToMove,_CharacterToMove->getCurrentDirection()));
	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(_CharacterToMove->GetOwnerPlayer(), _CharacterToMove->getCurrentDirectionToShow());

	ActionInterval* actionDefault = Animate::create(animationDefault);

	FiniteTimeAction* seq = Spawn::create(actionMove, moveTo, nullptr);
	FiniteTimeAction* seq1 = Sequence::create(seq,/*defaultCall*/actionDefault, nextCall, nullptr);

	_CharacterToMove->stopAllActions();
	_CharacterToMove->setAnchorPoint(Vec2(0.5f, 0.13f));
	_CharacterToMove->setZOrder(_TargetTile->getZOrder() + 100);
	_CharacterToMove->runAction(seq1);
	_CharacterToMove->setAnimState(ANIM_MOVE);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/Jump_03.wav");
}

bool HistoryEventMoveCharacter::IsDone()
{
	///# 아래처럼 float이나 double은 절대로 == 비교를 하면 안된다. 그 이유는? (게임프로그래밍의 정석 책에서 부동소수점 부분을 공부하고 정리할 것)

	if (_CharacterToMove->getPositionX() == _TargetTile->getPositionX() + 80 && _CharacterToMove->getPositionY() == _TargetTile->getPositionY() + 60)
		return true;
	return false;
}