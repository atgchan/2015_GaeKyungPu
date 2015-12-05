#pragma once
#include "definition.h"
#include "PlayerData.h"

class ResultLayer : public cocos2d::LayerColor
{
public:
	bool init();
	static cocos2d::Scene* scene();
	void SetValue(PlayerData* playerData1, PlayerData* playerData2);

	CREATE_FUNC(ResultLayer);

private:
	LayerColor* BackLayer;
	void		ReturnToMenu();
};