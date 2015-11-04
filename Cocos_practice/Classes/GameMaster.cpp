#include "pch.h"
#include <iostream>
#include "GameMaster.h"

//USING_NS_CC;
#define COCOS2D_DEBUG 1

GameMaster* GameMaster::inst = NULL;




void GameMaster::Phase_Harvest()
{
	getCurrentPlayerData()->setFood(1);

	//만약 옥토 타일 위에 턴주의 병사가 있다면 해당 병사 한명당 식량 1 ++해야함.
	auto CharacterList = getCurrentPlayerData()->getCharacterList(); ///# 코딩 컨벤션: 지역변수는 소문자로 시작하도록 추천.

	for (auto iter : *CharacterList)
	{
		if (iter->getCurrentTile()->getTypeOfTile() == TILE_RICH)
			getCurrentPlayerData()->addFood(1);
	}
	currentPhase = PHASE_OCCUPY;
}

void GameMaster::Phase_Occupy()
{
	auto CharacterList = getCurrentPlayerData()->getCharacterList();
	for (auto iter : *CharacterList)
	{
		if (iter->getCurrentTile()->getOwnerPlayer() == getCurrentPlayer())
		{
			giveTileToPlayer(iter->getCurrentTile(), getCurrentPlayer());
		}
	}
	currentPhase = PHASE_VOLCANO;
}


void GameMaster::Phase_Volcano()
{
	switch (_progressVolcano)
	{
	case 0:
		if (cocos2d::random(1, 5) == 1)//5분의 1 확률로 이벤트 발생
		{
			_isVolcanoActivated = true;
			_progressVolcano = 1;
		}
		break;

	default:
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
		playerData[i] = new PlayerData();  //PlayerData::create();
	}
}

void GameMaster::mouseDownDispatcher(cocos2d::EventMouse *event)
{
	//이하 입력이 제대로 들어오는지 확인하기 위한 테스트코드.
	//입력이 제대로 들어왔다면 마우스 버튼따라서 도레미가 나온다.
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
		for (auto iter : TileList) ///# 버튼 누를때마다 모든 타일을 순회하는것이 좋을까? 더 좋은 방법은 없는가?
		{
			auto tile = getExistingTileWithMousePoint(Vec2(xPos, yPos));
			if (tile != nullptr)
			{
				if (tile->getCharacterOnThisTile() != nullptr)
				{
					Character* target = tile->getCharacterOnThisTile();
					target->rotateToDirection(ROTATE_LEFT, target);
					frequency = 1000;
					break;
				}
				else if (tile->getCharacterOnThisTile() == nullptr) ///# 그냥 else하면 되는거 아닌가?
				{
					Character* sprite = Character::create(getCurrentPlayer());
					sprite->setAnchorPoint(Vec2(0.5, 0.13));

					tile->setCharacterOnThisTile(sprite);
					TileMap::getInstance()->setCharacterOnTile(sprite, tile);
					playerData[getCurrentPlayer()]->addCharacter(sprite);
					sprite->setCurrentTile(tile);
					frequency = 262;
					break;
				}
			}
		}
		break;

	case MOUSE_BUTTON_RIGHT:
		for (auto iter : TileList)
		{
			auto tile = getExistingTileWithMousePoint(Vec2(xPos, yPos));
			if (tile != nullptr)
			{
				if (tile->getCharacterOnThisTile() != nullptr)
				{
					frequency = 1000;
					Character* target = tile->getCharacterOnThisTile();
					target->rotateToDirection(ROTATE_RIGHT, target);
					break;
				}
			}
		}
		frequency = 330;
		break;

	case MOUSE_BUTTON_MIDDLE:
	{
		auto tile = getExistingTileWithMousePoint(Vec2(xPos, yPos));
		if (tile != nullptr)
		{
			if (tile->getCharacterOnThisTile() != nullptr)
			{
				Character* target = tile->getCharacterOnThisTile();
				killCharacter(target);
				//TileMap::getInstance()->removeChild(target);
				//tile->setCharacterOnThisTile(nullptr);
				return;
			}
		}

		frequency = 294;

		break;
	}
	default:
		break;
	}
	//Beep(frequency, 200);
	//테스트코드 끝
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
		
	case PHASE_ACTION:
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
	target->getCurrentTile()->setCharacterOnThisTile(nullptr);
	TileMap::getInstance()->killCharacter(target);
	CharacterList->remove(target);
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

void GameMaster::pushTileToList(Rect rect, Self_Tile* tile)
{
	TILEARRAYSET tileSet;
	tileSet.tile = tile;
	tileSet.rect = rect;

	TileList.push_back(tileSet);
}

Self_Tile* GameMaster::getExistingTileWithMousePoint(Vec2 vec)
{
	for (auto iter : TileList)
	{
		if (iter.rect.containsPoint(vec))
		{
			return iter.tile;
		}
	}
	return nullptr;
}
