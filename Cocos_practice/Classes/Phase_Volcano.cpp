#include "pch.h"
#include "Phase_Volcano.h"
#include "TileMap.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <iterator>
#include "SimpleAudioEngine.h"

Phase_Volcano::Phase_Volcano()
{
	_VolcanoTileList = TileMap::getInstance()->getRichTiles();
	_Gen = std::mt19937(_RandomDevice());
	std::srand(std::time(0));
	
	//std::random_shuffle(_VolcanoTileList.begin(), _VolcanoTileList.end());
	//화산으로 변화를 시작할 타일을 가리킨다.
	_VolcanoTileListIter = _VolcanoTileList.begin();
}


Phase_Volcano::~Phase_Volcano()
{
}

void Phase_Volcano::Tick()
{
	if (false == GM->getIsVolcanoActivated())
	{
		int randNum;
		randNum = std::rand() % 5;
		if (randNum == 1)//5분의 1 확률로 이벤트 발생
		{
			GM->setVolcanoActivated(true);
			GM->setProgressVolcano(0);
			std::shuffle(_VolcanoTileList.begin(), _VolcanoTileList.end(), _Gen);
		}
	}

	switch (GM->getProgressVolcano())
	{
	case 0:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/lava-01.wav");
		GM->setProgressVolcano(1);
		break;
	case 1:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/lava-01.wav");
		ChangeRichToLava(1);
		GM->setProgressVolcano(2);
		break;
	case 2:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/lava-01.wav");
		ChangeRichToLava(2);
		GM->setProgressVolcano(3);
		break;
	case 3:
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/lava-01.wav");
		ChangeRichToLava(3);
		GM->setProgressVolcano(4);
		break;
	case 4:
		ChangeAllLavaToPlane();
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

	_NextPhase = PHASE_ACTION;
}

void Phase_Volcano::ChangeRichToLava(int repeat)
{
	for (int i = 0; i < repeat; i++)
	{
		GM->ChangeRichToLava(*_VolcanoTileListIter);
		++_VolcanoTileListIter;
	}
}

void Phase_Volcano::ChangeAllLavaToPlane()
{
	for (Vector<std::shared_ptr<Self_Tile>>::iterator iter = _VolcanoTileList.begin(); iter != _VolcanoTileList.end(); ++iter)
	{
		static_cast<std::shared_ptr<Self_Tile>>(*iter)->ChangeTile(TILE_PLAIN);
	}
}

void Phase_Volcano::ChangePlanesToRich()
{
	for (std::shared_ptr<Self_Tile> iter : _VolcanoTileList)
	{
		iter->ChangeTile(TILE_RICH);
	}
}