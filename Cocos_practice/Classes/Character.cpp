#include "pch.h"
#include "definition.h"
#include "CharacterAnimation.h"
#include "Character.h"
#include "TileMap.h"
#include "GameSceneManager.h"
#include "EventManager.h"
#include "HistoryEventMoveCharacter.h"
#include "HistoryEventRotateCharacter.h"

Character::Character(PlayerInfo cPInfo, DirectionKind spriteNum)
{
	autorelease();
	setCurrentPlayerInfo(cPInfo);
	setCurrentDirection(spriteNum);
	setCurrentDirectionToShow(spriteNum);
}

std::shared_ptr<Character> Character::create(PlayerInfo cPInfo, DirectionKind spriteNum)
{
	std::shared_ptr<Character> character(new Character(cPInfo, spriteNum));
	
	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(cPInfo, spriteNum);
	character->init();
	character->runAction(Animate::create(animationDefault));

	character->_ThisShared = character;

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

	DirectionKind characterDirection = getCurrentDirection();

	if (rotateDirection == ROTATE_LEFT)
		characterDirection = static_cast<DirectionKind>( (characterDirection + 1) % 6 );

	if (rotateDirection == ROTATE_RIGHT)
		characterDirection = static_cast<DirectionKind>( (characterDirection + 5) % 6 );

	EventManager::getInstance()->AddHistory(HistoryEventRotateCharacter::Create(_ThisShared, characterDirection));

	setCurrentDirection(DirectionKind(characterDirection));

	return;
}

void Character::RotateToDirection(DirectionKind targetDirection)
{
	EventManager::getInstance()->AddHistory(HistoryEventRotateCharacter::Create(_ThisShared, targetDirection));

	setCurrentDirection(DirectionKind(targetDirection));

	return;
}

void Character::MovoToTile(std::shared_ptr<Self_Tile> dest)
{
	this->getCurrentTile()->setCharacterOnThisTile(nullptr);
	dest->setCharacterOnThisTile(_ThisShared);
	this->setCurrentTile(dest);

	EventManager::getInstance()->AddHistory(HistoryEventMoveCharacter::Create(_ThisShared, dest));
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

void Character::ShowMovableTile()
{
	if (TileMap::getInstance()->getChildByName("move"))
		TileMap::getInstance()->removeChildByName("move");

	Sprite* tileMove = Sprite::create();
	tileMove->initWithFile("Map/tile_move.png");
	tileMove->setAnchorPoint(cocos2d::Vec2(0, 0));

	DirectionKind dir = this->getCurrentDirection();
	std::shared_ptr<Self_Tile> tile = this->getCurrentTile()->getNearTile(dir);
	if (tile->getTypeOfTile() == TILE_NULL)
		return;

	float tilePosX = this->getCurrentTile()->getNearTile(dir)->getPositionX();
	float tilePosY = this->getCurrentTile()->getNearTile(dir)->getPositionY();

	tileMove->setPosition(tilePosX, tilePosY);
	tileMove->setName("move");

	tileMove->setZOrder(this->getCurrentTile()->getNearTile(dir)->getZOrder());
	TileMap::getInstance()->addChild(tileMove);
}

std::shared_ptr<Character> Character::GetNearCharacter(DirectionKind direction)
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
