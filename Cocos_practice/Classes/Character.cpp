#include "pch.h"
#include "definition.h"
#include "Character.h"


Character* Character::create(PlayerInfo cPInfo, int spriteNum)
{
	Character* sprite = new Character();
	//std::string fileName = std::string("Character/spear_"); 
	std::string fileName("Character/spear_"); ///# �̷��� �ٷ� �����ص� ���ٵ�?

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

	if (sprite && (sprite->initWithFile(fileName)))
	{
		sprite->autorelease();
		sprite->setCurrentPlayerInfo(cPInfo);
		sprite->setCurrentAngle(ANGLE_DOWN_LEFT);
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
	{
		return true;
	}
	else return false; ///# �ڵ� ������ �����
}

void Character::rotateToDirection(RotateDirection rotateDirection, Character* character)
{
	///# �� �Լ��� �Ҹ������� �Ʒ�ó�� ���ҽ��̸��� �׶��׶� ��Ʈ������ ����(1)�ؼ� ��������Ʈ �ε�(2)�ϴ� ���� ��û ��ȿ����.. 
	// �����ϸ� ���α׷� ���۽� �Ǵ� ���� ���۽ÿ� ���ҽ� �ε��� �� ��� �ε��س��� ����ϵ���!!

	std::string fileName = std::string("Character/spear_"); ///# �ٷ� ���� �����ϸ� �� ������� ���� �ʵ���..
	if (character->getCurrentPlayerInfo() == PLAYER_RED)
	{
		fileName += std::string("red");
	}
	else if (character->getCurrentPlayerInfo() == PLAYER_BLUE)
	{
		fileName += std::string("blue");
	}

	int cAngle = character->getCurrentAngle();

	if (rotateDirection == ROTATE_LEFT)
	{
		if (cAngle == 5) cAngle = 0; ///# �ڵ� ������
		else cAngle++;

		std::ostringstream ostr;
		ostr << cAngle;
		fileName += std::string("_0");
		fileName += std::string(ostr.str());
		fileName += std::string(".png");
	}
	else if (rotateDirection == ROTATE_RIGHT)
	{
		if (cAngle == 0) cAngle = 5;
		else cAngle--;

		std::ostringstream ostr;
		ostr << cAngle;
		fileName += std::string("_0");
		fileName += std::string(ostr.str());
		fileName += std::string(".png");
	}
	character->setCurrentAngle(CharacterAngle(cAngle));

	character->initWithFile(fileName);
	character->setAnchorPoint(Point(0.5, 0.13));
}
