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
		if (cocos2d::random(1, 5) == 1)//5���� 1 Ȯ���� �̺�Ʈ �߻�
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
