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

std::shared_ptr<Character> Character::create(PlayerInfo cPInfo, DirectionKind spriteNum)
{
	std::shared_ptr<Character> character(new Character(cPInfo, spriteNum));
	
	Animation* animationDefault = CharacterAnimation::getInstance()->getAnimationDefault(cPInfo, spriteNum);
	character->init();
	character->runAction(Animate::create(animationDefault));

	return character;
}

bool Character::IsOnTile(TileKind tileTypeToCheck)
{
	if (this->getCurrentTile()->getTypeOfTile() == tileTypeToCheck)
		return true;
	return false;
}

void Character::RotateToDirection(RotateDirection rotateDirection)
{

	DirectionKind characterDirection = getCurrentDirection();

	if (rotateDirection == ROTATE_LEFT)
		characterDirection = static_cast<DirectionKind>( (characterDirection + 1) % 6 );

	if (rotateDirection == ROTATE_RIGHT)
		characterDirection = static_cast<DirectionKind>( (characterDirection + 5) % 6 );

	EventManager::getInstance()->AddHistory(HistoryEventRotateCharacter::Create(this->shared_from_this(), characterDirection));

	setCurrentDirection(DirectionKind(characterDirection));

	return;
}

void Character::RotateToDirection(DirectionKind targetDirection)
{
	EventManager::getInstance()->AddHistory(HistoryEventRotateCharacter::Create(this->shared_from_this(), targetDirection));

	setCurrentDirection(DirectionKind(targetDirection));

	return;
}

void Character::MovoToTile(Self_Tile* dest)
{
	this->getCurrentTile()->setCharacterOnThisTile(nullptr);
	dest->setCharacterOnThisTile(this->shared_from_this());
	this->setCurrentTile(dest);

	EventManager::getInstance()->AddHistory(HistoryEventMoveCharacter::Create(this->shared_from_this(), dest));
	//GM->getPlayerDataByPlayerInfo(_OwnerPlayer)->AddFood(dest->getFoodToConsume() * -1);
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
	Sprite* tileMove = Sprite::createWithSpriteFrameName("tile_move.png");
	tileMove->setOpacity(96);
	tileMove->setAnchorPoint(cocos2d::Vec2(0, 0));

	DirectionKind dir = this->getCurrentDirection();
	Self_Tile* tile = this->getCurrentTile()->getNearTile(dir);

	if (GM->getPlayerDataByPlayerInfo(_OwnerPlayer)->getFood() < tile->getFoodToConsume())
		return;
	if (!tile->isMovable())
		return;

	float tilePosX = tile->getPositionX();
	float tilePosY = tile->getPositionY();

	tileMove->setPosition(tilePosX, tilePosY);
	tileMove->setName("moveable");
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

void Character::InitAttackPowerSprite()
{
	_AttackPowerLabel = Label::createWithTTF(std::to_string(_AttackPowerToDisplay), "fonts/upheavtt.ttf", 20);
	float posX = this->getPositionX();
	float posY = this->getPositionY();

	_AttackPowerLabel->setName("attackPower");
	_AttackPowerLabel->setAnchorPoint(Vec2(0, 0));
	_AttackPowerLabel->setPosition(posX + 25, posY + 80);

	this->addChild(_AttackPowerLabel);
}

void Character::UpdateAttackPowerSprite()
{
	int directionBonus = 0;
	std::shared_ptr<Character> charUpFront = GetNearCharacter(_CurrentDirectionToShow);
	
	if (charUpFront != nullptr && charUpFront->GetOwnerPlayer() != _OwnerPlayer)
		directionBonus = CalculateDiffBetweenDirections(_CurrentDirectionToShow, charUpFront->getCurrentDirectionToShow());
	
	if (CurrentTile->getTypeOfTile() == TILE_FOREST)
		directionBonus++;
	
	_AttackPowerLabel->setString(std::to_string(_AttackPowerToDisplay + directionBonus));
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