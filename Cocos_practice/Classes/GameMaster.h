#ifndef Game_h__
#define Game_h__

#include "PlayerData.h"

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


	void clickEventDispatcher(cocos2d::EventMouse event);
	PlayerData* getCurrentPlayer();
	static GameMaster* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new GameMaster();
		}
		return inst;
	}


	static bool initialized;

private:
	PlayerData playerData[2];
	PlayerInfo currentPlayer;
	static GameMaster *inst;
};

#endif // Game_h__