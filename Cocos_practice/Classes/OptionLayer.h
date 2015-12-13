#pragma once
#include "definition.h"
#include "PlayerData.h"

class OptionLayer : public cocos2d::LayerColor
{
public:
	bool init();
	static cocos2d::Scene* scene();

	CREATE_FUNC(OptionLayer);

private:
	LayerColor* BackLayer;
	void		ReturnToMenu();
	void		Mute();
	void		Resume();
};