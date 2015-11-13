#include "pch.h"
#include "definition.h"
#include "CharacterAnimation.h"
#include "Character.h"

Character::Character(PlayerInfo cPInfo, int spriteNum)
{
	autorelease();
	setCurrentPlayerInfo(cPInfo);
	setCurrentDirection((DirectionKind)spriteNum);
}

Character* Character::create(PlayerInfo cPInfo, int spriteNum)
{
	Character* character = new Character(cPInfo, spriteNum);

//	���� �� ������ Red Blue ������ CharacterAnimation���ο��� �����Ѵ�.
//	create�� ���� ĳ���� ��ü�� ���� ��, ���� �׷��� ������ CharacterAnimation���� ó���ϴ� ����

	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(cPInfo, spriteNum);
	character->init();
	character->runAction(Animate::create(animationDefault));

	if (!character)
	{
		CC_SAFE_DELETE(character);
		return nullptr;
	}

	return character;
}

bool Character::isOnTile(TileKind tileTypeToCheck)
{
	if (this->getCurrentTile()->getTypeOfTile() == tileTypeToCheck)
		return true;
	else
		return false;
}

void Character::rotateToDirection(RotateDirection rotateDirection)
{
	int chracterDirection = getCurrentDirection();

	if (rotateDirection == ROTATE_LEFT)
		chracterDirection = (chracterDirection + 1) % 6;

	if (rotateDirection == ROTATE_RIGHT)
		chracterDirection = (chracterDirection + 5) % 6;

	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(getCurrentPlayerInfo(), chracterDirection);
	init();
	stopAllActions();
	runAction(Animate::create(animationDefault));

	setAnchorPoint(Vec2(0.5, 0.13));
	setCurrentDirection(DirectionKind(chracterDirection));

	return;	
}

Character* Character::GetNearCharacter(DirectionKind direction)
{
	return this->getCurrentTile()->GetNearTile(direction)->getCharacterOnThisTile();
}