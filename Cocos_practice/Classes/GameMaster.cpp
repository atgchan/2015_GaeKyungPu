#include "pch.h"
#include <iostream>
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
	if (currentPhase != PHASE_ACTION)
		return;

	int frequency = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	float xPos = event->getCursorX();
	float yPos = event->getCursorY() + visibleSize.height;

	auto children = TileMap::getInstance()->getChildren();
	
	switch (event->getMouseButton())
	{
	case MOUSE_BUTTON_LEFT:
		for (auto iter = children.begin(); iter != children.end(); ++iter)
		{
			if ((*iter)->getBoundingBox().containsPoint(Vec2(xPos, yPos)))
			{
				Self_Tile* tile = dynamic_cast<Self_Tile*> (*iter);
				if (!tile)
					break;

				if (tile->getCharacterOnThisTile() != nullptr)
				{
					Character* target = tile->getCharacterOnThisTile();
					target->rotateToDirection(ROTATE_LEFT, target);
					frequency = 1000;
				}

				if (tile->getCharacterOnThisTile() == nullptr)
				{
					Character* sprite = Character::create(getCurrentPlayer());
					sprite->setAnchorPoint(Vec2(0.5, 0.13));

					tile->setCharacterOnThisTile(sprite);
					TileMap::getInstance()->setCharacterOnTile(sprite, tile);
					playerData[getCurrentPlayer()]->addCharacter(sprite);
					sprite->setCurrentTile(tile);
					frequency = 262;
				}
			}
		}
		break;

	case MOUSE_BUTTON_RIGHT:
		for (auto iter = children.begin(); iter != children.end(); ++iter)
		{
			if ((*iter)->getBoundingBox().containsPoint(Vec2(xPos, yPos)))
			{
				Self_Tile* tile = dynamic_cast<Self_Tile*> (*iter);
				if (!tile)
					break;

				if (tile->getCharacterOnThisTile() != nullptr)
				{
					frequency = 1000;
					Character* target = tile->getCharacterOnThisTile();
					target->rotateToDirection(ROTATE_RIGHT, target);
				}
			}
		}
		frequency = 330;
		break;

	case MOUSE_BUTTON_MIDDLE:
		for (auto iter = children.begin(); iter != children.end(); ++iter)
		{
			if ((*iter)->getBoundingBox().containsPoint(Vec2(xPos, yPos)))
			{
				Self_Tile* tile = dynamic_cast<Self_Tile*> (*iter);
				if (!tile)
					break;

				if (tile->getCharacterOnThisTile() != nullptr)
				{
					Character* target = tile->getCharacterOnThisTile();
					TileMap::getInstance()->removeChild(target);
					tile->setCharacterOnThisTile(nullptr);
					children.erase(iter);
					return;
				}
			}
		}
		frequency = 294;
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
	if (currentPhase != PHASE_ACTION)
		return;

	if (currentPlayer == PLAYER_RED)
	{
		currentPlayer = PLAYER_BLUE;
		return;
	}
	if (currentPlayer == PLAYER_BLUE)
	{
		currentPlayer = PLAYER_RED;
		return;
	}
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
		Phase_Action();
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

PlayerInfo GameMaster::getCurrentPlayer()
{
	return currentPlayer;
}

void GameMaster::addChild(Node* targetNode)
{
	nodes->addChild(targetNode);
}

void GameMaster::toggleTurn(Object* pSender)
{
	if (currentPhase != PHASE_ACTION)
		return;

	ChangePlayer();
	Beep(262, 300);
	Beep(294, 300);
	Beep(330, 300);
	currentPhase = PHASE_PASTEUR;
}

GameMaster::GameMaster()
{

}

GameMaster::~GameMaster()
{

}
