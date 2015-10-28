#ifndef Game_h__
#define Game_h__

#include "PlayerData.h"
#include "TileMap.h"


enum PlayerInfo{
	PLAYER_RED,
	PLAYER_BLUE,
	PLAYER_ERR = -1
};

//½Ì±ÛÅæÀ¸·Î ±¸Çö
class GameMaster
{
public:
	GameMaster();
	~GameMaster();

	void InitializeGame();

	void mouseDownDispatcher(EventMouse *event);

	void addChild(Node* targetNode)
	{
		nodes->addChild(targetNode);
	}
	static GameMaster* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new GameMaster();
		}
		return inst;
	}

	Node* getNodes(){ return nodes; }
	PlayerData* getCurrentPlayer();

private:
	TileMap* tileMap;
	static const int numOfPlayer = 2;
	PlayerData playerData[numOfPlayer];
	PlayerInfo currentPlayer = PLAYER_RED;
	static GameMaster *inst;
	bool isGameInitialized = false;
	Node* const nodes = Node::create();
};

#endif // Game_h__