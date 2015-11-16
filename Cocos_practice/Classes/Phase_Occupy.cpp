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
	GameSceneManager* gm = GM;
	std::list<Character*>* CharacterList = gm->getCurrentPlayerData()->getCharacterList();
	for (Character* iter : *CharacterList)
	{
		if (iter->getCurrentTile()->getOwnerPlayer() != gm->getCurrentPlayer())
		{
			gm->GiveTileToPlayer(iter->getCurrentTile(), gm->getCurrentPlayer());
			if (iter->getCurrentTile()->getTypeOfTile() == TILE_VILLAGE)
				iter->getCurrentTile()->ChangeTile(TILE_BARRACK);
		}
	}
	_NextPhase = PHASE_VOLCANO;
}
