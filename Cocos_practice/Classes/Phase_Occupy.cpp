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
	auto gm = GM;
	auto CharacterList = gm->getCurrentPlayerData()->getCharacterList();
	for (auto iter : *CharacterList) ///# 이번 개경프는 auto를 최대한 쓰지 말고 해볼 것.. 타입추론 개념 및 이터래이터 타입에 대한 이해를 확실히 하기 위함.
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
