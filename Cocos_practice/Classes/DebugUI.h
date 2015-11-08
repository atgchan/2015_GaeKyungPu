#pragma once
#include "definition.h"
#include "PlayerData.h"

class DebugUI : public cocos2d::LayerColor
{
public:
	bool init();
	static cocos2d::Scene* scene();
	const void SetValue(PlayerData* playerData1, PlayerData* playerData2) const;

	CREATE_FUNC(DebugUI);

private:
	LayerColor* backLayer;
	LayerColor* popUpLayer;
};