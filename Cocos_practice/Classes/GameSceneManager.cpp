#include "pch.h"
#include <iostream>
#include "GameSceneManager.h"
#include "Phase.h"
#include "Phase_Harvest.h"
#include "Phase_Occupy.h"
#include "Phase_Volcano.h"
#include "Phase_Action.h"
#include "Phase_Pasteur.h"
#include "DebugUI.h"
#include "BattleManager.h"
#include "DiceDice.h"

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
	_BMInstance = new BattleManager();
	_Nodes = Node::create();
	this->_Nodes->setName("MasterNode");
	_TileMap = TileMap::getInstance();
	_TileMap->create();

	this->addChild(_TileMap);
	for (int i = 0; i < NUM_OF_PLAYER; ++i)
	{
		_PlayerData[i] = new PlayerData();
		_PlayerData[i]->setFood(0);
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

	dice = new DiceDice();
}

void GameSceneManager::EndGame()
{

	_TileMap->Terminate();
	delete(dice);
	delete(this);
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
	return _PlayerData[player];
}

bool GameSceneManager::DraftNewCharacterByClick(Self_Tile* clickedTile)
{
	if (clickedTile == nullptr)
		return false;
	int foodToConsume = 0;
	if (_DraftMode == true)
	{
		//클릭한 타일이 배럭 주변이고 이미 위치한 유닛이 없으면
		if ((draftTile->CheckNearTileAndReturnItsDirection(clickedTile) != IT_IS_NOT_NEAR_TILE) && (clickedTile->getCharacterOnThisTile() == nullptr))
		{
			foodToConsume = (clickedTile->getTypeOfTile() == TILE_FOREST) ? 2 : 1;
			if (getCurrentPlayerData()->getFood() >= foodToConsume)
			{
				int spriteNum = draftTile->CheckNearTileAndReturnItsDirection(clickedTile);
				SpawnCharacterOnTile(draftTile, spriteNum, foodToConsume);
				draftTile->getCharacterOnThisTile()->MovoToTile(clickedTile);
				draftTile = nullptr;
				_DraftMode = false;
				return true;
			}
			
		}
		else
		{
			draftTile = nullptr;
			_DraftMode = false;
			return false;
		}
	}
	else//if (_DraftMode == false)
	{
		if ((clickedTile->getOwnerPlayer() == currentPlayer) && (clickedTile->getTypeOfTile() == TILE_BARRACK || clickedTile->getTypeOfTile() == TILE_HEADQUARTER) && (clickedTile->getCharacterOnThisTile() == nullptr))
		{
			draftTile = clickedTile;
			_DraftMode = true;
			return false;
		}
	}
	return false;
}

void GameSceneManager::MoveCharacterByClick(Self_Tile* clickedTile)
{
	if (clickedTile == nullptr)
		return;
	int foodToComsume = 0;

	if (readyToMove == true)
	{
		foodToComsume = (clickedTile->getTypeOfTile() == TILE_FOREST) ? 2 : 1;
		//클릭한 타일이 옮길 유닛 주변이고 
		if ((characterToMove->getCurrentTile()->CheckNearTileAndReturnItsDirection(clickedTile) == characterToMove->getCurrentDirection()))
		{
			if (clickedTile->getCharacterOnThisTile() == nullptr)//위에 아무 유닛도 없으면
			{
				if (getCurrentPlayerData()->getFood() >= foodToComsume)
				{
					getCurrentPlayerData()->AddFood(foodToComsume * -1);
					characterToMove->MovoToTile(clickedTile);
				}
			}
			else if (clickedTile->getCharacterOnThisTile()->GetOwnerPlayer() != currentPlayer)
				_BMInstance->BattleBetween(characterToMove, clickedTile->getCharacterOnThisTile());
		}
		
		characterToMove = nullptr;
		readyToMove = false;
		return;
	}
	else
	{
		if (clickedTile->getCharacterOnThisTile() != nullptr)
		{
			if (clickedTile->getCharacterOnThisTile()->GetOwnerPlayer() != currentPlayer)
				return;
			characterToMove = clickedTile->getCharacterOnThisTile();
			readyToMove = true;
			return;
		}
	}
}

void GameSceneManager::SpawnCharacterOnTile(Self_Tile* tile, int spriteNum, int spendFood/*=1*/)
{
	Character* unit = Character::create(getCurrentPlayer(), spriteNum);
	unit->SetOwnerPlayer(currentPlayer);
	unit->setAnchorPoint(Vec2(0.5, 0.13));

	TileMap::getInstance()->setCharacterOnTile(unit, tile);
	_PlayerData[getCurrentPlayer()]->AddCharacter(unit);
	unit->setCurrentTile(tile);
	
	getCurrentPlayerData()->AddFood(-1 * spendFood);
}

void GameSceneManager::KeyReleasedDispatcher(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	switch (keyCode)
	{

	case EventKeyboard::KeyCode::KEY_TAB:
	{
		if (_IsDebugingActivated == false)
		{
			DebugUI* DebugingUI = DebugUI::create();
			DebugingUI->SetValue(getPlayerDataByPlayerInfo(PLAYER_RED), getPlayerDataByPlayerInfo(PLAYER_BLUE));
			DebugingUI->setName("debug");
			this->addChild(DebugingUI);
			_IsDebugingActivated = true;
			break;
		}
		else
		{
			this->_Nodes->removeChildByName("debug", true);
			_IsDebugingActivated = false;
			break;
		}
	}
		break;

	default:
		break;
	}
}

void GameSceneManager::mouseDownDispatcher(cocos2d::EventMouse *event)
{
	if (currentPhaseInfo != PHASE_ACTION)
		return;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	float xPos = event->getCursorX();
	float yPos = event->getCursorY() + visibleSize.height;
	auto children = TileMap::getInstance()->getChildren();

	Self_Tile* clickedTile = getTileFromMouseEvent(event);
	switch (event->getMouseButton())
	{
	case MOUSE_BUTTON_LEFT:
		if (clickedTile == nullptr) { break; }
		if(!DraftNewCharacterByClick(clickedTile))
			MoveCharacterByClick(clickedTile);
		break;

	case MOUSE_BUTTON_RIGHT:
		if (clickedTile != nullptr && clickedTile->getCharacterOnThisTile() != nullptr)
		{
			Character* target = clickedTile->getCharacterOnThisTile();
			target->rotateToDirection(ROTATE_RIGHT);
			break;
		}

	case MOUSE_BUTTON_MIDDLE:
		if (clickedTile != nullptr && clickedTile->getCharacterOnThisTile() != nullptr)
		{
			Character* target = clickedTile->getCharacterOnThisTile();
			killCharacter(target);
			break;

			/*_BMInstance->SetAttackFormation(target);
			auto AF = _BMInstance->GetCurrentAttackFormation();
			for (auto i : AF)
				killCharacter(i);*/
		}

	default:
		break;
	}
}

PlayerData* GameSceneManager::getCurrentPlayerData()
{
	return _PlayerData[currentPlayer];
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
	ChangePhase(currentPhase->_NextPhase);
}

void GameSceneManager::GiveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo)
{
	targetTile->setOwnerPlayer(pInfo);
}

void GameSceneManager::killCharacter(Character* target)
{
	auto CharacterList = getPlayerDataByPlayerInfo(target->GetOwnerPlayer())->getCharacterList();
	target->getCurrentTile()->setCharacterOnThisTile(nullptr);
	target->CharacterBeHit();
	TileMap::getInstance()->killCharacter(target);
	CharacterList->remove(target);
}

void GameSceneManager::ChangePhase(PhaseInfo _NextPhase)
{
	currentPhaseInfo = _NextPhase;
	currentPhase = phases[_NextPhase];
}

PlayerInfo GameSceneManager::getCurrentPlayer()
{
	return currentPlayer;
}

void GameSceneManager::addChild(Node* targetNode)
{
	_Nodes->addChild(targetNode);
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
	return;
}

GameSceneManager::~GameSceneManager()
{
	delete(_BMInstance);
	delete dice;
	delete[] phases;
	return;
}