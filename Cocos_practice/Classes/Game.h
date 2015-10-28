#ifndef Game_h__
#define Game_h__

#include "PlayerData.h"

enum PlayerInfo{
	PLAYER_RED,
	PLAYER_BLUE,
	PLAYER_ERR = -1
};

//�̱������� ����
class GameMaster
{
public:
	void clickEventDispatcher(cocos2d::EventMouse event);
	PlayerData* getCurrentPlayer();

private:
	PlayerData playerData[2];
	PlayerInfo currentPlayer;
};
#endif // Game_h__