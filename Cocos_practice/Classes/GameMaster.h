#ifndef Game_h__
#define Game_h__

#include "PlayerData.h"
#include "TileMap.h"


enum PlayerInfo{
	PLAYER_RED,
	PLAYER_BLUE,
	PLAYER_ERR = -1
};

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
	void mouseDownDispatcher(EventMouse *event);
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

	PlayerData* getCurrentPlayerData()
	{
		return playerData[currentPlayer];
	}
	PlayerInfo getCurrentPlayer()
	{
		return currentPlayer;
	}

	void ChangePlayer();

private:
	static GameMaster *inst;

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

	void Run();

	void Phase_Harvest();
	void Phase_Occupy();
	void Phase_Volcano();
	void Phase_Action();
	void Phase_Pasteur();
	void giveTileToPlayer(Self_Tile* targetTile, PlayerInfo pInfo);

};

#endif // Game_h__