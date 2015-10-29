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