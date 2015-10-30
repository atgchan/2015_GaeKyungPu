#include "pch.h"
#include "GameMaster.h"

USING_NS_CC;

GameMaster* GameMaster::inst = NULL;




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
	currentPhase = PHASE_OCCUPY;
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
	currentPhase = PHASE_VOLCANO;
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
	currentPhase = PHASE_ACTION;
}

void GameMaster::Phase_Action()
{

}

void GameMaster::Phase_Pasteur()
{
	currentPhase = PHASE_HARVEST;
	ChangePlayer();
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
	for (int i = 0; i < NUM_OF_PLAYER; ++i)
	{
		playerData[i] = PlayerData::create();
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
	switch (currentPhase)
	{
	case PHASE_HARVEST:
		Phase_Harvest();
		break;
	case PHASE_OCCUPY:
		Phase_Occupy();
		break;
	case PHASE_VOLCANO:
		Phase_Volcano();
		break;
	case PHASE_ACTION:
		break;
	case PHASE_PASTEUR:
		Phase_Pasteur();
		break;
	case PHASE_ERR:
		Beep(1000, 300);
		Director::getInstance()->end();
		break;
	default:
		break;
	}
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
