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
	/*
	@brief		mouse��ư �̺�Ʈ �����ʿ� �ɾ�� �� �ִ� 2�� �������Դϴ�.
	*/
	void		mouseDownDispatcher(cocos2d::EventMouse *event);

	/*
	@brief		mouse��ư �̺�Ʈ �����ʿ� �ɾ�� �� �ִ� 2�� �������Դϴ�.
	*/
	void		KeyReleasedDispatcher(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	/*
	@brief		GameMaster���Լ� ��û�� ��� ����̶� getInstance()�� ���� pointer�� ��� ��û�մϴ�.
	*/
	static GameSceneManager* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new GameSceneManager();
		}
		return inst;
	}
	/*
	@brief		GameMaster�� �����ϰ� �ִ� ��� node�� �ϳ��� Ʈ���� ���� �����ͷ� ��ȯ�մϴ�.
	*/
	Node*		getNodes(){ return _Nodes;}

	PlayerData*	getCurrentPlayerData();
	PlayerInfo	getCurrentPlayer();

	void		ChangePlayer();
	bool		getIsVolcanoActivated(){	return _IsVolcanoActivated;	}
	int			getProgressVolcano(){ return progressVolcano; }
	void		setProgressVolcano(int progress){ progressVolcano = progress; }
	bool		getIsMouseLocked(){ return _IsMouseLocked; }

	void		scheduleCallback(float delta);

	/*
	@brief		GameScene���κ��� CALLBACK �޾� �� ����. (���Ŀ� UI Ŭ�������� CALLBACK �ϵ���)
	*/
	void		toggleTurn(Object* pSender);

	/*
		@brief	Ÿ���� �����Ϳ� Ÿ���� Ŭ�� ������ ��ġ�� ��Ÿ���� �簢���� �޾Ƽ� �迭�� �����Ѵ�.
	*/
	void		pushTileToList(Rect rect, Self_Tile* tile);

	/*
		@brief	Ÿ�� ����Ʈ���� �ش� ��ǥ���� ��ġ�� ���ԵǴ� Ÿ���� �ִ��� �˻��ؼ� ������ Ÿ�� �����͸� ��ȯ�Ѵ�.
	*/
	Self_Tile*	getExistingTileWithMousePoint(Vec2 vec);

	void		addChild(Node* targetNode);
	void		ChangeRichToLava(Self_Tile* target);
	void		GiveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo);
	void		killCharacter(Character* target);
	void		setVolcanoActivated(bool activated){ _IsVolcanoActivated = activated; };

	Self_Tile*	getTileFromMouseEvent(const cocos2d::EventMouse *event);

	PlayerData*	getPlayerDataByPlayerInfo(PlayerInfo player);
	bool		DraftNewCharacterByClick(Self_Tile* clickedTile);
	void		MoveCharacterByClick(Self_Tile* clickedTile);

	bool		readyToMove = false;
	Character*	characterToMove = nullptr;
private:
	BattleManager*	_BMInstance;
	GameSceneManager();
	~GameSceneManager();

	static GameSceneManager *inst;
	TileMap*	_TileMap;
	PlayerData*	_PlayerData[NUM_OF_PLAYER];
	Node*		_Nodes;

	PhaseInfo	currentPhaseInfo = PHASE_HARVEST;
	PlayerInfo	currentPlayer = PLAYER_RED;
	Phase*		currentPhase = nullptr;

	///# ��� ���� �ʱ�ȭ�� ���ϵǰ� ����� ���ÿ� �ϵ簡 �����ڿ��� �ϵ簡.. �ڵ� ���������� ���� ��.

	bool		draftMode = false;

	void		SpawnCharacterOnTile(Self_Tile* tile, int spriteNum, int spendFood=1);

	int			progressVolcano = 0;

	/*Ÿ�ϸ� ������ ������ �迭�� �����..*/
	std::vector<TILEARRAYSET> TileList;

	bool		_IsMouseLocked = true;
	bool		_IsGameInitialized = false;
	bool		_IsVolcanoActivated = false;
	bool		_IsTurnRunning = true;
	bool		_IsDebugingActivated = false;

	Phase*		phases[7];
	Self_Tile*	draftTile;

	DiceDice* dice;

	void		ChangePhase(PhaseInfo);

};