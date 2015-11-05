#pragma once

#include "definition.h"
#include "PlayerData.h"

#include "TileMap.h"
class Phase;

struct TILEARRAYSET ///# 구조체나 클래스의 멤버변수는 반드시 기본값으로 초기화.
{
	Self_Tile* tile = nullptr;
	Rect rect;
};

//싱글톤으로 구현
class GameSceneManager
{
public:
	GameSceneManager();
	~GameSceneManager();

	/*
	@brief		게임의 초기 셋팅을 진행합니다. 현재 기능 : 초기 맵 그리기
	@warning	이 함수를 통해 셋팅하지 않은 GameMaster는 사용할 수 없습니다.
	*/
	void InitializeGame();
	/*
	@brief		mouse버튼 이벤트 리스너에 걸어둘 수 있는 2차 디스패쳐입니다.
	*/
	void mouseDownDispatcher(cocos2d::EventMouse *event);
	/*
	@brief		GameMaster에게서 요청할 어떠한 기능이라도 getInstance()를 통해 pointer를 얻어 요청합니다.
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
	@brief		GameMaster가 포함하고 있는 모든 node를 하나의 트리로 묶어 포인터로 반환합니다.
	*/
	Node* getNodes(){ return nodes; }

	PlayerData* getCurrentPlayerData();
	PlayerInfo getCurrentPlayer();

	void	ChangePlayer();
	bool	getIsVolcanoActivated(){	return isVolcanoActivated;	}
	int		getProgressVolcano(){ return progressVolcano; }
	void	setProgressVolcano(int progress){ progressVolcano = progress; }
	bool	getIsMouseLocked(){ return _isMouseLocked; }

	void scheduleCallback(float delta);

	/*
	@brief		GameScene으로부터 CALLBACK 받아 턴 변경. (추후에 UI 클래스에서 CALLBACK 하도록)
	*/
	void toggleTurn(Object* pSender);

	/*
		@brief	타일의 포인터와 타일의 클릭 가능한 위치를 나타내는 사각형을 받아서 배열로 저장한다.
	*/
	void pushTileToList(Rect rect, Self_Tile* tile);

	/*
		@brief	타일 리스트에서 해당 좌표값의 위치에 포함되는 타일이 있는지 검사해서 있으면 타일 포인터를 반환한다.
	*/
	Self_Tile* getExistingTileWithMousePoint(Vec2 vec);

	void addChild(Node* targetNode);
	void ChangeRichToLava(Self_Tile* target);
	void GiveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo);
	void killCharacter(Character* target);
	void setVolcanoActivated(bool activated){ isVolcanoActivated = activated; };

private:
	static GameSceneManager *inst; ///# 멤버 변수 코딩 컨벤션
	TileMap* tileMap;
	PlayerData* playerData[NUM_OF_PLAYER];
	Node* const nodes = Node::create(); ///# 함수 호출해서 초기화하는 종류는 생성자 또는 init에서 직접

	PhaseInfo currentPhaseInfo = PHASE_HARVEST;
	PlayerInfo currentPlayer = PLAYER_RED;
	Phase* currentPhase = nullptr;

	int progressVolcano = 0;

	/*타일만 별도로 저장할 배열을 만든다..*/
	std::vector<TILEARRAYSET> TileList;

	bool _isMouseLocked = true; ///# 코딩 컨벤션. _의 의미는..
	bool isGameInitialized = false;
	bool isVolcanoActivated = false;
	bool isTurnRunning = true;
	Phase* phases[7];

	void ChangePhase(PhaseInfo);
};