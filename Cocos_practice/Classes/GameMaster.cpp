#include "pch.h"
#include "GameMaster.h"

GameMaster* GameMaster::inst = NULL;

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

GameMaster::GameMaster()
{

}

GameMaster::~GameMaster()
{

}
