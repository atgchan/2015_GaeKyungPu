#include "pch.h"
#include "GameMaster.h"

USING_NS_CC;

GameMaster* GameMaster::inst = NULL;



void GameMaster::Run()
{
	this->Phase_Harvest();
	this->Phase_Occupy();
	this->Phase_Volcano();
	this->Phase_Action();
	this->Phase_Pasteur();

	this->ChangePlayer();
}

void GameMaster::Phase_Harvest()
{
	getCurrentPlayerData()->setFood(1);

	//���� ���� Ÿ�� ���� ������ ���簡 �ִٸ� �ش� ���� �Ѹ�� �ķ� 1 ++�ؾ���.
	auto CharacterList = getCurrentPlayerData()->getCharacterList();
	for (auto iter = CharacterList->begin(); iter != CharacterList->end(); ++iter)
	{
		if ((*iter)->getCurrentTile()->getTypeOfTile() == TILE_RICH)
			getCurrentPlayerData()->addFood(1);
	}
}

void GameMaster::Phase_Occupy()
{
	auto CharacterList = getCurrentPlayerData()->getCharacterList();
	for (auto iter = CharacterList->begin(); iter != CharacterList->end(); ++iter)
	{
		if ((*iter)->getCurrentTile()->getOwnerPlayer() == getCurrentPlayer())
		{
			giveTileToPlayer((*iter)->getCurrentTile(), getCurrentPlayer());
		}
	}
}


void GameMaster::Phase_Volcano()
{
	switch (_progressVolcano)
	{
	case 0:
		if (cocos2d::random(1, 5) == 1)//5���� 1 Ȯ���� �̺�Ʈ �߻�
		{
			_isVolcanoActivated = true;
			_progressVolcano = 1;
		}
		break;
	case 1:
		
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	}
}

void GameMaster::Phase_Action()
{

}

void GameMaster::Phase_Pasteur()
{

}

void GameMaster::ChangeRichToLava(Self_Tile* target)
{
	target->changeTile(TILE_LAVA);
	killCharacter(target->getCharacterOnThisTile());
}

void GameMaster::InitializeGame()
{
	this->nodes->setName("MasterNode");
	tileMap = TileMap::getInstance();
	tileMap->create();
	this->addChild(tileMap);
	for (int i = 0; i < numOfPlayer; ++i)
	{
		playerData[numOfPlayer] = PlayerData::create();
	}
}

void GameMaster::mouseDownDispatcher(cocos2d::EventMouse *event)
{
//���� �Է��� ����� �������� Ȯ���ϱ� ���� �׽�Ʈ�ڵ�.
	//�Է��� ����� ���Դٸ� ���콺 ��ư���� �����̰� ���´�.
	int frequency = 0;
	switch (event->getMouseButton())
	{
	case 0:
		frequency = 262;
		break;
	case 2:
		frequency = 294;
		break;
	case 1:
		frequency = 330;
		break;
	default:
		break;
	}
	Beep(frequency, 200);
//�׽�Ʈ�ڵ� ��
}

PlayerData* GameMaster::getCurrentPlayerData()
{
	return playerData[currentPlayer];
}

void GameMaster::ChangePlayer()
{
	if (currentPlayer == PLAYER_RED)
		currentPlayer = PLAYER_BLUE;
	else if (currentPlayer == PLAYER_BLUE)
		currentPlayer = PLAYER_RED;
	else
	{
		Beep(1000, 1000);
		Director::getInstance()->end();
	}
}

void GameMaster::scheduleCallback(float delta)
{

}

void GameMaster::giveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo)
{
	targetTile->setOwnerPlayer(pInfo);
}

void GameMaster::killCharacter(Character* target)
{
	auto CharacterList = getCurrentPlayerData()->getCharacterList();
	for (auto iter = CharacterList->begin(); iter != CharacterList->end(); ++iter)
	{
		if ( (*iter) == target )
		{
			CharacterList->erase(iter);
		}
	}
	TileMap::getInstance()->killCharacter(target);
	
	
}

GameMaster::GameMaster()
{

}

GameMaster::~GameMaster()
{

}
