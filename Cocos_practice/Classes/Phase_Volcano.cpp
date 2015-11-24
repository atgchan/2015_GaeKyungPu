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
	//��ġ Ÿ�ϸ� ��Ƴ��� ����Ʈ�� �����Ѵ�.
	for (cocos2d::Node* iter : TileMap::getInstance()->getChildren())
	{
		if (static_cast<Self_Tile*>(iter)->getTypeOfTile() == TILE_RICH)
		{
			_VolcanoTileList.pushBack(iter);
		}
	}

	//������ ����Ʈ�� �������� ���´�.
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(_VolcanoTileList.begin(), _VolcanoTileList.end(), g);

	//ȭ������ ��ȭ�� ������ Ÿ���� ����Ų��.
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
		std::srand(std::time(0));
		randNum = std::rand() % 5;
		if (randNum == 1)//5���� 1 Ȯ���� �̺�Ʈ �߻�
		{
			GM->setVolcanoActivated(true);
			GM->setProgressVolcano(0);
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
		GM->ChangeRichToLava(static_cast<Self_Tile*>(*_VolcanoTileListIter));
		_VolcanoTileListIter++; ///# �̷��� �ϸ� ������ ������.. ��? ��� ���ľ� �ұ�?
	}
}

void Phase_Volcano::ChangeAllLavaToPlane()
{
	///# �Ʒ�ó�� ���ͷ����͸� ���� ����ؼ� ��ȸ�� �غ� ��.
	for (Vector<cocos2d::Node*>::iterator iter = _VolcanoTileList.begin(); iter != _VolcanoTileList.end(); ++iter)
	//for (cocos2d::Node* iter : _VolcanoTileList)
	{
		//static_cast<Self_Tile*>(iter)->ChangeTile(TILE_PLAIN);
		dynamic_cast<Self_Tile*>(*iter)->ChangeTile(TILE_PLAIN);
	}
}

void Phase_Volcano::ChangePlanesToRich()
{
	for (cocos2d::Node* iter : _VolcanoTileList)
	{
		static_cast<Self_Tile*>(iter)->ChangeTile(TILE_RICH);
	}
}
