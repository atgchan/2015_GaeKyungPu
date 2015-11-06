#include "pch.h"
#include "Phase_Occupy.h"

Phase_Occupy::Phase_Occupy()
{
}


Phase_Occupy::~Phase_Occupy()
{
}

void Phase_Occupy::Tick()
{
	auto CharacterList = GM->getCurrentPlayerData()->getCharacterList();
	for (auto iter : *CharacterList)
	{
		if (iter->getCurrentTile()->getOwnerPlayer() == GM->getCurrentPlayer())
		{
			GM->GiveTileToPlayer(iter->getCurrentTile(), GM->getCurrentPlayer());
		}
	}
	nextPhase = PHASE_VOLCANO;
}
