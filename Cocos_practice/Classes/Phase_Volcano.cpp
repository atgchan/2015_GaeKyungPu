#include "pch.h"
#include "Phase_Volcano.h"


Phase_Volcano::Phase_Volcano()
{
}


Phase_Volcano::~Phase_Volcano()
{
}

void Phase_Volcano::Tick()
{
	switch (GM->getProgressVolcano())
	{
	case 0:
		if (cocos2d::random(1, 5) == 1)//5분의 1 확률로 이벤트 발생
		{
			GM->setVolcanoActivated(true);
			GM->setProgressVolcano(1);
		}
		break;

	default:
		break;
	}
	nextPhase = PHASE_ACTION;
}
