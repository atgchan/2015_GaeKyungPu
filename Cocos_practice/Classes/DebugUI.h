#pragma once
#include "definition.h"

class DebugUI : public cocos2d::LayerColor
{
public:
	bool init();
	static cocos2d::Scene* scene();

	CREATE_FUNC(DebugUI);

private:
	LayerColor* backLayer;
	LayerColor* popUpLayer;
};