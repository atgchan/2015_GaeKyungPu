#include "pch.h"
#include "definition.h"
#include "Character.h"


Character* Character::create(PlayerInfo cPInfo, int spriteNum)
{
	Character* sprite = new Character();
	std::string fileName("Character/spear_");

	if (cPInfo == PLAYER_RED)
	{
		fileName += std::string("red");
	}
	else if (cPInfo == PLAYER_BLUE)
	{
		fileName += std::string("blue");
	}
	fileName += std::string("_0");
	fileName += std::to_string(spriteNum);
	fileName += std::string(".png");

	if (sprite && (sprite->initWithFile(fileName))) ///# sprite�� ��üũ �� �ʿ䰡 �ֳ�? 
	{
		sprite->autorelease();
		sprite->setCurrentPlayerInfo(cPInfo);
		sprite->setCurrentDirection((DirectionKind)spriteNum);
		//��Ÿ �ʿ��Ѱ�

		///# ���⼭ �����ϸ� new�ѰŴ� ����ǳ�?
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Character::isOnTile(TileKind tileTypeToCheck)
{
	if (this->getCurrentTile()->getTypeOfTile() == tileTypeToCheck)
		return true;
	else
		return false;
}

void Character::rotateToDirection(RotateDirection rotateDirection, Character* character)
{
	///# �� �Լ��� �Ҹ������� �Ʒ�ó�� ���ҽ��̸��� �׶��׶� ��Ʈ������ ����(1)�ؼ� ��������Ʈ �ε�(2)�ϴ� ���� ��û ��ȿ����.. 
	// �����ϸ� ���α׷� ���۽� �Ǵ� ���� ���۽ÿ� ���ҽ� �ε��� �� ��� �ε��س��� ����ϵ���!!

	std::string fileName = std::string("Character/spear_"); ///# �ٷ� ���� �����ϸ� �� ������� ���� �ʵ���..

	if (character->getCurrentPlayerInfo() == PLAYER_RED)
		fileName += std::string("red");
	
	if (character->getCurrentPlayerInfo() == PLAYER_BLUE)
		fileName += std::string("blue");

	int chracterDirection = character->getCurrentDirection();

	if (rotateDirection == ROTATE_LEFT)
		chracterDirection = (chracterDirection + 1)%6;
	
	if (rotateDirection == ROTATE_RIGHT)
		chracterDirection = (chracterDirection + 5) % 6;
	
	fileName += std::string("_0");
	fileName += std::to_string(chracterDirection);
	fileName += std::string(".png");

	character->setCurrentDirection(DirectionKind(chracterDirection));
	character->initWithFile(fileName);
	character->setAnchorPoint(Point(0.5, 0.13));
}

Character* Character::GetNearCharacter(DirectionKind direction)
{
	return this->getCurrentTile()->GetNearTile(direction)->getCharacterOnThisTile();
}
