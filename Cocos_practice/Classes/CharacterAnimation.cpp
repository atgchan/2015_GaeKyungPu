#include "pch.h"
#include "definition.h"
#include "Character.h"
#include <array>
#include "CharacterAnimation.h"

Animation* CharacterAnimation::CreateAnimationDefault(PlayerInfo cPInfo, int spriteNum)
{
	std::string frameName = "spear_";
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	if (cPInfo == PLAYER_RED || PLAYER_BLUE)
	{
		frameName += "R_";
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Character/unit_red.plist");
	}
	/*else if (cPInfo == PLAYER_BLUE)
	{
		frameName += "B_";
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Character/unit_blue.plist");
	}*/

	std::string direction = GetDirectionName(spriteNum);
	frameName += direction;

	std::array<SpriteFrame*, 4> frameArray =
	{
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_00.png"),
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_01.png"),
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_02.png"),
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_03.png")
	};

	animation->addSpriteFrame(frameArray[0]);
	animation->addSpriteFrame(frameArray[1]);
	animation->addSpriteFrame(frameArray[2]);
	animation->addSpriteFrame(frameArray[3]);
	animation->addSpriteFrame(frameArray[2]);
	animation->addSpriteFrame(frameArray[1]);
	animation->addSpriteFrame(frameArray[0]);

	animation->setLoops(-1);
	return animation;
}

Animation* CharacterAnimation::CreateAnimationMove(int spriteNum)
{
	Animation* animation = Animation::create();
	return animation;
}

Animation* CharacterAnimation::CreateAnimationAttack(PlayerInfo cPInfo, int spriteNum)
{
	Animation* animation = Animation::create();
	return animation;
}

Animation* CharacterAnimation::CreateAnimationBeHit(PlayerInfo cPInfo, int spriteNum)
{
	Animation* animation = Animation::create();
	return animation;
}

std::string CharacterAnimation::GetDirectionName(int spriteNum)
{
	std::string direction = "";
	switch (spriteNum)
	{
	case 0:
		direction = "ld";
		break;
	case 1:
		direction = "d";
		break;
	case 2:
		direction = "rd";
		break;
	case 3:
		direction = "ru";
		break;
	case 4:
		direction = "u";
		break;
	case 5:
		direction = "lu";
		break;
	default:
		direction = "ld";
		break;
	}

	return direction;
}
