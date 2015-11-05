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
	bool	getIsMouseLocked(){ return isMouseLocked; }

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

	/*타일만 별도로 저장할 배열을 만든다..*/
	std::vector<TILEARRAYSET> TileList;

	bool isMouseLocked = true;
	bool isGameInitialized = false;
	bool isVolcanoActivated = false;
	bool isTurnRunning = true;
	Phase* phases[7];

	void ChangePhase(PhaseInfo);
};