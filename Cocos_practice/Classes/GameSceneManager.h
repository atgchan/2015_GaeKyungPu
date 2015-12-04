#pragma once

#include "definition.h"
#include "PlayerData.h"

#include "TileMap.h"

class Phase;
class BattleManager;
class DiceDice;

struct TILEARRAYSET
{
	Self_Tile* tile = nullptr;
	Rect rect = Rect();
};
//�̱������� ����
class GameSceneManager
{
public:

	/*
	@brief		������ �ʱ� ������ �����մϴ�. ���� ��� : �ʱ� �� �׸���
	@warning	�� �Լ��� ���� �������� ���� GameMaster�� ����� �� �����ϴ�.
	*/
	void		InitializeGame();
	void		EndGame();

	/*
	@brief		mouse��ư �̺�Ʈ �����ʿ� �ɾ�� �� �ִ� 2�� �������Դϴ�.
	*/
	void		MouseDownDispatcher(cocos2d::EventMouse *event);

	/*
	@brief		mouse��ư �̺�Ʈ �����ʿ� �ɾ�� �� �ִ� 2�� �������Դϴ�.
	*/
	void		KeyReleasedDispatcher(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	/*
	@brief		GameMaster���Լ� ��û�� ��� ����̶� getInstance()�� ���� pointer�� ��� ��û�մϴ�.
	*/
	static GameSceneManager* getInstance();
	/*
	@brief		GameMaster�� �����ϰ� �ִ� ��� node�� �ϳ��� Ʈ���� ���� �����ͷ� ��ȯ�մϴ�.
	*/
	Node*		getNodes(){ return _Nodes;}

	PlayerData*	getCurrentPlayerData();
	PlayerInfo	getCurrentPlayer();

	void		ChangePlayer();
	bool		getIsVolcanoActivated();
	int			getProgressVolcano();
	void		setProgressVolcano(int progress);
	bool		getIsMouseLocked();

	void		ScheduleCallback(float delta);

	/*
	@brief		GameScene���κ��� CALLBACK �޾� �� ����. (���Ŀ� UI Ŭ�������� CALLBACK �ϵ���)
	*/
	void		ToggleTurn(Object* pSender);

	/*
		@brief	Ÿ���� �����Ϳ� Ÿ���� Ŭ�� ������ ��ġ�� ��Ÿ���� �簢���� �޾Ƽ� �迭�� �����Ѵ�.
	*/
	void PushTileToList(const Rect& rect, Self_Tile* tile);

	/*
		@brief	Ÿ�� ����Ʈ���� �ش� ��ǥ���� ��ġ�� ���ԵǴ� Ÿ���� �ִ��� �˻��ؼ� ������ Ÿ�� �����͸� ��ȯ�Ѵ�.
	*/
	Self_Tile* getExistingTileWithMousePoint(Vec2 vec);

	void		AddChild(Node* targetNode);
	void		ChangeRichToLava(Self_Tile* target);
	void		GiveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo);
	void		KillCharacter(Character* target);
	void		setVolcanoActivated(bool activated);

	Self_Tile*	getTileFromMouseEvent(const cocos2d::EventMouse *event);

	PlayerData*	getPlayerDataByPlayerInfo(PlayerInfo player);
	bool		DraftNewCharacterByClick(Self_Tile* clickedTile);
	void		MoveCharacterByClick(Self_Tile* clickedTile);

	bool		_ReadyToMove = false;
	Character*	_CharacterToMove = nullptr;
	void		setInputMode(bool mode);

	bool		getIsInputAble(){ return _IsInputAble; }

private:
	BattleManager*	_BMInstance;
	GameSceneManager();
	~GameSceneManager();

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

	/*Ÿ�ϸ� ������ ������ �迭�� �����..*/
	std::vector<TILEARRAYSET> _TileList;

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
};