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

GameMaster::GameMaster()
{

}

GameMaster::~GameMaster()
{

}
