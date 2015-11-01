#pragma once
#ifndef Game_h__
#define Game_h__

#include "definition.h"
#include "PlayerData.h"

#include "TileMap.h"

//�̱������� ����
class GameMaster
{
public:
	GameMaster();
	~GameMaster();

	/**
	@date		2015/10/29
	@author		�뼮��
	@brief		������ �ʱ� ������ �����մϴ�. ���� ��� : �ʱ� �� �׸���
	@warning	�� �Լ��� ���� �������� ���� GameMaster�� ����� �� �����ϴ�.
	*/
	void InitializeGame();
	/**
	@date		2015/10/29
	@author		�뼮��
	@brief		mouse��ư �̺�Ʈ �����ʿ� �ɾ�� �� �ִ� 2�� �������Դϴ�.
	*/
	void mouseDownDispatcher(cocos2d::EventMouse *event);
	/**
	@date		2015/10/29
	@author		�뼮��
	@brief		GameMaster���Լ� ��û�� ��� ����̶� getInstance()�� ���� pointer�� ��� ��û�մϴ�.
	*/
	static GameMaster* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new GameMaster();
		}
		return inst;
	}
	/**
	@date		2015/10/29
	@author		�뼮��
	@brief		GameMaster�� �����ϰ� �ִ� ��� node�� �ϳ��� Ʈ���� ���� �����ͷ� ��ȯ�մϴ�.
	*/
	Node* getNodes(){ return nodes; }

	PlayerData* getCurrentPlayerData();
	PlayerInfo getCurrentPlayer();

	void ChangePlayer();
	bool getIsVolcanoActivated(){	return _isVolcanoActivated;	}
	char getProgressVolcano(){ return _progressVolcano; }
	bool getIsMouseLocked(){ return _isMouseLocked; }

	void scheduleCallback(float delta);
	void toggleTurn(Object* pSender);

private:
	enum { NUM_OF_PLAYER = 2 };
	static GameMaster *inst;
	TileMap* tileMap;
	PlayerData* playerData[NUM_OF_PLAYER];
	Node* const nodes = Node::create();

	PhaseInfo currentPhase = PHASE_HARVEST;
	PlayerInfo currentPlayer = PLAYER_RED;
	char _progressVolcano = 0;

	bool _isMouseLocked = true;
	bool isGameInitialized = false;
	bool _isVolcanoActivated = false;
	bool isTurnRunning = true;

	void addChild(Node* targetNode);
	void ChangeRichToLava(Self_Tile* target);
	void giveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo);
	void killCharacter(Character* target);

	void Phase_Harvest();
	void Phase_Occupy();
	void Phase_Volcano();
	void Phase_Action();
	void Phase_Pasteur();
};

#endif // Game_h__