#include "pch.h"
#include "GameMaster.h"
#include "Character.h"


Character* Character::create(PlayerInfo currentPlayerInfo)
{
	Character* sprite = new Character();

	if (sprite && (sprite->initWithFile(파일이름)))
	{
		sprite->autorelease();
		sprite->setOwnerCharacter(currentPlayerInfo);
		//기타 필요한거
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
