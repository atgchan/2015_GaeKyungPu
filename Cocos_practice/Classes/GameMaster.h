#pragma once
#ifndef Game_h__
#define Game_h__

#include "definition.h"
#include "PlayerData.h"

#include "TileMap.h"

struct TILEARRAYSET ///# 구조체나 클래스의 멤버변수는 반드시 기본값으로 초기화.
{
	Self_Tile* tile = nullptr;
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
	@author		노석민 ///# 코드 부분마다 저작자 이름 뺄 것.. 이것은 공통 프로젝트여서 어느 코드가 누가 작성했는지는 의미 없음. 코드 부분에 대항 오너십을 가져서도 안됨.
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
	enum { NUM_OF_PLAYER = 2 }; ///# 코딩 컨벤션, 그리고 이런 전역 설정에 관계된거는 config.h같은거 만들어서 빼놔도 좋다.
	static GameMaster *inst; ///# 멤버 변수 코딩 컨벤션
	TileMap* tileMap;
	PlayerData* playerData[NUM_OF_PLAYER];
	Node* const nodes = Node::create(); ///# 함수 호출해서 초기화하는 종류는 생성자 또는 init에서 직접

	PhaseInfo currentPhase = PHASE_HARVEST;
	PlayerInfo currentPlayer = PLAYER_RED;
	char _progressVolcano = 0;

	/*타일만 별도로 저장할 배열을 만든다..*/
	std::vector<TILEARRAYSET> TileList;

	bool _isMouseLocked = true; ///# 코딩 컨벤션. _의 의미는..
	bool isGameInitialized = false;
	bool _isVolcanoActivated = false;
	bool isTurnRunning = true;

private:
	void addChild(Node* targetNode);
	void ChangeRichToLava(Self_Tile* target);
	void giveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo);
	void killCharacter(Character* target);

	void Phase_Harvest(); ///# 멤버 함수들 코딩 컨벤션 (대문자 시작? 소문자 시작?)
	void Phase_Occupy();
	void Phase_Volcano();
	void Phase_Action();
	void Phase_Pasteur();
};

#endif // Game_h__