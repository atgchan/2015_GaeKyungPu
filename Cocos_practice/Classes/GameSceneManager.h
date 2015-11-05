#pragma once

#include "definition.h"
#include "PlayerData.h"

#include "TileMap.h"
class Phase;

struct TILEARRAYSET
{
	Self_Tile* tile = nullptr;
	Rect rect = Rect();
};

//�̱������� ����
class GameSceneManager
{
public:
	GameSceneManager();
	~GameSceneManager();

	/*
	@brief		������ �ʱ� ������ �����մϴ�. ���� ��� : �ʱ� �� �׸���
	@warning	�� �Լ��� ���� �������� ���� GameMaster�� ����� �� �����ϴ�.
	*/
	void InitializeGame();
	/*
	@brief		mouse��ư �̺�Ʈ �����ʿ� �ɾ�� �� �ִ� 2�� �������Դϴ�.
	*/
	void mouseDownDispatcher(cocos2d::EventMouse *event);
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
	Node* getNodes(){ return nodes; }

	PlayerData* getCurrentPlayerData();
	PlayerInfo getCurrentPlayer();

	void	ChangePlayer();
	bool	getIsVolcanoActivated(){	return isVolcanoActivated;	}
	int		getProgressVolcano(){ return progressVolcano; }
	void	setProgressVolcano(int progress){ progressVolcano = progress; }
	bool	getIsMouseLocked(){ return isMouseLocked; }

	void scheduleCallback(float delta);

	/*
	@brief		GameScene���κ��� CALLBACK �޾� �� ����. (���Ŀ� UI Ŭ�������� CALLBACK �ϵ���)
	*/
	void toggleTurn(Object* pSender);

	/*
		@brief	Ÿ���� �����Ϳ� Ÿ���� Ŭ�� ������ ��ġ�� ��Ÿ���� �簢���� �޾Ƽ� �迭�� �����Ѵ�.
	*/
	void pushTileToList(Rect rect, Self_Tile* tile);

	/*
		@brief	Ÿ�� ����Ʈ���� �ش� ��ǥ���� ��ġ�� ���ԵǴ� Ÿ���� �ִ��� �˻��ؼ� ������ Ÿ�� �����͸� ��ȯ�Ѵ�.
	*/
	Self_Tile* getExistingTileWithMousePoint(Vec2 vec);

	void addChild(Node* targetNode);
	void ChangeRichToLava(Self_Tile* target);
	void GiveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo);
	void killCharacter(Character* target);
	void setVolcanoActivated(bool activated){ isVolcanoActivated = activated; };

	Self_Tile* getTileFromMouseEvent(const cocos2d::EventMouse *event);

private:
	static GameSceneManager *inst;
	TileMap* tileMap;
	PlayerData* playerData[NUM_OF_PLAYER];
	Node* nodes;

	PhaseInfo currentPhaseInfo = PHASE_HARVEST;
	PlayerInfo currentPlayer = PLAYER_RED;
	Phase* currentPhase = nullptr;

	bool	draftMode = false;

	void	SpawnCharacterOnTile(Self_Tile*);

	int progressVolcano = 0;

	/*Ÿ�ϸ� ������ ������ �迭�� �����..*/
	std::vector<TILEARRAYSET> TileList;

	bool isMouseLocked = true;
	bool isGameInitialized = false;
	bool isVolcanoActivated = false;
	bool isTurnRunning = true;
	Phase* phases[7];

	void ChangePhase(PhaseInfo);
};