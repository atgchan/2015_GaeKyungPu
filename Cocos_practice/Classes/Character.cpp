#include "pch.h"
#include "definition.h"
#include "CharacterAnimation.h"
#include "Character.h"
#include "TileMap.h"

Character::Character(PlayerInfo cPInfo, int spriteNum)
{
	autorelease();
	setCurrentPlayerInfo(cPInfo);
	setCurrentDirection((DirectionKind)spriteNum);
}

Character* Character::create(PlayerInfo cPInfo, int spriteNum)
{
	Character* character = new Character(cPInfo, spriteNum);
	
	if (!character)
	{
		CC_SAFE_DELETE(character);
		return nullptr;
	}
	
	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(cPInfo, spriteNum);
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
	int chracterDirection = getCurrentDirection();

	if (rotateDirection == ROTATE_LEFT)
		chracterDirection = (chracterDirection + 1) % 6;

	if (rotateDirection == ROTATE_RIGHT)
		chracterDirection = (chracterDirection + 5) % 6;

	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(getCurrentPlayerInfo(), chracterDirection);
	init();
	stopAllActions();
	setAnchorPoint(Vec2(0.5f, 0.13f));
	runAction(Animate::create(animationDefault));

	setCurrentDirection(DirectionKind(chracterDirection));

	return;	
}

void Character::MovoToTile(Self_Tile* dest)
{
	Animation* animationMove = CharacterAnimation::CreateAnimationMove(GetOwnerPlayer(), getCurrentDirection());
	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(GetOwnerPlayer(), getCurrentDirection());
	
	ActionInterval* actionMove = Animate::create(animationMove);

	ActionInterval* moveTo = MoveTo::create(1, Vec2(dest->getPositionX() + 80, dest->getPositionY() + 60));
	ActionInterval* actionDefault = Animate::create(animationDefault);

	FiniteTimeAction* seq = Spawn::create(actionMove, moveTo, NULL);
	FiniteTimeAction* seq1 = Sequence::create(seq, actionDefault, NULL);

	init();
	stopAllActions();
	setAnchorPoint(Vec2(0.5f, 0.13f));

	getCurrentTile()->setCharacterOnThisTile(nullptr);
	dest->setCharacterOnThisTile(this);
	setCurrentTile(dest);
	this->setZOrder(dest->getZOrder() + 100);

	runAction(seq1);
}

void Character::CharacterBeHit()
{
	Animation* animationBeHit = CharacterAnimation::CreateAnimationBeHit(GetOwnerPlayer(), 2);
	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(GetOwnerPlayer(), getCurrentDirection());

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
	Animation* animationAttack = CharacterAnimation::CreateAnimationAttack(GetOwnerPlayer(), 2);
	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(GetOwnerPlayer(), getCurrentDirection());

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