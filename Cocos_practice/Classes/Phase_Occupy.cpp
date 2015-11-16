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
	for (auto iter : *CharacterList) ///# �̹� �������� auto�� �ִ��� ���� ���� �غ� ��.. Ÿ���߷� ���� �� ���ͷ����� Ÿ�Կ� ���� ���ظ� Ȯ���� �ϱ� ����.
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
