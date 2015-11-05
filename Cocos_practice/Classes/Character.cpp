#include "pch.h"
#include "definition.h"
#include "Character.h"


Character* Character::create(PlayerInfo cPInfo, int spriteNum)
{
	Character* sprite = new Character();
	//std::string fileName = std::string("Character/spear_"); 
	std::string fileName("Character/spear_"); ///# 이렇게 바로 생성해도 될텐데?

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
		//기타 필요한거

		///# 여기서 리턴하면 new한거는 어찌되노?
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
	else return false; ///# 코딩 컨벤션 맞출것
}

void Character::rotateToDirection(RotateDirection rotateDirection, Character* character)
{
	///# 이 함수가 불릴때마다 아래처럼 리소스이름을 그때그때 스트링으로 생성(1)해서 스프라이트 로딩(2)하는 것은 엄청 비효율적.. 
	// 웬만하면 프로그램 시작시 또는 씬의 시작시에 리소스 로딩할 때 모두 로딩해놓고 사용하도록!!

	std::string fileName = std::string("Character/spear_"); ///# 바로 생성 가능하면 꼭 복사생성 하지 않도록..
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
		if (cAngle == 5) cAngle = 0; ///# 코딩 컨벤션
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
