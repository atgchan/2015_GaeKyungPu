#include "pch.h"
#include "GameMaster.h"
#include "PlayerData.h"

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

	//만약 옥토 타일 위에 턴주의 병사가 있다면 해당 병사 한명당 식량 1 ++해야함.
	auto CharacterList = getCurrentPlayerData()->getCharacterList();
	for (auto iter = CharacterList->begin(); iter != CharacterList->end(); ++iter)
	{
		if (iter->getCurrentTile()->getTypeOfTile() == TILE_RICH)
			getCurrentPlayerData()->addFood(1);
	}
}

void GameMaster::Phase_Occupy()
{
	auto CharacterList = getCurrentPlayerData()->getCharacterList();
	for (auto iter = CharacterList->begin(); iter != CharacterList->end(); ++iter)
	{
		if (iter->getCurrentTile()->getOwnerPlayer() == getCurrentPlayer())
		{
			giveTileToPlayer(iter->getCurrentTile(), getCurrentPlayer());
		}
	}
}


void GameMaster::giveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo)
{
	
	targetTile->setOwnerPlayer(pInfo);
}

void GameMaster::InitializeGame()
{
	this->nodes->setName("MasterNode");
	tileMap = TileMap::getInstance();
	tileMap->create();
	this->addChild(tileMap);
}

void GameMaster::mouseDownDispatcher(EventMouse *event)
{
//이하 입력이 제대로 들어오는지 확인하기 위한 테스트코드.
	//입력이 제대로 들어왔다면 마우스 버튼따라서 도레미가 나온다.
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
//테스트코드 끝
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

GameMaster::GameMaster()
{

}

GameMaster::~GameMaster()
{

}
