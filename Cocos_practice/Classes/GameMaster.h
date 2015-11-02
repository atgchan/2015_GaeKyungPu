#pragma once
#ifndef Game_h__
#define Game_h__

#include "definition.h"
#include "PlayerData.h"

#include "TileMap.h"

struct TILEARRAYSET
{
	Self_Tile* tile;
	Rect rect;
};

//싱글톤으로 구현
class GameMaster
{
public:
	GameMaster();
	~GameMaster();

	/**
	@date		2015/10/29
	@author		노석민
	@brief		게임의 초기 셋팅을 진행합니다. 현재 기능 : 초기 맵 그리기
	@warning	이 함수를 통해 셋팅하지 않은 GameMaster는 사용할 수 없습니다.
	*/
	void InitializeGame();
	/**
	@date		2015/10/29
	@author		노석민
	@brief		mouse버튼 이벤트 리스너에 걸어둘 수 있는 2차 디스패쳐입니다.
	*/
	void mouseDownDispatcher(cocos2d::EventMouse *event);
	/**
	@date		2015/10/29
	@author		노석민
	@brief		GameMaster에게서 요청할 어떠한 기능이라도 getInstance()를 통해 pointer를 얻어 요청합니다.
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
	@author		노석민
	@brief		GameMaster가 포함하고 있는 모든 node를 하나의 트리로 묶어 포인터로 반환합니다.
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
		Description: 타일의 포인터와 타일의 클릭 가능한 위치를 나타내는 사각형을 받아서 배열로 저장한다.
	*/
	void pushTileToList(Rect rect, Self_Tile* tile);

	/**
		Autor: Wonseok
		Description: 타일 리스트에서 해당 좌표값의 위치에 포함되는 타일이 있는지 검사해서 있으면 타일 포인터를 반환한다.
	*/
	Self_Tile* getExistingTileWithMousePoint(Vec2 vec);

private:
	enum { NUM_OF_PLAYER = 2 };
	static GameMaster *inst;
	TileMap* tileMap;
	PlayerData* playerData[NUM_OF_PLAYER];
	Node* const nodes = Node::create();

	PhaseInfo currentPhase = PHASE_HARVEST;
	PlayerInfo currentPlayer = PLAYER_RED;
	char _progressVolcano = 0;

	/*타일만 별도로 저장할 배열을 만든다..*/
	std::vector<TILEARRAYSET> TileList;

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