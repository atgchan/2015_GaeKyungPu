#pragma once
#include "definition.h"
#include "PlayerData.h"

class UILayer : public cocos2d::LayerColor
{
public:
	bool init();
	static cocos2d::Scene* scene();
	const void SetFoodValue(PlayerData* playerData1, PlayerData* playerData2) const;

	CREATE_FUNC(UILayer);

private:
	LayerColor* BackLayer;
	LayerColor* PopUpLayer;
	void SetUIBar();

};