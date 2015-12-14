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
	InitAttackPowerSprite();
}

Character* Character::create(PlayerInfo cPInfo, DirectionKind spriteNum)
{
	Character* character(new Character(cPInfo, spriteNum));
	
	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(cPInfo, spriteNum);
	character->init();
	character->runAction(Animate::create(animationDefault));
	character->setName("character");
	return character;
}

void Character::RotateToDirection(RotateDirection rotateDirection)
{
	DirectionKind characterDirection = getCurrentDirection();

	if (rotateDirection == ROTATE_LEFT)
		characterDirection = static_cast<DirectionKind>((characterDirection + 1) % DIRECTION_MAX);

	if (rotateDirection == ROTATE_RIGHT)
		characterDirection = static_cast<DirectionKind>((characterDirection + 5) % DIRECTION_MAX);
	DirectionKind tempDirection = _CurrentDirection;
	setCurrentDirection(characterDirection);
	CalculateAttackPower();
	setCurrentDirection(tempDirection);
	EventManager::getInstance()->AddHistory(HistoryEventRotateCharacter::Create(this, characterDirection));
	setCurrentDirection(characterDirection);
	CalculateAttackPowerAllNearTile();
	return;
}

void Character::RotateToDirection(DirectionKind targetDirection)
{
	CalculateAttackPower();
	EventManager::getInstance()->AddHistory(HistoryEventRotateCharacter::Create(this, targetDirection));
	setCurrentDirection(DirectionKind(targetDirection));
	return;
}

void Character::MovoToTile(Self_Tile* dest)
{
	Self_Tile* prevTile = this->getCurrentTile();

	this->getCurrentTile()->setCharacterOnThisTile(nullptr);
	dest->setCharacterOnThisTile(this);
	this->setCurrentTile(dest);

	prevTile->CaculateAttackPowerAllNearTile();
	dest->CaculateAttackPowerAllNearTile();

	EventManager::getInstance()->AddHistory(HistoryEventMoveCharacter::Create(this, dest));
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
	Sprite* tileMove = Sprite::createWithSpriteFrameName(FILENAME_IMG_GAME_CHARACTER_MOVABLE_TILE);
	tileMove->setOpacity(96);
	tileMove->setAnchorPoint(cocos2d::Vec2(0, 0));

	DirectionKind dir = this->getCurrentDirection();
	Self_Tile* tile = this->getCurrentTile()->getNearTile(dir);

	if (GM->getPlayerDataByPlayerInfo(_OwnerPlayer)->getFood() < tile->getFoodToConsume())
		return;
	if (!tile->isMovable())
		return;

	float tilePosX = tile->getPositionX();
	float tilePosY = tile->getPositionY() + 21;

	tileMove->setPosition(tilePosX, tilePosY);
	tileMove->setName("moveable");
	tileMove->setZOrder(this->getCurrentTile()->getNearTile(dir)->getZOrder());
	TileMap::getInstance()->addChild(tileMove);

	//타일 위에 캐릭터가 있으면 머리 위에 커서를 보여줌

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

void Character::InitAttackPowerSprite()
{
	_AttackPowerBall = CCSprite::createWithSpriteFrameName(FILENAME_IMG_ATTACK_POWER_2); 

	float posX = this->getPositionX();
	float posY = this->getPositionY();

	_AttackPowerBall->setName("attackPower");
	_AttackPowerBall->setAnchorPoint(Vec2(0, 0));
	_AttackPowerBall->setPosition(posX + 25, posY + 80);

	this->addChild(_AttackPowerBall);
}

void Character::UpdateAttackPowerSprite()
{/*
	int directionBonus = 0;
	Character* charUpFront = GetNearCharacter(_CurrentDirectionToShow);
	
	if (charUpFront != nullptr && charUpFront->GetOwnerPlayer() != _OwnerPlayer)
		directionBonus = CalculateDiffBetweenDirections(_CurrentDirectionToShow, charUpFront->getCurrentDirectionToShow());
	
	if (CurrentTile->getTypeOfTile() == TILE_FOREST)
		directionBonus++;*/
	
	setAttackPowerBallNameFromNumber(_AttackPowerToDisplay/* + directionBonus*/);
}

void Character::setAttackPowerToDisplay(int ap)
{
	_AttackPowerToDisplay = ap;
}

int Character::getAttackPowerToDisplay()
{
	return _AttackPowerToDisplay;
}

int Character::CalculateDiffBetweenDirections(DirectionKind dir1, DirectionKind dir2)
{
	int diff = dir1 - dir2;

	diff = std::abs(diff);

	if (diff == 3)
		return 0;
	
	if (diff == 2 || diff == 4)
		return 1;

	if (diff == 1 || diff == 5)
		return 2;	

	if (diff == 0)
		return 3;

	return -100000;
}

void Character::setAttackPowerBallNameFromNumber(int power)
{
	switch (power)
	{
	case 1:
		_AttackPowerBall->setSpriteFrame(FILENAME_IMG_ATTACK_POWER_1);
		break;
	case 2:
		_AttackPowerBall->setSpriteFrame(FILENAME_IMG_ATTACK_POWER_2);
		break;
	case 3:
		_AttackPowerBall->setSpriteFrame(FILENAME_IMG_ATTACK_POWER_3);
		break;
	case 4:
		_AttackPowerBall->setSpriteFrame(FILENAME_IMG_ATTACK_POWER_4);
		break;
	case 5:
		_AttackPowerBall->setSpriteFrame(FILENAME_IMG_ATTACK_POWER_5);
		break;
	case 6:
		_AttackPowerBall->setSpriteFrame(FILENAME_IMG_ATTACK_POWER_6);
		break;
	default:
		_AttackPowerBall->setSpriteFrame(FILENAME_IMG_ATTACK_POWER_2);
	}
}

void Character::CalculateAttackPower()
{
	int directionBonus = 0;
	Character* charUpFront = GetNearCharacter(_CurrentDirection);

	if (charUpFront != nullptr && charUpFront->GetOwnerPlayer() != _OwnerPlayer)
		directionBonus = CalculateDiffBetweenDirections(_CurrentDirection, charUpFront->getCurrentDirection());

	if (CurrentTile->getTypeOfTile() == TILE_FOREST)
		directionBonus++;
	_AttackPower = ATTACK_POWER_DEFAULT + directionBonus;
	_AttackPowerToDisplay = _AttackPower;
}

void Character::CalculateAttackPowerAllNearTile()
{
	this->getCurrentTile()->CaculateAttackPowerAllNearTile();
}