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
#include "EventManager.h"
#include "HistoryEventKillCharacter.h"
#include "ResultLayer.h"
#include "CharacterAnimation.h"

//USING_NS_CC;
#define COCOS2D_DEBUG 1

GameSceneManager* GameSceneManager::_Inst = nullptr;


GameSceneManager* GameSceneManager::getInstance()
{
	if (_Inst == nullptr)
	{
		CharacterAnimation::getInstance()->Init();
		_Inst = new GameSceneManager();
	}
	return _Inst;
}

GameSceneManager::GameSceneManager()
{
}

GameSceneManager::~GameSceneManager()
{
	delete _BMInstance;
	delete _Dice;

	for (int i = 0; i != MAX_PHASE; ++i)
	{
		delete _Phases[i];
	}
	delete[] _Phases;
	_TileMap->Terminate();
}

void GameSceneManager::InitializeGame()
{
	_BMInstance = new BattleManager();
	_Nodes = Node::create();
	_Dice = new DiceDice();
	_TileMap = TileMap::getInstance();

	_TileMap->create();
	this->AddChild(_TileMap);

	for (int i = 0; i < NUM_OF_PLAYER; ++i)
	{
		_PlayerData[i] = new PlayerData(0, 1);
	}

	_Phases[PHASE_READY] = nullptr;
	_Phases[PHASE_HARVEST] = new Phase_Harvest();
	_Phases[PHASE_OCCUPY] = new Phase_Occupy();
	_Phases[PHASE_VOLCANO] = new Phase_Volcano();
	_Phases[PHASE_ACTION] = new Phase_Action();
	_Phases[PHASE_PASTEUR] = new Phase_Pasteur();
	_Phases[PHASE_ERR] = nullptr;

	_CurrentPlayer = PLAYER_RED;
	_CurrentPhase = _Phases[PHASE_HARVEST];	
}

void GameSceneManager::EndGame()
{
	Director::getInstance()->pause();
	ResultLayer* result = ResultLayer::create();
	AddChild(result);
}

Self_Tile* GameSceneManager::getTileFromMouseEvent(const cocos2d::EventMouse *event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	float xPos = event->getCursorX();
	float yPos = event->getCursorY() + visibleSize.height;

	for (auto iter = _TileList.begin(); iter != _TileList.end(); ++iter)
	{
		if (iter->rect.containsPoint(Vec2(xPos, yPos)))
		{
			return iter->tile;
		}
	}

	//std::shared_ptr<Self_Tile> tile = getExistingTileWithMousePoint(Vec2(xPos, yPos));

	//return tile;
}
//
//std::shared_ptr<Self_Tile> GameSceneManager::getExistingTileWithMousePoint(Vec2 vec)
//{
//	for (auto iter = _TileList.begin(); iter != _TileList.end(); ++iter)
//	{
//		if (iter->rect.containsPoint(vec))
//		{
//			return iter->tile;
//		}
//	}
//	return nullptr;
//}

bool GameSceneManager::DraftNewCharacterByClick(Self_Tile* clickedTile)
{
	if (clickedTile == nullptr)
		return false;
	int foodToConsume = 0;
	if (_DraftMode == true)
	{

		//클릭한 타일이 배럭 주변이고 이미 위치한 유닛이 없으면
		if (!(clickedTile->getTypeOfTile() == TILE_LAVA || clickedTile->getTypeOfTile() == TILE_VOCANO || clickedTile->getTypeOfTile() == TILE_NULL || clickedTile->getTypeOfTile() == TILE_LAKE))
		{
			if (_DraftTile->CheckNearTile(clickedTile) && (clickedTile->getCharacterOnThisTile() == nullptr))
			{
				foodToConsume = (clickedTile->getTypeOfTile() == TILE_FOREST) ? 2 : 1;
				if (getCurrentPlayerData()->getFood() >= foodToConsume)
				{
					DirectionKind direction = _DraftTile->ReturnNearTileDirection(clickedTile);
					SpawnCharacterOnTile(_DraftTile, direction, foodToConsume);
					_DraftTile->getCharacterOnThisTile()->MovoToTile(clickedTile);
					_DraftTile = nullptr;
					_DraftMode = false;
					//AnimationManager::getInstance()->PlayHistory();
					return true;
				}
			}
			else
			{
				_DraftTile = nullptr;
				_DraftMode = false;
				return false;
			}
		}
	}
	else//if (_DraftMode == false)
	{
		if ((clickedTile->getOwnerPlayer() == _CurrentPlayer) && (clickedTile->getTypeOfTile() == TILE_BARRACK || clickedTile->getTypeOfTile() == TILE_HEADQUARTER) && (clickedTile->getCharacterOnThisTile() == nullptr))
		{
			SelectBarrack(clickedTile);
			_DraftTile = clickedTile;
			_DraftMode = true;
			ShowSpawnableTile(clickedTile);

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

	if (_ReadyToMove == true)
	{
		foodToComsume = (clickedTile->getTypeOfTile() == TILE_FOREST) ? 2 : 1;
		//클릭한 타일이 옮길 유닛 주변이고 
		if (!(clickedTile->getTypeOfTile() == TILE_LAVA || clickedTile->getTypeOfTile() == TILE_VOCANO || clickedTile->getTypeOfTile() == TILE_NULL || clickedTile->getTypeOfTile() == TILE_LAKE))
		{
			if ((_CharacterToMove->getCurrentTile()->ReturnNearTileDirection(clickedTile) == _CharacterToMove->getCurrentDirection()))
			{

				if (clickedTile->getCharacterOnThisTile() == nullptr)//위에 아무 유닛도 없으면
				{
					if (getCurrentPlayerData()->getFood() >= foodToComsume)
					{
						getCurrentPlayerData()->AddFood(foodToComsume * -1);
						_CharacterToMove->MovoToTile(clickedTile);
					}
				}
				else if (clickedTile->getCharacterOnThisTile()->GetOwnerPlayer() != _CurrentPlayer)
				{
					if (getCurrentPlayerData()->getFood() >= foodToComsume)
					{
						getCurrentPlayerData()->AddFood(foodToComsume * -1);
						_BMInstance->BattleBetween(_CharacterToMove, clickedTile->getCharacterOnThisTile());
					}
				}
				//AnimationManager::getInstance()->PlayHistory();
			}
		}

		_CharacterToMove = nullptr;
		_ReadyToMove = false;
		return;
	}
	else
	{
		if (clickedTile->getCharacterOnThisTile() != nullptr)
		{
			if (clickedTile->getCharacterOnThisTile()->GetOwnerPlayer() != _CurrentPlayer)
				return;
			_CharacterToMove = clickedTile->getCharacterOnThisTile();
			_ReadyToMove = true;
			return;
		}
	}
}

void GameSceneManager::SpawnCharacterOnTile(Self_Tile* tile, DirectionKind spriteNum, int spendFood/*=1*/)
{
	std::shared_ptr<Character> unit = Character::create(getCurrentPlayer(), spriteNum);
	unit->SetOwnerPlayer(_CurrentPlayer);
	unit->setAnchorPoint(Vec2(0.5f, 0.13f));

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
			this->AddChild(DebugingUI);
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

void GameSceneManager::MouseDownDispatcher(cocos2d::EventMouse *event)
{
	if (_CurrentPhaseInfo != PHASE_ACTION)
		return;
	if (_IsInputAble == false)
		return;

	Unselect();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float xPos = event->getCursorX();
	float yPos = event->getCursorY() + visibleSize.height;

	Self_Tile* clickedTile = getTileFromMouseEvent(event);
	switch (event->getMouseButton())
	{
	case MOUSE_BUTTON_LEFT:
		if (clickedTile == nullptr)
			break;

		if (!DraftNewCharacterByClick(clickedTile))
		{
			SelectCharacter(clickedTile->getCharacterOnThisTile());
			MoveCharacterByClick(clickedTile);
		}

		break;

	case MOUSE_BUTTON_RIGHT:
		if (clickedTile != nullptr && clickedTile->getCharacterOnThisTile() != nullptr && clickedTile->getCharacterOnThisTile()->GetOwnerPlayer() == _CurrentPlayer)
		{
			std::shared_ptr<Character> target = clickedTile->getCharacterOnThisTile();
			target->RotateToDirection(ROTATE_RIGHT);
			clickedTile->getCharacterOnThisTile()->ShowMovableTile();
			break;
		}

	case MOUSE_BUTTON_MIDDLE:
		if (clickedTile != nullptr && clickedTile->getCharacterOnThisTile() != nullptr && clickedTile->getCharacterOnThisTile()->GetOwnerPlayer() == _CurrentPlayer)
		{
			std::shared_ptr<Character> target = clickedTile->getCharacterOnThisTile();
			target->RotateToDirection(ROTATE_LEFT);
			clickedTile->getCharacterOnThisTile()->ShowMovableTile();
			break;
		}

	default:
		break;
	}
}

PlayerData* GameSceneManager::getCurrentPlayerData()
{
	return _PlayerData[_CurrentPlayer];
}

void GameSceneManager::ChangePlayer()
{
	if (_CurrentPlayer == PLAYER_RED || _CurrentPlayer == PLAYER_BLUE)
		_CurrentPlayer = (PlayerInfo)((_CurrentPlayer + 1) % 2);
	else
		Director::getInstance()->end();
}

void GameSceneManager::ScheduleCallback(float delta)
{
	EventManager::getInstance()->ScheduleCallback();
	_CurrentPhase->Tick();

	ChangePhase(_CurrentPhase->_NextPhase);
}

void GameSceneManager::GiveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo)
{
	targetTile->setOwnerPlayer(pInfo);
}

void GameSceneManager::KillCharacter(std::shared_ptr<Character> target)
{
	std::list<std::shared_ptr<Character>>* CharacterList = getPlayerDataByPlayerInfo(target->GetOwnerPlayer())->getCharacterList();
	target->getCurrentTile()->setCharacterOnThisTile(nullptr);
	CharacterList->remove(target);

	///# shared_ptr은 new하는 시점에 포인터를 담아와야 한다. (make_shared를 사용하는 시점)
	EventManager::getInstance()->AddHistory(HistoryEventKillCharacter::Create(target));
}

void GameSceneManager::ChangePhase(PhaseInfo nextPhase)
{
	_CurrentPhaseInfo = nextPhase;
	_CurrentPhase = _Phases[nextPhase];
}

PlayerInfo GameSceneManager::getCurrentPlayer()
{
	return _CurrentPlayer;
}

void GameSceneManager::AddChild(Node* targetNode)
{
	_Nodes->addChild(targetNode);
}

void GameSceneManager::ToggleTurn(Object* pSender)
{
	if (_CurrentPhaseInfo != PHASE_ACTION)
		return;

	ChangePhase(PHASE_PASTEUR);
}

void GameSceneManager::PushTileToList(const Rect& rect, Self_Tile* tile)
{
	TILEARRAYSET tileSet;
	tileSet.tile = tile;
	tileSet.rect = rect;

	_TileList.push_back(tileSet);
}

bool GameSceneManager::getIsVolcanoActivated()
{
	return _IsVolcanoActivated;
}

int GameSceneManager::getProgressVolcano()
{
	return _ProgressVolcano;
}

void GameSceneManager::setProgressVolcano(int progress)
{
	_ProgressVolcano = progress;
}

bool GameSceneManager::getIsMouseLocked()
{
	return _IsMouseLocked;
}

void GameSceneManager::setVolcanoActivated(bool activated)
{
	_IsVolcanoActivated = activated;
}

void GameSceneManager::setInputMode(bool mode)
{
	_IsInputAble = mode;
}

PlayerData* GameSceneManager::getPlayerDataByPlayerInfo(PlayerInfo player)
{
	return _PlayerData[player];
}

void GameSceneManager::SelectCharacter(std::shared_ptr<Character> character)
{
	if (character)
	{
		float posX = character->getPositionX();
		float posY = character->getPositionY();

		Sprite* indicator = Sprite::createWithSpriteFrameName("indicator.png");
		indicator->setName("indicator");
		indicator->setZOrder(11);
		indicator->setAnchorPoint(Vec2(0, 0));
		indicator->setPosition(posX-25, posY + 100);

		character->ShowMovableTile();

		this->_Nodes->addChild(indicator);
	}
}

void GameSceneManager::SelectBarrack(Self_Tile* tile)
{
	if (tile)
	{
		float posX = tile->getPositionX();
		float posY = tile->getPositionY();
		
		Sprite* indicator = Sprite::createWithSpriteFrameName("indicator.png");
		indicator->setName("indicator");
		indicator->setZOrder(11);
		indicator->setAnchorPoint(Vec2(0, 0));
		indicator->setPosition(posX + 60, posY + 110);

		ShowSpawnableTile(tile);

		this->_Nodes->addChild(indicator);
	}
}

void GameSceneManager::ShowSpawnableTile(Self_Tile* tile)
{
	for (int i = 0; i < 6; ++i)
	{
		DirectionKind dir = static_cast<DirectionKind>(i);
		Self_Tile* nearTile = tile->getNearTile(dir);

		if (nearTile->getTypeOfTile() == TILE_NULL || nearTile->getTypeOfTile() == TILE_LAVA || nearTile->getTypeOfTile() == TILE_VOCANO || nearTile->getTypeOfTile() == TILE_LAKE)
			continue;

		if ((nearTile->getTypeOfTile() == TILE_FOREST) && (getCurrentPlayerData()->getFood() < 2))
			continue;

		Sprite* tileMove = Sprite::createWithSpriteFrameName("tile_move.png");
		tileMove->setOpacity(96);
		tileMove->setAnchorPoint(cocos2d::Vec2(0, 0));
		
		float tilePosX = nearTile->getPositionX();
		float tilePosY = nearTile->getPositionY();

		tileMove->setPosition(tilePosX, tilePosY);
		tileMove->setName("spwanable");

		tileMove->setZOrder(nearTile->getZOrder());
		TileMap::getInstance()->addChild(tileMove);
	}
}

void GameSceneManager::Unselect()
{
	while (TileMap::getInstance()->getChildByName("moveable"))
		TileMap::getInstance()->removeChildByName("moveable");

	while (TileMap::getInstance()->getChildByName("spwanable"))
		TileMap::getInstance()->removeChildByName("spwanable");

	while (this->_Nodes->getChildByName("indicator"))
		this->_Nodes->removeChildByName("indicator");

}