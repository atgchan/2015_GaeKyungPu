#pragma once
#include "definition.h"

class DefaultLayer : public cocos2d::LayerColor
{
public:
	bool init();
	static cocos2d::Scene* scene();

	CREATE_FUNC(DefaultLayer);

private:
	LayerColor* BackLayer;
	void		Resume();
};