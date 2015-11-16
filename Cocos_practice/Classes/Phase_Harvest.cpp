#include "pch.h"
#include "Phase_Harvest.h"
#include "UILayer.h"

Phase_Harvest::Phase_Harvest()
{
}


Phase_Harvest::~Phase_Harvest()
{
}

void Phase_Harvest::Tick()
{
	PlayerData* currentPlayerData = GameSceneManager::getInstance()->getCurrentPlayerData();
	currentPlayerData->setFood(1);

	//���� ���� Ÿ�� ���� ������ ���簡 �ִٸ� �ش� ���� �Ѹ�� �ķ� 1 ++�ؾ���.
	auto characterList = currentPlayerData->getCharacterList();

	for (auto iter : *characterList)
	{
		if (iter->getCurrentTile()->getTypeOfTile() == TILE_RICH)
			currentPlayerData->AddFood(1);
	}
	_NextPhase = PHASE_OCCUPY;
}