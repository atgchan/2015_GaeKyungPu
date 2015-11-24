#include "pch.h"
#include "definition.h"
#include "CharacterAnimation.h"
#include "Character.h"
#include "TileMap.h"
#include "GameSceneManager.h"
#include "EventManager.h"
#include "HistoryEventMoveCharacter.h"
#include "HistoryEventRotateCharacter.h"

Character::Character(PlayerInfo cPInfo, int spriteNum)
{
	autorelease();
	setCurrentPlayerInfo(cPInfo);
	setCurrentDirection((DirectionKind)spriteNum);
	setCurrentDirectionToShow((DirectionKind)spriteNum);
}

Character* Character::create(PlayerInfo cPInfo, DirectionKind spriteNum)
{
	Character* character = new Character(cPInfo, spriteNum);

	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(cPInfo, spriteNum);
	character->init();
	character->runAction(Animate::create(animationDefault));

	return character;
}

bool Character::IsOnTile(TileKind tileTypeToCheck)
{
	if (this->getCurrentTile()->getTypeOfTile() == tileTypeToCheck)
		return true;
	else
		return false;
}

void Character::RotateToDirection(RotateDirection rotateDirection)
{
	std::shared_ptr<Character>	sThis(this); ///# 잘못된 사용. shared_ptr은 생성시에 메모리 할당이 되어야 한다. 즉 아래로 shared_ptr은 전부 잘못 사용됨.

	DirectionKind characterDirection = getCurrentDirection();

	if (rotateDirection == ROTATE_LEFT)
		characterDirection = static_cast<DirectionKind>( (characterDirection + 1) % 6 );

	if (rotateDirection == ROTATE_RIGHT)
		characterDirection = static_cast<DirectionKind>( (characterDirection + 5) % 6 );

	EventManager::getInstance()->AddHistory(HistoryEventRotateCharacter::Create(sThis, characterDirection));

	setCurrentDirection(DirectionKind(characterDirection));

	return;
}

void Character::RotateToDirection(DirectionKind targetDirection)
{
	std::shared_ptr<Character>	sThis(this);
	EventManager::getInstance()->AddHistory(HistoryEventRotateCharacter::Create(sThis, targetDirection));

	setCurrentDirection(DirectionKind(targetDirection));

	return;
}

void Character::MovoToTile(Self_Tile* dest)
{
	this->getCurrentTile()->setCharacterOnThisTile(nullptr);
	dest->setCharacterOnThisTile(this);
	this->setCurrentTile(dest);

	std::shared_ptr<Character>	sThis(this);
	std::shared_ptr<Self_Tile>	sDest(dest);

	EventManager::getInstance()->AddHistory(HistoryEventMoveCharacter::Create(sThis, sDest));
}

void Character::CharacterBeHit()
{
	Animation* animationBeHit = CharacterAnimation::getInstance()->getAnimationBeHit(GetOwnerPlayer(), getCurrentDirection());
	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(GetOwnerPlayer(), getCurrentDirection());

	ActionInterval* actionBeHit = Animate::create(animationBeHit);
	ActionInterval* actionDefault = Animate::create(animationDefault);

	FiniteTimeAction* seq = Sequence::create(actionBeHit, actionDefault, NULL);
	init();
	stopAllActions();
	setAnchorPoint(Vec2(0.5f, 0.13f));

	runAction(seq);
}

void Character::CharacterAttack()
{
	Animation* animationAttack = CharacterAnimation::getInstance()->getAnimationAttack(GetOwnerPlayer(), getCurrentDirection());
	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(GetOwnerPlayer(), getCurrentDirection());

	ActionInterval* actionAttack = Animate::create(animationAttack);
	ActionInterval* actionDefault = Animate::create(animationDefault);

	FiniteTimeAction* seq = Sequence::create(actionAttack, actionDefault, NULL);

	init();
	stopAllActions();
	setAnchorPoint(Vec2(0.5f, 0.13f));

	runAction(seq);
}

Character* Character::GetNearCharacter(DirectionKind direction)
{
	return this->getCurrentTile()->getNearTile(direction)->getCharacterOnThisTile();
}

const PlayerInfo Character::GetOwnerPlayer()
{
	return _OwnerPlayer;
}

void Character::SetOwnerPlayer(PlayerInfo pInfo)
{
	_OwnerPlayer = pInfo;
}

Character::~Character()
{
	stopAllActions();
}

void Character::InitializeDirection(DirectionKind direction)
{
	this->_CurrentDirection = direction;
	this->_CurrentDirectionToShow = direction;
}

DirectionKind Character::getCurrentDirectionToShow()
{
	return _CurrentDirectionToShow;
}

void Character::setCurrentDirectionToShow(DirectionKind direction)
{
	_CurrentDirectionToShow = direction;
}

DirectionKind Character::getCurrentDirection()
{
	return _CurrentDirection;
}

void Character::setCurrentDirection(DirectionKind direction)
{
	_CurrentDirection = direction;
}

int Character::getAttackPower()
{
	return _AttackPower;
}

void Character::setAttackPower(int attackPower)
{
	_AttackPower = attackPower;
}
