#ifndef Game_h__
#define Game_h__

#include "TileMap.h"
#include "PlayerData.h"
#include "Character.h"


enum PlayerInfo{
	PLAYER_RED,
	PLAYER_BLUE,
	PLAYER_ERR = -1
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
	void mouseDownDispatcher(EventMouse *event);
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

	PlayerData* getCurrentPlayerData()
	{
		return playerData[currentPlayer];
	}
	PlayerInfo getCurrentPlayer()
	{
		return currentPlayer;
	}

	void ChangePlayer();
	bool getIsVolcanoActivated(){	return _isVolcanoActivated;	}
	char getProgressVolcano(){ return _progressVolcano; }
	bool getIsMouseLocked(){ return _isMouseLocked; }

	void scheduleCallback(float delta);


private:
	char _progressVolcano = 0;
	static GameMaster *inst;
	bool _isMouseLocked = true;

	TileMap* tileMap;
	static const int numOfPlayer = 2;
	PlayerData *playerData[numOfPlayer];
	PlayerInfo currentPlayer = PLAYER_RED;

	bool isGameInitialized = false;
	Node* const nodes = Node::create();
	void addChild(Node* targetNode)
	{
		nodes->addChild(targetNode);
	}
	bool _isVolcanoActivated = false;

	void ChangeRichToLava(Self_Tile* target);

	void Run();

	void Phase_Harvest();
	void Phase_Occupy();
	void Phase_Volcano();
	void Phase_Action();
	void Phase_Pasteur();
	void giveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo);

	void killCharacter(Character* target);

};

#endif // Game_h__