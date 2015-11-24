#pragma once
#include "definition.h"
#include "PlayerData.h"

class ResultLayer : public cocos2d::LayerColor
{
public:
	bool init();
	static cocos2d::Scene* scene();
	const void SetValue(PlayerData* playerData1, PlayerData* playerData2) const; ///# const void´Â ¹¹Áö?

	CREATE_FUNC(ResultLayer);

private:
	LayerColor* BackLayer;
	LayerColor* PopUpLayer;
};