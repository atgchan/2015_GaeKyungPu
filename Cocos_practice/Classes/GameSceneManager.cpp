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
		_Inst = new GameSceneManager();
	}
	return _Inst;
}

GameSceneManager::~GameSceneManager()
{
	delete _BMInstance;
	delete _Dice;

	for (int i = PHASE_HARVEST; i <= PHASE_PASTEUR; ++i)
	{
		delete _Phases[i];
	}
	_Inst = nullptr;
	_TileMap->release();
	_Nodes->release();
}

void GameSceneManager::InitializeGame()
{
	CharacterAnimation::getInstance()->Init();
	_BMInstance = new BattleManager();
	_Nodes = Node::create();
	_Dice = new DiceDice();
	_TileMap = TileMap::getInstance();

	_TileMap->create();
	this->AddChild(_TileMap);
	this->_Nodes->retain();
	this->_Nodes->setName("GameSceneManager");
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
			return iter->tile;
	}
}

bool GameSceneManager::DraftNewCharacterByClick(Self_Tile* clickedTile)
{
	if (clickedTile == nullptr)
		return false;

	if (_DraftMode == true)
	{
		bool result = true;

//		예외의 경우는 빠져 나가자
		if (!clickedTile->isMovable() || !_DraftTile->CheckNearTile(clickedTile) || clickedTile->getCharacterOnThisTile() != nullptr)
			result = false;

//		앞에서 false였다면 (타일이 spawn 불가능이라면) 여기는 안돌아가겠지
		if (result && getCurrentPlayerData()->getFood() >= clickedTile->getFoodToConsume())
		{
			DirectionKind direction = _DraftTile->getNearTileDirection(clickedTile);
			SpawnCharacterOnTile(_DraftTile, direction, clickedTile->getFoodToConsume());
			_DraftTile->getCharacterOnThisTile()->MovoToTile(clickedTile);
		}

		_DraftTile = nullptr;
		_DraftMode = false;
		return result;
	}

	else//if (_DraftMode == false)
	{
		if (_ReadyToMove)
			return false;

		if ((clickedTile->getOwnerPlayer() == _CurrentPlayer) && clickedTile->isSpawnable())
		{
			if ((clickedTile->getCharacterOnThisTile() != nullptr) && (clickedTile->getCharacterOnThisTile()->GetOwnerPlayer() == _CurrentPlayer))
				return false;

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

	if (_ReadyToMove == true)
	{
		bool check = true;

		if (!clickedTile->isMovable())
			check = false;
		if (!(_CharacterToMove->getCurrentTile()->getNearTileDirection(clickedTile) == _CharacterToMove->getCurrentDirection()))
			check = false;
		
		if (check && getCurrentPlayerData()->getFood() >= clickedTile->getFoodToConsume())
		{
			if (clickedTile->getCharacterOnThisTile() == nullptr)
			{
				_CharacterToMove->MovoToTile(clickedTile);
				getCurrentPlayerData()->AddFood(clickedTile->getFoodToConsume() * -1);
			}

			if (clickedTile->getCharacterOnThisTile()->GetOwnerPlayer() != _CurrentPlayer)
			{
				_BMInstance->BattleBetween(_CharacterToMove, clickedTile->getCharacterOnThisTile());
				getCurrentPlayerData()->AddFood(clickedTile->getFoodToConsume() * -1);
			}
		}

		_CharacterToMove = nullptr;
		_ReadyToMove = false;
		return;
	}

	else // if(_ReadyToMove == false)
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
	Character* unit = Character::create(getCurrentPlayer(), spriteNum);
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
		getCurrentPlayerData()->AddFood(100);
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
	case MOUSE_BUTTON_MIDDLE:
		if (clickedTile != nullptr && clickedTile->getCharacterOnThisTile() != nullptr && clickedTile->getCharacterOnThisTile()->GetOwnerPlayer() == _CurrentPlayer)
		{
			Character* target = clickedTile->getCharacterOnThisTile();
			if (event->getMouseButton() == MOUSE_BUTTON_RIGHT)
				target->RotateToDirection(ROTATE_RIGHT);
			if( event->getMouseButton() == MOUSE_BUTTON_MIDDLE)
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

	TrimZorder();
}

void GameSceneManager::GiveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo)
{
	targetTile->setOwnerPlayer(pInfo);
}

void GameSceneManager::KillCharacter(Character* target)
{
	target->getCurrentTile()->setCharacterOnThisTile(nullptr);
	getPlayerDataByPlayerInfo(target->GetOwnerPlayer())->RemoveCharacter(target);

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
	if (_IsInputAble == false)
		return;
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

void GameSceneManager::SelectCharacter(Character* character)
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
	for (int i = 0; i < MAX_DIRECTION; ++i)
	{
		DirectionKind dir = static_cast<DirectionKind>(i);
		Self_Tile* nearTile = tile->getNearTile(dir);

		if (!nearTile->isMovable())
			continue;

		if (getCurrentPlayerData()->getFood() < nearTile->getFoodToConsume())
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

void GameSceneManager::TrimZorder()
{
	for (auto iter : TileMap::getInstance()->getChildren())
		if (iter->getName() == "character")
			iter->setZOrder(-100 * iter->getPositionY() + 10300);
}
