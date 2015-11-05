#include "pch.h"
#include <iostream>
#include "GameSceneManager.h"
#include "Phase.h"
#include "Phase_Harvest.h"
#include "Phase_Occupy.h"
#include "Phase_Volcano.h"
#include "Phase_Action.h"
#include "Phase_Pasteur.h"


//USING_NS_CC;
#define COCOS2D_DEBUG 1

GameSceneManager* GameSceneManager::inst = NULL;

void GameSceneManager::ChangeRichToLava(Self_Tile* target)
{
	target->changeTile(TILE_LAVA);
	killCharacter(target->getCharacterOnThisTile());
}

void GameSceneManager::InitializeGame()
{
	this->nodes->setName("MasterNode");
	tileMap = TileMap::getInstance();
	tileMap->create();
	this->addChild(tileMap);
	for (int i = 0; i < NUM_OF_PLAYER; ++i)
	{
		playerData[i] = new PlayerData();
	}
	
	phases[PHASE_READY] = nullptr;
	phases[PHASE_HARVEST] = new Phase_Harvest();
	phases[PHASE_OCCUPY] = new Phase_Occupy();
	phases[PHASE_VOLCANO] = new Phase_Volcano();
	phases[PHASE_ACTION] = new Phase_Action();
	phases[PHASE_PASTEUR] = new Phase_Pasteur();
	phases[PHASE_ERR] = nullptr;

	currentPlayer = PLAYER_RED;
	currentPhase = phases[PHASE_HARVEST];
}

void GameSceneManager::mouseDownDispatcher(cocos2d::EventMouse *event)
{
	if (currentPhaseInfo != PHASE_ACTION)
		return;

	int frequency = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	float xPos = event->getCursorX();
	float yPos = event->getCursorY() + visibleSize.height;
	auto children = TileMap::getInstance()->getChildren();

	switch (event->getMouseButton())
	{
	case MOUSE_BUTTON_LEFT:
		{
			auto tile = getExistingTileWithMousePoint(Vec2(xPos, yPos));
			if (tile != nullptr)
			{
				if (tile->getCharacterOnThisTile() != nullptr)
				{
					Character* target = tile->getCharacterOnThisTile();
					target->rotateToDirection(ROTATE_LEFT, target);
					break;
				}
				else
				{
					Character* sprite = Character::create(getCurrentPlayer());
					sprite->setAnchorPoint(Vec2(0.5, 0.13));

					tile->setCharacterOnThisTile(sprite);
					TileMap::getInstance()->setCharacterOnTile(sprite, tile);
					playerData[getCurrentPlayer()]->AddCharacter(sprite);
					sprite->setCurrentTile(tile);
					break;
				}
			}
		}
		break;

	case MOUSE_BUTTON_RIGHT:
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
				return;
			}
		}
		break;
	}
	default:
		break;
	}
}

PlayerData* GameSceneManager::getCurrentPlayerData()
{
	return playerData[currentPlayer];
}

void GameSceneManager::ChangePlayer()
{
	if (currentPhaseInfo != PHASE_ACTION)
		return;

	if (currentPlayer == PLAYER_RED || currentPlayer == PLAYER_BLUE)
	{
		currentPlayer = (PlayerInfo)((currentPlayer + 1) % 2);
	}
	else
	{	Director::getInstance()->end();	}
}

void GameSceneManager::scheduleCallback(float delta)
{
	currentPhase->Tick();
	ChangePhase(currentPhase->nextPhase);
}

void GameSceneManager::GiveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo)
{
	targetTile->setOwnerPlayer(pInfo);
}

void GameSceneManager::killCharacter(Character* target)
{
	auto CharacterList = getCurrentPlayerData()->getCharacterList();
	target->getCurrentTile()->setCharacterOnThisTile(nullptr);
	TileMap::getInstance()->killCharacter(target);
	CharacterList->remove(target);
}

void GameSceneManager::ChangePhase(PhaseInfo nextPhase)
{
	currentPhaseInfo = nextPhase;
	currentPhase = phases[nextPhase];
}

PlayerInfo GameSceneManager::getCurrentPlayer()
{
	return currentPlayer;
}

void GameSceneManager::addChild(Node* targetNode)
{
	nodes->addChild(targetNode);
}

void GameSceneManager::toggleTurn(Object* pSender)
{
	if (currentPhaseInfo != PHASE_ACTION)
		return;

	ChangePlayer();
	currentPhaseInfo = PHASE_PASTEUR;
}

void GameSceneManager::pushTileToList(Rect rect, Self_Tile* tile)
{
	TILEARRAYSET tileSet;
	tileSet.tile = tile;
	tileSet.rect = rect;

	TileList.push_back(tileSet);
}

Self_Tile* GameSceneManager::getExistingTileWithMousePoint(Vec2 vec)
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

GameSceneManager::GameSceneManager()
{

}

GameSceneManager::~GameSceneManager()
{

}