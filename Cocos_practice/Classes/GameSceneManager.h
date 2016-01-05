#pragma once

#include "definition.h"
#include "PlayerData.h"

#include "TileMap.h"

class Phase;
class BattleManager;
class DiceDice;

class GameSceneManager
{
public:
	static GameSceneManager* getInstance();

	void		InitializeGame();
	void		EndGame();
	
	void		MouseDownDispatcher(cocos2d::EventMouse *event);
	void		KeyReleasedDispatcher(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	
	Node*		getNodes(){ return _Nodes;}

	PlayerData*	getCurrentPlayerData();
	PlayerInfo	getCurrentPlayer();

	void		ScheduleCallback(float delta);

	void		ChangePlayer();
	bool		getIsVolcanoActivated();
	int			getProgressVolcano();
	void		setProgressVolcano(int progress);
	bool		getIsMouseLocked();

	void		ToggleTurn();
	void		PushTileToList(Self_Tile* tile);

	void		AddChild(Node* targetNode);
	void		ChangeRichToLava(Self_Tile* target);
	void		GiveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo);
	void		KillCharacter(Character* target, bool showHitEffect = false);
	void		setVolcanoActivated(bool activated);

	Self_Tile*	getTileFromMouseEvent(const cocos2d::EventMouse *event);

	PlayerData*	getPlayerDataByPlayerInfo(PlayerInfo player);
	bool		DraftNewCharacterByClick(Self_Tile* clickedTile);
	void		MoveCharacterByClick(Self_Tile* clickedTile);

	bool		_ReadyToMove = false;
	Character*	_CharacterToMove = nullptr;
	void		setInputMode(bool mode);

	bool		getIsInputAble();
	bool		_DebugMode = false;
	void		ResetLastCharacter();
	void		ResetCharacterMovable();

	cocos2d::Node*	GetChildByName(const std::string& name)
	{ return _Nodes->getChildByName(name); };

	void	RemoveChildByName(const std::string& name)
	{ _Nodes->removeChildByName(name); };

	~GameSceneManager();

private:
	BattleManager*	_BMInstance;
	GameSceneManager(){};

	Character* _SelectedCharacter;

	static GameSceneManager *_Inst;
	TileMap*	_TileMap;
	PlayerData*	_PlayerData[NUM_OF_PLAYER];
	Node*		_Nodes;

	PhaseInfo	_CurrentPhaseInfo = PHASE_HARVEST;
	PlayerInfo	_CurrentPlayer = PLAYER_RED;
	Phase*		_CurrentPhase = nullptr;

	bool		_DraftMode = false;
	void		SpawnCharacterOnTile(Self_Tile* tile, DirectionKind spriteNum, int spendFood = 1);
	int			_ProgressVolcano = -1;

	/*타일만 별도로 저장할 배열을 만든다..*/
	std::vector<Self_Tile*> _TileList;

	bool		_IsMouseLocked = true;
	bool		_IsGameInitialized = false;
	bool		_IsVolcanoActivated = false;
	bool		_IsTurnRunning = true;
	bool		_IsDebugingActivated = false;
	bool		_IsInputAble = true;

	Phase*		_Phases[MAX_PHASE];
	Self_Tile*	_DraftTile;
	DiceDice*	_Dice;

	void		ChangePhase(PhaseInfo);
	void		ShowSpawnableTile(Self_Tile* tile);
	void		Unselect();

	void		SelectCharacter(Character* character);
	void		SelectBarrack(Self_Tile* tile);
	void		TrimZorderAndRefreshAP();

	void		SetRotateButton(Character* character);
	void		ResetRotateResource();
	void		RotateToDirection(Character* character, RotateDirection rotateDirection);
	void		RemoveCursor();
	
};