#include "pch.h"
#include "GameMaster.h"
#include "Character.h"


Character* Character::create(PlayerInfo currentPlayerInfo)
{
	Character* sprite = new Character();

	if (sprite && (sprite->initWithFile(�����̸�)))
	{
		sprite->autorelease();
		sprite->setOwnerCharacter(currentPlayerInfo);
		//��Ÿ �ʿ��Ѱ�
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
