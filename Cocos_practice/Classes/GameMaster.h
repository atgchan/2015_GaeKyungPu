#pragma once
#ifndef Game_h__
#define Game_h__

#include "definition.h"
#include "PlayerData.h"

#include "TileMap.h"

struct TILEARRAYSET ///# ����ü�� Ŭ������ ��������� �ݵ�� �⺻������ �ʱ�ȭ.
{
	Self_Tile* tile = nullptr;
	Rect rect;
};

//�̱������� ����
class GameMaster
{
public:
	GameMaster();
	~GameMaster();

	/**
	@date		2015/10/29
	@author		�뼮�� ///# �ڵ� �κи��� ������ �̸� �� ��.. �̰��� ���� ������Ʈ���� ��� �ڵ尡 ���� �ۼ��ߴ����� �ǹ� ����. �ڵ� �κп� ���� ���ʽ��� �������� �ȵ�.
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

	/**
		Author: Wonseok
		Description: Ÿ���� �����Ϳ� Ÿ���� Ŭ�� ������ ��ġ�� ��Ÿ���� �簢���� �޾Ƽ� �迭�� �����Ѵ�.
	*/
	void pushTileToList(Rect rect, Self_Tile* tile);

	/**
		Autor: Wonseok
		Description: Ÿ�� ����Ʈ���� �ش� ��ǥ���� ��ġ�� ���ԵǴ� Ÿ���� �ִ��� �˻��ؼ� ������ Ÿ�� �����͸� ��ȯ�Ѵ�.
	*/
	Self_Tile* getExistingTileWithMousePoint(Vec2 vec);

private:
	enum { NUM_OF_PLAYER = 2 }; ///# �ڵ� ������, �׸��� �̷� ���� ������ ����ȰŴ� config.h������ ���� ������ ����.
	static GameMaster *inst; ///# ��� ���� �ڵ� ������
	TileMap* tileMap;
	PlayerData* playerData[NUM_OF_PLAYER];
	Node* const nodes = Node::create(); ///# �Լ� ȣ���ؼ� �ʱ�ȭ�ϴ� ������ ������ �Ǵ� init���� ����

	PhaseInfo currentPhase = PHASE_HARVEST;
	PlayerInfo currentPlayer = PLAYER_RED;
	char _progressVolcano = 0;

	/*Ÿ�ϸ� ������ ������ �迭�� �����..*/
	std::vector<TILEARRAYSET> TileList;

	bool _isMouseLocked = true; ///# �ڵ� ������. _�� �ǹ̴�..
	bool isGameInitialized = false;
	bool _isVolcanoActivated = false;
	bool isTurnRunning = true;

private:
	void addChild(Node* targetNode);
	void ChangeRichToLava(Self_Tile* target);
	void giveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo);
	void killCharacter(Character* target);

	void Phase_Harvest(); ///# ��� �Լ��� �ڵ� ������ (�빮�� ����? �ҹ��� ����?)
	void Phase_Occupy();
	void Phase_Volcano();
	void Phase_Action();
	void Phase_Pasteur();
};

#endif // Game_h__