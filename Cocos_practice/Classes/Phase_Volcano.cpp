#include "pch.h"
#include "Phase_Volcano.h"
#include "TileMap.h"
#include <cstdlib>
#include <ctime>


Phase_Volcano::Phase_Volcano()
{
}


Phase_Volcano::~Phase_Volcano()
{
}

void Phase_Volcano::Tick()
{
	int randNum;
	if (GM->getIsVolcanoActivated())
	{
		GM->setVolcanoActivated(false);
		GM->setProgressVolcano(0);
	}
	switch (GM->getProgressVolcano())
	{
	case 0: 
		std::srand(std::time(0));
		randNum = (std::rand() % 5);
		if (randNum == 1)//5분의 1 확률로 이벤트 발생
		{
			GM->setVolcanoActivated(true);
			GM->setProgressVolcano(1);
			cocos2d::Label* explositionMent = cocos2d::Label::createWithTTF("Fire in the hole!!!!!", "fonts/Marker Felt.ttf", 20);
			explositionMent->setPosition(cocos2d::Vec2(200, 300));
			TileMap::getInstance()->addChild(explositionMent);
		}
		break;

	default:
		break;
	}

	_NextPhase = PHASE_ACTION;
}
