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

	//만약 옥토 타일 위에 턴주의 병사가 있다면 해당 병사 한명당 식량 1 ++해야함.
	auto characterList = currentPlayerData->getCharacterList();

	for (auto iter : *characterList)
	{
		if (iter->getCurrentTile()->getTypeOfTile() == TILE_RICH)
			currentPlayerData->AddFood(1);
	}
	_NextPhase = PHASE_OCCUPY;
}