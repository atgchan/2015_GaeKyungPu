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

	if (sprite && (sprite->initWithFile(fileName))) ///# sprite를 널체크 할 필요가 있나? 
	{
		sprite->autorelease();
		sprite->setCurrentPlayerInfo(cPInfo);
		sprite->setCurrentDirection((DirectionKind)spriteNum);
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
		return true;
	else
		return false;
}

void Character::rotateToDirection(RotateDirection rotateDirection, Character* character)
{
	///# 이 함수가 불릴때마다 아래처럼 리소스이름을 그때그때 스트링으로 생성(1)해서 스프라이트 로딩(2)하는 것은 엄청 비효율적.. 
	// 웬만하면 프로그램 시작시 또는 씬의 시작시에 리소스 로딩할 때 모두 로딩해놓고 사용하도록!!

	std::string fileName = std::string("Character/spear_"); ///# 바로 생성 가능하면 꼭 복사생성 하지 않도록..

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
