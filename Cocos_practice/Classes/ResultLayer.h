#pragma once
#include "definition.h"
#include "PlayerData.h"

class ResultLayer : public cocos2d::LayerColor
{
public:
	bool	init();
	static	cocos2d::Scene* scene();
	
	CREATE_FUNC(ResultLayer);

private:
	LayerColor* BackLayer;
	void		ReturnToMenu();

	void		ShowRecentGame(int numOfGet);
	void		ShowTopPlayer(int numOfGet);
	void		ShowLeastTurn(int numOfGet);
};