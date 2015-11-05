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
	nodes = Node::create();
	this->nodes->setName("MasterNode");
	tileMap = TileMap::getInstance();
	tileMap->create();
	this->addChild(tileMap);
	for (int i = 0; i < NUM_OF_PLAYER; ++i)
	{
		playerData[i] = new PlayerData();
		playerData[i]->setFood(0);
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

Self_Tile* GameSceneManager::getTileFromMouseEvent(const cocos2d::EventMouse *event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float xPos = event->getCursorX();
	float yPos = event->getCursorY() + visibleSize.height;

	Self_Tile* tile = getExistingTileWithMousePoint(Vec2(xPos, yPos));

	return tile;
}

PlayerData* GameSceneManager::getPlayerDataByPlayerInfo(PlayerInfo player)
{
	return playerData[player];
}

void GameSceneManager::DraftNewCharacterByClick(Self_Tile* clickedTile)
{
	if (clickedTile == nullptr)
		return;

	if (draftMode == true)
	{
		//클릭한 타일이 배럭 주변이고 이미 위치한 유닛이 없으면
		if ((draftTile->CheckTileAndReturnItsType(clickedTile) != IT_IS_NOT_NEAR_TILE) && (clickedTile->getCharacterOnThisTile() == nullptr))
		{
			int spriteNum = draftTile->CheckTileAndReturnItsType(clickedTile);
			SpawnCharacterOnTile(clickedTile, spriteNum);
			draftTile = nullptr;
			draftMode = false;
			return;
		}
		else
		{
			draftTile = nullptr;
			draftMode = false;
			return;
		}
	}
	else//if (draftMode == false)
	{
		if (clickedTile->getTypeOfTile() == TILE_BARRACK || clickedTile->getTypeOfTile() == TILE_HEADQUARTER)
		{
			if (getCurrentPlayerData()->getFood() >= 1)
			{
				draftTile = clickedTile;
				draftMode = true;
				return;
			}
		}
	}
}

void GameSceneManager::SpawnCharacterOnTile(Self_Tile* tile, int spriteNum, bool spendFood/*=true*/)
{
	Character* unit = Character::create(getCurrentPlayer(), spriteNum);
	unit->ownerPlayer = currentPlayer;
	unit->setAnchorPoint(Vec2(0.5, 0.13));

	tile->setCharacterOnThisTile(unit);
	TileMap::getInstance()->setCharacterOnTile(unit, tile);
	playerData[getCurrentPlayer()]->AddCharacter(unit);
	unit->setCurrentTile(tile);
	
	getCurrentPlayerData()->AddFood(-1 * spendFood);

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

	Self_Tile* clickedTile = getTileFromMouseEvent(event);
	switch (event->getMouseButton())
	{
	case MOUSE_BUTTON_LEFT:
		if (clickedTile == nullptr) { break; }
		DraftNewCharacterByClick(clickedTile);


		//돌리는 부분. 추후 함수화
		if (clickedTile->getCharacterOnThisTile() != nullptr)
		{
			Character* target = clickedTile->getCharacterOnThisTile();
			target->rotateToDirection(ROTATE_LEFT, target);
			return;
		}

		break;

	case MOUSE_BUTTON_RIGHT:
		{
			if (clickedTile != nullptr)
			{
				if (clickedTile->getCharacterOnThisTile() != nullptr)
				{
					Character* target = clickedTile->getCharacterOnThisTile();
					target->rotateToDirection(ROTATE_RIGHT, target);
					break;
				}
			}
		}
		break;

	case MOUSE_BUTTON_MIDDLE:
	{
		if (clickedTile != nullptr)
		{
			if (clickedTile->getCharacterOnThisTile() != nullptr)
			{
				Character* target = clickedTile->getCharacterOnThisTile();
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
	auto CharacterList = getPlayerDataByPlayerInfo(target->ownerPlayer)->getCharacterList();
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
	ChangePhase(PHASE_PASTEUR);
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
