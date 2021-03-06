#include "pch.h"
#include "Phase_Volcano.h"
#include "TileMap.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <iterator>
#include "SimpleAudioEngine.h"
#include "DiceDice.h"
#include "EventManager.h"
#include "HistoryEventChangeTile.h"
#include "definition.h"

Phase_Volcano::Phase_Volcano()
{
	_VolcanoTileList = TileMap::getInstance()->getRichTiles();
	_Gen = std::mt19937(_RandomDevice());
	std::srand(std::time(0));
	
	//용암으로 변화를 시작할 타일을 가리킨다.
	_VolcanoTileListIter = _VolcanoTileList.begin();
	_PhaseInfo = PHASE_VOLCANO;
}

void Phase_Volcano::Tick()
{
	if (false == GM->getIsVolcanoActivated())
	{
		int randNum = DiceDice::getInstance()->RollDiceBetween(1, 5);
		if (randNum == 1)//5분의 1 확률로 이벤트 발생
		{
			GM->setVolcanoActivated(true);
			ChangeVolcanoActivted();
			GM->setProgressVolcano(0);
			std::shuffle(_VolcanoTileList.begin(), _VolcanoTileList.end(), _Gen);
		}
	}

	switch (GM->getProgressVolcano())
	{
	case 0:
	case 1:
	case 2:
	case 3:
		ChangeRichToLava(GM->getProgressVolcano());
		GM->setProgressVolcano(GM->getProgressVolcano() + 1);
		break;

	case 4:
		ChangeAllLavaToPlane();
		ChangeVolcanoDisactivted();
		GM->setProgressVolcano(5);
		break;

	case 5:
		GM->setVolcanoActivated(false);
		GM->setProgressVolcano(-1);
		ChangePlanesToRich();
		_VolcanoTileListIter = _VolcanoTileList.begin();
		break;

	default:
		break;
	}

	GM->ResetCharacterMovable();

	_NextPhaseInfo = PHASE_ACTION;
}

void Phase_Volcano::ChangeRichToLava(int repeat)
{
	for (int i = 0; i < repeat; i++)
	{
		EventManager::getInstance()->AddHistory(HistoryEventChangeTile::Create(*_VolcanoTileListIter, TILE_LAVA));
		if ((*_VolcanoTileListIter)->getCharacterOnThisTile() != nullptr)
			GM->KillCharacter((*_VolcanoTileListIter)->getCharacterOnThisTile());

		++_VolcanoTileListIter;
	}
}

void Phase_Volcano::ChangeAllLavaToPlane()
{
	for (Vector<Self_Tile*>::iterator iter = _VolcanoTileList.begin(); iter != _VolcanoTileList.end(); ++iter)
	{
		EventManager::getInstance()->AddHistory(HistoryEventChangeTile::Create(*iter, TILE_PLAIN));
	}
}

void Phase_Volcano::ChangePlanesToRich()
{
	for (Self_Tile* iter : _VolcanoTileList)
	{
		EventManager::getInstance()->AddHistory(HistoryEventChangeTile::Create(iter, TILE_RICH));
	}
}

void Phase_Volcano::ChangeVolcanoActivted()
{
	for (Self_Tile* iter : TileMap::getInstance()->getVolcanoTiles())
	{
		EventManager::getInstance()->AddHistory(HistoryEventChangeTile::Create(iter, TILE_VOLCANO_ACTIVATED));
	}
}

void Phase_Volcano::ChangeVolcanoDisactivted()
{
	for (Self_Tile* iter : TileMap::getInstance()->getVolcanoTiles())
	{
		EventManager::getInstance()->AddHistory(HistoryEventChangeTile::Create(iter, TILE_VOLCANO));
	}
}