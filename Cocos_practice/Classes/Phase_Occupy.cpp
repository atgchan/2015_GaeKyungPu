#include "pch.h"
#include "Phase_Occupy.h"
#include "UILayer.h"

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
			if (iter->getCurrentTile()->getTypeOfTile() == TILE_VILLAGE)
			{
				iter->getCurrentTile()->ChangeTile(TILE_BARRACK);
			}
			if (iter->getCurrentTile()->getTypeOfTile() == TILE_BARRACK || iter->getCurrentTile()->getTypeOfTile() == TILE_HEADQUARTER)
			{
				iter->getCurrentTile()->ChangeTile(TILE_BARRACK);
				gm->getCurrentPlayerData()->_PlayerBarrackNum++;

				PlayerInfo opponent = GM->getCurrentPlayer() == PLAYER_RED ? PLAYER_BLUE : PLAYER_RED;
				gm->getPlayerDataByPlayerInfo(opponent)->_PlayerBarrackNum--;
			}

			PlayerInfo opponent = iter->getCurrentTile()->getOwnerPlayer();
			if ((opponent == PLAYER_BLUE || opponent == PLAYER_RED) && gm->getPlayerDataByPlayerInfo(opponent)->_PlayerBarrackNum <= 0)
			{
				gm->EndGame();
			}
			gm->GiveTileToPlayer(iter->getCurrentTile(), gm->getCurrentPlayer());
		}
	}
	_NextPhase = PHASE_VOLCANO;
}
