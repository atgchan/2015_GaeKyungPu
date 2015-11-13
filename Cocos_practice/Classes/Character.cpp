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

//	파일 명 때문에 Red Blue 구분은 CharacterAnimation내부에서 구분한다.
//	create은 그저 캐릭터 객체를 만들 뿐, 실제 그래픽 구현은 CharacterAnimation에서 처리하는 형식

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